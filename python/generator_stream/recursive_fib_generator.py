
# 等效clojure 中 (def fib (cons 1 (map + fib next(fib)))
def fib():
    #注意这个yield必须放在递归之前，否则会造成无限
    yield 1
    t = fib()
    current = 1
    while True:
        previous = next(t)
        yield current
        current += previous

if __name__ == '__main__':
    t = fib()
    print([next(t) for _ in range(10)])