;就是LeetCode里的word transfer 
;把一组文本转成另外一组文本的最短路径

;这里采用记忆化方法，也可以自低向上用矩阵做
(defn myers-diff[lines1, lines2]
    ;貌似能够强制刷新diff，不加不知道为啥有问题，第一次返回的上一次的结果，diff没有被重新定义
    (def diff)
    (def diff
        (memoize 
            (fn[line-num1, line-num2, result]
                (cond 
                    (= line-num1 (count lines1)) 
                        (concat 
                            result 
                            (map #(list 2 %) (subvec lines2 line-num2)))
                    (= line-num2 (count lines2)) 
                        (concat 
                            result 
                            (map #(list 1 %) (subvec lines1 line-num1)))
                    :else 
                        (let [line1 (nth lines1 line-num1)
                              line2 (nth lines2 line-num2)]
                            (if (=  line1 line2)
                                (diff (inc line-num1) (inc line-num2) (concat result (list (list 0 line1))))
                                (let [result1 (diff (inc line-num1) line-num2 '())
                                    result2 (diff line-num1 (inc line-num2) '())]
                                   ;(println result result1 result1)
                                   (if (< (count result1) (count result2))
                                       (concat result (list (list 1 line1)) result1)
                                       (concat result (list (list 2 line2)) result2)))))))))
                                   

        (diff 0 0 '()))
            
(myers-diff [1 2 3] [1 3 3])
(myers-diff [1 2 3] [2 3])

(myers-diff [1 2 3 3 2 4 5 2 3 4 5 1 2 3] [2 3 2 3 2 3 4 1 2 3 4 5])

(defn print-diff-result[result]
    (doseq [[type line] result]
        (cond 
            (= type 0) (println line "\t|" line)
            (= type 1) (println line "\t| ")
            :else (println " \t|" line ))))

(print-diff-result (myers-diff [1 2 3] [1 3 3]))
(print-diff-result (myers-diff [1 2 3] [2 3]))

(print-diff-result (myers-diff [1 2 3 3 2 4 5 2 3 4 5 1 2 3] [2 3 2 3 2 3 4 1 2 3 4 5]))

(defn rand-in-10[& arg](rand-int 10))

;容易爆栈
(print-diff-result 
    (myers-diff 
        (vec (map rand-in-10 (range 50))) 
        (vec (map rand-in-10 (range 50)))))
        
