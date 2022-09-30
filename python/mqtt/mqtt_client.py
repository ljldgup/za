import datetime
import hashlib
import json
import time

#pip install paho-mqtt  -i https://mirrors.aliyun.com/pypi/simple/
import paho.mqtt.client as mqtt


def client_loop(host: str, port: str, client_id: str, username: str, password: str):
    client = mqtt.Client(client_id, reconnect_on_failure=False)  # ClientId
    client.username_pw_set(username, password)  # 用户名 密码
    client.on_connect = on_connect
    client.on_message = on_message
    client.on_disconnect = on_disconnect
    client.reconnect_delay_set(1, 1)
    client.connect(host, port, 60)
    client.gateway_id = client_id

    client.loop_forever()


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

    if topic.endswith("command"):
        publish_command_reply(client, decode_payload, topic)
    elif topic.endswith("/service/shadow/property"):
        # function_index = random.randint(0, len(function_list) - 1)
        # function_list[function_index](client, decode_payload['device_id'], gateway_id)
        publish_service_data_upload_message(client, decode_payload['deviceId'], client.gateway_id,
                                            param=decode_payload['param'])
        # publish_offline_message(client, decode_payload)
    # else:
    #     publish_offline_message(client, decode_payload)


def publish_command_reply(client, decode_payload, topic):
    response = {
        "timestamp": int(round(time.time() * 1000)),
        "mid": decode_payload['mid'],
        "deviceId": decode_payload['deviceId'],
        "expire": 60000,
        "param": {},
        "mgs": "foe疾风欧偶数的时代☺",
        "code": "200"
    }
    topic = topic.replace("command", "reply")
    print("reply:", topic, response)
    client.publish(topic,
                   payload=json.dumps(response), qos=0,
                   retain=False)


def publish_offline_message(client, device_id, gateway_id):
    md5hash = hashlib.md5(str(time.time()).encode())
    md5 = md5hash.hexdigest()
    # 下线
    response = {
        "timestamp": int(round(time.time() * 1000)),

        "mid": md5,
        "deviceId": device_id,
        "expire": 60000,
        "param": {},
    }
    topic = '/v1/{}/device/offline'.format(gateway_id)
    print("reply:", topic, response)
    client.publish(topic,
                   payload=json.dumps(response), qos=0,
                   retain=False)


def publish_service_data_upload_message(client, device_id, gateway_id, param=None):
    md5hash = hashlib.md5(str(time.time()).encode())
    md5 = md5hash.hexdigest()
    # 下线
    response = {
        "timestamp": int(round(time.time() * 1000)),
        "mid": md5,
        "deviceId": device_id,
        "expire": 60000,
    }

    if param:
        response['param'] = param

    topic = '/v1/{}/service/data'.format(gateway_id)
    print("reply:", topic, response)
    client.publish(topic,
                   payload=json.dumps(response), qos=0,
                   retain=False)


def publish_device_data_upload_message(client, device_id, gateway_id):
    md5hash = hashlib.md5(str(time.time()).encode())
    md5 = md5hash.hexdigest()
    # 下线
    response = {
        "timestamp": int(round(time.time() * 1000)),
        "mid": md5,
        "deviceId": device_id,
        "expire": 60000,
        "param": {"cpuRate": "10"},
    }
    topic = '/v1/{}/device/status/data'.format(gateway_id)
    print("reply:", topic, response)
    client.publish(topic,
                   payload=json.dumps(response), qos=0,
                   retain=False)


def publish_service_event_upload_message(client, device_id, gateway_id):
    md5hash = hashlib.md5(str(time.time()).encode())
    md5 = md5hash.hexdigest()
    # 下线
    response = {
        "timestamp": int(round(time.time() * 1000)),

        "mid": md5,
        "deviceId": device_id,
        "expire": 60000,
        "param": {"event": "sync-failer",
                  "data": {
                      "cpuAlm": "85",
                      "memAlm": "90",
                      "diskAlm": "95"
                  }}}
    topic = '/v1/{}/service/event'.format(gateway_id)
    print("reply:", topic, '\n', response, '\n\n')
    client.publish(topic,
                   payload=json.dumps(response), qos=0,
                   retain=False)


def publish_device_event_upload_message(client, device_id, gateway_id):
    md5hash = hashlib.md5(str(time.time()).encode())
    md5 = md5hash.hexdigest()
    # 下线
    response = {
        "timestamp": int(round(time.time() * 1000)),
        "mid": md5,
        "deviceId": device_id,
        "expire": 60000,
        "param": {
            "event": "1001",
            "msg": "",
        }
    }
    topic = '/v1/{}/device/alarm/event'.format(gateway_id)
    print("reply:", topic, '\n', response, '\n\n')
    client.publish(topic,
                   payload=json.dumps(response), qos=0,
                   retain=False)


def publish_device_time_sync_request(client, device_id, gateway_id):
    md5hash = hashlib.md5(str(time.time()).encode())
    md5 = md5hash.hexdigest()
    # 下线
    response = {
        "timestamp": int(round(time.time() * 1000)),
        "mid": md5,
        "deviceId": device_id,
        "expire": 60000,
    }
    topic = '/v1/{}/device/time/request'.format(gateway_id)
    print("reply:", topic, '\n', response, '\n\n')
    client.publish(topic,
                   payload=json.dumps(response), qos=0,
                   retain=False)


def publish_device_file_upload(client, device_id, gateway_id):
    md5hash = hashlib.md5(str(time.time()).encode())
    md5 = md5hash.hexdigest()
    # 下线
    response = {
        "timestamp": int(round(time.time() * 1000)),
        "mid": md5,
        "deviceId": device_id,
        "expire": 60000,
        "param": {"file":
                      {"md5": "md5",
                       "url": "url",
                       "name": "sdfsdf.mp4",
                       "size": 123
                       }
                  }}
    topic = '/v1/{}/service/file'.format(gateway_id)
    print("reply:", topic, '\n', response, '\n\n')
    client.publish(topic,
                   payload=json.dumps(response), qos=0,
                   retain=False)


def repeat_publish_invalid_data(client, gateway_id):
    topic = '/v1/{}/device/alarm/event'.format(gateway_id)
    for i in range(1000):
        print(i, "reply:", "invalid_data")
        client.publish(topic, payload=json.dumps("invalid_data"), qos=0, retain=False)


def repeat_publish_not_belong_data(client, gateway_id, device_id):
    md5hash = hashlib.md5(str(time.time()).encode())
    md5 = md5hash.hexdigest()
    # 下线
    response = {
        "timestamp": int(round(time.time() * 1000)),
        "mid": md5,
        "deviceId": device_id,
        "expire": 60000,
        "param": {"file":
                      {"md5": "md5",
                       "url": "url",
                       "name": "sdfsdf.mp4",
                       "size": 123
                       }
                  }}
    topic = '/v1/{}/service/file'.format(gateway_id)
    print("reply:", topic, '\n', response, '\n\n')
    for i in range(1000):
        print(i, "reply:", "not_belong_data")
        client.publish(topic, payload=json.dumps(response), qos=0, retain=False)


if __name__ == '__main__':
    password = "W+F7EZPBtDLDSN/DfiqEeZOfsbz9DNx5jSUhGQNitv4oXINkvv8OesCR5/c9HRfG"
    client_id = "1564864858657689600"
    username = "1564864858657689600&1663725858465a"
    # with ThreadPoolExecutor(max_workers=1000) as executor:
    #     rst = []
    #     for i in range(1000):
    #         rst.append(executor.submit(client_loop, "localhost", 1883))
    # client_loop("localhost", 1883)
    function_list = [publish_service_event_upload_message, publish_device_event_upload_message,
                     publish_service_data_upload_message, publish_device_data_upload_message,
                     publish_device_file_upload, publish_device_time_sync_request, publish_offline_message]

    client_loop("localhost", 1883, client_id, username, password)
    time.sleep(109)
    pass
