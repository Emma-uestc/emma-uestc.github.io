import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

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
    # get all the stocks the user owns displaying in a table using a SQL query
    portfolio = db.execute("""
    SELECT symbol SUM(shares) as total_share
    FROM transactions
    WHERE id = ?
    GROUP BY symbol
    HAVING SUM(shares) > 0
    """, session["user_id"])
    # get the cash the user has
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    # compute the total value of the user's portfolio
    total_value = cash[0]["cash"] # set total_value initially to the cash the user has
    for stock in portfolio:
        quote = lookup(stock["symbol"])
        stock["name"] = quote["name"]
        stock["price"] = quote["price"]
        stock["total"] = stock["price"] * stock["total_shares"]
        total_value += stock["total"]
    return render_template("index.html", portfolio=portfolio, cash=cash, total_value=total_value)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # Get the symbol and shares from form
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        # check data
        # 1. check symbol and shares are not empty
        if not symbol:
            return apology("must provide symbol", 400)
        if not shares:
            return apology("must provide shares", 400)
        # 2. check if shares is a positive integer
        try:
            shares = int(shares)
            if shares <= 0:
                return apology("shares must be positive", 400)
        except ValueError:
            return apology("shares must be a positive integer", 400)
        # get the stock through lookup
        stock = lookup(symbol)
        if stock is None:
            return apology("invalid symbol", 400)
        # compute total cost to buy the stock
        total_cost = shares * stock["price"]
        # check if the user has enough cash to buy the stock
        user = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = user[0]["cash"]
        if cash < total_cost:
            return apology("you do not have enough cash to buy the stock", 400)
        # update the user's cash
        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", total_cost, session["user_id"])
        # record transactions
        db.execute("INSERT INTO transactions (id, symbol, shares, price) VALUES (?, ?, ?, ?)",
        session["user_id"], stock["symbol"], shares, stock["price"])
        # flash a message
        flash(f"Bought {shares} shares of {symbol} for {usd(total_cost)}")
        return redirect("/")
    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("""
    SELECT symbol, shares, price transacted_timestamp
    FROM transactions
    WHERE id = ?
    ORDER BY timestamp DESC
    """,session["user_id"])
    return render_template("history.html",transactions = transactions)


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
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide symbol", 400)
        stock = lookup(symbol().upper())
        if stock is None:
            return apology("invalid symbol", 400)
        return render_template("quoted.html",  stock = stock)
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # Get username and password from form
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        # check 
        # 1. check username and password is not empty
        # if not username or not password or not confirmation:
        if not username:
            return apology("must provide username", 400)
        if not password:
            return apology("must provide password", 400)
        if not confirmation:
            return apology("must provide confirmation", 400)
        # 2.check if passwords match for the confirmation
        if password != confirmation:
            return apology("confirmation does not match pawword", 400)
        # check if username has already taken
        existing = db.execute("SELECT * FROM users WHERE username = ?", username)
        if existing:
            return apology("username has already been taken", 400)
        # insert user account into database
        hash_password = generate_password_hash(password)
        user = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash_password)
        session["user_id"] = user["id"]
        return redirect("/")
    else: # GET 
        return render_template("register.html")

@app.route("/sell", methods=["GET","POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # Get the symbol and shares to sell
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
    # check data from user
    if not symbol or not shares:
        return apology("must provide symbol and shares")
    # check if the shares value is integer
    try:
        shares = int(shares)
        if shares <= 0:
            return apology("shares must be a positive")
    except ValueError:
        return apology("share must be a positive integer")
    # get how many shares the user has of the stock
    holdings = db.execute("""
        SELECT SUM(shares) as total_shares
        FROM transactions
        WHERE id = ?
        AND symbol = ?""",session["user_id"],symbol)

    # check if the user owns any shares of the stock
    if not holdings or holdings[0]["total_shares"] <= 0:
        return apology("you do not own any shares of the stock", 400)
    # check if the user has enough shares to sell
    if holdings[0]["total_shares"] < shares:
        return apology("you do not have enough shares to sell")
    # get the current price of the stock
    stock = lookup(symbol)
    if stock is None:
        return apology("invalid symbol")
    # compute the total value
    total_sale = shares * stock["price"]
    # update the user's cash
    db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", total_sale, session["usre_id"])
    # record transactions
    db.execute("INSERT INTO transactions (id, symbol, shares, price) VALUES (?, ?, ?, ?)",
     session["user_id"], symbol, shares, stock["price"])
    flash(f"Sold {shares} shares of {symbol} for {usd(total_sale)}")
    return redirect("/")
    else: # GET request
        stocks = db.execute("""
        SELECT symbol
        FROM transactions
        WHERE id = ?
        GROUP BY symbol
        HAVING SUM(shares) > 0
        """,session["user_id"])
        return render_template("sell.html",symbol=symbol,shares=shares)
    # get the current price of the stock
