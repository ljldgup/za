import sys
import redis
import random
from threading import Thread
import time

names=['a','b','c','d']

def init_item(conn, num):
    conn.set('product_num', num)
    conn.delete('name_list')

def buy_without_lock(conn):
    num = int(conn.get('product_num'))
    while (num > 0):
        i = random.randint(0,3)
        conn.decr('product_num')
        conn.lpush('name_list', names[i])
        num = int(conn.get('product_num'))
    conn.close()


#wathc 适合不频繁变动的，不然效率低   
def buy_with_watch(conn):
    pipe = conn.pipeline()
    num = int(conn.get('product_num'))

    while (num > 0):
        i = random.randint(0,3)
        pipe.watch("name_list", "product_num")
        pipe.multi()
        pipe.decr('product_num')
        pipe.lpush('name_list', names[i])
        pipe.execute()
        num = int(conn.get('product_num'))
    conn.close()

#此种线程多了以后性能很差
def buy_with_setnx_lock(conn):
    num = int(conn.get('product_num'))
    while (num > 0):
        t = time.time()
        #去除数据比较之前要进行处理
        if conn.set("lock", t, nx = True, ex = 2) and t == float(conn.get("lock")): 
            #枷锁后一定要在比较一次资源，这点多线程中很重要
            # print(num)
            if num == int(conn.get("product_num")):
                i = random.randint(0,3)
                conn.decr('product_num')
                conn.lpush('name_list', names[i]) 
            conn.delete("lock")
        num = int(conn.get('product_num'))
    conn.close()

if __name__ == "__main__":
    #这里db参数类似mysql database 不一样数据隔离
    connect = redis.Redis(host='localhost',port=16379,db=0)
    nums = int(sys.argv[1])
    threads_nums = int(sys.argv[2])
    func = (buy_without_lock, buy_with_watch, buy_with_setnx_lock)[int(sys.argv[3])]
    #用法 python redisLock.py 10 3000 1
    #主要影响的是并发数量并发数量越大，结果偏差越大

    print("products num:" + sys.argv[1])
    print("threads_num:" + sys.argv[2])
    print("saling.")

    init_item(connect, nums)
    start_time=time.time()
    for i in range(threads_nums):
        Thread(target=func, args=(redis.Redis(host='localhost',port=16379,db=0),)).start()

    num = int(connect.get('product_num'))
    while num > 0:
        time.sleep(0.1)
        num = int(connect.get('product_num'))
    print("product_num left:" + str(num))
    print("customers name length:" + str(connect.llen("name_list")))
    print("time:" + str(time.time() - start_time))
    connect.close()
