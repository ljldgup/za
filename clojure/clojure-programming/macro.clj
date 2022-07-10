;常用宏
;doto 将第一个式子的结果加到后面每个列表的最后一个执行
;doto 适合java对象操作
;->>,-> 是将每次计算的结果作为后一个表达式的参数
;->>放在结尾，->放在第二个
(doto 1 (println 1 ) (println 2 ) (println 3))
(->> 1 (println 1 ) (println 2 ) (println 3))
(-> 1 (println 1 ) (println 2 ) (println 3))

;cond-> cond->> 为真的时候执行
(cond-> 1          ; we start with 1
    true inc       ; the condition is true so (inc 1) => 2
    false (* 42)   ; the condition is false so the operation is skipped
    (= 2 2) (* 3))
;some-> some->> 任意不为真就停止

;注意如果需要放在第一个作为函数，reduce就可以直接实现

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(require '(clojure [string :as str]
                   [walk :as walk]))

;postwalk 递归便利一个嵌套列表, 然后反转每一个符号
(defmacro reverse-it [form]
    (walk/postwalk 
        #(if (symbol? %)
            (symbol (str/reverse (name %)))
            %)
        form))

;(inc (inc 1))
(reverse-it (cni (cni 1)))

;macroexpand-1 展开最外层的宏，macroexpand递归展开所有宏
;注意展开表达式要引用
(macroexpand-1 '(reverse-it (cni (cni 1))))

(pprint (macroexpand '(reverse-it (cni (cni 1)))))      

;其实就是返回可执行的代码 符号列表
(defmacro macro_test 
    [& body]
    '(println 1))
;这里x xx xxx没有定义，但是没有求值，所以也不会报错
(macro_test x xx xxx)
(macroexpand-1 '(macro_test x xx xxx))

;` 外层语义引述， ~内层反引述
;`和'的区别在于 `给没有命名空间的符号赋予当前命名空间， 
;keyword将字符串转为关键字
`(map ~(keyword (str 'key)))  
  
;'~先求值，再转引用
`(map '~(keyword (str 'key)))  
  
;返回(do (quote user/arr)), '被引用， arr被赋予当前命名空间
`(do 'arr)
;~@列表解引用
(def arr '(1 2 3))
;得到的是(do 1 2 3)
`(do ~@arr) 

;效果一样，会被解包
(def arr [1 2 3]) 
`(do ~@arr) 


(defmacro foo 
    [& body]
    `(dosomething ~@body))
(macroexpand-1 '(foo x xx xxx))

(defmacro macro-hello [x]
    `(str "hello, " ~x "!"))
(macro-hello 'ljl)

;宏不能作为值传递，不能和高阶函数合作
macro-hello
(map macro-hello '(a b c))

;包裹在函数中能传递
(map #(macro-hello %) '(a b c))

;通过gensym生成符号，避免冲突
(defmacro hygienic
    [& body]
    (let [sym (gensym)]
        `(let [~sym :macro-value]
            ~@body)))
(let [sym :important-value]
    (hygienic (println "sym:" sym)))

;可以看到sym名称是个生成符号
(macroexpand-1 '(hygienic 'sym))

;xxx#， gensym语法糖，同时可以避免x是函数情况下，多次x求值的问题
(defmacro hygienic2
    [& body]
    `(let [sym# :macro-value]
            (println sym#)))
(macroexpand-1 '(hygienic2 'sym))  

;同一个`范围内的xx#才能保证一样
`(x# x#)
[`x# `x#]   

;不再同一`中还是需要手动let

;使用name对应的符号来绑定,采用用户的符号避免污染
(defmacro with 
    [name & body]
    `(let [~name 5]
        ~@body))
        
(with bar (+ bar 10))
(macroexpand-1 '(with bar (+ bar 10)))

(def x 1)
(eval 'x)
@(resolve 'x)

宏重载
(defmacro reload_test
  ([x]  `(reload_test ~x ~x nil))
  ([x y & oldform] `(println ~x ~y)))

(reload_test 1)

vector直接做函数 let [form (bindings 0) tst (bindings 1)]

for配合while
(take 100 (for [x (range 100000000) y (range 1000000) :while (< y x)] [x y]))

(keys { :a 1 :n 2 })
(vals { :a 1 :n 2 })


(defmacro  env_test
  []
  (let [ks (keys &env)]
  ;这里~ks会被转符号，
  `(prn (zipmap '~ks [~@ks]))))
  
(let [x 1 y 2]
    (env_test))

;上面的过程等效下面代码， zipmap 返回map
;~@返回的是
(let [x 1 y 2]
    (zipmap '(x y) [x y]))

;所有参数均绑定,提前计算结果
(defmacro simplify
  [expr]
  (let [locals (set (keys &env))]
    (if (some locals (flatten expr)) 
        expr
        (do
            (println "Precomputing:" expr)
            ;返回计算结果
            (list `quote (eval expr))))))

;代码直接被替换为常数            
(simplify (apply + (range 5e7)))

(defmacro ontology
    [& triples]
    (println &form)
    (println (meta &form)))
(ontology 1 2 3)

(reduce #(and %1 %2) #(inc 1) '(1 2 3))

(reduce #(println %1 %2) (partition 2 '(1 2 3 4)))


;if-let 和let形式一样，只是第二个值如果是nil 或者false执行else部分，没有就不执行
(if-let [ [x  & xs] '(1 2 3)] x)
(if-let [ [x  & xs] nil] x)

;and和or都是宏可以直接查看源码
;均返回最后一个判断的元素，and为假直接返回，or为真直接返回
(if-let [x  (and 1 2)] x)
(if-let [x  (and 1 nil 2)] x)
(if-let [x  (or nil 2 3)] x)
(if-let [x  (or nil false nil)] x)
       