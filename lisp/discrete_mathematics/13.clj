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



;自动机器正则匹配
;匹配结束
(defn final-status[string] '( \n ) )
(final-status "123123")

    
(defn ch-match? [raw-ch pattern-chs]
    (if (or (= pattern-chs :any-ch) (pattern-chs raw-ch))
        true
        false))




;固定长度匹配，返回lamdba，传入下一个状态生成匹配函数
(defn fixed-match-status [pattern-chs length]
    ;(println pattern-chs length)
    (fn[next-status]
        ;(println next-status)
        (fn[string]
            (println pattern-chs string)
            (if (< (count string) length) 
                nil
                (let [raw-str (take length string)
                      rest-string (subs string length)]
                    (if (every? #(ch-match? % pattern-chs)  raw-str)
                        (if-let[rest-matched-str (next-status rest-string)]
                            (concat raw-str rest-matched-str))))))))
							
;单个匹配，返回lamdba，传入下一个状态生成匹配函数
(defn single-match-status [pattern-chs]
    (fixed-match-status pattern-chs 1))
						
(defmulti gen-status (fn[& args](if (= :or (first args) :or (keyword (str "and" (count args)))))))

;把status作为raw-status下一个调用的匹配器
(defn assembly-status[status raw-status]
    (println status raw-status)
    (raw-status status))

;并行化状态，用于或
(defn parallel-status[& statuses]
    (fn[next-status]
        (let [new-statuses (map 
                                #(assembly-status %1 next-status) 
                                (map gen-statuses statues))]
            (fn[string]
                (some #(% string) new-status)))))

;不是or就是and，and根据入参确定是单个还是定长，还是范围
(defmethod gen-status :or [pattern-chs]
    (single-match-status pattern-chs))
(defmethod gen-status :and1 [pattern-chs]
    (single-match-status pattern-chs))
(defmethod gen-status :and2 [pattern-chs length]
    (fixed-match-status pattern-chs length))





(gen-status \a)
(gen-status \a 2)

(def parsed-pattern '((#{\a} 2) (:or (#{\d \c \b}) (#{\e} 3))) (#{\a}))
(def regular-match-machine (reduce 
                #(assembly-status %1 %2) 
                final-status 
                (reverse (map #(apply gen-status %) parsed-pattern))))

(regular-match-machine  "aabsadfwe")
(regular-match-machine  "absadfwe")
(regular-match-machine  "aaccccc")
(regular-match-machine  "aadef")