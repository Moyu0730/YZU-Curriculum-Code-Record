from configparser import ConfigParser

# Set up the config parser
config = ConfigParser()
config.read("config.ini")

from langchain_google_genai import ChatGoogleGenerativeAI

import google.generativeai as genai
genai.configure(api_key=config["Gemini"]["API_KEY"])

# List all available models
for model in genai.list_models():
    print(f"Model: {model.name}")

llm_gemini = ChatGoogleGenerativeAI(
    model="gemini-2.0-flash-lite", 
    google_api_key=config["Gemini"]["API_KEY"]
)

user_input = "What is the meaning of life ?"

role_description = """ 
You are a philosopher, please answer in Traditional Chinese.
"""

messages = [
    ("system", role_description),
    ("human", user_input),
]

response_gemini = llm_gemini.invoke(messages)

print(f"Ask : {user_input}")
print(f"Gemini : {response_gemini.content}")