(defn square [x] (* x x))
(square 11)


(defn abs [x]
   (cond
      (> x 0) x
      :else (- x)))
     
(defn average [x y]
    (/ (+ x y) 2))
    
(defn improve [target guess]
    (average guess (/ target guess)))

(defn good_enough [target guess]
    ;;用于调试
    ;;(println (format "%s , %s" target (float (* guess guess))))
    ;;(println (double (abs (- target (* guess guess)))))
    ;;(Thread/sleep 1000)
    (< (abs (- (* guess guess) target)) 0.001))


(defn sqrt_iter [target guess]
    (if (good_enough target guess)
        (float guess)
        (sqrt_iter target (improve target guess))))


(defn new_if [predict then_statment else_statment]
    (cond 
       predict then_statment
        :else else_statment))
    

;;练习1.3
(defn maxTwoSum [x, y, z]
    (if 
        (and (>= x z) (>= y z)) (+ x y) 
            (if (>= x y) (+ z x) (+ z y))))

(maxTwoSum 1 2 3)

;;练习1.5, 该函数将造成无限递归
(defn p [] (p))

        
      
