;;练习2.1 x分子 y分母
(defn make_rat [x y]
    (if (= y 0) (throw (new Exception "denominator is 0"))
        (cond 
            (< y 0) (list ( - x) (- y))
            :else (list x y))))
            
            
;;练习2.6 
(defn zero_fn [] 
    (fn[f] 
        (fn[x] x)))
  
(defn add_1_fn [n] 
    (fn[f]
        (fn[x] (f ((n f) x)))))

;一次也不打印
(((zero_fn) (fn[x] (println "execuate one times"))) nil)
;执行1次(add_1_fn (zero_fn))
(((add_1_fn (zero_fn)) (fn[x] (println "execuate one times"))) nil)
;执行2次(add_1_fn (add_1_fn (zero_fn)))
(((add_1_fn (add_1_fn (zero_fn))) (fn[x] (println "execuate one times"))) nil)
  
(defn one_fn [] 
    (fn[f] 
        (fn[x] (f x))))

(defn two_fn [] 
    (fn[f] 
        (fn[x] (f (f x)))))
        
(((one_fn) (fn[x] (println "execuate one times"))) nil)
(((two_fn) (fn[x] (println "execuate one times"))) nil)  
  
;;练习1.14
(defn make_interval [a, b] 
    (if (or ( <= a 0) (<= b 0) (> a b)) 
        (throw (new Exception (String/join " " (map #(str %) ["invalid bound" a b]))))
        (list a b)))
        
   
(defn lower [interval] (first interval))
(defn upper [interval] (second interval))
   
(defn interval_substract [i1, i2]
    (make_interval (/ (lower i1) (upper i2)) (/ (upper i1) (lower i2))))

(defn interval_add [i1, i2]
    (make_interval (+ (lower i1) (lower i2)) (+ (upper i1) (upper i2))))
    
(defn interval_multiply [i1, i2]
    (make_interval (* (lower i1) (lower i2)) (* (upper i1) (upper i2))))
  
(interval_substract (make_rat 1.05 1.1) (make_rat 2.05 2.1))


(defn make_constant_interval [a] 
    (if (or ( <= a 0)) 
        (throw (new Exception (+ "negative number" (str a)))))
        (list a a))
(def interval_one (make_constant_interval 1))


(def R1 (make_interval 1.95 2.05))
(def R2 (make_interval 3.95 4.10))

;两种并联计算都有误差，原因应该是计算机的精度误差，解决方法用分数
(interval_substract interval_one 
    (interval_add (interval_substract interval_one R1) (interval_substract interval_one R2)))
  
(interval_substract (interval_multiply R1 R2) (interval_add R1 R2))

  
  
  
  
  
  
  
  
  