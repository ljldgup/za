

(defn pairs-2-maps[pairs]
    (let [result {}
          accumulator (fn[rst y]
                    ;(println rst y)
                    (let [[from to] y]
                        (if (rst from) 
                            (assoc rst from (cons to (rst from)))
                            (assoc rst from (list to)))))]
            
        (reduce accumulator {} pairs)))
(pairs-2-maps '())
(pairs-2-maps '((1 2) (2 3) (2 4)))

(defn maps-2-pairs[maps]
    (mapcat (fn[entry](map #(list (first entry) %) (second entry))) maps))
    
(-> '((1 2) (2 3) (2 4)) pairs-2-maps maps-2-pairs)

;9.1练习32
(defn map-relation[relation1, relation2]
    (let [map1 (pairs-2-maps relation1)
          map2 (pairs-2-maps relation2)]
          (maps-2-pairs (into {} (for [[from to] map1]
                            [from (mapcat #(map2 %) to)])))))


(map-relation '((1 2) (2 3) (2 4)) '((2 5) (2 6) (3 7)))
(map-relation '((1 2) (2 3) (2 4)) '((3 5) (4 6) (4 8)))


(defn print-matrix[m]
    (doseq [line m] (println line))
    (println))
    
(defn matrix-bool-union[m1 m2]
    ;(println m1 m2 (number? m1))
    ;可以处理任意维度
    (if (number? m1) 
        (bit-or m1 m2)
        (mapv matrix-bool-union m1 m2)))
    
(print-matrix (matrix-bool-union [[1 1] [1 0]] [[1 0] [1 0]]))
(print-matrix (matrix-bool-union [[[[[0]], [[1]]]]] [[[[[0]],[[1]]]]]))
(print-matrix (matrix-bool-union [[[[[1]]]]] [[[[[0]]]]]))


(defn matrix-multiply[m1 m2]
    ;这里lamdba没有办法简单定义出接受任意参数。。只能直接把代码拼出来
    (let [  tranpose-code (concat '[map vector] m2)
            tranpose-m2 (eval tranpose-code)]
        ;(println tranpose-code)
        (mapv (fn[line1]
                (mapv 
                    ;#(reduce + (map * line1 %)) 
                    ;注意+对应并集*对应交集
                    #(reduce bit-or (map bit-and line1 %)) 
                    tranpose-m2))
              m1)))
(print-matrix (matrix-multiply [[1 2] [3 4]] [[1 2] [3 4]]))
(print-matrix (matrix-multiply [[1 1 1] [1 0 1]] [[1 0] [1 0] [0 1]]))
(print-matrix (matrix-multiply [[1 1 1]] [[1] [1] [0]]))


;M^1,M^2....
(defn matrix-exp-stream
    ([m ans]
        ;(println m ans)
        (let [new-ans (matrix-multiply m ans)]
            (cons ans (lazy-seq (matrix-exp-stream m new-ans)))))
    ([m](matrix-exp-stream m m)))

(->> [[1 0 1] [0 1 0] [1 1 0]] (matrix-exp-stream)  (take 3) (map print-matrix))

;传递闭包
(defn tranpass-closure[m1]
    (let [exp-stream (matrix-exp-stream m1)
          n (count m1)
          ms (take n exp-stream)]
        ;(print (take (count m1) exp-stream))
        (reduce  matrix-bool-union ms )))
        
(->>  [[1 0 1] [0 1 0] [1 1 0]] tranpass-closure print-matrix)

;沃舍尔
(defn warshall[m]
    (defn warshall-1d[m]
        (let [w (->> m (reduce concat) vec transient)
              n (count m)
              get-index (fn[x y](+ (* x n) y))
              get-value (fn[x y](nth w (get-index x y)))]
            (doseq [k (range n) i (range n) j (range n)]
                ;这个直接用了1个矩阵，貌似也是可以的，不影响最终答案
                (assoc! 
                    w 
                    (get-index i j)
                    (bit-or (get-value i j) (bit-and (get-value i k) (get-value k j)))))
            (persistent! w)))
    (let [one-d-result (warshall-1d m)
          n (count m)
          ;直接用partition分割1维度矩阵
          n-d-result (map vec (partition n one-d-result))
          result (vec (reduce conj []  n-d-result))]
          result))
                
            
(->>  [[1 0 1] [0 1 0] [1 1 0]] warshall print-matrix)
    
(defn gen-random-matrix[n]
    (for[x (range n)] 
        (mapv 
            (fn[x](if (> (rand-int 10) 7.5) 1 0)) 
            (range n))))
(def rand-matrix (gen-random-matrix 10))
(->>  rand-matrix tranpass-closure print-matrix)
(->>  rand-matrix warshall print-matrix)
    
    
    
    
    
    
    
    
    
    