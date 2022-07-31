并行交错的可能性
假设a有n条指令，b有m条指令
两者交错，首先a，b自身指令相对顺序不变，可以看成将b的m条指令插入a的n+1个槽位中，

b只占用a中k个槽位则，将b中指令分为k组
相当于在排好序的m个命令中插入k-1个板,不能插在两边
即C(m-1,k-1)

此时插入a的可能性为C(n+1,k)
所以可能性为∑C(m-1,k-1)*C(n+1,k)
k=1,...m

(defn c[n m] 
    ;(printf "C(%d, %d)\n", n, m)
    (reduce #(* %1 (/ (- n %2 -1) %2)) 1 (range 1 (inc m))))
(c 10 10)
(c 10 1)
(c 10 2)
(c 10 11)

;输入指令交错排序数量
(defn possibilities[n m](reduce #(+ %1 (* (c (dec m) (dec %2)) (c (inc n) %2))) 0 (range 1 (inc m))))
(possibilities  1 3)

(possibilities  3 1)

(possibilities  11 13)

(possibilities  13 11)


(defn real_possibilities[t-rst ns ms]
    (if (empty? ns) 
        (list (concat (reverse ms) t-rst))
        (if (empty? ms)
            (list (concat (reverse ns) t-rst))
            (lazy-cat 
                (real_possibilities (cons (first ns) t-rst) (rest ns) ms)
                (real_possibilities (cons (first ms) t-rst) ns (rest ms))))))
                
(count (real_possibilities '() '(a b c) '(1 2 3 4)))

(possibilities  3 4)