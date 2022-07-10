;binding +  ^:dynamic 跳出binding后就失效了，无法作为变量
(defn accumulator
    ([](accumulator 0))
    ([x]
        (def sum-value (atom x))
        (fn [y]
            (swap! sum-value + y)
            @sum-value)))
(def accumulate-from-one (accumulator 1))  
(accumulate-from-one 1)
(accumulate-from-one 2)

(def accumulate-from-zero (accumulator))
(accumulate-from-zero 1)
(accumulate-from-zero 2)

;练习3.2,dispatch可以通过clojure的协议实现
(defn make-monitor [f]
    (def call-times (atom 0))
    (defn call [args]
        (swap! call-times inc)
        (apply f args))
    (defn get-call-times [] @call-times)
    (defn reset-call-times [] (swap! call-times (fn[&args] 0)))
    (defn dispatch[& args]
        (cond 
            (= (first args) :reset) (do (reset-call-times) @call-times)
            (= (first args) :get) (get-call-times)
            :else (call args))))
            
(def accumulate-from-zero (accumulator))      
(def counted-accumulator (make-monitor accumulate-from-zero))
(counted-accumulator 1)
(counted-accumulator 2)
(counted-accumulator :get)
(counted-accumulator :reset)
(counted-accumulator :get)
(counted-accumulator 2)
(counted-accumulator :get)