;13.2例5,单位延迟机

;这里直接用一个map来表示输入带来的状态变化，状态隐含在value中的函数中，就是list ?
(def machine-s1-s2 {0,(fn[x](list 0 (machine-s1-s2 x))) 1,(fn[x](list 1 (machine-s1-s2 x)))})
(def s0 (fn[x](list 0 (machine-s1-s2 x))))
(def input (repeatedly 20 #(rand-int 2)))
(loop [signals input
        status s0]
        (if (not (empty? signals))
            (let [signal (first signals)
                  [output new-status] (status signal)]
                (println signal output)
                (recur (rest signals) new-status))))
                
;不用loop的遍历方案          
(defn status-reducer[status signal]
    (let [[output new-status] (status signal)]
        (println signal output)
        new-status))
(reduce status-reducer s0 input)