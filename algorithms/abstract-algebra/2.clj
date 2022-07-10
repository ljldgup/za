;置换循环,模运算加法
(->> (iterate #(mod (+ %1 3) 11) 0) 
    (take 33) 
    (partition 11) 
    (map println))
    
(->> (iterate #(mod (* %1 3) 11) 1) 
    (take 33) 
    (partition 11) 
    (map println))

;随机打乱  
(defn get-random-permutation[n]
    (->> (range n) shuffle vec))

;获得置换的组成
(defn get-cycle-permutation[permutation]
    (println 'permutation permutation)
    (let [result (transient #{})
         visited (transient #{})
         dfs (fn[ele visiting]
                ;(println ele visiting)
                (if (visited ele)
                    (conj! result (persistent! visiting))
                    (do 
                        (conj! visited ele)
                        (recur (permutation ele) (conj! visiting ele)))))]
         (doseq [element (range (count permutation))]
            (if (not (visited element)) (dfs element (transient []))))
         (persistent! result)))

(->> 10 get-random-permutation  get-cycle-permutation)

(->> 13 get-random-permutation  get-cycle-permutation)

;注意 gcd,lcm都是可以reduce的
(defn gcd[a b]
    ;(println a b)
    (if (= b 0)
        a
        (recur b (mod a b))))
(reduce gcd '(60 40 12 80))

(defn lcm[a b]
    (/ (* a b) (gcd a b)))
(reduce lcm '(60 40 12 80))

;例2.52，命题2.55，群元素的阶
;每个r-循环置换，经过r幂次，变成恒等变换，则一个置换变成恒等变换，需要每个循环置换的公倍数的幂次
;其实就是求的元素阶的最小公倍数
(def n 13)
(def permutation-n (get-random-permutation 13))
(def cycle-permutation-n (get-cycle-permutation permutation-n))
(def permutation-n-lcm  (->> cycle-permutation-n (map count) (reduce lcm)))
(def no-change-permutation (apply comp (repeat permutation-n-lcm permutation-n)))
(map no-change-permutation (range n))



;mod n的子群数量，f1群乘积方法
(def n 15)
(defn gen-sub-group[x n f]
    (set (reductions f x (repeat n x))))
    

(def mod-fn #(mod (apply + %&) n))
(gen-sub-set 2 13 mod-fn)
(def all-sub-group (map (fn[x] (gen-sub-group x n mod-fn)) (range 1 (inc n))))

;定理2.72 生成元为φ(n)个,及阶为n的子群数量
(map #(println (key %) (count (val %))) (group-by count all-sub-group))
;φ(n)
(defn get-fain[n] (count (filter  #(= (gcd n %) 1) (range 1 (inc n)))))
(println "φ(n)" (get-fain n))

;命题2.75,阶因子d的子群唯一
(group-by count (distinct all-sub-group))