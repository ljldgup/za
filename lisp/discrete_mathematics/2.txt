;A-B交集
(clojure.set/intersection #{1 2 3 4} #{1 'a 'b 'c 'd})
;A-B并级
(clojure.set/union #{1 2 3 4} #{1 'a 'b 'c 'd})
;A-B差集
(clojure.set/difference #{1 2 3 4} #{1 'a 'b 'c 'd})

;复合函数
((comp #(* % %) inc) 10)

;偏函数
((partial #(* %1 %2) 3) 2)

;2.5.2有理数集,可以通过映射到
(defn rational_number[]
    (defn helper[n numerator denominator]
         
        (if (= denominator 0)
            (helper (inc n) 1 n)
            (do (println numerator denominator)  
                (cons (/ numerator denominator) 
                    (lazy-seq (helper n (inc numerator) (dec denominator)))))))
    (helper 2 1 1))

(take 10 (rational_number))


;集合的德摩根定律
(def A #{1 2 3 4 5})
(def B #{4 5 6 7})

(filter #(and (not (A %)) (not (B %)))  #{0 1 3 5 7 9})
(filter #(not ((clojure.set/union A B) %))  #{0 1 3 5 7 9})

(filter #(or (not (A %)) (not (B %)))  #{0 1 3 5 7 9})
(filter #(not ((clojure.set/intersection A B) %))  #{0 1 3 5 7 9})