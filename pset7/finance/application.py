from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash
from passlib.apps import custom_app_context as pwd_context
import datetime

from helpers import apology, login_required, lookup, usd, lookup1

# Configure application
app = Flask(__name__)

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


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    sumashares = 0
    cash = db.execute("SELECT cash FROM users WHERE id = :id",
                          id=session["user_id"])

    shares1 = db.execute("SELECT symbol, SUM(number_of_stocks) as total FROM shares GROUP BY symbol HAVING user_id = :id AND total > 0",
                id=session["user_id"])
    for index, item in enumerate(shares1):
        quote1 = lookup1(shares1[index]['symbol'])
        a = quote1['price']
        item.update( {"price":a})
        b = shares1[index]['price'] * shares1[index]['total']
        item.update( {"totalcash":b})
        sumashares += b
    sumaall = sumashares + cash[0]["cash"]

    return render_template("index.html", shares = shares1, cash = cash[0]["cash"], suma = sumaall)




@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 403)

        digit = request.form.get("shares")

        if int(digit) < 1:
              return apology("number must be a posivite integer", 403)




        # Using helpers function to get stock data
        quote = lookup(request.form.get("symbol"))

        # Checking if symbol exists
        if quote == None:
            return apology("wrong symbol", 403)

        rows = db.execute("SELECT cash FROM users WHERE id = :id",
                          id=session["user_id"])

        if rows[0]['cash'] < quote["price"] * int(digit):
            return apology("not enough cash, sorry!", 403)

        left = rows[0]['cash'] - (quote["price"] * int(digit))


        db.execute("INSERT INTO shares (symbol, time, price, user_id, number_of_stocks) VALUES (:symbol, :time, :price, :user_id, :number_of_stocks)",
                          symbol=request.form.get("symbol"), time = datetime.datetime.now(), price = quote["price"], user_id = session["user_id"], number_of_stocks = int(digit))

        db.execute("UPDATE users SET cash = :cash WHERE id = :id",
        cash = left, id=session["user_id"])

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():

    shares1 = db.execute("SELECT symbol, price, time, number_of_stocks FROM shares WHERE user_id = :id",
                id=session["user_id"])

    return render_template("history.html", shares = shares1)

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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
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


@app.route("/change", methods=["GET", "POST"])
@login_required
def change():
    """Change user password"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure new password was submitted
        if not request.form.get("new_pass"):
            return apology("must provide new password", 403)

        # Ensure new passwords match
        elif not request.form.get("new_pass") == request.form.get("confirmation"):
            return apology("passwords do not match!", 403)

        hash = generate_password_hash(request.form.get("new_pass"))

        db.execute("UPDATE users SET hash = :hash WHERE id = :id",
        hash = hash, id=session["user_id"])


        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("change.html")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 403)

        # Using helpers function to get stock data
        quote = lookup(request.form.get("symbol"))

        # Checking if symbol exists
        if quote == None:
            return apology("wrong symbol", 403)

        return render_template("quoted.html", symbol = quote["symbol"], price = quote["price"])

    else:
        return render_template("quote.html")




@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Ensure passwords match
        elif not request.form.get("password") == request.form.get("confirmation"):
            return apology("passwords do not match!", 403)

        hash = generate_password_hash(request.form.get("password"))

        #adding user to database with hashed password
        result = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)",
                          username=request.form.get("username"), hash=hash)

        if not result:
            return apology("username is taken!", 405)

        session["user_id"] = result


        return redirect("/")


    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 405)

        digit = request.form.get("shares")

        if int(digit) < 1:
              return apology("number must be a posivite integer", 403)




        # Using helpers function to get stock data
        quote = lookup(request.form.get("symbol"))

        # Checking if symbol exists
        if quote == None:
            return apology("wrong symbol", 403)

        cash = db.execute("SELECT cash FROM users WHERE id = :id",
                          id=session["user_id"])

        left = cash[0]['cash'] + (quote["price"] * int(digit))

        sell = db.execute('SELECT SUM(number_of_stocks) as total FROM shares WHERE user_id = :id AND symbol = :symbol',
        symbol = request.form.get("symbol"), id=session["user_id"])

        t = request.form.get("shares")
        n = sell[0]['total']

        if int(n) < int(t):
            return apology("not enough shares, sorry!", 403)




        db.execute("INSERT INTO shares (symbol, time, price, user_id, number_of_stocks) VALUES (:symbol, :time, :price, :user_id, :number_of_stocks)",
                          symbol=request.form.get("symbol"), time = datetime.datetime.now(), price = quote["price"], user_id = session["user_id"], number_of_stocks = -int(digit))

        db.execute("UPDATE users SET cash = :cash WHERE id = :id",
        cash = left, id=session["user_id"])

        return redirect("/")

    else:
        return render_template("sell.html")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
