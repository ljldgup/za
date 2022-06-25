;¬∧∨→←

#异或
(for [x (range 2) y (range 2)] 
    (println x y 'xor (bit-xor x y)))
(doseq [x (range 2) y (range 2)] 
    (println x y 'xor (bit-xor x y)))

;笛卡尔乘积实现，惰性
(defn append-value[lists, value]
    (map #(cons value %) lists)) 
;map会返回一个seq，只能用apply调用concat
(defn append-values[lists, values]
    (mapcat #(append-value lists %) values))
(defn cross-join[& list-values]
    (reduce #(append-values %1 %2) '(()) list-values))

(def bool-values (list true false))
;n对真假值得笛卡尔乘积
(defn muti-bool-values[n]
    (apply cross-join (repeat n bool-values)))

(defn printAlign[& args](doseq [arg args] (print arg "\t"))(println))

检验左式和右式子是否相等
(defn law-check[n left-op, right-op]
    (doseq [values (muti-bool-values n)]
        (let [left-result (apply left-op values)
              right-result (apply right-op values)]
            (printAlign values left-result right-result))))

;德摩根定义 
;¬(X∧Y)等价(¬X)∨(¬Y)
;¬(X∨Y)等价(¬X)∧(¬Y)
;这里用符号将导致true false变成符号
(law-check 2 #(or (not %1) (not %2)) #(not (and %1 %2)))
(law-check 2 #(and (not %1) (not %2)) #(not (or %1 %2)))
        
;交换律
(law-check 2 #(or %1 %2) #(or %2 %1))

;结合律
(law-check 3 #(or (or %1 %2) %3) #(or %1 (or %2 %3)))
(law-check 3 #(and (and %1 %2) %3) #(and %1 (and %2 %3)))

;分配律
(law-check 3 #(and (or %2 %3) %1) #(or (and %2 %1) (and %3 %1)))
(law-check 3 #(or (and %2 %3) %1) #(and (or %2 %1) (or %3 %1)))

;条件命题 及其逆否命题登记分配律
;X->Y 等价 X∧¬Y, ¬Y->¬X 等价 ¬Y∧X,
(law-check 2 #(and %1 (not %2)) #(and (not %2) %1))

;量词的德摩根定律
(law-check 3 #(every? (complement identity) %&) #(not (some identity %&)))
(law-check 3 #(some (complement identity) %&) #(not (every? identity %&)))
