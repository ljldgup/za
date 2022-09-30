import gevent


def work(n):
    for i in range(n):
        # 获取当前协程
        print(gevent.getcurrent(), i)


if __name__ == '__main__':
    g1 = gevent.spawn(work, 100)
    g2 = gevent.spawn(work, 50)
    g3 = gevent.spawn(work, 50)
    g1.join()
