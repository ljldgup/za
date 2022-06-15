﻿
coljure相除默认分数，
可以通过float, double获得小数
也可以通过小数点.
(/ 1 2.)
(/ 1 1.5)

;保留小数点
(with-precision 2 (/ 1 3.0))

(quot 22 7) ;整除
(rem 22 7) (mod 22 7) ;余数
 
不等于是not= 
(not=  1 2)



;基本的特殊符号
; &不定长参数  apply和直接调用等效 count 尺寸
(defn average [& args]
    (/ (apply + args) (count args)))
(average 1 2 3 4)



;双向引用可以用def定义一个空变量，后面再扩充
(def a)
(defn b[x](if (> x 0) (a (dec x)) (println x)))
(defn a[x] (println 'a x) (b (dec x)))
(b 10)

;这种方法也可以用来设计的时候预定义函数



;#""表示正则, re-开头的几个正则操作
(re-seq #"a.+?b" "adbacb")




lamdba
(fn[args]body)
(#(inc %) 1)
(#(+ %1 %2) 1 2)
(#(reduce + %&) 1 2 3)

;编译的时候会根据%的编号，定义入参个数，前两个通不过
(#(+ %1) 1 2)
(#(+ %1 1) 1 2)
(#(+ 1 %2) 1 2)
;reduce可以通过上面这种办法直接使用外部变量累加，很适合java的数据结构
 
 

;#_注释忽略后面一个clojure形式
'(1 2 3 #_(* 1 2) 4)

;quote 数据结构返回的是数据结构，内部表达式不求值
(list? '(+ x x))

;let解构list map
(let [[x & rest_args] '("123" 2 3 "4")]
    (println x)
    (println rest_args))



;多重解包, _占位类似python
(let [ [_ [_ target]] [[1 2] [3 4]]] target)
            
            

;函数参数可以直接用let形式解构
((fn[[x & rest_args]] 
    (println rest_args)) 
 '("123" 2 3 "4"))

defn 后面可以直接跟多个函数体，实现重载,注意每个重载都要用括号包起来
(defn test
  ([x] (println x))
  ([x y] (println x y)))

;通过索引关键字进行解构，可以用于list map等
;3索引 :as返回自己
(let [{b 3, :as args} '("123" 2 3 "4")]
    (println b)
    (println args))
    
(let [{a :a} {:a "1", "b":2}]
    (println a))  

;email join_date 关键字参数， :or定义默认值 join_date 
;email join_date 关键字参数， :or定义默认值 join_date 
;java.util.Date. 貌似和 new等效
(defn make_user
    [username & {:keys [email join_date]
                :or {join_date (java.util.Date.)}}]
    {:username username
    :join_date join_date
    :email email
    :exp_date (java.util.Date. (long (+ 2.592e9 (.getTime join_date))))})
    
(make_user "bob")
(make_user "bob" :join_date (java.util.Date. 111 0 1))

;recur可以在不消耗堆栈的情况下，
;转移到最近的函数定义或loop定义的头部
(defn print-n1[x n]
    (if (> n 0)
        (do (print x)
            (recur x (dec n)))))

匿名函数递归
(def print-n2 (fn[x n]    
                (if (> n 0)
                (do (println x)
                    (recur x (dec n))))))
        
(def print-n2 (fn[x n]    
                (if (> n 0)
                (do (println x)
                    (recur x (dec n))))))

loop+recur实现可变的局部变量
(loop [x 10]
    (if (> x 1)
        (do
            (println x)
            (recur (dec x)))))

通过do执行多个表达式
(do
  (println "first")
  (println "second")
  "not return"
  "return")
  
  
  
for each:
(doseq [n [1 2 3]] ; 将列表[1 2 3]中的每一个元素依次绑定到n
  (println n))
  
  
  
deseq实现嵌套  
(doseq [m [1 2], n [3 4]]
  (println
  (str m " + " n " = " (+ m n))))
  
  
for也能实现嵌套,for会将结果作为容器返回
(for [x (range 4 8), y (range 11 13)] [(list x y)])

[]中用配合:when :let，
:when可以避免返回nil元素，
(for [x (range 4 8), y (range 11 13) :when (even? x)] [(list z y)])

:let是因为x，y是笛卡尔乘积，直接z (* x y)无法得到正确结果
(for [x (range 4 8), y (range 11 13) z (* x y)] z )
(for [x (range 4 8), y (range 11 13) :let [z (* x y)]] z )

;any?有任意元素返回true
(any? '(false))
;some任意一个满足表达式为真的元素
(some identity '(false))
(some #(not %) '(false))

or 效果类似，or 全不为真返回false
every? 和 and和上面类同



letfn定义临时函数，避免函数内定义的函数需要递归时的空间污染
(defn outer[x]
    (defn inner [y]
                (if (> y 0)
                    (do (println x)
                        (inner (dec y)))))
    inner)
        
       
(defn letfn-outer[x]
    (letfn [(inner [y]
                (if (> y 0)
                    (do (println x)
                        (inner (dec y)))))]
       inner))
       
(def inner1 (outer 1))
(def inner2 (outer 2))
;结果错误因为递归调用的inner已经被(outer 2)调用时重新定义
(inner1 3)
(inner2 3)

(def inner1 (letfn-outer 1))
(def inner2 (letfn-outer 2))
;结果正确，因为两个inner都是局部函数
(inner1 3)
(inner2 3)

letfn [(x[]...)] 等效于 let [x (fn[]...)]

;recur配合loop实现循环   
(loop [x 0]
    (if (<= x 10) 
        x
        (recur (inc x))))
        
        
;元数据
(def a ^{:created (System/currentTimeMillis)}
        [1 2 3])
(meta a)

case使用
(def x 1)
(case x
    :a (println 'a)
    :b (println 'b)
    (println 'c))
    
;clojure 字符串也可以像python那样迭代
(for [x "xfsdf"] x)