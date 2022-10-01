# pip install memory_profiler  -i https://mirrors.aliyun.com/pypi/simple/


import time

from memory_profiler import profile


@profile(precision=4) # 在需要做性能分析的函数前面加装饰器 @profile
def my_func():
    a = [1] * (10 ** 6)
    b = [2] * (2 * 10 ** 7)
    time.sleep(10)
    del b
    del a
    print("+++++++++")

if __name__ == '__main__':
    my_func()