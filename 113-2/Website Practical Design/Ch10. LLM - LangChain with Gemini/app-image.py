from langchain_core.messages import HumanMessage
from langchain_google_genai import ChatGoogleGenerativeAI
from IPython.display import Image, display
from configparser import ConfigParser
import base64

config = ConfigParser()
config.read("config.ini")

# gemini-2.0-flash-exp
# gemini-1.5-flash-latest

llm = ChatGoogleGenerativeAI(
    model="gemini-2.0-flash-exp",
    google_api_key=config["Gemini"]["API_KEY"],
    max_tokens=8192,
)


def image4LangChain(image_url):
    if "http" in image_url:
        return {"url": image_url}
    else:
        with open(image_url, "rb") as image_file:
            image_data = base64.b64encode(image_file.read()).decode("utf-8")
        return {"url": f"data:image/jpeg;base64,{image_data}"}


user_messages = []
# append user input question
user_input = "What is the same in these images? Please describe it in detail."

user_messages.append({"type": "text", "text": user_input + "Please answer in Traditional Chinese."})
image_url = "https://cdn.pixabay.com/photo/2024/05/26/10/15/bird-8788491_1280.jpg"
image_url_2 = "http://d1jyxxz9imt9yb.cloudfront.net/medialib/4350/image/s768x1300/AdobeStock_123823873_433578_reduced.jpg"

user_messages.append(
    {
        "type": "image_url",
        "image_url": image4LangChain(image_url),
    }
)
user_messages.append(
    {
        "type": "image_url",
        "image_url": image4LangChain(image_url_2),
    }
)

human_messages = HumanMessage(content=user_messages)
result = llm.invoke([human_messages])

print("Q: " + user_input)
print("A: " + result.content)

# Display the image
display(Image(url=image_url))
display(Image(url=image_url_2))