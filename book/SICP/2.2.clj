;;练习2.22
(defn square [x] 
    ;(println x)
    (* x x))

(defn square_list [items]
    (defn helper [answer things]
        ;(println things)
        (if (empty? things) answer
            (helper (conj answer (square (first things)))  (rest things))))
    (helper [] items))
    
(square_list [1 2 3 4 5])


;;练习2.23
(defn subset [s]
    ;(println s)
    (if (empty? s)
        ;两者等效
        ;(list)
        '(())
        (let [rest_set (subset (rest s))]
            ;(println rest_set)
            (concat rest_set (map (fn[x] (cons (first s) x)) rest_set)))))
            
     
(defn accumulate [op init seq]
    ;(println seq)
    (if (empty? seq)
        init
        (op (first seq) (accumulate op init (rest seq)))))
(accumulate + 0 '(1 2 3 4))

;;练习 2.34, accumulate 是递归从结尾开始求的, 这个用reduce是从头部开始求的 实现不了
;;
(defn horner-eval [x coefficient-seq]
    (accumulate (fn[a b] (do (println a b) (+ (* b x) a))) 0 coefficient-seq))
          
;reduce是先取两个，然后再一个个取          
(horner-eval 2 '(1 3 0 5 0 1))       


;;注意是各个序列的同一位置进行操作，实际上用map+解包就可以
(defn accumulate_n [op init seqs]
    (accumulate #(cons %1 (accumulate op init (map %1)
    ;(println seqs)
    (if (or (empty? seqs) (empty? (first seqs)))
        '()
        (cons (accumulate op init (map first seqs))
                (accumulate_n op init (map rest seqs)))))
    ;用map实现，缺个解包,需要用符号完成比较烦
    ;(map (fn[x y](if (= (type x) (type '())) (cons x y) (list x y))) seqs)
    
(accumulate_n + 0 '((1 2 3 4) (11 22 33 44)))

;;练习2.37
(defn dot-product [v w]
    (reduce + 0 (map * v w)))
    
(dot-product '(1 2 3 4) '(4 3 2 1))

(defn matrix_*_vector [m v]
    (map (fn[w](dot-product v w)) m))
    
(matrix_*_vector '((4 3 2 1) (1 2 3 4)) '(1 2 3 4) )
                
(defn transpose [m]
    (accumulate_n cons '() m))
(transpose '((4 3 2 1) (1 2 3 4)))
    
(defn matrix_*_matrix [m n]
    (let [cols (transpose n)]
        (map (fn [v](matrix_*_vector m v)) cols)))
            
(matrix_*_matrix '((1) (2)) '((3 4))) 
      
(matrix_*_matrix '((3 4)) '((1) (2)))             
            
;;嵌套映射
(def primes #{2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 \
    53 59 61 67 71 73 79 83 89 97 101 103 107 109 113})
(defn prime? [x]
    (contains? primes x))

(sort #(< (first %1) (first %2)) 
    (filter #(prime? (reduce + %)) 
        (reduce concat '() 
            (map 
                (fn[x](map (fn[y] (list x y)) (range 1 x))) 
                (range 1 7)))))
                

(defn remove[x s]
    (filter #(not= x %) s))
       
;;注意这里因为要map 增加新元素，返回空的时候要返回嵌套元素
;;否则永远为空       
(defn permutations [seq]
    ;(println seq)
    (if (empty? seq)
        '(())
        (reduce concat 
            (map (fn[x]  
                 ;(println "outer" x)
                 (map 
                    (fn[s]
                        ;(println "inner" s) 
                        (cons x s))               
                    (permutations (remove x seq))))  
                 seq))))
                 
