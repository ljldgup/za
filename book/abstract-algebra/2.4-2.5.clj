;模17的乘法群
(def group_num 17)
(def func *)

(defn get_sub_group[n] 
    (set (reductions 
			#(mod (func %1 %2) group_num)  
			(repeat group_num n))))
    
;注意乘法群要去掉0，所以大小是17-1=16的因子


(def sub_group 
	(->> (map get_sub_group (range 1 group_num)) 
		set))
(->> sub_group 
	(group-by count) 
	sort 
	(map println))

(def one_group 
	(second 
		(rest (sort-by count sub_group ))))

;陪集
(defn get_coset[n group]
	(set (map #(mod (func n %) group_num) group)))
	
(get_coset (rand-int group_num) one_group)

;商群
(set (map #(get_coset % one_group) (range 1 group_num) ))

;按陪集对单个元素聚合，可以看到得到陪集的元素，都陪集中
(->> 
	(range 1 group_num) 
	(group-by #(get_coset % one_group))
	(map println))
	

	