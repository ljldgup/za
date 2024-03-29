;8.6练习7，不是正整数次幂的数字
(def integers (cons 1 
                (lazy-seq (map inc integers))))
                
(defn exp-stream[n]
        (map #(-> % (Math/pow n) long) (rest integers)))

(->> (map exp-stream integers) (take 10) (map first))

(defn sort-streams
    ([streams](sort-streams (first streams) '() (rest streams)))
    ([stream, left-streams, right-streams]
        (let [num (first stream)
            right-num (-> right-streams first first)]
            ;(println num right-num (< num right-num))
            (if (< num right-num) 
                (concat (reverse left-streams) (list stream) right-streams)
                (recur stream (cons (first right-streams) left-streams) (rest right-streams))))))

(defn remove-first-first[streams]
    (cons (-> streams first rest) (rest streams)))
    
(remove-first-first '((1 2 3) (1 2 3)))
(sort-streams '((4 3) (1 2 3) (5 2 3)))
;流中的每个元素都是一个幂次项流，如4 9 16 25
(defn interleave-sorted[streams]
    (cons 
        (-> streams first first)
        (lazy-seq (interleave-sorted (-> streams remove-first-first sort-streams)))))

(->> (map exp-stream (rest integers)) interleave-sorted distinct (take 100))
    
;展开e^-1,1-1/1! + 1/2!......
(defn e-series
    ([n rst] 
        (let [new-rst (* -1 (/ rst n))]
            (cons new-rst (lazy-seq (e-series (inc n) new-rst)))))
    ([](cons 1 (e-series 1 1))))
    
;错位排列Dn
(defn misplace[n]
    (* 
        (reduce * (range 1 (inc n))) 
        (reduce + (take (inc n) (e-series )))))