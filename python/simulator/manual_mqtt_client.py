import datetime
import hashlib
import json
import random
import time
import uuid
from urllib import request

import paho.mqtt.client as mqtt

from config.logging_config import simulator_logger


def client_loop(host: str, port: int, client_id: str, username: str, password: str):
    client = mqtt.Client(client_id, reconnect_on_failure=False)  # ClientId
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
    simulator_logger.info("Connected with result code " + str(rc))
    # repeat_publish_invalid_data(client, client_id)
    # repeat_publish_not_belong_data(client, device_id)
    # repeat_publish_invalid_data(client, device_id)
    # client.subscribe("test")


def on_disconnect(client: mqtt.Client, userdata, msg):
    simulator_logger.info("disconnect " + str(msg))


def on_message(client: mqtt.Client, userdata, msg):
    simulator_logger.info(datetime.datetime.now())
    simulator_logger.info("receive:", msg.topic + " " + msg.payload.decode("utf-8"))
    reply_command(client, msg)


def reply_command(client, msg):
    decode_payload = json.loads(msg.payload.decode())
    topic = str(msg.topic)

    if topic.endswith("command"):
        pass
        # publish_command_reply(client, decode_payload, topic)
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
    simulator_logger.info("reply:", topic, response)
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
    topic = '/v1/{}/device/offline/data'.format(gateway_id)
    simulator_logger.info("reply:", topic, response)
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
        "param": {
            "data": {
                "p1": 12,
            }
        }
    }

    if param:
        response['param'] = param

    topic = '/v1/{}/service/data'.format(gateway_id)
    simulator_logger.info("reply:", topic, response)
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
    simulator_logger.info("reply:", topic, response)
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
                      "p1": "6",
                  }}}
    topic = '/v1/{}/service/event'.format(gateway_id)
    simulator_logger.info("reply:", topic, '\n', response, '\n\n')
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
    simulator_logger.info("reply:", topic, '\n', response, '\n\n')
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
    simulator_logger.info("reply:", topic, '\n', response, '\n\n')
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
    simulator_logger.info("reply:", topic, '\n', response, '\n\n')
    client.publish(topic,
                   payload=json.dumps(response), qos=0,
                   retain=False)


def publish_child_device_register(client, device_id, gateway_id):
    md5hash = hashlib.md5(str(time.time()).encode())
    md5 = md5hash.hexdigest()
    # 下线
    response = {
        "mid": 1000000000020028,
        "timestamp": int(round(time.time() * 1000)),
        "expire": -1,
        "deviceId": device_id,
        "param": {
            "deviceInfos": [
                {
                    "parentNodeId": "test4fsjNode2Node2Node2",
                    "nodeId": "test4fsjSub2Sub2Sub2",
                    "name": "test4sub2sub2sub2",
                    "description": "子子设备",
                    "modelId": "test2"
                },
                {
                    "parentNodeId": "test4fsjgatewaygatewaygateway",
                    "nodeId": "test4fsjNode2Node2Node2",
                    "name": "test4children2children2children2",
                    "description": "边下子设备2",
                    "modelId": "product2"
                },
                {
                    "parentNodeId": "test4fsjgatewaygatewaygateway",
                    "nodeId": "test4fsjNode1Node1Node1",
                    "name": "test4children1children1children1",
                    "description": "边下子设备1",
                    "modelId": "product2"
                },
                {
                    "parentNodeId": "notExistnotExistnotExist",
                    "nodeId": "test4fsjNode3Node3Node3",
                    "name": "test4children3children3children3",
                    "description": "边下子设备3",
                    "modelId": "product2"
                }
            ]
        }
    }
    topic = '/v1/{}/topo/add/request'.format(gateway_id)
    simulator_logger.info("reply:", topic, '\n', response, '\n\n')
    client.publish(topic,
                   payload=json.dumps(response), qos=0,
                   retain=False)


def publish_device_children_online(client, device_id, gateway_id):
    response = {
        "mid": "2a76839a6e7f42c7b5149bccdf198408",
        "timestamp": 1667285094451,
        "expire": -1,
        "deviceId": "1579640765576941568",
        "param": {
            "nodeStatuses": [
                {
                    "deviceId": "1579678123722575872",
                    "status": "online"
                },
            ]
        }
    }
    # {"timestamp": int(round(time.time() * 1000)),
    #             "mid": str(uuid.uuid4()),
    #             "deviceId": device_id,
    #             "expire": 600000,
    #             'param': {
    #                 "nodeStatuses":
    #                     [{'status': 'online', 'deviceId': device_id}]}
    #             }

    topic = '/version/{}/topo/update/request'.format(gateway_id)
    client.publish(topic,
                   payload=json.dumps(response), qos=0,
                   retain=False)


def publish_device_children_offline(client, device_id, gateway_id):
    response = {"timestamp": int(round(time.time() * 1000)),
                "mid": str(uuid.uuid4()),
                "deviceId": device_id,
                "expire": 600000,
                'param': {
                    "nodeStatuses":
                        [{'status': 'offline', 'deviceId': device_id}]}
                }

    topic = '/version/{}/topo/update/request'.format(gateway_id)
    client.publish(topic,
                   payload=json.dumps(response), qos=0,
                   retain=False)


def repeat_publish_invalid_data(client, gateway_id):
    topic = '/v1/{}/device/alarm/event'.format(gateway_id)
    for i in range(1000):
        simulator_logger.info(i, "reply:", "invalid_data")
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
    simulator_logger.info("reply:", topic, '\n', response, '\n\n')
    for i in range(100000):
        simulator_logger.info(i, "reply:", "not_belong_data")
        client.publish(topic, payload=json.dumps(response), qos=0, retain=False)


login_authenticate_url = "http://{}:{}/test/device/login_message"
headers = {'Accept-Charset': 'utf-8', 'Content-Type': 'application/json'}


def get_authentication(device_id_list: list, env: str):
    if env == 'dev':
        get_authentication_by_http(device_id_list, "")


def get_authentication_by_http(device_id_list: list, host: str, port: str):
    req = request.Request(url=login_authenticate_url.format(host, port),
                          data=json.dumps(device_id_list).encode(),
                          headers=headers,
                          method='POST')
    return json.loads(request.urlopen(req).read())['result']


if __name__ == '__main__':

    # publish_device_children_online(client, device_id, client_id)
    # publish_service_data_upload_message(client, device_id, client_id)
    # publish_service_event_upload_message(client, device_id, client_id)
    # publish_device_file_upload(client, device_id, client_id)
    # publish_offline_message(client, device_id, client_id)

    password = "onf/1ly4YrLd9b6bmR6E9ngArr+XQYxqXl89jlGoSurM5lt4wjszgfos/llGiZXC"
    client_id = "1592782335674253312"
    device_id = '1592782335674253312'
    username = "1592782335674253312&1668583962868"
    client = client_loop("localhost", 1883, client_id, username, password)
    # # client.disconnect()
    # while True:
    #     try:
    #         client = client_loop("10.233.90.50", 1883, client_id, username, password)
    #         time.sleep(random.randint(20, 40))
    #         client.disconnect()
    #         time.sleep(random.randint(20, 40))
    #     except:
    #         pass

