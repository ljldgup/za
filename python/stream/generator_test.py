import itertools

if __name__ == '__main__':
    # 流合并
    for i in itertools.chain(range(10), range(100, 110)):
        print(i)

    #循环
    cycle_10 = itertools.cycle(range(10))
    for i in range(20):
        print(next(cycle_10))


