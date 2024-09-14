import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database
        name = request.form.get("name")

        month = request.form.get("month")
        try:
            month = int(month)
        except ValueError:
            return render_template("index.html", errorMsg="Please enter a valid month")

        day = request.form.get("day")
        try:
            day = int(day)
        except ValueError:
            return render_template("index.html", errorMsg="Please enter a valid day")

        db.execute("INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?);", name, month, day)

        # return render_template("index.html", bday=bday)
        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        bday = db.execute("SELECT * FROM birthdays ORDER BY month, day, name;")
        # print(bday)

        return render_template("index.html", bday=bday, errorMsg="")


