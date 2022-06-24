(defn gcd[a b]
    (if (= a 0) 
        (list b 0 1)
        (let [  r1 (mod b a)
                q (/ (- b r1) a)
                ;r2 = k1*r1 + k2*a = k1*(b - q*a)+k2*a= k1*b +(k2 -k1*q)*a
                [r2 k1 k2] (gcd r1 a)]
            (list r2 (- k2 (* k1 q)) k1 ))))
            
(defn vis_gcd[x y]
    (let [[r a b] (gcd x y)]
        (println a "*" x "+" b "*" y "=" r)))
        
(vis_gcd 24 42)

;复平方求模
(defn exp-mod[b n m]
    ;(println b n m)
    (cond 
        (= n 0) 1
        (= m 1) 0
        :else 
            (let [half (exp-mod b (quot n 2) m)]
                ;(println half)
                (if (= (mod n 2) 1)
                    (-> (* half half) (* b) (mod m))
                    (-> (* half half) (mod m))))))
(exp-mod 3 644 645)

;递归定义的随机数生成器 7 4 9可以得到随机数
(take 10 (iterate #(mod (+ (* % 7)  4) 9) 3))
;7 4 6不行，周期只有3
(take 10 (iterate #(mod (+ (* % 7)  6) 9) 3))

(defn random-generator-test[m]
    ;初始值0
    (doseq [a (range 1 m) b (range 1 m)]
        (let [nums (take m (iterate #(mod (+ (* % a)  b) m) 0))]
            (if (= (count (distinct nums)) m)
                (do 
                    (println a b m)
                    (doseq [x nums] (print x " "))
                    (println))))))
;基本上a b 和m公约数都是1
;m是奇数效果更好
(random-generator-test 9)
(random-generator-test 11)