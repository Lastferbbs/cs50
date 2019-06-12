from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash
from passlib.apps import custom_app_context as pwd_context
import datetime

from helpers import apology, login_required, lookup, usd, lookup1

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

shares1 = db.execute("SELECT symbol, time, price, number_of_stocks FROM shares WHERE user_id = 9")

print(shares1)