#尾递归优化
def cal_1(seq):
    if len(seq) == 1:
        return seq[0]
    head,*taiseq = seq
    return head+cal_1(taiseq)

def cal_2(seq):
    print(seq)
    if len(seq) == 1:
        return seq[0]
    
    #注意这种写法，很有意思
    first,second,*args = seq
    seq[0] = first + second
    seq.pop(1)
    return cal_2(seq)

#闭包，装饰器
def log(func):
    def wrapper(*args, **kw):
        
        #括号可以换行
        print('call %s():'
              % func.__name__)
        
        return func(*args, **kw)
    return wrapper

#@log修饰器
@log
def now(seq):
    t = [ i for i in map(lambda x:x*x,seq)]
    print(t)
     
if __name__ == "__main__":
    
    print("------------------------")
    print(cal_1(range(10)))
    
    print("------------------------")
    #[i for i in range(10)] 等价于 list(range(10))
    #生成器
    x = cal_2([i for i in range(10)])
    print(x)
    print("------------------------")
    f=now
    f([1,2,3])
    
