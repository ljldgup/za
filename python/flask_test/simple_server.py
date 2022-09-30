from flask import Flask, request

app = Flask(__name__)


@app.route("/")
def index():
    print_request()
    return "root"


@app.route("/hello")
def hello():
    print_request()
    return "Hello"


def print_request():
    print(request)
    try:
        print(request.path)
        print(request.get_data())
        print(request.headers)
    except Exception as e:
        print(e)


if __name__ == "__main__":
    app.run()
