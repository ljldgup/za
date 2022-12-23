import time
import random


def timer(func):
    def wrapper(*args, **kw):
        t = time.time()
        #括号可以换行
        rst = func(*args, **kw)
        print( "运行时间：" + str(time.time() - t) )
        return rst
    return wrapper


@timer
def test():
    sum1 = 0
    r = random.randint(10, 13)
    i = j = -1
    while( i < 40000 + r):
        i += 1
        while (j < 40000):
            j += 1
            sum1 += i*j

        j = 0

    print(sum1)

if __name__ == "__main__":
    test()
