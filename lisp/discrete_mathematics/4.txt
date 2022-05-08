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