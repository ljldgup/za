;模17的乘法群
(def group_num 17)
(defn get_sub_group[n] 
    (set (reductions #(mod (* %1 %2) group_num)  (repeat group_num n))))
    
;注意乘法群要去掉0，所以大小是17-1=16的因子
(map println 
    (sort (group-by count (map get_sub_group (range 1 group_num)))))