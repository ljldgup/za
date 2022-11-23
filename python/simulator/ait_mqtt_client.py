import hashlib
import json
import threading
import time
import traceback
from concurrent.futures import ThreadPoolExecutor, wait
from functools import reduce

from paho.mqtt.client import Client

from config.common_config import common_config
from config.device_config import device_config
from config.logging_config import simulator_logger
from models.gateway_children_model import add_gateway_children, find_all_gateway_children
from protocol import cloud_edge_protocol
from protocol.cloud_edge_protocol import async_direct_publish

time_record = {}

executor = ThreadPoolExecutor(max_workers=100)

lock = threading.Lock()


def log_record(record):
    count_record = {time.strftime("%H:%M:%S", time.localtime(k)): len(v) for k, v in record.items()}
    simulator_logger.info(count_record)


def log_msg_count():
    global time_record
    second = int(time.time())
    if second not in time_record:
        with lock:
            if second not in time_record:
                if len(time_record) > 10:
                    old_time_record = time_record
                    time_record = {}
                    executor.submit(log_record, old_time_record)
            time_record[second] = []

    # time_record[second].append(client.gateway_id)
    time_record[second].append(1)
    # simulator_logger.info("publish to {}  {}".format(topic, msg))


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
            if common_config["log"]["log_device_message"]:
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
        log_msg_count()
        self.paho_client.publish(**kwargs)


def get_device_count(clients):
    children_num = reduce(lambda x, y: x + y,
                          map(lambda clt: len(clt.gateway_children_map.keys()),
                              clients))
    return len(clients) + children_num


def profile_test(clients):
    for i in range(10):
        cloud_edge_protocol.publish_test(clients)


if __name__ == '__main__':
    # password = "fSw8RwMDjr8cj+NOAk7p6iZb7v5UQpl4nIpjyoGNBKNVFgXJ6cVlhbHClZ9oBSag",
    # clientId = "1564786985231405056",
    # username = "1564786985231405056&1663642037784"
    # mqtt_client = AitMqttClient(client_id, username, password)
    # mqtt_client.connect("localhost", 1883)

    clients = []
    connect_per_times = common_config["device"]["connect_number_each_turn"]
    with ThreadPoolExecutor(max_workers=80) as executor:
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

        simulator_logger.info("connect finished, total " + str(len(clients)))

        device_count = get_device_count(clients)
        common_config["device"]["publish_possibility"] = common_config["device"][
                                                             "publish_number_each_round"] / device_count

        time.sleep(common_config["device"]["init_send_delay_seconds"])
        delay = common_config["device"]["publish_interval_seconds"]
        # profile_test(clients)
        results = []
        for i in range(common_config["device"]['publish_times']):
            results.append(executor.submit(async_direct_publish, clients))
            time.sleep(delay)
        wait(results)
        log_record(time_record)
