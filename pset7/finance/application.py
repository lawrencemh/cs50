from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import gettempdir

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = gettempdir()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")




@app.route("/")
@login_required
def index():
    return apology("TODO")




@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        
        # validate ticker is posted
        if not request.form.get('symbol'):
            return apology('Please enter a symbol!')
        ticker = request.form.get('symbol')
        
        # validate quantity provided
        if not request.form.get('quantity'):
            return apology('Please enter a quantity to purchase!')
        
        quantity = request.form.get('quantity', type=int)

        if not quantity > 0:
            return apology('Please enter a quantity greater than 0!')
            
        # get latest ticker data
        data = lookup(ticker)
        if not data:
            return apology("Couldn't get info for {}".format(request.form.get("symbol")))
        
        # get price
        price = data["price"]
        
        # check user has sufficient cash before carrying out transaction!
        cash = db.execute("SELECT cash FROM users WHERE id = :id ", id=session["user_id"])
        cash = cash[0]['cash']
        cash_req = price * quantity
        if cash < cash_req:
            return apology("Sorry you don't have sufficient funds for this transaction!")
        
        # insert purchase into user_history
        r = db.execute("INSERT INTO user_history ('user_id', 'symbl', 'price', 'type') VALUES (:user_id, :symbol, :price, :type)", user_id=session["user_id"], symbol=ticker, price=price, type=1)
        if not r:
            return apology("Sorry - somthing went wrong with this transaction!")
            
        # deduct cash_req from user's cash on table user
        r = db.execute("UPDATE users SET cash = :new_cash WHERE id = :user_id", new_cash=(cash - cash_req), user_id=session["user_id"])
        
        return "you have {} ".format(cash)
        
        return "bought!"
    elif request.method == "GET":
        return render_template('buy.html') 




@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
    return apology("TODO")




@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")




@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))




@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        # check ticker was submitted
        if not request.form.get("symbol"):
            return apology("please enter a symbol!")
        
        # try getting ticker info
        data = lookup(request.form.get("symbol"))
        if not data:
            return apology("There was a problem retrieving {} info!".format(request.form.get("symbol")))
        
        # return quote view
        return render_template("quote_view.html", ticker=request.form.get("symbol"), name=data["name"], price=usd(data["price"]))
    elif request.method =="GET":
        return render_template("quote.html")




@app.route("/register", methods=["GET", "POST"])
def register():
    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        
        # ensure username was submitted
        if not request.form.get("username"):
            return apology("Please enter a username!")
        
        # ensure password was submitted and matches
        if not request.form.get("password") == request.form.get("password_validate") or len(request.form.get("password_validate")) < 1:
            return apology("The passwords do not match or are empty!")
        
        # check username doesn't already exist
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
        if len(rows) != 0:
            return apology('{} is already a registered username'.format(request.form.get("username")))
        
        # has user's password
        hPass = pwd_context.encrypt(request.form.get("password"))
        
        # insert new user to users
        r = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)", username=request.form.get("username"), hash=hPass)
        if not r:
            return apology("An error occured creating your username!")
        
        # log new user in
        user = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
        session['user_id'] = user[0]['id']
        
        # success return to index and flash success message
        flash('You were successfully registered')
        return redirect(url_for("index"))
        
    elif request.method =="GET":
        return render_template("register.html")




@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    return apology("TODO")
