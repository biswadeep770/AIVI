from http.server import BaseHTTPRequestHandler, HTTPServer
import json
import urllib.request

GEMINI_SERVER = "http://127.0.0.1:5000/ask"


class AIVIWebHandler(BaseHTTPRequestHandler):

    def do_GET(self):

        if self.path == "/" or self.path == "/aivi_phone.html":

            try:
                with open(
                    r"C:\Users\BISWADEEP\aivi_phone.html",
                    "rb"
                ) as f:
                    content = f.read()

                self.send_response(200)
                self.send_header(
                    "Content-Type",
                    "text/html; charset=utf-8"
                )
                self.end_headers()
                self.wfile.write(content)

            except Exception as e:

                self.send_error(500, str(e))

        else:

            self.send_error(404)


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

            request_data = json.loads(
                body.decode("utf-8")
            )

            user_text = request_data.get(
                "text",
                ""
            )

            data = json.dumps({
                "text": user_text
            }).encode("utf-8")

            req = urllib.request.Request(
                GEMINI_SERVER,
                data=data,
                headers={
                    "Content-Type":
                    "application/json"
                },
                method="POST"
            )

            with urllib.request.urlopen(req) as response:

                result = response.read()

            self.send_response(200)

            self.send_header(
                "Content-Type",
                "application/json"
            )

            self.send_header(
                "Access-Control-Allow-Origin",
                "*"
            )

            self.end_headers()

            self.wfile.write(result)

        except Exception as e:

            print("Web server error:", e)

            self.send_response(500)

            self.send_header(
                "Content-Type",
                "application/json"
            )

            self.end_headers()

            self.wfile.write(
                json.dumps({
                    "error": str(e)
                }).encode("utf-8")
            )


    def do_OPTIONS(self):

        self.send_response(204)

        self.send_header(
            "Access-Control-Allow-Origin",
            "*"
        )

        self.send_header(
            "Access-Control-Allow-Methods",
            "GET, POST, OPTIONS"
        )

        self.send_header(
            "Access-Control-Allow-Headers",
            "Content-Type"
        )

        self.end_headers()


server = HTTPServer(
    ("0.0.0.0", 8000),
    AIVIWebHandler
)

print("AIVI web server running on port 8000")

server.serve_forever()