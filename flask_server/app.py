from flask import Flask, render_template, make_response, request
import requests

cards = {
	"46:0C:C8:0F": "gulbahar",
	"26:B8:3C:1E": "mike",
	"A6:88:E8:21": "selbi",
	"23:BB:97:79": "dowletyar",
	"C6:1D:D6:21": "Merdan",
	"06:75:BC:1E": "dowlpack",
}

esp_device_key = "rfid_secret"
esp_device_ip = "192.168.1.145"


app = Flask(__name__)

@app.route("/")
def root():
	return "hey there"


@app.route("/esp/door/")
def esp_door():
	device_key = request.args.get("device_key")
	command = request.args.get("command")
	data = request.args.get("data")

	if device_key == esp_device_key:

		if data in cards:
			print(cards[data])

			return "ok"

		return "not found"

	print("==========")

	return "err"


@app.route("/door_action/")
def door_action():
	command = request.args.get("command")
	print(command)
	payload = "http://{}/door/?command={}&secret={}".format(esp_device_ip, command, esp_device_key)
	r = requests.get(payload)
	print(r.text)
	return "ok"

@app.route("/ui_control/")
def ui_control():
	return render_template("/index.html")


if __name__=="__main__":
	app.run("0.0.0.0")