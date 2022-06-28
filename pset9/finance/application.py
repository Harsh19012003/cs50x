import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from datetime import datetime
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, password_check

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    # Show portfolio of stocks
    user_id = session["user_id"]

    rows = db.execute("SELECT users.cash, transactions.symbol, SUM(transactions.shares) FROM transactions JOIN users ON users.id = transactions.u_id WHERE transactions.u_id = ? GROUP BY transactions.symbol", user_id)
    if rows != []:
        values = []
        i = 0

        # Insert into the values list the dictionaries which get returned by lookup function which takes argument as stock's symbol
        for row in rows:
            values.insert(i, lookup(f"{row['symbol']}"))
            i += 1

        # Iterate for each row
        for row in rows:
            symbol = row["symbol"]
            # Iterate for each object of values list of dictionaries
            for value in values:
                if value["symbol"] == symbol:
                    # Set that dictionary's price to realtime stock price
                    row["price"] = value["price"]

        # Cash that user owns
        amount = rows[0]["cash"]

        # Total money user owns is sum of cash and (no.of stocks*present stock price)
        for row in rows:
            amount += row["SUM(transactions.shares)"] * row["price"]
        print(rows)
        return render_template("index.html", rows=rows, amount=amount)

    else:
        rows = [{"cash": 10000, "symbol": "None", "SUM(transactions.shares)": 0, "price": 0}]
        print(type(rows[0]["cash"]))
        return render_template("index.html", rows=rows, amount=0)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    # Buy shares of symbol

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        symbol = request.form.get("symbol")
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("Invalid share. Must enter integer share")

        # Ensure symbol text was not blank
        if symbol == "":
            return apology("Must enter stock symbol")

        # Ensure user enters positive integer as shares
        if shares <= 0:
            return apology("Invalid no of shares")

        output = lookup(symbol)
        # Ensure correct symbol was submitted
        if output == None:
            return apology("Invalid stock symbol")

        name = output["name"]
        price = output["price"]
        symbol = output["symbol"]
        user_id = session["user_id"]

        # Query database for amount user has
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        total_price = price*shares

        # Ensure whether user has enough money to buy selected stocks
        if cash < total_price:
            return apology("Insufficient cash!!!")
        else:
            dt = datetime.now()
            db.execute("UPDATE users SET cash = ? WHERE id = ?", cash - total_price, user_id)
            db.execute("INSERT INTO transactions (u_id, symbol, shares, dt) VALUES (?, ?, ?, ?)", user_id, symbol, shares, dt)

            # Successfully bought. Here, javascript can be added.
            return redirect("/")

    # User reached route via GET (as by clicking a link)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    # Show history of transactions

    user_id = session["user_id"]

    # User reaches route via GET (as by clicking a link)
    history = db.execute("SELECT * FROM transactions WHERE u_id = ?", user_id)
    symbols = db.execute("SELECT symbol FROM transactions WHERE u_id = ? GROUP BY symbol", user_id)

    values = []
    i = 0

    # lookup the current price of owned stocks
    for symbol in symbols:
        values.insert(i, lookup(f"{symbol['symbol']}"))
        i += 1

    # Insert in history list of dict current price of stock
    # Iterate over rows in history
    for row in history:
        # Iterate over rows in value
        for value in values:
            # If both symbol of history and value is same, insert current value to that row of history
            if row["symbol"] == value["symbol"]:
                x = {"price": f'{value["price"]}'}
                row.update(x)

    return render_template("history.html", history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    # Log user in

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    # Log user out

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    # Get symbol quote.

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        symbol = request.form.get("symbol")

        # Ensure symbol text was not blank
        if symbol == "":
            return apology("Must enter symbol")

        output = lookup(symbol)

        # Ensure correct symbol was submitted
        if output == None:
            return apology("Invalid symbol")

        else:
            name = output["name"]
            price = output["price"]
            symbol = output["symbol"]
            # Successfull quoted. Here, javascript can be added.
            return render_template("quoted.html", name=name, price=price, symbol=symbol)

    # User reached route via GET (as by clicking a link)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    # Register user

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Creat variables
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Ensure user has written username
        if not username:
            return apology("Must provide Username", 400)

        # Ensure no other user is in database with same username
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        if len(rows) != 0:
            return apology("Username is already taken")

        # Ensure user has written password
        if not password:
            return apology("Must provide password", 400)

        # Ensure user has written confirmation of password
        if not confirmation:
            return apology("Must provide confirmation", 400)

        # Ensure password in both fields(password and confirmation) is same
        if password != confirmation:
            return apology("Password and Confirmation donot match")

        # Ensure password satisfies the requirements of one uppercase, one lowercase, one numeric and one symbol
        ps = list(password.strip(" "))
        requirement = password_check(ps)
        if requirement == False:
            return apology("Password Requirement")

        # Register user by storing it in database. Here, javascript can be added.
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, generate_password_hash(password))
        return redirect("/")

    # User reached route via GET (as by clicking a link)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    # Sell shares of stock

    user_id = session["user_id"]

    # Get info about cash, owned stocks and no.of stocks owned
    rows = db.execute("SELECT users.cash, transactions.symbol, SUM(transactions.shares) FROM users JOIN transactions ON users.id = transactions.u_id WHERE users.id = ? GROUP BY transactions.symbol", user_id)

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        shares = int(shares)

        # Get info about which company and how much stocks were selected
        for row in rows:
            if row["symbol"] == symbol:
                selected_symbol = row["symbol"]
                owned_shares = row["SUM(transactions.shares)"]

        # Ensure user try to sell number of stocks which they own and not more than that
        # More error checking can be added but here we are keeping it simple..........
        if shares > owned_shares or owned_shares == 0:
            return apology("You dont own enough shares")
        else:
            # Update the database

            # 1. Update no.of stocks
            dt = datetime.now()
            db.execute("INSERT INTO transactions (u_id, symbol, shares, dt) VALUES (?, ?, ?, ?)", user_id, symbol, -shares, dt)

            # 2. Update the cash
            current_price = lookup(symbol)["price"]
            owned_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
            updated_cash = int(owned_cash + (current_price*shares))
            db.execute("UPDATE users SET cash = ? WHERE id = ?", updated_cash, user_id)

            # Return back to sell route once the process is successfull. Here, javascript can be added.
            return redirect("/")

    # User reached route via GET (as by clicking a link)
    else:
        return render_template("sell.html", rows=rows)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
