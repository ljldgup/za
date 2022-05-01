;基于惰性的快排，每次取出第一个放到对应位置，然后递归处理该位置前面的元素，直到头部元素就是最小值为止
;循环不变试可理解为第一个seq(part)的所有元素均小于seq右侧的值，（初始化
;惰性序列递归不需要recur
(defn my-sort-parts[work]
    ;(println 1)
    (if (empty? work) '()
        (let [[pivot & parts] work
                smaller? #(< % pivot)]
                (println pivot)
                (lazy-cat 
                    (my-sort-parts (filter smaller? parts))
                    (list pivot)
                    ;这里用remove不需要再定义一个lambda表达清晰
                    (my-sort-parts (remove smaller? parts))))))
                    
(my-sort-parts '(1 2 123 122 2 33))

(defn random-ints[n] (map (fn[x](rand-int 1000000)) (range n)))  
(take 10 (my-sort-parts random-ints))
(println (time (take 10 (my-sort-parts (random-ints 10)))))

(->> (random-ints 10000000) my-sort-parts (take 10))
   
(->> (random-ints 10000000) my-sort-parts (take 1))
