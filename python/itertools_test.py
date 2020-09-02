from itertools import *

# itertools 中很多操作普通列表也能做，不过他主要针对迭代器
list(permutations('ABC', 3))

list(combinations('ABC', 2))

list(product('ABC', '123'))

list(product('ABCD', repeat=2))

# 不考虑顺序的组合
combinations_with_replacement('ABCD', 2) 

list(chain('ABC', 'DEF'))

list(repeat(10, 3))

# 右侧为0不输出
list(compress('ABCDEF', [1,0,1,0,1,1]))

# 循环无限迭代
t = cycle('ABCDEFG')
for i in range(100):
    print(next(t))

    
# 从10开始计数,无限迭代
for i in count(10):
    print(i)
    if i >100:
        break
        
        

list(zip_longest('ABCD', 'xy', fillvalue='-'))

# 在条件为false之后的第一次, 返回迭代器中剩下来的项. -2 会被返回
list(dropwhile(lambda x:x<1, [ -1, 0, 1, 2, 3, 4, 1, -2 ]))

list(product('ABCD', repeat=2))

a = ['aa', 'ab', 'abc', 'bcd', 'abcde']
for i, k in groupby(a, len):
    print i, list(k)