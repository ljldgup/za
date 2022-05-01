;第一种
;基于amb风格实现惰性笛卡尔乘积,使用回退点完成
;整个选择集合cols为空,说明所有集合都取过一次
;backword记录每次回退点,第一个集合为空说明当前的选择结束，直接回退

(defn lazy-product-amb[& cols]

    (defn helper[cols, production, backword]
        ;注意这里println会导致惰性流rst被实现，如果有无穷流将导致卡死
        ;(println cols (first production))
        (if (empty? cols)
            ;这里因为后面的选择cons在头部，所以需要逆序
            (cons (reverse production) (lazy-seq (backword)))
            (let [first-col (first cols)
                  rest-cols (rest cols)
                  first-ele (first first-col)]
                (if (empty? first-col)
                    (backword)
                    (recur rest-cols 
                        (cons first-ele production)
                        
                        ;回推到当前搜索集合下一个选择
                        (fn[](helper 
                                (cons (rest first-col) rest-cols)
                                production
                                backword)))))))
    ;顶层回退返回空集
    (helper cols '(), (fn[] '())))
    
    
(lazy-product-amb '(1 2 3) '(5 6 7))

;注意这里如果没有写成(cons 1 (lazy-seq,是无法实现的，因为没有推迟会发现integer没有被定义
(def integer (cons 1 (lazy-seq (map inc integer))))

(take 10 (lazy-product-amb integer '(6 7 8 9 10)))

(first (lazy-product-amb integer '(6 7 8 9 10)))

;直接卡死！！！！
(println (lazy-product-amb integer '(6 7 8 9 10)))

(take 10 (lazy-product-amb integer integer))

----------------------------------------------------------------------
;第二种
;两层map+递归实现，这种实现方式比amb更加简单一些
;两层嵌套+递归，由于延时执行的效果，基本能实现所有正常的递归
(defn lazy-product-recur[& cols]
    ;(println cols)
    (if (and (empty? (first cols)) (empty (rest cols))) 
        '(())
        (let [first-col (first cols)
              rest-production (apply lazy-product-recur (rest cols))]
            ;因为map返回会包一层括号，这里用一次 concat 将内部map包的括号去掉
            ;concat内容是惰性序列，则返回还是惰性序列
            (apply concat
                (map 
                    (fn[ele]
                        (map 
                            (fn[production](cons ele production))
                            rest-production))
                    first-col)))))

(lazy-product-recur '(1 2 3) '(5 7))

;注意这里如果没有写成(cons 1 (lazy-seq,是无法实现的，因为没有推迟会发现integer没有被定义
(def integer (cons 1 (lazy-seq (map inc integer))))

;concat内容是lazy序列，则返回还是惰性序列
(take 10 (concat integer integer))

(take 10 (lazy-product-recur integer '(6 7 8 9 10)))

(first (lazy-product-recur integer '(6 7 8 9 10)))

;直接卡死！！！！
(println (lazy-product-recur integer '(6 7 8 9 10)))

(take 10 (lazy-product-recur integer integer))

------------------------------------------------------------------------
;将过程拆成两个过程执行,内部返回的是惰性序列

(defn append-value[lists, value]
    (map #(cons value %) lists))
    
    
;map会返回一个seq，只能用apply调用concat

(defn append-values[lists, values]
    (apply concat (map #(append-value lists %) values)))
    
;reduce,concat内容是惰性序列，则返回还是惰性序列 
(defn cross-join[& list-values]
    (reduce #(append-values %1 %2) '(()) list-values))
    
    
