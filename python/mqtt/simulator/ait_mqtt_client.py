import hashlib
import json
import random
import time
import traceback
from concurrent.futures import ThreadPoolExecutor
from functools import reduce

from paho.mqtt.client import Client

from config.common_config import common_config
from config.device_config import device_config
from config.logging_config import simulator_logger
from models.gateway_children_model import find_all_gateway_children, add_gateway_children
from protocol import cloud_edge_protocol
from protocol.cloud_edge_protocol import schedule_publisher


class AitMqttClient:
    def __init__(self, gateway_id: str, username: str, password: str,
                 device_config, on_connect=None, on_message=None, on_disconnect=None):
        self.gateway_id = gateway_id
        self.username = username
        self.password = password
        self.device_config = device_config

        # 重连会大量占用线程
        self.paho_client = Client(client_id=gateway_id, reconnect_on_failure=False)  # ClientId
        self.paho_client.username_pw_set(username, password)  # 用户名 密码
        self.paho_client.on_connect = self.on_connect_wrap(on_connect)
        self.paho_client.on_message = self.on_message_wrap(on_message)
        self.paho_client.on_disconnect = self.on_disconnect_wrap(on_disconnect)
        self.paho_client.reconnect_delay_set(1, 1)
        self.get_children_device()

    def get_children_device(self):
        if self.gateway_id in self.device_config['childrenInfo']:
            self.children_config_hash = hashlib.md5(
                json.dumps(self.device_config['childrenInfo'][self.gateway_id]).encode('utf-8')).hexdigest()
            children = find_all_gateway_children(self.gateway_id, self.children_config_hash)
        else:
            children = []

        self.gateway_children_map = {child.device_id: child for child in children}

    def set_children_device(self, gateway_children_map: dict):
        self.gateway_children_map = gateway_children_map
        add_gateway_children(list(gateway_children_map.values()))

    def connect(self, host: str, port: int):
        try:
            self.paho_client.connect(host, port)
            self.paho_client.loop_start()
        except:
            traceback.print_exc()

    def on_connect_wrap(self, function):
        def on_connect(client: Client, userdata, flags, rc):
            simulator_logger.info("device {} connected with result code {}".format(self.gateway_id, str(rc)))

            if function:
                function(self, userdata, flags, rc)

        return on_connect

    def on_message_wrap(self, function):
        def on_message(client: Client, userdata, msg):
            simulator_logger.info("gateway {} receive message, topic: {}, body: {}".format(
                self.gateway_id, msg.topic, msg.payload.decode("utf-8")))
            if function:
                function(self, msg)

        return on_message

    def on_disconnect_wrap(self, function):
        def on_disconnect(client: Client, userdata, msg):
            simulator_logger.info("device {} disconnect, code {} ".format(self.gateway_id, msg))
            if function:
                function(self, userdata, msg)

        return on_disconnect

    def publish(self, **kwargs):
        self.paho_client.publish(**kwargs)


def get_device_count():
    gateway_count = len(device_config['gatewayInfo'])
    plus = lambda a, b: a + b
    children_count = reduce(plus,
                            map(lambda children_config:
                                reduce(plus,
                                       map(lambda config: config["number"],
                                           children_config)),
                                device_config['childrenInfo'].values()))
    return gateway_count + children_count


if __name__ == '__main__':
    # password = "fSw8RwMDjr8cj+NOAk7p6iZb7v5UQpl4nIpjyoGNBKNVFgXJ6cVlhbHClZ9oBSag",
    # clientId = "1564786985231405056",
    # username = "1564786985231405056&1663642037784"
    # mqtt_client = AitMqttClient(client_id, username, password)
    # mqtt_client.connect("localhost", 1883)

    device_count = get_device_count()
    common_config["device"]["publish_possibility"] = common_config["device"]["publish_number_each_round"] / device_count

    clients = []
    connect_per_times = common_config["device"]["connect_number_each_turn"]
    with ThreadPoolExecutor(max_workers=connect_per_times) as executor:
        count = 0
        connected_count = 0
        for login_info in device_config['gatewayInfo'].values():
            mqtt_client = AitMqttClient(login_info['clientId'], login_info['username'], login_info['password'],
                                        device_config, cloud_edge_protocol.on_connect,
                                        cloud_edge_protocol.reply_msg)
            mqtt_client.connect(common_config['mqttServer']['host'], common_config['mqttServer']['port'])
            clients.append(mqtt_client)

            count += 1
            if count == connect_per_times:
                connected_count += count
                count = 0
                simulator_logger.info("connected " + str(connected_count))
                time.sleep(common_config["device"]['connect_interval_seconds'])

        simulator_logger.info("connect finished, total " + str(connected_count))

        schedule_publisher(clients)
        time.sleep(10000)
