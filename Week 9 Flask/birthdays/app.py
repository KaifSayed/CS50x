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
        # Add the user's entry into the database
        name = request.form.get("name")
        day = request.form.get("day")
        month = request.form.get("month")

        db.execute("INSERT INTO birthdays (name, day, month) VALUES (?, ?, ?)", name, day, month)
        return redirect("/")
    else:
        # TODO: Display the entries in the database on index.html
        birthdays = db.execute("SELECT * FROM birthdays")

        return render_template("index.html", birthdays=birthdays)

@app.route("/cleanup", methods=["POST"])
def cleanup():
    # Get the selected id to delete
    selected_ids = request.form.getlist("selected_ids")

    if selected_ids:
        # Delete the selected id from the database
        db.execute("DELETE FROM birthdays WHERE id IN (?)", (", ".join(selected_ids),))

    # Redirect to the home page after cleaning up the data
    return redirect("/")

