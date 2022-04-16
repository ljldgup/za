;methods是关键字，就是用来管理函数映射的

(def method_map 
{'add {}, 
'sub {}, 
'mul {} 
'div {}
'make {}})

;;因为clojure 参数不可变，method_map值不会变，用def双层map极其繁琐，且会有多线程问题，
;;这种做法无法实现。。

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;clojure 实现了defmulti defmethod 来进行函数派发
;defmulti 定义一个函数返回标志位，然后根据defmethod的同名过程进行选择
;实际使用一般标志位用，:开头关键字来实现，
(defn type_tag [x]
    (first x))
    
(defn attach_tag [t x]
    (cons t x))
    
(defn real [complex_number]
    (nth complex_number 1))
    
(defn image [complex_number]
    (nth complex_number 2))

;#()返回的会自动用括号包围
(defmulti add (fn[x y]
    ;(println x y)
    (list (type_tag x) (type_tag y))))

(defmethod add '(my_number my_number) [x y] 
    (attach_tag 'my_number (list (+ (second x) (second y)))))
    
(defmethod add '(complex_number complex_number)[x y] 
    (attach_tag 'complex_number (list (+ (real x) (real y)) (+ (image x) (image y)))))
    
(defmethod add '(my_number complex_number)[x y] 
    (attach_tag 'complex_number (list (+ (second x) (real y)) (image y))))
    
(defmethod add '(complex_number my_number)[x y] 
    (attach_tag 'complex_number (list (+ (second y) (real x)) (image x))))
    
(defn make_my_number [x] (list 'my_number x))
(defn make_complex_number [x y] (list 'complex_number x y))

;;Wrong number of args (2) passed to: 出现这个错误救是没找到对应派发函数
(add (make_my_number 23)  (make_my_number 12))
(add (make_complex_number 23 12)  (make_complex_number 12 23))
(add '(my_number 1) '(my_number 1))
(add (list 'complex_number 23 12) (list 'complex_number 23 12))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; polymonial 多项式 term 每项常数项 和 幂次项  order 幂次项 coeff 常数项
; 多尝试按照幂次项项order拍过序再输入

(defmulti =zero? #(type_tag %))
(defmethod =zero? 'my_number [n] (= (second n) 0))
(defmethod =zero? 'complex_number [n] (and (= (real n) 0) (= (image n) 0)))
(=zero? (make_my_number 0))

(defmulti larger? #(list (type_tag %1) (type_tag %2)))
;;复数如何比较大小？？
(defmethod larger? '(my_number my_number) [x y] (> (second x) (second y)))

(defn make_poly [v terms]
    (list 'polymonial v terms))

;获取幂次项
(defn get_order [term]
    (if (= (first term) 'term) (second term)))
    
;获取常数项
(defn get_coeff [term]
    (if (= (first term) 'term) (nth term 2)))

;获取变量命
(defn get_varible [p]
    (second p))

(defn make_term [c o]
    (list 'term c o))

(defn get_term_list [p]
    (nth p 2))

(defn empty_term_list? [term_list]
    (empty? term_list))
    
(defn first_term [term_list]
    (first term_list))
    
(defn same_varible? [p1 p2]
    (= (get_varible p1) (get_varible p2)))

;将单个系数加入的多项式系数列表中
(defn adjoin_term [term term_list]
    ;(println term term_list)
    (if (=zero? (get_coeff term))
        term_list
        (cons term term_list)))

    
(defn add_terms [term_list1 term_list2]
    ;(println 'add_terms term_list1 term_list2)
    (cond 
        (empty_term_list? term_list1) term_list2
        (empty_term_list? term_list2) term_list1
        :else 
            (let [t1 (first term_list1), t2 (first term_list2)]
                ;(println 'add_terms_let t1 t2)
                (cond 
                    ;;复数这个>怎么定义？？     
                    (larger? (get_order t1) (get_order t2)) (adjoin_term t1 (add_terms (rest term_list1) term_list2))
                    (larger? (get_order t2) (get_order t1)) (adjoin_term t2 (add_terms (rest term_list2) term_list1))
                    :else (adjoin_term 
                            (make_term (get_order t1) (add (get_coeff t1) (get_coeff t2)))
                            
                            (add_terms (rest term_list1) (rest term_list2)))))))
        
(defn add_poly [p1 p2]
    (if (same_varible? p1 p2)
        (make_poly (get_varible p1) (add_terms (get_term_list p1) (get_term_list p2)))))
    
(defn the_empty_term_list []
    '())


(defmulti mul #(list (type_tag %1) (type_tag %2)))
(defmethod mul '(my_number my_number) [x y] (make_my_number (* (second x) (second y))))
(defmethod mul '(complex_number complex_number) [x y] 
    (make_complex_number
        (- (* (real x) (real y)) (* (image x) (image y)))
        (+ (* (image x) (real y)) (* (image x) (real y)))))
        
(defmethod mul '(my_number complex_number) [x y] 
    (make_complex_number (* (second x) (real y)) (* (second x) (image y))))
(defmethod mul '(complex_number my_number) [x y] 
    (make_complex_number (* (second y) (real x)) (* (second y) (image x))))

;单个式子和表达式相乘
(defn mul_term_by_all_terms [t1 terms1]
    (if (empty_term_list? terms1)
        (the_empty_term_list)
        (let [t2 (first_term terms1)]
            (adjoin_term 
                (make_term 
                    ;多态
                    (add (get_order t1) (get_order t2))
                    (mul (get_coeff t1) (get_coeff t2)))
                (mul_term_by_all_terms t1 (rest terms1))))))

   
;两个表达式相乘   
(defn mul_terms [terms1 terms2]
    (if (empty_term_list? terms1)
        (the_empty_term_list)
        (add_terms 
            (mul_term_by_all_terms (first_term terms1) terms2)
            (mul_terms (rest terms1) terms2))))
            
            
(defn mul_poly [p1 p2]
    (if (same_varible? p1 p2)
        (make_poly (get_varible p1) (mul_terms (get_term_list p1) (get_term_list p2)))))
        
;这里第一项幂指数要从大到小排序
(def poly1 
    (make_poly 'x 
        (list 
            (make_term (make_my_number 3) (make_my_number 2)) 
            (make_term (make_my_number 1) (make_my_number 1)))))
        
(def poly2 
    (make_poly 'x 
        (list 
            (make_term (make_my_number 3) (make_my_number 1)) 
            (make_term (make_my_number 1) (make_my_number 3)))))
            
;;幂次项有复数会造成大小无法判断
(def poly3 
    (make_poly 'x 
        (list 
            (make_term (make_my_number 4) (make_my_number 3)) 
            (make_term (make_my_number 1) (make_complex_number 2 4)))))
        
(def poly4
    (make_poly 'x 
        (list 
            (make_term (make_my_number 3) (make_complex_number 3 3)) 
            (make_term (make_my_number 1) (make_my_number 3)))))

        
(defmulti to_string #(type_tag %))
(defmethod to_string 'my_number [n] (format "%s" (second n)))
(defmethod to_string 'complex_number [n] (format "(%s + %sj)" (real n) (image n)))
(defmethod to_string 'term [term] (format "%sVar^%s" (to_string (get_coeff term)) (to_string (get_order term))))
(defmethod to_string 'polymonial [poly] 
    (.replace 
        (String/join " + " (map to_string (get_term_list poly))) 
        "Var" 
        (str (get_varible poly))))
   
(to_string poly3)
(to_string poly4)


(to_string poly1)
(to_string poly2) 
(to_string (add_poly poly1 poly2))
(to_string (mul_poly poly1 poly2))

(to_string poly3)
(to_string poly4) 
(to_string (add_poly poly4 poly3))
(to_string (mul_poly poly3 poly4))
