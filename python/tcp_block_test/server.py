# _*_ coding:utf-8 _*_
# 服务端
# 导入socket模块
import socket


# Press the green button in the gutter to run the script.
from time import sleep

if __name__ == '__main__':


    # 创建TCP类型的socket
    host = '127.0.0.1'
    port = 8997
    # 建立一个socket对象,AF_INET说明将使用标准的IPv4地址,SOCK_STREAM说明是一个TCP客户端
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((host, port))
    s.listen(2)
    conn, addr = s.accept()  # 创建socket和客户端通信；
    print("Connected by", addr)
    while 1:
        # pass
        #conn.sendall("yes sir".encode())
        sleep(1)
        print(conn.recv(40000))
    # conn.close()
    # conn.sendall('reply')
