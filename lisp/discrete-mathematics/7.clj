(defn combination[a b]
    (let [upper (reduce * (range (inc (- a b)) (inc a)))
          lower (reduce * (range 1 (inc b)))]
          (/ upper lower)))
          
;7.1练习15
(def tonghua (* 4 (combination 13 4)))
(def shunzi (* 9 4 4 4 4 4))
(def tonghuashun (* 9 4))
(def total (combination 52 5))
;同花∪顺子 = 同花+顺子-同花顺
(def probility (/ (- total (- (+ tonghua shunzi) tonghuashun)) total))


(defn gcd[a b]
    (if (= b 0) 
        a
        (gcd b (mod a b))))
        
     
;补充练习，练习15     
(defn exercise15[a b]
    (set
        (concat 
            (map #(* % a) (range 1 (inc b)))
            (map #(* % b) (range 1 (inc a))))))

;两个值应该相同
(def a (rand-int  100))
(def b (rand-int  100))
(count (exercise15 a b))
(- (+ a b) (gcd a b))
