import os
from datetime import datetime
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

#
from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# allows lookup function to be called from html
app.jinja_env.globals.update(lookup=lookup)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # get user id
    userId = session["user_id"]

    # get distinct stocks with grouped shares and costs
    portfolio = db.execute(
        "SELECT stock as name, SUM(shares) as shares, share_price FROM transact WHERE user_id = ? GROUP BY stock HAVING SUM(shares) > 0;",
        userId,
    )
    # print("________________________________________________________________")
    # print(portfolio)

    # get users cash balance
    cash = db.execute("SELECT cash FROM users WHERE id = ?;", userId)
    cash = cash[0]["cash"]

    # get users total portfolio value
    total = cash
    for item in portfolio:
        total += item["shares"] * lookup(item["name"])["price"]

    # return portfolio of stocks
    return render_template("index.html", portfolio=portfolio, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # user submitted buy request
    if request.method == "POST":
        # get submitted symbol and validate input
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must enter symbol", 400)

        # get submitted price and validate shares is an int > 0
        shares = request.form.get("shares")
        try:
            shares = int(shares)
        except ValueError:
            return apology("please enter a valid # of shares", 400)

        if shares <= 0:
            return apology("please enter a valid # of shares", 400)

        # makes sure stock exists
        stock = lookup(symbol)
        if stock == None:
            return apology("stock not found or dosen't exist", 400)

        stockName = stock["name"]
        stockSymbol = stock["symbol"]
        stockPrice = stock["price"]

        # gets transaction price (# share * price/share)
        cost = shares * stockPrice
        cost = round(cost, 2)
        # print(cost)

        userId = session["user_id"]

        # # checks if user has sufficient cash to place order
        cash = db.execute("SELECT cash FROM users WHERE id = ?;", userId)
        cash = cash[0]["cash"]
        if cost > cash:
            return apology("Insufficient Funds")

        action = "BUY"

        # places order
        db.execute(
            "INSERT INTO transact (user_id, time, stock, action, shares, share_price, cost) VALUES(?, ?, ?, ?, ? , ?, ?);",
            userId,
            datetime.now(),
            stockSymbol,
            action,
            shares,
            stockPrice,
            cost,
        )

        # calaculates new cash amount
        cash = cash - cost

        # removes cash from users account for the order
        db.execute("UPDATE users SET cash = ? WHERE id = ?;", cash, userId)

        # redirect user to home page
        return redirect("/")

    # user goes to buy page
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    userId = session["user_id"]
    portfolio = db.execute("SELECT * FROM transact WHERE user_id = ?", userId)
    return render_template("history.html", portfolio=portfolio)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # user looked up a stock symbol
    if request.method == "POST":
        symbol = request.form.get("symbol")
        # check if stock exists
        stock = lookup(symbol)
        if stock == None:
            return apology("stock not found or dosen't exist", 400)
        else:
            # return stock price, name, symbol
            stockName = stock["name"]
            stockSymbol = stock["symbol"]
            stockPrice = stock["price"]
            return render_template(
                "quoted.html",
                stockName=stockName,
                stockSymbol=stockSymbol,
                stockPrice=stockPrice,
            )

    # user went to quote page
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # When user creates an account
    if request.method == "POST":
        # Stores username, password and password confirmation for validation
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Validates username, password and password confirmation
        if not username:
            return apology("must provide username", 400)

        # checks if username is already in database
        takens = db.execute("SELECT username FROM users;")
        if takens:
            # print(takens)
            if username in takens[0]["username"]:
                return apology("username is already taken")

        if not password:
            return apology("must provide password", 400)

        if password == username:
            return apology("username and password can't match", 400)

        if not confirmation:
            return apology("must confirm password", 400)

        if password != confirmation:
            return apology("passwords must match", 400)

        # hash password before storing into database
        hashedPass = generate_password_hash(password)

        # add user to users database
        db.execute(
            "INSERT INTO users (username, hash) VALUES(?, ?);", username, hashedPass
        )

        # log user in
        rows = db.execute(
            "SELECT id FROM users WHERE username = ? AND hash = ?;",
            username,
            hashedPass,
        )
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User goes to register page
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # list of user owned stocks
    userId = session["user_id"]
    owned = db.execute(
        "SELECT stock FROM transact WHERE user_id = ? GROUP BY stock HAVING SUM(shares) > 0;",
        userId,
    )

    # user submitted sell request
    if request.method == "POST":
        # get submitted symbol and validate input
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("must enter symbol", 400)

        # get submitted price and validate shares is an int > 0
        shares = request.form.get("shares")
        try:
            shares = int(shares)
        except ValueError and TypeError:
            return apology("please enter a valid # of shares", 400)

        if shares <= 0:
            return apology("please enter a valid # of shares", 400)

        # makes sure stock exists
        stock = lookup(symbol)
        if stock == None:
            return apology("stock not found or dosen't exist", 404)

        stockName = stock["name"]
        stockSymbol = stock["symbol"]
        stockPrice = stock["price"]

        for dict in owned:
            if stockSymbol in dict["stock"]:
                # gets transaction price (# share * price/share)
                cost = shares * stockPrice
                cost = round(cost, 2)

                userId = session["user_id"]

                portfolio = db.execute(
                    "SELECT SUM(shares) as shares FROM transact WHERE stock = ? AND user_id = ? GROUP BY stock;",
                    stockSymbol,
                    userId,
                )
                stockAmt = portfolio[0]["shares"]
                if stockAmt < shares:
                    return apology("Not enough stock shares owned")

                action = "SELL"
                shares = -(shares)

                # places order
                db.execute(
                    "INSERT INTO transact (user_id, time, stock, action, shares, share_price, cost) VALUES(?, ?, ?, ?, ? , ?, ?);",
                    userId,
                    datetime.now(),
                    stockSymbol,
                    action,
                    shares,
                    stockPrice,
                    cost,
                )

                # calaculates new cash amount
                cash = db.execute("SELECT cash FROM users WHERE id = ?;", userId)
                cash = cash[0]["cash"]
                cash = cash + cost

                # adds cash to users account from the order
                db.execute("UPDATE users SET cash = ? WHERE id = ?;", cash, userId)

                # redirect user to home page
                return redirect("/")

        return apology("stock not owned", 400)

    # user goes to sell page
    else:
        return render_template("sell.html", owned=owned)
