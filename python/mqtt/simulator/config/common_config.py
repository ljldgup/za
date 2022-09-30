import logging

common_config = {
    "mqttServer": {
        "host": "192.168.10.144",
        "port": 1883
    },
    "database": {
        "host": "10.233.3.100",
        "port": 5432,
        "database": "simulator",
        "username": "postgres",
        "password": "Agioe@123"
    },
    "log": {
        "level": {
            # 控制台和文件的日志等级
            "console": logging.ERROR,
            "file": logging.INFO
        },
        "path": "demo.log",
        # 日志文件滚动时间单位 日 时 分 d,h,m
        "rotate_time_unit": "h"
    },
    "device": {
        # 子设备上线后开始上传数据初始间隔
        "init_send_delay_seconds": 2,
        # 数据事件上传间隔
        "publish_interval_seconds": 5,
        # 每次连接网关个数
        "connect_number_each_turn": 20,
        # 网关启动连接间隔
        "connect_interval_seconds": 2,
        # 每次发送数据/事件条数,由发送条数/总设备数得到一个概率，按概率发送,发送数量在该值上下浮动
        "publish_number_each_round": 2500,
    }

}
