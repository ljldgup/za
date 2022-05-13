;递归定义的数据结构
(defn sub-set[eles]
    (if (empty? eles) 
        '(())
        (let [first-ele (first eles)
             rest-sub-set (sub-set (rest eles))]
            (concat 
                (map #(do (println %) (cons first-ele %)) rest-sub-set)
                rest-sub-set))))

(sub-set (range 5))

;2^5=32
(count (sub-set (range 5)))

(take 1 (sub-set '(a b c d)))
