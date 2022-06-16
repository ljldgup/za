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
;                (println signal output)
                (recur (rest signals) new-status))))
                
;不用loop的遍历方案          
(defn status-reducer[status signal]
    (let [[output new-status] (status signal)]
;        (println signal output)
        new-status))
(reduce status-reducer s0 input)



;自动机器正则匹配

;单个字符匹配  
(defn ch-match? [pattern-chs raw-ch]
;    (println 'ch-match? pattern-chs raw-ch )
    (if (or (= pattern-chs :any-ch) (pattern-chs raw-ch))
        true
        false))

;固定长度匹配，返回lamdba，传入下一个状态生成匹配函数
(defn fixed-match-status [pattern-chs length]
;    (println 'fixed-match-status pattern-chs length)
    (fn[next-status]
        ;(println next-status)
        (fn[string]
;            (println pattern-chs string)
            (if (< (count string) length) 
                nil
                (let [raw-str (take length string)
                      rest-string (subs string length)]
                    (if (every? #(ch-match? pattern-chs %)  raw-str)
                        (if-let[rest-matched-str (next-status rest-string)]
                            (concat raw-str rest-matched-str))))))))
							
;单个匹配，返回lamdba，传入下一个状态生成匹配函数
(defn single-match-status [pattern-chs]
    (fixed-match-status pattern-chs 1))

;匹配结束
(defn final-status[string] '( \n ) )

;把status作为raw-status下一个调用的匹配器
(defn assembly-status[raw-status status]
    ;(println raw-status status)
    (raw-status status))

(defn choose-generator[args]
;        (println args (first args) (keyword? (first args)))
        (if (keyword? (first args))
            (first args) 
            (count args)))
        
(defmulti gen-status choose-generator)

;并行化状态，用于或
(defn or-assembly-status[parsed-patterns]
;    (println 'or-assembly-status parsed-patterns)
    (fn[next-status]
        ;把每个过程和下一个过程串联
        (let [new-statuses (map 
                                #(assembly-status %1 next-status) 
                                (map gen-status parsed-patterns))]
            (fn[string]
                ;返回第一个能匹配的结果，失败继续尝试下次，实现回溯
                (some #(% string) new-statuses)))))
                
(defn serial-status-assemble [parsed-patterns]
;    (println 'serial-assembly-status parsed-patterns)
    (fn[next-status]
        (reduce 
            #(assembly-status %2 %1) 
            next-status
            (reverse (map gen-status parsed-patterns)))))
                
;不是or就是and，and根据入参确定是单个还是定长，还是范围
(defmethod gen-status :or [patterns]
    (or-assembly-status (rest patterns)))
(defmethod gen-status :serial [patterns]
    (serial-status-assemble (rest patterns)))
(defmethod gen-status 1 [patterns]
    (apply single-match-status patterns))
(defmethod gen-status 2 [patterns]
    (apply fixed-match-status patterns))


(((gen-status '(#{\a})) final-status) "a")
(((gen-status '(#{\a} 2)) final-status)  "aab")
(((gen-status '(#{\a} 2)) final-status)  "ab")
(((gen-status '(:serial (#{\a} 2) (#{\b})))  final-status) "aabc")
(((gen-status '(:or (#{\a} 2) (#{\b}))) final-status) "aabc")
(((gen-status '(:or (#{\a} 2) (#{\b}))) final-status) "babc")

(def patterns '(:serial (#{\a} 2) (:or (#{\d \c \b}) (#{\e} 3)) (#{\f} 2)))
(def regular-match-machine ((gen-status patterns) final-status))

(regular-match-machine  "aabffwe")
(regular-match-machine  "aaaffwe")
(regular-match-machine  "aaeeeffwe")
(regular-match-machine  "aaeeffwe")