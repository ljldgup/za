方法1， 用def+memoize+匿名调用实现
(def m-fib
  (memoize (fn [n]
             (condp = n
               0 1
               1 1
               (+ (m-fib (dec n)) (m-fib (- n 2)))))))
               

;方法2,def空定义           
(def fib)
(def m-fib (memoize fib))            
(defn fib[n]
  (condp = n
               0 1
               1 1
               (+ (m-fib (dec n)) (m-fib (- n 2)))))