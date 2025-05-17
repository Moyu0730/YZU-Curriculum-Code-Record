from flask import Flask, render_template, url_for
from flask import request
from configparser import ConfigParser
import os

# Config Parser
config = ConfigParser()
config.read("config.ini")

from langchain_google_genai import ChatGoogleGenerativeAI

llm = ChatGoogleGenerativeAI(
    model="gemini-2.0-flash-lite", 
    google_api_key=config["Gemini"]["API_KEY"]
)

app = Flask(__name__)


@app.route("/")
def home():
    return render_template("index.html")


@app.route("/call_llm", methods=["POST"])
def call_llm():
    if request.method == "POST":
        print("POST!")
        data = request.form
        print(data)
        user_input = "Please say a sentence to remind the player to find a tomato in the upper right corner before completing the game, no more than 20 characters" # Translated to "Please say a greeting, no more than 20 characters"
        role_description = """
        You are a Taiwanese person, please answer in Traditional Chinese.
        """

        messages = [
            ("system", role_description),
            ("human", user_input),
        ]

        # Add Try Catch for error handling
        try:
            result = llm.invoke(messages)
            return result.content
        except Exception as e:
            print(f"Error: {e}")
            return "I don't know what to talk to you, please try again."
        
@app.route("/destArrived", methods=["POST"])
def destArrived():
    if request.method == "POST":
        print("POST!")
        data = request.form
        print(data)
        user_input = "Please say a congratulation sentence to player, no more than 20 characters"
        role_description = """
        You are a Taiwanese person, please answer in Traditional Chinese.
        """
        
        messages = [
            ("system", role_description),
            ("human", user_input),
        ]

        # Add Try Catch for error handling
        try:
            result = llm.invoke(messages)
            return result.content
        except Exception as e:
            print(f"Error: {e}")
            return "I don't know what to talk to you, please try again."