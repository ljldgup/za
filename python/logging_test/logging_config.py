import logging
# 默认的warning级别，只输出warning以上的
# 使用basicConfig()来指定日志级别和相关信息
import queue
import sys
from logging.handlers import TimedRotatingFileHandler, QueueHandler, QueueListener

from config.common_config import common_config

logging.basicConfig(level=logging.INFO  # 设置日志输出格式
                    # , filemode="w"  # 文件的写入格式，w为重新写入文件，默认是追加
                    , format="%(asctime)s [%(levelname)s] %(filename)s:%(lineno)s - %(message)s"
                    # 日志输出的格式
                    # -8表示占位符，让输出左对齐，输出长度都为8位
                    , datefmt="%m-%d %H:%M:%S"  # 时间输出的格式
                    )

formatter = logging.Formatter("%(asctime)s [%(levelname)s] %(filename)s:%(lineno)s - %(message)s", "%m-%d %H:%M:%S")

log_file_handler = TimedRotatingFileHandler(when=common_config["log"]["rotate_time_unit"],
                                            filename=common_config["log"]["path"])
log_file_handler.setFormatter(formatter)
log_file_handler.setLevel(common_config["log"]["level"]['file'])

console_handler = logging.StreamHandler(sys.stdout)
console_handler.setLevel(level=common_config["log"]["level"]['console'])
console_handler.setFormatter(formatter)

que = queue.Queue(100000)
queue_handler = QueueHandler(que)
listener = QueueListener(que, log_file_handler, console_handler, respect_handler_level=True)
listener.start()

simulator_logger = logging.getLogger('mylogger')

simulator_logger.addHandler(queue_handler)
# simulator_logger.addHandler(console_handler)
# simulator_logger.addHandler(log_file_handler)
simulator_logger.propagate = False

# 按秒统计 awk '{record[$2]+=1}END{for(time in record){print time,record[time]}}' demo.log |sort -k1
# 按网关统计 awk '{print $8}'  demo.log|grep '/'|awk  -F '/' '{record[$3]+=1}END{for(time in record){print time,record[time]}}'
if __name__ == '__main__':
    # logging.debug("logging debug log.")
    # logging.info("logging info log.")
    # logging.warning("logging warning log.")
    # logging.error("logging error log.")
    # logging.critical("logging critical log.")
    simulator_logger.debug("simluator_logger debug log.")
    simulator_logger.info("simluator_logger info log.")
    simulator_logger.warning("simluator_logger warning log.")
    simulator_logger.error("simluator_logger error log.")
    simulator_logger.critical("simluator_logger critical log.")
