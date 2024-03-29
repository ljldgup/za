;;filter是个关键字，入参和局部变量无法使用，这里也不会报错是个坑！！
;这是递归版本，非递归需要辅助函数，用其入参保存临时累积和及左边界
(defn accumulate [combiner, my_fiter, null-value, term, a, b, next]
    (if (> a b) null-value
        (if (my_fiter a) 
            (combiner (term a) (accumulate combiner my_fiter null-value term (next a) b next))
            (combiner null-value (accumulate combiner my_fiter null-value term (next a) b next)))))

(defn next_one [x]
    (+ x 1))

(defn adder [x y]
    (println (format "%s %s" x y))
    (+ x y))

(defn self_term [x] x)

(accumulate adder odd? 0 self_term 0 10 next_one) 

;;lambda实现
(accumulate adder (fn[x] (= 1 (mod x 2))) 0 (fn[x] x ) 0 10 (fn[x](+ x 1))) 

;;let定义局部变量和过程，类似lambda的定义+调用
(let [a 2 b ((fn[] 1))] (> a b))

;;练习1.37,结果应为0.618

;;使用内部定义函数时，很多参数可以直接用外部函数的参数变量，不需要自己再传入，这样可以实现类似循环时外部量的效果
;递归
(defn continued_fraction_rec [func_n, func_d, combiner, k]
    (defn continued_fraction_helper[i]
        (if (> i k) 0
            (double (/ (func_n i) 
                (combiner (func_d i) (continued_fraction_helper (inc i)))))))
    (continued_fraction_helper 1))

(continued_fraction_rec (fn[x] 1) (fn[x] 1) + 100)


;;练习1.37 迭代，从最底层开始算
(defn continued_fraction_iter [func_n, func_d, combiner, k]
    (defn continued_fraction_helper[result, i]
        (if (< i 1) result
            (let [new_result (double (/ (func_n i) (combiner (func_d i) result)))]
                (continued_fraction_helper new_result (dec i)))))
    (continued_fraction_helper 0 k))
    

(continued_fraction_iter (fn[x] 1) (fn[x] 1) + 100)
    
;;练习1.38
(defn fn_d138 [x] 
    (if (= (mod x 3) 2) 
        (* 2 (+ 1 (int (/ x 3.0)))) 
        1))

(continued_fraction_iter (fn[x] 1) fn_d138  + 100)

;;练习1.41，1.43,扩展至任意次，使用闭包要尽可能减少内部函数的传参
;clojure 关键字repeat
(defn repeat_func [f, n] 
    (defn helper[x i] 
        (if ( < i n ) (helper (f x) (+ i 1)) x))
    (fn[x] (helper x 0)))

((repeat_func inc 10) 1)

;;练习1.42,复合过程关键在于返回函数
;clojure 关键字comp
(defn compose [f g]
    (fn [x] (f (g x))))
    
((compose (fn[x] (* x x)) (fn[x] (+ x x))) 2)
    
;;练习1.44,try是个关键字，不能使用
(def tolerence 0.0001)
(def max_iter_times 400)

(defn average_damp [f]
    (fn [x] (/ (+ x (f x)) 2.0)))

(def no_damp identity)

(defn find_fixed_point [f first_guess damp]
    (defn is_close_enough [a b]  
        ;;(println (Math/abs (- a b)))    
        (< (Math/abs (- a b)) tolerence))
    (defn next_func[x] ((damp f) x))
    (defn try_next [guess times]
        (if (> times max_iter_times)
            guess
            (let [next (next_func guess)]
                (if (is_close_enough next guess)
                    next
                    (try_next next (+ 1 times))))))
    (try_next first_guess 0))

;;(fn[f] f)无阻尼平均
(find_fixed_point (fn[x] (Math/cos x)) 1 identity)

;; y=2/x=x -> x^2 = 2, x为2的平方根
(find_fixed_point (fn[x] (/ 2.0 x)) 1 no_damp)
(find_fixed_point (fn[x] (/ 2.0 x)) 1 average_damp)

(defn prod [x times]
    (defn prod_helper [result left_times]
        (if ( < left_times 1) result
            (prod_helper (* result x) (- left_times 1))))
    (prod_helper 1 times))

求1-10次方根
(dotimes [expr_times 10]
( println expr_times 
    (prod 
        (find_fixed_point 
            (fn[x] (/ 10.0 (prod x (- expr_times 1)))) 1 average_damp) 
     expr_times)))
    
(dotimes [expr_times 10]
( println expr_times  
    (prod 
        (find_fixed_point 
            (fn[x] (/ 10.0 (prod x (- expr_times 1)))) 1 (repeat_func average_damp 2)) 
     expr_times)))

;;平均阻尼反复3次效果较好
(dotimes [expr_times 10]
( println expr_times  
    (prod 
        (find_fixed_point 
            (fn[x] (/ 10.0 (prod x (- expr_times 1)))) 1 (repeat_func average_damp 3)) 
     expr_times)))
     
