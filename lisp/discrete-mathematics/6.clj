;有重复组合 数量为组合 C(N - 1 + LENGHTH, N-1),N为eles尺寸
(defn reptable-conbination[eles length]
    ;(println eles length)
    (if (= length 0)
        '(())
        (mapcat 
            (fn[rst](map #(cons % rst) eles)) 
            (reptable-conbination eles (dec length)))))

(apply * (repeat 5 7))
(count (reptable-conbination '(1 2 5 10 20 50 100) 5))    
(take 2 (reptable-conbination '(1 2 5 10 20 50 100) 5))

;6.3联系29
(defn get-key [eles]
    (reduce #(+ (* 10 %1) %2) (sort eles)))

;:when跳过nil,:let用到前面元素，造for里面只能用let，否则笛卡尔乘积有问题
(def result-1 
    (filter count
        (for [x (range 1 99)
                y (range 1 101)
                :let [continous-set #{x (+ x 1) (+ x 2)}]
                :when (not (continous-set y))]
         (list x (+ x 1) (+ x 2) y))))
         
;带重复结果98*97
(count result-1)


(def result-2 (into #{} (map get-key  result-1)))

;去重复结果97*97
(count result-2)

6.5练习14
(defn get-conbination[sum-val var-num]
    ;(println sum-val var-num)
    (defn helper[ele]
        (map 
            #(cons ele %)
            (get-conbination (- sum-val ele) (dec var-num))))
    (cond 
        (= var-num 1) (list (list sum-val))
        (< sum-val 0) '(())
        :else (mapcat helper (range (inc sum-val)))))
        
;结果是C（17,4)
(count (get-conbination 17 4))
(/  (* 20 19 18) (* 1 2 3))                
    
;6.6练习16，给定整数，翻译成对应的字典序
;字典序可看成第i位是(n-i)!进制的数   
(defn  factorial[n]
    (if (= n 0) 1
        (* n (factorial (dec n)))))
(def memoize-factorial (memoize factorial))

(defn remove-n[n eles]
    (if (= n 0) 
        (rest eles)
        (cons (first eles) (remove-n (dec n) (rest eles)))))
(remove-n 2 (range 10))

(defn translate-alphabet-order[n eles]
    ;(println n eles)
    (if (or (empty? eles) (>= n (memoize-factorial (count eles))))
        '()
        (let [count-num (count eles)
              choice-num (memoize-factorial (dec count-num))
              position (quot n choice-num)
              ele (nth eles position)]
          ;(println n choice-num position ele)
          (cons 
            ele 
            (translate-alphabet-order 
                (- n (* choice-num position)) 
                ;这里用filter性能有问题，且有相同元素会造成错误
                ;删除操作但普适，clojure没提供普适的删除操作
                ;(filter #(not= % ele) eles)
                (remove-n position eles))))))

注意范围是0~n!-1
(translate-alphabet-order  0 '(a b c d))  
(translate-alphabet-order  2 '(a b c d))
(translate-alphabet-order  23 '(a b c d))        






