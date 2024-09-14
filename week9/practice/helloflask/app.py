from flask import Flask, render_template, request

app = Flask(__name__)

vals = ["red", "blue"]

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "GET":
        return render_template("index.html")
    else:
        print("Form Submitted!")
        color = request.form.get("color")
        if color in vals:
            return render_template("color.html", color=color)
        else:
            return "<h1>Please choose either red or blue</h1>"
