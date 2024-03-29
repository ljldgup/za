;;尾递归测试,即使尾递归还是会爆栈
;;recur 来代替原函数，可以实现尾递归
;;变量可以通过反复def改变
(defn rec_test [base_num times]
    (def result 0)
    (defn helper[left_times]
        ;(println left_times result)
        (def result (+ base_num result))
        (if (< left_times 1) 
            result
            ;(rec_test (- left_times 1))))
            (recur (- left_times 1))))
    (helper times))
(rec_test 11 111111)


;;练习1.11
(defn fn_add [fn-1, fn-2, fn-3] (+ fn-1 (* 2 fn-2) (* 3 fn-3)))

(defn fn1_11_iter [fn-1 fn-2 fn-3 current n]
    (if (= current n) (fn_add fn-1 fn-2 fn-3)
        (fn1_11_iter fn-2 fn-3  (fn_add fn-1 fn-2 fn-3) (+ current 1) n)))

(defn fn1_11 [n]
    (if (< n 3) n (fn1_11_iter 0 1 2 3 n)))


;;练习1.12 y为深度
(defn pascal_triangle [x y]
    (cond
        (or (< x 1) (< y 1)) 0
        (or (= x 1) (= x y)) 1
        :else (+ (pascal_triangle (- x 1) (- y 1)) (pascal_triangle x (- y 1)))))       
        
;;练习1.16 迭代求幂， 书中展示的是递归
;;;通过尾递归实现迭代，就是把循环中所有要用到的变量传到递归参数里
;;;不变参数可以考虑闭包提出

;;从小到大累加,当没法翻倍时将临时结果prod放到总结果total_prod里面
(defn fast_expr [base_num, expr_num]
    (defn fast_expr_iter [total_prod, prod, cur_expr_num, left_expr_num]
        ;(println (format "%s %s %s %s" total_prod prod cur_expr_num left_expr_num))
        (cond 
            (= cur_expr_num left_expr_num) (* total_prod prod)
            (= cur_expr_num 0) (fast_expr_iter total_prod base_num 1 left_expr_num)
            (> (* cur_expr_num 2) left_expr_num) (fast_expr_iter (* total_prod prod) 1 0 (- left_expr_num cur_expr_num))
            :else (fast_expr_iter total_prod (* prod prod) (* cur_expr_num 2) left_expr_num)))

    (fast_expr_iter 1 1 0 expr_num))
    
;;从大到小分解
(defn fast_expr_big [base_num, expr_num]
    (defn rec_helper[result base_num, expr_num]
        (cond
            (= expr_num 0) result
            (odd? expr_num) (rec_helper (* result base_num) (* base_num 2) (quot expr_num 2))
            :else (rec_helper result (* base_num 2) (quot expr_num 2))))
    (rec_helper 1 base_num expr_num))
    
;;费马素数检测
(defn odd [x] 
    (= (mod x 2) 1))

(defn half_int [x] 
    (int (/ x 2)))

(defn square [x] (* x x))


;;负平方求模， 幂不是1的情况下，将底倍增，注意这里的终止条件是1
(defn exp_mod [base_num exp_num mod_num]
    ;;(print (format "%s %s %s \n" base_num exp_num mod_num))
    (cond 
        ( = 1 exp_num) (mod base_num mod_num)
        (odd? exp_num)
            ;这里利用了 (a*b) mod c = (a * ( b mod c)) mod c
            (mod 
                (* base_num 
                    (exp_mod (mod (square base_num) mod_num) (half_int exp_num) mod_num)) 
                mod_num)
        :else 
            (mod 
                (exp_mod (mod (square base_num) mod_num) (half_int exp_num) mod_num) 
                mod_num)))
                

(defn fermat_test [n]
    (def x (rand-int n))
    (= (exp_mod x n n) x))
 
(defn fast_prime [n times]
    (print (format "%s %s %s \n" x n times))
    (cond 
        (= 0 times) true
        :else
            (if (fermat_test n) (fast_prime n (- times 1))
                false)))
        
    
     
    