from flask import Flask, redirect, render_template, request, url_for

import helpers
import nltk
import os
import sys

from nltk.tokenize import TweetTokenizer
from analyzer import Analyzer

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():

    # validate screen_name
    screen_name = request.args.get("screen_name", "").lstrip("@")
    if not screen_name:
        return redirect(url_for("index"))
    
    # get screen_name's tweets
    tweets = helpers.get_user_timeline(screen_name)
    
    # check tweets is not empty
    if not tweets:
        return redirect(url_for("index"))
    
    # absolute paths to lists
    positives = os.path.join(sys.path[0], "positive-words.txt")
    negatives = os.path.join(sys.path[0], "negative-words.txt")
    
    # initalise analyzer
    analyzer = Analyzer(positives, negatives)
    
    # initalise tweet tokenizer
    tknzr = TweetTokenizer()
    
    # initalise loop variables
    pos, neg, neu = 0, 0, 0
    
    # analyze the tweets
    for tweet in tweets:
        score = 0
        t = tknzr.tokenize(tweet)
        for c in t:
            score += analyzer.analyze(c)
            
        # set colour for output based on score
        if score > 0.0:
            pos += 1
        elif score < 0.0:
            neg += 1
        else:
            neu += 1
    
    # calculate percentages
    total = pos + neg + neu
    positive = pos / total
    negative = neg / total
    neutral  = neu / total

    # TODO
    #positive, negative, neutral = 0.0, 0.0, 100.0

    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart=chart, screen_name=screen_name)
