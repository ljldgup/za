;delay后面要加括号
(def d (delay (println "Running..") :done!))
;deref只会运行一次， @简写不需要括号
;多个线程求值会被同时阻塞，还是只求一次
(deref d)
(deref d)
@d

;slurp打开网页或文件，返回字符串
(defn get-document
    []
    {:url "www.baidu.com"
     :content (delay (slurp "http://www.baidu.com"))})

;content 状态是pending
(def document (get-document))
;realized?判断是否执行
(realized? (:content document))
@(:content document)
(realized? (:content document))
------------------------------------------------------------------------
;future异步执行后直接返回nil，执行的代码需要用()包起来，和swaq！不同
(def future_item (future (Thread/sleep 5000) :done))

;使用@解引用返回值 ,没有执行完就变成同步了会阻塞
@future_item

;deref指定超时1000ms
(deref (future (Thread/sleep 5000) :done) 1000 :timeout)

future 实现异步函数函数
(defn future-func[] (future (func)))
(defn future-func[] (future (func)))
-------------------------------------------------------------
;promise作为管道容器
(def p (promise))
(realized? p)

(deliver p 42)
(realized? p)


(def a (promise))
(def b (promise))
(def c (future (+ @a @b)))
;阻塞
@c

(deliver a 42)
(deliver b 42)
;不阻塞
@c

-----------------------------------------------------------------
;这边time貌似有点问题
(defn pmap_test[x] (Thread/sleep 1000))
(time (map pmap_test (range 5)))
(time (pmap pmap_test (range 5)))

------------------------------------------------------------
(def sarah (atom {:name "Sarah" :age 25 :wears-glasses? false}))

;swap!采用cas更新atom类型，update-in 更新map函数
(swap! sarah update-in [:age] + 3)

;swap!第二个参数是函数，将atom的值作为函数的入参进行调用，返回值替换原来atom的值
(swap! sarah #(println %))
@sarah

;直接cas
(compare-and-set! sarah nil "new value")
@sarah

;强制修改
(reset! sarah "reset value")
@sarah
-----------------------
;ref 引用
(def names (ref []))
;;=> #'user/names

;; dosync 中作为一个事务，才能用alter改变其值
(dosync
    (alter names conj "zack"))
;;=> ["zack"]

(dosync
    (ref-set names ["zack" "shelley"]))

------------------------------------------
;观察器
(defn echo-watch
    [key identity old new]
    (println key old "=>" new))
; 关键字 :echo 是传到echo-watch函数的第一个参数,用于派发，多个监控函数这个key值不能相同
(add-watch sarah :echo echo-watch)
;新值相同也会触发
(reset! sarah "reset value")
;移除
(remove-watch sarah :echo)

;校验器
(def sarah (atom {:name "Sarah" :age 25 :wears-glasses? false}))
;传进来的是值，不需要@， 
;满足穿进去的函数时，认为校验不通过，报Invalid reference state
;设置的时候就会校验一次
(set-validator! sarah (fn[x](println x)(> 28 (:age x))))
;失败
(swap! sarah update-in [:age] + 3)
;成功
(swap! sarah update-in [:age] + 2)


;组包成map
(defn d[x & {:as opt}] 
    (println opt))
(d 1 :a 1)


;等待事务1执行完了，事务2才能结束
(def x (ref 0))
(future 
    (dosync 
        (ref-set x 2)
        (Thread/sleep 4000)
        (println "transaction 1 finished")))
(future  
    (dosync 
        (ref-set x 3)
        (println "transaction 2 finished")))

;ref历史版本,可以根据读写快慢，设置历史版本数量
(def x (ref 0 :max-history 30 :min-history 19))
(ref-history-count x)
(future (dotimes [_ 500] (dosync (alter x inc ))))
(ref-history-count x)
(ref-min-history x)
(ref-max-history x)


(def ^:private something "something doc" 42)
something
;#'等效(var 
(meta #'something)
;私有在其他环境无法访问
(ns other_namespace)
something

;动态绑定，需要dynamic关键字
(def ^:dynamic v :root)
v
;可以在future生成另外一个线程中传播
(binding [v :a]
    (binding [v :b]
        (binding [v :c]
            (future (println v)))))

;agent send固定线程池 send-off不限制线程池
(def a (agent 50000))
(def b (agent 100000))
;send，send-off将用第二个参数作为函数，将agent的值作为入参进行调用
;并将返回值替换agent的值
(send b #(Thread/sleep %))
(send-off a  #(Thread/sleep %))
;在函数执行完结前不会替换值
@a

;await 等待所有agent结束
(await a b)

;貌似没挂。。clojure中异常被当成普通对象操作，不会打断流程，
;打印会有所有信息，用来空值流程没有什么效果
(send b (throw (new Exception "agent die!!??")))
(send-off b (throw (new Exception "agent die!!??")))


(def url-queue (java.util.concurrent.LinkedBlockingQueue.))
;定义不赋值
(declare get-url)
;:: 指定为当前命名空间下关键字，'#get-url:queue 默认的参数
{::t '#get-url:queue url-queue}

;fnil 增加空判断
((fnil inc 0) nil)