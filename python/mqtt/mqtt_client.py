import datetime
import hashlib
import json
import time
from concurrent.futures import ThreadPoolExecutor

# pip install paho-mqtt  -i https://mirrors.aliyun.com/pypi/simple/
import paho.mqtt.client as mqtt


def client_loop(host: str, port: str, client_id: str, username: str, password: str):
    client = mqtt.Client(client_id, reconnect_on_failure=True)  # ClientId
    client.username_pw_set(username, password)  # 用户名 密码
    client.on_connect = on_connect
    client.on_message = on_message
    client.on_disconnect = on_disconnect
    client.reconnect_delay_set(1, 1)
    client.connect(host, port, 60)
    client.gateway_id = client_id

    client.loop_start()
    return client


def on_connect(client: mqtt.Client, userdata, flags, rc):
    print("Connected with result code " + str(rc))
    device_id = '95dcfa81725e4bcf8195f21f7fed4870'
    # repeat_publish_not_belong_data(client, device_id)
    # repeat_publish_invalid_data(client, device_id)
    # client.subscribe("test")


def on_disconnect(client: mqtt.Client, userdata, msg):
    print("disconnect " + str(msg))


def on_message(client: mqtt.Client, userdata, msg):
    print(datetime.datetime.now())
    print("receive:", msg.topic + " " + msg.payload.decode("utf-8"))
    reply_command(client, msg)


def reply_command(client, msg):
    decode_payload = json.loads(msg.payload.decode())
    topic = str(msg.topic)
    print(topic + "收到:" + decode_payload)
    repeat_publish_invalid_data(client)


def repeat_publish_invalid_data(client):
    topic = '/topic'
    for i in range(1000):
        print(i, "reply:", "invalid_data")
        client.publish(topic, payload=json.dumps("invalid_data"), qos=0, retain=False)


if __name__ == '__main__':
    #使用activemq作为mqtt服务端
    password = "admin"
    username = "admin"

    client_loop("localhost", 1883, "client_id", username, password)
    # futures = []
    # with ThreadPoolExecutor(max_workers=2) as executor:
    #     for i in range(1000):
    #         time.sleep(0.01)
    #         futures.append(executor.submit(client_loop, "localhost", 1883, str(i), username, password))
