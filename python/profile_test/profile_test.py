import profile
import pstats


def a():
    sum = 0
    for i in range(1, 10001):
        sum += i
    return sum

def b(c):
    sum = 0
    for i in range(1, 100):
        sum += a()
    return sum + c

if __name__ == "__main__":
    c=1
    profile.run("b(c)",'result')
    pstats.Stats('result').sort_stats(-1).print_stats()
    '''
        ncall：函数运行次数tottime： 函数的总的运行时间，减去函数中调用子函数的运行时间

    第一个percall：percall = tottime / nclall

        cumtime:函数及其所有子函数调整的运行时间，也就是函数开始调用到结束的时间。

    第二个percall：percall = cumtime / nclall
    
    看结果的时候先看cumtime,找占用最多的函数，再去找下面的函数各自的cumtime，如果调用函数占用不多，则看当前函数自身是否可以优化
    '''
