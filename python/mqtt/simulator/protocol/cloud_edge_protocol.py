import json
import random
import sched
import time
import traceback
import uuid
from concurrent.futures import ThreadPoolExecutor
from functools import reduce

from config.common_config import common_config
from config.logging_config import simulator_logger
from models.gateway_children_model import GatewayChild

version = 'v1'

handler_map = {}


def publish_mqtt_msg(client, response, topic):
    simulator_logger.info("publish to {}  {}".format(topic, response))
    client.publish(topic=topic, payload=json.dumps(response), qos=0, retain=False)


def get_timestamp():
    return int(time.time() * 1000)


def publish_common_command_reply(client, msg, topic):
    reply = {
        "timestamp": get_timestamp(),
        "mid": msg['mid'],
        "deviceId": msg['deviceId'],
        "expire": 600000,
        "param": {},
        "mgs": "foe疾风欧偶数的时代☺",
        "code": "200"
    }
    topic = topic.replace("command", "reply")
    publish_mqtt_msg(client, reply, topic)


def on_connect(client, userdata, flags, rc):
    try:
        #
        if client.gateway_id not in client.device_config['childrenInfo'] \
                or not client.device_config['childrenInfo'][client.gateway_id]:
            return

        if not client.gateway_children_map:
            publish_device_children_register(client, client.device_config['childrenInfo'][client.gateway_id])
        else:
            publish_device_children_update(client, 'online')
    except:
        traceback.print_exc()


def publish_command_response(client, msg, topic):
    response = {
        "timestamp": get_timestamp(),
        "mid": msg['mid'],
        "deviceId": msg['deviceId'],
        "expire": 600000,
        "param": {},
        "mgs": "foe疾风欧偶数的时代☺",
        "code": "200"
    }
    topic = topic.replace("request", "response")
    publish_mqtt_msg(client, response, topic)


def publish_offline_message(client, device_id):
    # 下线
    response = {
        "timestamp": get_timestamp(),

        "mid": str(uuid.uuid4()),
        "deviceId": device_id,
        "expire": 600000,
        "param": {},
    }
    topic = '/{}/{}/device/offline'.format(version, client.gateway_id)
    publish_mqtt_msg(client, response, topic)


def publish_service_data_upload_message(client, device_id):
    try:
        model_info = get_model_info(client, device_id)

        if 'data' in model_info:
            data_param = model_info['data']
            response = {
                "timestamp": get_timestamp(),

                "mid": str(uuid.uuid4()),
                "deviceId": device_id,
                "expire": 600000,
                "param": data_param,
            }

            topic = '/{}/{}/device/status/data'.format(version, client.gateway_id)
            publish_mqtt_msg(client, response, topic)
    except:
        traceback.print_exc()


def get_model_info(client, device_id):
    if hasattr(client, 'model_info'):
        model_info = client.model_info
    else:
        if device_id == client.gateway_id:
            product_code = client.device_config['gatewayInfo'][device_id]['productCode']
        else:
            product_code = client.gateway_children_map[device_id].product_code

        if product_code in client.device_config['productModel']:
            model_info = client.device_config['productModel'][product_code]
        else:
            model_info = {}
        client.model_info = model_info
    return model_info


def publish_device_data_upload_message(client, device_id):
    try:
        model_info = get_model_info(client, device_id)
        if 'data' in model_info:
            data_param = model_info['data']
            response = {
                "timestamp": get_timestamp(),

                "mid": str(uuid.uuid4()),
                "deviceId": device_id,
                "expire": 600000,
                "param": data_param,
            }

            topic = '/{}/{}/device/status/data'.format(version, client.gateway_id)
            publish_mqtt_msg(client, response, topic)
    except:
        traceback.print_exc()


def publish_service_event_upload_message(client, device_id):
    try:
        model_info = get_model_info(client, device_id)
        if 'event' in model_info:
            event_param = random.sample(model_info['event'], 1)[0]
            response = {
                "timestamp": get_timestamp(),

                "mid": str(uuid.uuid4()),
                "deviceId": device_id,
                "expire": 600000,
                "param": event_param,
            }

            topic = '/{}/{}/service/event'.format(version, client.gateway_id)
            publish_mqtt_msg(client, response, topic)
    except:
        traceback.print_exc()


def publish_device_event_upload_message(client, device_id):
    # 下线
    response = {
        "timestamp": get_timestamp(),
        "mid": str(uuid.uuid4()),
        "deviceId": device_id,
        "expire": 600000,
        "param": {
            "event": "1001",
            "msg": "",
        }
    }
    topic = '/{}/{}/device/alarm/event'.format(version, client.gateway_id)
    publish_mqtt_msg(client, response, topic)


def publish_device_time_sync_request(client, device_id):
    # 下线
    response = {
        "timestamp": get_timestamp(),
        "mid": str(uuid.uuid4()),
        "deviceId": device_id,
        "expire": 600000,
    }
    topic = '/{}/{}/device/time/request'.format(version, client.gateway_id)
    publish_mqtt_msg(client, response, topic)


def publish_device_file_upload(client, device_id):
    # 下线
    response = {
        "timestamp": get_timestamp(),
        "mid": str(uuid.uuid4()),
        "deviceId": device_id,
        "expire": 600000,
        "param": {"file":
                      {"md5": "md5",
                       "url": "url",
                       "name": "sdfsdf.mp4",
                       "size": 123
                       }
                  }}
    topic = '/{}/{}/service/file'.format(version, client.gateway_id)
    publish_mqtt_msg(client, response, topic)


def publish_device_children_register(client, children_info: dict):
    if children_info:
        child_device = reduce(lambda x, y: x + y,
                              map(lambda child:
                                  gen_child_device(child['number'],
                                                   child['productCode'],
                                                   client.gateway_id,
                                                   client.device_config['gatewayInfo'][client.gateway_id][
                                                       'deviceCode']),
                                  children_info))

        client.product_map = {device["nodeId"]: device["modelId"] for device in
                              child_device}

        response = {"timestamp": get_timestamp(), "mid": str(uuid.uuid4()), "deviceId": client.gateway_id,
                    "expire": 600000,
                    'param': {"deviceInfos": child_device}}

        topic = '/{}/{}/topo/add/request'.format(version, client.gateway_id)
        publish_mqtt_msg(client, response, topic)


def gen_child_device(num: int, product_code: str, gateway_id: str, device_code: str):
    child_device = [{"parentNodeId": device_code,
                     "nodeId": "fake_{}_{}".format(gateway_id, code),
                     "name": "fake_{}_{}".format(gateway_id, code),
                     "description": gateway_id + "的模拟子设备",
                     "modelId": product_code} for code in map(lambda n: uuid.uuid4(), range(num))]

    return child_device


def handle_children_register_reply(client, msg):
    date_str = time.strftime('%Y-%m-%d')
    children_map = {info['deviceId']: gen_gateway_children(client, info, date_str) for info in
                    filter(lambda rst: 'statusCode' in rst and rst['statusCode'] == '200', msg["param"]["result"])}
    client.set_children_device(children_map)
    publish_device_children_update(client, 'online')


def gen_gateway_children(client, msg, date_str):
    return GatewayChild(gateway_id=client.gateway_id,
                        parent_node_id=client.gateway_id,
                        node_id=msg['nodeId'],
                        device_id=msg['deviceId'],
                        product_code=client.product_map[msg['nodeId']],
                        hash=client.children_config_hash,
                        date=date_str)


def publish_device_children_update(client, status):
    response = {"timestamp": get_timestamp(), "mid": str(uuid.uuid4()), "deviceId": client.gateway_id, "expire": 600000,
                'param': {
                    "nodeStatuses":
                        [{'status': status, 'deviceId': device.device_id} for device in
                         client.gateway_children_map.values()]}
                }

    topic = '/{}/{}/topo/update/request'.format(version, client.gateway_id)
    publish_mqtt_msg(client, response, topic)


def repeat_publish_invalid_data(client):
    topic = '/{}/{}/device/alarm/event'.format(version, client.gateway_id)
    for i in range(1000):
        simulator_logger.info(i, "reply:", "invalid_data")
        client.publish(topic=topic, payload=json.dumps("invalid_data"), qos=0, retain=False)


def repeat_publish_not_belong_data(client, device_id):
    # 下线
    response = {
        "timestamp": get_timestamp(),
        "mid": str(uuid.uuid4()),
        "deviceId": device_id,
        "expire": 600000,
        "param": {"file":
                      {"md5": "md5",
                       "url": "url",
                       "name": "sdfsdf.mp4",
                       "size": 123
                       }
                  }}
    topic = '/{}/{}/service/file'.format(version, client.gateway_id)
    for i in range(1000):
        simulator_logger.info(i, "reply:", "not_belong_data")
        publish_mqtt_msg(client, response, topic)


def reply_msg(client, msg):
    decode_payload = json.loads(msg.payload.decode())
    topic = str(msg.topic)

    if topic.endswith("command"):
        publish_common_command_reply(client, decode_payload, topic)
    if topic.endswith("/topo/add/response"):
        handle_children_register_reply(client, decode_payload)
    elif topic.endswith("/service/shadow/property"):
        function_index = random.randint(0, len(random_publisher_list) - 1)
        random_publisher_list[function_index](client, decode_payload['device_id'])


random_publisher_list = [publish_service_event_upload_message, publish_device_event_upload_message,
                         publish_service_data_upload_message, publish_device_data_upload_message,
                         publish_device_file_upload, publish_device_time_sync_request, publish_offline_message]

schedule_executor = ThreadPoolExecutor(max_workers=100)


def schedule_publisher(clients):
    schedule_executor.submit(schedule_publish, clients)


def wrap_possible(publish_func):
    def wrapped_func(clients, device_id):
        if random.random() < common_config["device"]["publish_possibility"]:
            publish_func(clients, device_id)

    return wrapped_func


def publish_then_schedule(clients, functions):
    try:
        schedule_executor.submit(schedule_publish, clients)
        for func in functions:
            for client in clients:
                for device_id in client.gateway_children_map.keys():
                    func(client, device_id)
                func(client, client.gateway_id)
    except:
        traceback.print_exc()


wrapped_functions = list(
    map(wrap_possible, [publish_service_event_upload_message, publish_service_data_upload_message]))


def schedule_publish(clients):
    delay = common_config["device"]["publish_interval_seconds"]
    s = sched.scheduler(time.time, time.sleep)  # 生成调度器
    s.enter(delay, 1, publish_then_schedule, (clients, wrapped_functions))
    s.run()


if __name__ == '__main__':
    result = reduce(lambda x, y: x + y,
                    map(lambda child: gen_child_device(child['number'], child['productCode'], "sfsdf"),
                        [{"number": 15, "productCode": "test2"}, {"number": 10, "productCode": "123123123123"}]))
