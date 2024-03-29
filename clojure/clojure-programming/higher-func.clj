﻿;函数式编程
;map多多个序列操作相当于将同位置拼成一个序列，然后调用，最短结束，就结束过程
(map (fn[ & args] (reduce + args )) '(1 2 3 4) '(4 5 6) '(1 4 5))
(map #(reduce + %&) '(1 2 3) '(4 5 6) '(1 4 5))

;flatmap
(mapcat identity '((1 2 3) (4 5 6)))
;map成vector注意内层没变
(mapv identity '((1 2 3) (4 5 6)))

;mapcat 等价(apply concat (map .. 
;mapv 等价 (vec (map 应为vector是数组，所以应该不是惰性化实现
;filterv同理

(map inc (range 10)) 
((map inc) (range 10))

;; Used without a collection, map will create a transducer:
(def xf (map inc))
(transduce xf conj (range 5))
;; => [1 2 3 4 5]

;transduce 转换器+累加器+过滤器
(def xf (comp (filter odd?) (take 10)))
(transduce xf conj (range))
;;=> [1 3 5 7 9 11 13 15 17 19]
(transduce xf + (range))
;; => 100


(filter odd? (range 10))
((filter odd?) (range 10))


;将下标作为索引
(map-indexed vector "foobar")
(map-indexed hash-map "foobar")

;两两操作的都可以考虑reduce
(reduce max '(1 2 3))

;*+查看源码，入参为空会自动给值
(reduce * ())
(reduce + ())

;partial 类似克里化，克里化要在所有参数都齐了才求值
;partial 配合关键字 返回函数， 比匿名表达式好用些,如下
(def only-strings (partial filter string?))
(only-strings '("a" 5 "b" 6))

;行转列效果，map多个序列长度不同会按照最短的来
(map vector (repeat 1) '(1 2 3 4) '(3 2 1))


;comp 函数组合,和的复数转字符串
(def negated-sum-str (comp str - +))
(negated-sum-str 1 2)
注意这个函数是从右往左执行的

(compare 1 2)
(def negated-compare (comp - compare))
(negated-compare 1 2)

 ((comp (filter odd?) (map inc) (take 5)) (range 100))


;通过require加别名，  

(require '[clojure.string :as str])
(def camel->keyword (comp keyword 
                          str/join 
                          (partial interpose \-) 
                          (partial map str/lower-case)
                          #(str/split % #"(?<=[a-z])(?=[A-Z])")))
(camel->keyword "camelStyle")

interpose 在列表中没量过之间插入
(interpose '- '("a" "b" "c"))
;这个join只穿列表就是简单拼接，相当于分割符是""
(str/join ("a" "b" "c"))
(str/join '- ("a" "b" "c"))


(defn print-logger
    [writer]
    #(println %))

(require 'clojure.java.io)
(defn file-logger 
    [file]
    #(with-open [f (clojure.java.io/writer file :appedn true)]
        ((print-logger f) %)))

(def log->file (file-logger "message.log"))      

;memoize可用于纯函数缓存，这里因为随机数不是纯函数，所以结果不对    
;repeatedly 用于函数，会调用参数，repeat用于实体                
(repeatedly 10 (partial rand-int 10))
(repeatedly 10 (partial (memoize rand-int) 10)) 

lambda也可配合memoize使用,可以实现惰性求值槽位的效果
(def mem_fn (memoize (fn[] (rand-int 10))))
(mem_fn)


apply 和 直接括号执行的区别在于可以用容器解包为参数
(apply * (repeat 19 3))
直接(* (repeat 19 3))就不行 
经常用于不定参数截取后，递归调用

apply可以对多个参数调用，不需要写成lambda， edges会被解包放在后面参数上不是一个参数
(apply min-key #(nth % 2) '((1 0 62) (2 0 57) (2 1 50)))
等效
(min-key #(nth % 2) '(1 0 62) '(2 0 57) '(2 1 50))
;这个不行，后面作为一个元素处理
(min-key #(nth % 2) '((1 0 62) (2 0 57) (2 1 50)))

eval能执行符号表
(eval '(+ 1 2))
字符串需要read-string
(eval (read-string "(+ 1 2)"))




;iterate[f x] 返回x, (f x), (f (f x))的惰性序列,可以代替(def x (cons 1 (map fn x)))这样的流
(take 10 (iterate #(/ % 2) 1))
;整数数列，等价(range)
(iterate inc 1)

;两种基于流的斐波拉契实现

;这个函数返回两个数
(defn fib1 []
  (map first (iterate (fn [[a b]] [b (+ a b)]) [0N 1N])))

;这里通过(map + fib2 (rest fib2))实现交替的两个数相加，这里还可以扩展到任意个
(def fib2 (cons 1 (cons 2 (lazy-seq (map + fib2 (rest fib2))))))

doall 将惰性序列取出
(doall (range 3))


identity直接返回入参

;sort只能传入比较器
(sort (repeatedly 10 #(rand-int 20)))
(sort < (repeatedly 10 #(rand-int 20)))

;sort-by 使用函数进行转换后再排序
(sort-by  str (repeatedly 10 #(rand-int 20)))

;complement 取反，注意这里返回的是函数，可以直接高阶函数的参数
(sort (complement <) (repeatedly 10 #(rand-int 20)))
(sort < (repeatedly 10 #(rand-int 20)))

;sorted-map, sorted-map-by, sorted-set, sorted-set-by 类似红黑树的效果
;clojure里貌似没有自带的优先级队列，排序只能考虑用这个

;keep类似于map，但是去掉nil
(keep identity '(1 2 5 nil))

;去重
(distinct '(1 2 3 1 2 3))
;distinct可以惰性化，去重的时候只要可前面比较就可以了
(take 3 (distinct '(1 2 3 1 2 3)))
;distinct可以根据seq，vec的内容进行去重，但是sort确不能排序。。。python支持后者
(distinct (repeatedly 100 #(vector (rand-int 2) (rand-int 2))))
(distinct (repeatedly 100 #(vector (rand-int 2) (rand-int 2))))

;group-by类似java
(group-by #(mod % 3) (range 10))
;group-by直接用聚类函数的值作为key，没必要提前算出来聚类的列！！

;partition-by拆分流，返回是处拆分流
 (partition-by #(= 3 %) [1 2 3 4 5])
 
;shuffle随机打乱
(->> (partial shuffle [1 2 3]) (repeatedly 5))
 
;frequencies统计频次
(frequencies ['a 'b 'a 'a])

cumXxxx的效果
(reductions + (range 1 10))
(reductions * (range 1 10))
(reductions conj [] '(1 2 3))
