def test(x):
    def inner(n):
        if n > 0:
            print(x)
            inner(n-1)
    return inner

if __name__ == '__main__':
    test1 = test(1)
    test2 = test(2)
    test2(10)
    test1(10)