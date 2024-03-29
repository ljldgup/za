;这里stream对应 clojure的lazy-seq, 各类操作在clojure中都有对应的
;clojure 通过 (lazy-seq (cons  实现 cons-stream 如 (def x (lazy-seq (cons 1 (map inc x))))
;stream-car 对应 first, stream-cdr 对应rest
;filter map take 等都只是加了个前缀
;add mul 等使用for实现
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(def the-empty-stream '())

(defn stream-null? [s]
    (or (nil? s) (empty? s)))
    
;cons-stream传表达式会直接被执行，函数没法实现，只能用宏
;这里是用在宏内部，exp的执行环境仍然存在
;为了防止重复执行，使用记忆化
(defmacro stream-delay [exp]
    `(memoize (fn[] ~exp)))
    
(defmacro stream-force [exp]
    `(~exp))
    
;由于cons-stream是宏，所以不会加深堆栈，不会导致无求流爆栈 
(defmacro cons-stream [a b]
    `(list ~a (stream-delay ~b)))

(defn stream-car [stream]
        (first stream))

(defn stream-cdr [stream]
    (stream-force (second stream)))
    
(stream-cdr (cons-stream 1 (inc 2)))

;流操作函数，主要通过迭代实现
(defn stream-ref [n stream]
    (cond (> n 1) (recur (- n 1) (stream-cdr stream))
          (= n 1) (stream-car stream)
          :else nil))
          
(defn stream-filter [pred stream]
    (cond (stream-null? stream) the-empty-stream
          (pred (stream-car stream)) 
            (cons-stream 
                (stream-car stream) 
                (stream-filter pred (stream-cdr stream)))
          :else (stream-filter pred (stream-cdr stream))))

(defn stream-map [mapper stream]
    (if (stream-null? stream)
        the-empty-stream
        (cons-stream
            (mapper (stream-car stream))
            (recur mapper (stream-cdr stream)))))
    
(defn stream-for-each [proc s]
    ;(println (stream-null? s) (stream-car s))
    (if (stream-null? s)
        :done
        (do
            (proc (stream-car s))
            (recur proc (stream-cdr s)))))
            
(defn stream-enumerate-interval [low high]
    ;(println 'stream-enumerate-interval low high)
    (if (> low high)
        the-empty-stream
        (cons-stream
            low
            (stream-enumerate-interval (+ low 1) high))))
            
(-> (stream-enumerate-interval 0 100) stream-cdr stream-cdr stream-cdr)  
(-> (stream-enumerate-interval 0 100) stream-cdr stream-car)  
(stream-null? (stream-enumerate-interval 0 10))
(->> (stream-enumerate-interval 0 10) (stream-for-each #(println (* % %))))
(->> (stream-enumerate-interval 0 10) (stream-filter #(= (mod % 3) 0)) (stream-for-each #(println %)))
(->> (stream-enumerate-interval 0 10) (stream-map #(apply * (repeat % 3))) (stream-for-each #(println %)))

;不用recur直接递归会爆栈，stream-map，stream-filter 因为本质上没有计算，所以不会爆栈
(->> (stream-enumerate-interval 0 100000N) (stream-map #(dec %)) (stream-for-each #(inc %)))
(->> (stream-enumerate-interval 0 1000000) (stream-ref 99999))

;显示计算了几个
(->> (stream-enumerate-interval 0 10) (stream-map println) (stream-ref 7))
-----------------------------------------------------------------------------------
;取前几位
(defn stream-take [n stream]
    (if (= n 0)
        the-empty-stream
        (cons-stream 
            (stream-car stream)
            (stream-take (dec n) (stream-cdr stream)))))
            
;显示前n个元素
(defn display-stream [stream n]
       (->> stream (stream-take n) (stream-for-each println)))
       

(defn add-streams [s1 s2]
    ;(println (stream-car s1) "+" (stream-car s2))
    (cons-stream 
        (+ (stream-car s1) (stream-car s2))
        (add-streams (stream-cdr s1) ( stream-cdr s2))))
        
;1 和整数流，迭代实现
(def ones (cons-stream 1 ones))
(def integers 
    (cons-stream 1 (add-streams integers ones)))
(display-stream integers 10)
(->> integers stream-cdr  stream-cdr (stream-ref 7))  


;斐波拉契无穷流
(defn fib-stream
    ([] (fib-stream 0 1))
    ([a b] (cons-stream 
            a 
            (fib-stream b (+ a b)))))
(->> (fib-stream) (stream-ref 7))
(display-stream (fib-stream) 10)
 
     
;素数无穷流,这里1需要特殊处理，不能加到过滤条件里
(defn sieve 
    ([] (cons-stream 1 (sieve (stream-cdr integers))))
    ([stream] 
        (let [last-prime (stream-car stream)]
            ;(println last-prime)
            (cons-stream 
                last-prime
                (sieve 
                    ;增加当前的素数不为因子作为过滤器
                    (stream-filter 
                        #(not= (rem % last-prime) 0) 
                        (stream-cdr stream)))))))
;数量太大会报栈，因为过滤器太多，普通的是不会爆栈的
(->> (sieve) (stream-ref 10000))
;(display-stream (sieve) 10000)



(display-stream (add-streams (sieve) (fib-stream)) 20)

;直接通过add-streams 得到斐波拉契序列，
(def fibs (cons-stream 0 (cons-stream 1 (add-streams (stream-cdr fibs) fibs))))    
(display-stream fibs 20)
        
        


(defn mul-streams [s1 s2]
    (cons-stream 
        (* (stream-car s1) (stream-car s2))
        (mul-streams (stream-cdr s1) ( stream-cdr s2))))

;可以实现阶乘，这里factorials, integers 取下一个数是在mul-streams 实现的，不需要在定义中体现
(def factorials 
  (cons-stream 1 (mul-streams factorials (stream-cdr integers))))
       
(display-stream factorials 20)

;练习3.59
;积分，第n项代表x^(n-1)到积分 x^n前面的常数 (即1/n，d(x^n/n)/dx = x^(n-1), 具体的系统由series提供)      
(defn intergrate-series
    ([series] (intergrate-series series 1))
    ([series n](cons-stream 
                (/ (stream-car series) n)
                (intergrate-series (stream-cdr series) (+ n 1)))))
(def exp-series (cons-stream 1 (intergrate-series exp-series)))               
(display-stream (->> ones intergrate-series) 10)
(display-stream exp-series 10)

;通过相互引用实现sin cos 的无穷级数不先定义会报错
;不先定义会报错
(def cos-series)
(def sin-series)
(def cos-series (cons-stream 1 (stream-map #(- %) (intergrate-series sin-series))))
(def sin-series (cons-stream 0 (intergrate-series cos-series)))      

(display-stream cos-series 10)
(display-stream sin-series 10)
;不爆栈
;(stream-ref 10000 sin-series)

;无穷级数相乘，先算最小的一项，这一项不可能重复，后面的递归
(defn mul-streams [s1 s2]
    ;(println :mul-streams)
    (let [s1-car (stream-car s1)
          s2-car (stream-car s2)]    
        (cons-stream 
            (* s1-car s2-car)
            (add-streams 
                ;这里两个相乘比当前幂直接大了2，所以加个0
                (cons-stream 0 (mul-streams (stream-cdr s1) (stream-cdr s2))) 
                (add-streams
                    (stream-map #(* % s1-car) (stream-cdr s2))
                    (stream-map #(* % s2-car) (stream-cdr s1)))))))
            
(def cos-square (mul-streams cos-series cos-series))
(def sin-square (mul-streams sin-series sin-series))

(display-stream cos-square 10)
(display-stream sin-square 10)


;sinx^2 + cosx^2 = 1， 写个reduce更好点，懒得弄
(def ^:dynamic sum)
(binding [sum 0.0]
    (->> cos-square (stream-take 100) (stream-for-each #(set! sum (+ sum %))))
    (->> sin-square (stream-take 100) (stream-for-each #(set! sum (+ sum %))))
    (println sum))
--------------------------------------------------------------------------------------------
(defn sqrt-impore [guess x]
    (/ 
        (+  guess 
            (/ x guess)) 
        2.0))

(defn sqrt-stream[x]
    (def guesses (cons-stream 1.0 
                    (stream-map 
                        (fn[guess] 
                            (do
                                (println "improve guess " guess x)
                                (sqrt-impore guess x))) 
                        guesses)))
    guesses)
;这里是stream-map的嵌套，而stream-map 每次都会求好第一个参数，
;所以虽然嵌套结构，运行时每次只在第一个值上运行一次映射函数，不会嵌套执行
(display-stream (sqrt-stream 2) 10) 

---------------------------------------------------------------------------
;clojure自带interleave实现,无法用于我手工实现的stream,所以只能自己再写一个
;clojure的interleave在一个为空后就终止。。。和这里的不一样

;练习3.69 改成可以接受无穷个流  
(defn stream-interleave [s1 & ss]
    ;(println :stream-interleave  (conj ss (stream-cdr s1)))
    (if (stream-null? s1)
        (stream-interleave ss)
        (cons-stream
            (stream-car s1)
            (apply stream-interleave (concat ss (list (stream-cdr s1)))))))
                
(defn pairs [s1 & ss]
    (if (empty? ss)
        ;cons 需要第二个参数是seq
        (stream-map list s1)
        (let [s2 (first ss)
              rest-ss (rest ss)]
            (println :new-pairs)
            (cons-stream
                (cons (stream-car s1) (map stream-car ss))
                (stream-interleave
                    ;这里后半部分会递归排除每个流的第一个元素
                    (stream-map (fn[x] (cons (stream-car s1) x)) (apply pairs (cons (stream-cdr s2) rest-ss)))
                    (apply pairs (map stream-cdr (cons s1 ss))))))))
                    
;每执行2^n次方生成一个新pair，和我推导的一致,
(display-stream (pairs integers integers) 20)

;练习3.70，根据权重取，配合前面写成无限个流的使用，比较函数weight-fn可自定义
;总是比较前两个参数，然后大的后移，通过辅助函数helper来确定比较完毕,这里如果流多，理论上用堆会更好
;这里无法用尾递归，原因不明
(defn merge-weighted-gen [weight-fn]
    (defn helper[n ss]
        ;(println n :helper ss )
        ;(println (first ss)) 
        ;(println (second ss) )
        ;(println (weight-fn (stream-car (first ss)))) 
        ;(println (weight-fn (stream-car (second ss))))
        ;(println (rest (rest ss)))
            
        (cond (= n 1) (do 
                        ;(println (weight-fn (stream-car (first ss)))) ;这里会打印很多，因为不只一路在归并
                        (cons-stream 
                            (stream-car (first ss))
                            (helper (count ss) (conj (rest ss) (stream-cdr (first ss))))))
              :else (let [s1 (first ss)
                          s2 (second ss)
                        rest-ss (rest (rest ss))
                        w1 (weight-fn (stream-car s1))
                        w2 (weight-fn (stream-car s2))]
                        (if (< w1 w2)
                            ;把大的挪到队伍尾部，n-1,n=0直接返回队伍首部
                            (helper (dec n) (concat (conj rest-ss s1) (list s2)))
                            (helper (dec n) (concat (conj rest-ss s2) (list s1)))))))
    ;暴露给外部的函数处理不定长参数，传给内部处理序列
    (fn [& ss]
        (if (< 2 (count ss)) 
            (first ss)
            (helper (count ss)  ss))))

;通过递归 + 嵌套流实现;
;let [merged-stream (merge-weighted ss) 这句话会不断递归直到ss为空为止，不会delay，从而保证每次都是最大的
(defn new-merge-weighted-gen [weight-fn]
    (defn merge-weighted
        [s1 & ss]
        ;(println :s1 s1) 
        ;(println :ss ss)
        ;(println (weight-fn (stream-car s1))) 
        ;(println (weight-fn (stream-car (first ss))))
        (if (empty? ss) 
            s1
            (let [merged-stream (apply merge-weighted ss)
                  w1 (weight-fn (stream-car s1))
                  w2 (weight-fn (stream-car merged-stream))]
                (if (< w1 w2)
                    (cons-stream 
                        (stream-car s1) 
                        (merge-weighted (stream-cdr s1) merged-stream))
                    (cons-stream 
                        (stream-car merged-stream) 
                        (merge-weighted (stream-cdr merged-stream) s1)))))))
                
(def cube-weight (fn[x](reduce + (map #(apply * (repeat 3 %)) x))))
;(def merge-cube-weighted (merge-weighted-gen cube-weight))
(def merge-cube-weighted (new-merge-weighted-gen cube-weight))

;这里没有处理第一个  
(defn weighted-pairs [s1 & ss]
    (if (empty? ss)
        ;cons 需要第二个参数是seq
        (stream-map list s1)
        (let [s2 (first ss)
              rest-ss (rest ss)]
            ;(println :new-weighted-pairs (first s1) (first s2))
            (cons-stream
                (cons (stream-car s1) (map stream-car ss))
                (merge-cube-weighted 
                    ;这里后半部分会递归排除每个流的第一个元素
                    (stream-map (fn[x] (cons (stream-car s1) x)) (apply weighted-pairs (cons (stream-cdr s2) rest-ss)))
                    (apply weighted-pairs (map stream-cdr (cons s1 ss))))))))
                    
;这里没用recur，把数字取得非常大也不会爆栈。。只有像素数那样嵌套过滤太多才会爆           
(display-stream (weighted-pairs integers integers integers) 20)
   




(display-stream 
    (stream-map 
        (fn[x](reduce + (map #(apply * (repeat 3 %)) x))) 
        (weighted-pairs integers integers integers)) 
    20)
    
;练习3.71, 练习72 修改cube-weight, 和n的判断就可以了
(defn repeated-stream
    ([s](repeated-stream 0 s))
    ([n s]
        ;(println (cube-weight (stream-car s)) (cube-weight (stream-car (stream-cdr s))))
        (if (= (cube-weight (stream-car s)) (cube-weight (stream-car (stream-cdr s))))
            (cons-stream 
                    (stream-car s)
                    (repeated-stream (inc n) (stream-cdr s)))
            (if (> n 0)
                (cons-stream 
                    (stream-car s) 
                    (repeated-stream 0 (stream-cdr s)))
                (recur 0 (stream-cdr s))))))
                
(display-stream (->> 
                    (weighted-pairs integers integers) 
                    repeated-stream 
                    (stream-map #(list % (cube-weight %))))
                 20)
-----------------------------------------------------------------------------

;clojure的lazy-seq,lazy-cat
   
;随机无穷惰性序列         
(def rand-stream (lazy-seq (cons (rand) (map (fn[x](rand)) rand-stream))))
(take 40 rand-stream )

;随机无穷惰性序列  
(def integers (lazy-seq (cons 1 (map inc integers))))

;斐波拉契数列，注意这里map自己部分外面的cons需要加lazy-seq，否则没有延时直接爆栈
(def fib 
    (cons 1 
        (lazy-seq 
            (cons 1 
            (map + fib (rest fib))))))
(take 10 fib)

(def scale-2 (lazy-seq (cons 1 (map (fn[x](* x 2)) scale-2))))
(def scale-3 (lazy-seq (cons 1 (map (fn[x](* x 3)) scale-2))))
(def scale-5 (lazy-seq (cons 1 (map (fn[x](* x 5)) scale-2))))


;素数流
(def integers (lazy-seq (cons 2 (map inc integers))))
(def prime)
(defn prime?[x] 
    (not (some #(= (rem x %) 0) prime)))
(def prime (filter prime? integers))
(take 10 prime)