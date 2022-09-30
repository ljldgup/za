# 导入socket模块
import socket
from time import sleep

import numpy as np

if __name__ == '__main__':

    # 创建TCP类型的socket
    c = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # 建立到指定IP地址,端口的TCP连接
    c.connect(('127.0.0.1', 8997))
    for i in range(1000):
        # print(c.recv(1024))
        print(i)
        c.sendall(np.random.randint(0, 1000, size=(100, 100)).tobytes())
