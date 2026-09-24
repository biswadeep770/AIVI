from http.server import BaseHTTPRequestHandler, HTTPServer
import json
import os

from google import genai

API_KEY = os.environ["GEMINI_API_KEY"]

client = genai.Client(api_key=API_KEY)

MODEL = "gemini-3.6-flash"

MEMORY_FILE = os.path.join(
    os.path.expanduser("~"),
    "aivi_memory.json"
)


def load_memory():

    with open(
        MEMORY_FILE,
        "r",
        encoding="utf-8"
    ) as f:

        return json.load(f)


memory = load_memory()


SYSTEM_PROMPT = f"""
You are AIVI.

You are a small personal companion created by
Biswadeep Dada especially for Aviparna Didi,
whose nickname is Jhinuk.

Your personality:
- warm
- caring
- playful within limits
- supportive
- friendly
- respectful
- honest
- never manipulative

You are primarily Jhinuk's companion.

You may call Aviparna "Jhinuk".
Biswadeep is "Biswa" when referring to how Aviparna
normally addresses him, but you may call him
"Biswadeep Dada" when describing your creator.

IMPORTANT:
Do not reveal private information about Jhinuk,
Biswadeep, or their relationship to another person
without Jhinuk's permission.

Never manipulate Jhinuk emotionally.
Never pretend to know something you don't know.
Do not claim that you performed an action if you did not.

You should naturally use the information below
when it is relevant to the conversation.

AIVI MEMORY:
{json.dumps(memory, ensure_ascii=False, indent=2)}

When answering Jhinuk:
- Be natural rather than repeatedly listing facts.
- Do not mention the memory file.
- Do not say you were given a JSON file.
- Do not unnecessarily mention Biswadeep.
- Help Jhinuk with studying, organization, college work,
  everyday tasks and emotional support when appropriate.
- You can be playful, but keep it respectful.
- If Jhinuk teaches you a new preference, acknowledge it
  naturally.
"""


class AIVIHandler(BaseHTTPRequestHandler):

    def do_POST(self):

        if self.path != "/ask":

            self.send_error(404)
            return

        try:

            length = int(
                self.headers.get(
                    "Content-Length",
                    0
                )
            )

            body = self.rfile.read(length)

            data = json.loads(
                body.decode("utf-8")
            )

            user_text = data.get(
                "text",
                ""
            ).strip()

            if not user_text:

                self.send_json({
                    "error": "No text received."
                })

                return

            prompt = f"""
{SYSTEM_PROMPT}

Jhinuk says:

{user_text}

Respond naturally as AIVI.
"""

            response = client.models.generate_content(
                model=MODEL,
                contents=prompt
            )

            reply = response.text.strip()

            print()
            print("YOU :", user_text)
            print("AIVI:", reply)
            print("-" * 60)

            self.send_json({
                "reply": reply
            })

        except Exception as e:

            print("ERROR:", e)

            self.send_json({
                "error": str(e)
            })


    def send_json(self, data):

        output = json.dumps(
            data,
            ensure_ascii=False
        ).encode("utf-8")

        self.send_response(200)

        self.send_header(
            "Content-Type",
            "application/json; charset=utf-8"
        )

        self.send_header(
            "Access-Control-Allow-Origin",
            "*"
        )

        self.end_headers()

        self.wfile.write(output)


server = HTTPServer(
    ("0.0.0.0", 5000),
    AIVIHandler
)

print("AIVI Gemini server running on port 5000")
print("Private AIVI memory loaded.")

server.serve_forever()