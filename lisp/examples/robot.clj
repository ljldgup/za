(def bearing [{:x 0, :y 1} {:x 1 :y 0} {:x 0 :y 1} {:x -1 :y 0}])

;这里通过返回匿名函数，匿名函数右调用自己达到一种可以无穷调用的效果
;同时通过返回map带有额外的信息，类似对象
(defn bot [x y bearing-num]
    {:coord [x y]
    :bearing ([:nort :east :south :west] bearing-num)
    :forward (fn[](bot (+ x (:x (bearing bearing-num)))
                       (+ y (:y (bearing bearing-num)))
                       bearing-num))
    :turn-right (fn[](bot x y (mod (+ 1 bearing-num) 4)))
    :turn-left  (fn[](bot x y (mod (- 1 bearing-num) 4)))})
    
(:bearing ((:forward ((:forward ((:turn-right (bot 5 5 0))))))))
(:bearing (reduce #((%1 %2)) (bot 5 5 0) '( :turn-right :forward :forward)))
(:coord (reduce #((%1 %2)) (bot 5 5 0) '( :turn-right :forward :forward)))