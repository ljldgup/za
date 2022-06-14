;这里用嵌套的vector 来实现队列，内部是个嵌套的vector 
如：(1 (2 (3 (4 (5))))),本质上就是链表，只是实现在要更加抽象层面上

;对node的抽象
(defn get-item 
    [node]
    (nth node 0))

(defn get-parent 
    [node]
    (nth node 1))    
    
(defn get-child 
    [node]
    (nth node 2))

(defn set-parent! 
    [node p]
    (assoc! node 1 p))    
    
(defn set-child! 
    [node c]
    (assoc! node 2 c))

;对双向queue抽象
(defn get-front-ptr
    [queue] 
    (nth queue 0))
    
(defn get-tail-ptr
    [queue] 
    (nth queue 1))

(defn set-front-ptr!
    [queue item] 
    (assoc! queue 0 item))
    
(defn set-tail-ptr!
    [queue item] 
    (assoc! queue 1 item))

;可变集合不能用empty?
(defn empty-queue?
    [queue]
    (or
        ( = (count (get-front-ptr queue)) 0)
        (identical? (get-tail-ptr queue) (get-parent (get-front-ptr queue)))))

            
(def empty-vector [])
;易变集合不支持seq,只能用于vector map
(defn make-queue
    [] 
    (transient [empty-vector empty-vector]))

(defn front-queue
    [queue]
    (if (not (empty-queue? queue))
        (get-item (get-front-ptr queue))))

(defn tail-queue
    [queue]
    (if (not (empty-queue? queue))
        (get-item (get-tail-ptr queue))))
        
(defn delete-queue-front!
    [queue]
    (if (not (empty-queue? queue))
        ;这里front为空时插入会自动重置，所以不需要动tail部分
        (set-front-ptr! queue (get-child (get-front-ptr queue)))))
        
(defn delete-queue-tail!
    [queue]
    (if (not (empty-queue? queue))
        (do  
            (set-tail-ptr! queue (get-parent (get-tail-ptr queue))))))
        
(defn insert-queue-tail! 
    [queue item]
    (let [new-pair (transient [item empty-vector empty-vector])]
        (cond (empty-queue? queue)
            (do
                (set-front-ptr! queue new-pair)
                (set-tail-ptr! queue new-pair))
        :else
            (do
                ;注意这里存在赋值造成的顺序问题
                (set-parent! new-pair (get-tail-ptr queue))
                (set-child! (get-tail-ptr queue) new-pair)
                (set-tail-ptr! queue new-pair)))))
                
                
(defn insert-queue-front! 
    [queue item]
    (let [new-pair (transient [item empty-vector empty-vector])]
        (cond (empty-queue? queue)
            (do
                (set-front-ptr! queue new-pair)
                (set-tail-ptr! queue new-pair))
        :else
            (do
                ;注意这里存在赋值造成的顺序问题
                (set-parent! (get-front-ptr queue) new-pair)
                (set-child! new-pair (get-front-ptr queue))
                (set-front-ptr! queue new-pair)))))
                

(defn print-queue
    [queue]
    (if (not (empty-queue? queue))
        (loop [fq (get-front-ptr queue)]
            (do
                ;(println fq)
                (if (< 0 (count fq)) (print (nth fq 0) " "))
                (if (not (identical? fq (get-tail-ptr queue)))
                    (recur (nth fq 2)))))))     

(def q (make-queue))
(insert-queue-front! q 1)
(insert-queue-tail! q 2)
(print-queue q)

(doseq [x (range 4)]
    (insert-queue-front! q x))
(doseq [x (range 6)]
    (insert-queue-tail! q x))
(print-queue q)
(front-queue q)
(tail-queue q)

(doseq [x (range 3)]
    (delete-queue-front! q))
(doseq [x (range 9)]
    (delete-queue-tail! q))
(print-queue q)

-----------------------------------------------------
;lambda实现 递归，本质上就是定义函数递归一个意思，但是可以配合memoize等aop效果的包装使用，见下个列子
(def lambda-fib 
        (fn[x]
            (cond
                (= 0 x) 0
                (= 1 x) 1
                :else (+ (lambda-fib (- x 1)) (lambda-fib (- x 2))))))

;递归函数memoize，通过在lamdba中调用              
(def mome-fib 
    (memoize 
        (fn[x]
            (cond
                (= 0 x) 0
                (= 1 x) 1
                :else (+ (mome-fib (- x 1)) (mome-fib (- x 2)))))))
                
(time (lambda-fib 30))
(time (mome-fib 30))

--------------------------------------------------------------------------------------

(defprotocol signal-op
    (get-signal [self])
    (set-signal! [self new-value])
    (add-action! [self action_key action]))
    
(defrecord Wire [name signal]
    signal-op
        ;(:signal this) 等价java this.signal
        (set-signal! [this new-value] (reset! (:signal this) new-value))
        (get-signal [this] @(:signal this))
        (add-action!      
            [this action_key action]
            (future (action)) ;先异步执行初始化数据，再加添加监控
            (add-watch     ;这里一个输入加多个监控必须有不同的key才行，同一个key会相互覆盖
                (:signal this) 
                action_key
                (fn[k r old-val new-val]
                    (if (not (= old-val new-val))
                        (do 
                            (println (:name this) k old-val "->" new-val)
                            (future (action))))))))
(defn make-wire[name]
    (Wire. name (atom 0)))
    
;;测试       
(def test-wire (Wire. "test-wire" (atom 1)))
(add-action! test-wire :test_action (fn[] (do(Thread/sleep 1000) (println "changed"))))
(set-signal! test-wire 3)
(get-signal  test-wire)
 

    

;逻辑操作输入的是纯数字（信号）
(defn logic-and [s1 s2]
    (cond 
        (and (= s1 1) (= s2 1)) 1
        :else 0))
        
(defn logic-or [s1 s2]
    (cond 
        (and (= s1 0) (= s2 0)) 0
        :else 1))
        
(defn logic-not [s]
    (cond 
        (= s 1) 0
        :else 1))
        
;;测试    
(logic-and 1 1)
(logic-and 0 1)
(logic-or 0 1)
(logic-or 0 0)
(logic-not 0)
(logic-not 1)


;门控单元
(def or-gate-delay 0.1)
(def and-gate-delay 0.1)
(def inverter-delay 0.1)    
(defn after-delay [seconds action]
    (Thread/sleep (* seconds 1000))
    (action))
    
(defn or-gate [input1 input2 output]
    (defn or-input[]
        (let [new-value (logic-or (get-signal input1) (get-signal input2))]
            (after-delay 
                or-gate-delay 
                #(set-signal! output new-value))))
     
    ;这里如果输入连接多个与门应该会相互覆盖，可以考虑生成关键字 (keyword `or#)或者
    ;或者用名字拼接(keyword (str (map :name (input1 input2 output))))
    (add-action! input1 (keyword `or#)  -input)
    (add-action! input2 (keyword `or#) or-input))
    
(defn and-gate [input1 input2 output]
    (defn and-input[]
        (let [new-value (logic-and (get-signal input1) (get-signal input2))]
            (after-delay 
                and-gate-delay 
                #(set-signal! output new-value))))
    (add-action! input1 (keyword `and#) and-input)
    (add-action! input2 (keyword `and#) and-input))


    
(defn inverter [input output]
    (defn invert-input[]
        (let [new-value (logic-not (get-signal input))]
            (after-delay 
                inverter-delay 
                #(set-signal! output new-value))))
    (add-action! input (keyword `invert#) invert-input))

;;测试    
(def w1 (make-wire "w1"))
(def w2 (make-wire "w2"))
(inverter w1 w2)
(get-signal w2)
(set-signal! w1 1)
(get-signal w2)

(def w3 (make-wire "w3"))
(def w4 (make-wire "w4"))
(def w5 (make-wire "w5"))
(and-gate w3 w4 w5)
(get-signal w5)
(set-signal! w3 1)
(get-signal w5)
(set-signal! w4 1)
(get-signal w5)

(def w3 (make-wire "w3"))
(def w4 (make-wire "w4"))
(def w5 (make-wire "w5"))
(or-gate w3 w4 w5)
(get-signal w5)
(set-signal! w3 1)
(get-signal w5)
(set-signal! w4 1)
(get-signal w5)

;半加器 全加器
(defn half-adder [a b s c]
    (let [d (make-wire "d")
          e (make-wire "e")]
    (or-gate a b d)
    (and-gate a b c)
    (inverter c e)
    (and-gate d e s)
    d))

(def a (make-wire "a"))
(def b (make-wire "b"))
(def s (make-wire "s"))
(def c (make-wire "c"))

(def d (make-wire "d"))
(or-gate a b d)


(half-adder a b s c)
(set-signal!  a 1)
(get-signal s)
(set-signal!  a 0)
(get-signal s)
(set-signal! b 1)
(get-signal s)
(set-signal!  b 0)
(get-signal s)

(defn full-adder [a b c-in sum c-out]
    (let [s (make-wire "s")
          c1 (make-wire "c1")
          c2 (make-wire "c2")]
    (half-adder a s sum c2)
    (half-adder b c-in s c1)
    (or-gate c1 c2 c-out)
    'ok))

(def a (make-wire "a"))
(def b (make-wire "b"))
(def sum (make-wire "sum"))
(def c-in (make-wire "c-in"))
(def c-out (make-wire "c-out"))
(full-adder a b c-in sum c-out)




