# -*- coding: utf-8 -*-
"""
Created on Tue May 21 09:50:14 2019

@author: jialianl
"""
from functools import reduce



#_代表无关临时变量,即第二个变量不用
# range(n - 2)提供reduce和map的计算次数
def fib1(n:int) ->int:
    return reduce(lambda x, _:x + [x[-1] + x[-2]], range(n - 2),[0,1])[n-1]

def fib2(n:int) ->int:
    fib_list = [0, 1]
    #map是惰性运算，此处使用any的目的是使map执行，不然fib_list值不会变
    any(map(lambda _: fib_list.append(sum(fib_list[-2:])),
            range(n-2)))

    return fib_list[n-1]

#使用生成器，节省内存资源
def fib3(n:int):
    a = 1
    b = 0
    for i in range(n):
        yield b
        a,b = a+b,a


if __name__ == "__main__":

    #也可是使用next来获取生成器的值
    for i in fib3(10):
        print(i)

    print()

    print(fib2(10))

    print(fib1(10))

