;空集均为空
(map boolean '(() [] {} 0 nil false))

seq 检查空序列
(map #(->> % seq boolean) '(() [] {}))


;集合类数据结构
(def v [1 2 3 4 5 6])
;conj可以加多个，加在尾部
(conj v 7 8) 

;cons只能加一个，加在头部
(cons 1  v)
(cons 1 2 v) ;错误

;取头部3个
(take 3 v)
;舍弃头部3个
(drop 3 v)
;取子sequence的方法，1是位置，2是长度
(->> v (drop 1) (take 2))
;自带subseq不根据下标操作

;conj，cons都是加在最前面
;加在后面用concat

;clojure的几何操作会根据对象类型进行对应的操作
(empty #{'a})
(empty '(1 2))
(empty {:a 1})

;vec迭代加入vector， vector整个转成vector
(vec '(1 2 3))
(vector '(1 2 3 4))

map创建
{:a 3 :b 11 [1 2 3] 1}
(hash-map :a 3 :b 11 [1 2 3] 1)
;into只能配合vector不能配合list
(into {} '([:a 3] [:b 11] [[1 2 3] 1]))
(zipmap '(:a :b [1 2 3]) '(3 11 1))


;哈希表
(assoc {"a" 1, "b" 2, "c" 1} "a" 10)
(assoc {:b" 2, :c 1} a 10)
(dissoc {'a 10, 'b 2, 'c 1} a)

;update类似swap!的操作，提供的是个函数，或者可以作为函数的列表
(update {:name "James", :age 27} :age inc)
;;{:name "James", :age 28}
(update {:name "James", :age 27} :age + 10)
;;{:name "James", :age 37}
(update [0] 0 inc)


;合并map
(merge {:a 1} {:b 2})

assoc接收三个参数：第一个是向量，第二个是整数索引，第三个是一个值
(assoc [1 2 3] 0 10)  
[10 2 3]  
assoc不会修改原来容器 

;for 产生一个新列表 类似python
(for [[k v] ] [k (inc v)])





;list右侧尾部操作较快
(pop [1 2 3]) 移除尾部
(peek [1 2 3]) 尾部，类似last

;删除特定位置,用subvec，或者filter
(defn remove-n[n elements]
    (concat (subvec elements 0 n) (subvec elements (inc n))))

;递归删除特定位置
(def remove-n[n eles]
    (if (n == 0) 
        (rest eles)
        (cons (first eles) (remove-n (dec n) eles))))
        
定义类型的数组
 (vector-of :int 1.1 Math/PI)



;获取
(get {"a" 1, "b" 2, "c" 1} "a")
({"a" 1, "b" 2, "c" 1} "a")
(:a {:a 2 "b" 2})
('a {'a 3 "b" 1})
;vector也可以做函数
(['a 3 "b" 1] 1)


;set,没有时返回nil,否则返回键值
(map #{:a, 1}  '(1 2 3 :a))

;交叉并集
(clojure.set/intersection #{:b :c} (set (keys {:a 1  :b 2})))
(clojure.set/difference #{:b :c} (keys {:a 1  :b 2}))
(clojure.set/union #{:b :c} (keys {:a 1  :b 2}))

去掉set中的:a
(disj #{:a 1}  :a)
增加
(conj #{1} 2)

;seq 返回列表，是链表实现的
(seq "abfd")
(seq (hash-map :a 3 :b 11 :c 1))    



;惰性列表
(defn random-ints 
    [limit]
    (println "take one random number")
    (lazy-seq 
        (cons (rand-int limit)
        (random-ints limit))))

;等效(repeatedly 10 (random-int 100)
(take 10 (random-ints 100))

;一开始只拿一个，second才调用第二次
(def rands (take 10 (random-ints 100)))
(first rands)
(second rands)
;重复调用还能拿到之前的值，这个和生成器不一样
(first rands)

;last获取最后一个值
(last rands)

;加了map仍然是lazy-seq
(first (map inc rands))
(nth (map inc rands) 2)

;多重操作,
(ffirst '((1 2) 3))
(nnext '(1 2 3))

;next和rest的区别为空时返回nil，rest为空时返回()

lazy-cat，concat可以合并惰性流，  
(lazy-cat xs ys zs) === (concat (lazy-seq xs) (lazy-seq ys) (lazy-seq zs))
(-> (lazy-cat '(1 2) '(3 4) '(5 6)) (nth 3))




展开任意嵌套的数据结构
(flatten '(1 (2 3) (1  (2 (3)))))


mapcat和java中flatmap相同，只展开一层
(mapcat identity '((1 2 3) '(1 (2 3)) (1 (2 (3)))))





;interleave 交替取后面的数据，直到一个为空
(interleave (range 5) (range 6 10) (range 10 15))




;split-with 按条件分成两个惰性序列
(let [[t d] (split-with neg? (range -5 5))]
    (println t d))




;sorted 操作,按key比较
(def sm (sorted-map :a 3 :b 11 :c 1))
(rseq sm)
(subseq sm <= :b)




(sorted-map-by compare :a 3 :b 11 :c 1)
#(comp - compare) 复合- 和compare取原来相反的排序结果
(sorted-map-by (comp - compare) :a 3 :b 11 :c 1)
(sorted-set-by < 3 11 1)

    
;keys vals
(keys (sorted-map :a 3 :b 11 :c 1))
(vals (sorted-map :a 3 :b 11 :c 1))




;group-by 返回map,值是list和java中的是一样的
(group-by #(rem % 3) (range 10))

;frequencies统计类似python中的counter
(frequencies '(1 2 3 "f"))



;注意for返回的是序列，没法直接返回map,需要into
(defn reduce-by
    [key-fn m fn init]
    (into {}
        (for [[k v] (group-by key-fn m)]
            [k (reduce fn init v)])))



(reduce-by #(rem % 3) (range 10) + 0)


 
;易变集合
(def x (transient []))
(conj! x 1)
(count x)

可变集合操作也是返回自己，能用在reduce中
(conj! (conj! (transient []) 1) 2)
;另外可变map数量突破8个时必须用返回的新map，因为从arraymap变成了hashmap


(defn naive-into
    [coll source]
    (reduce conj coll source))


;使用可变容器
(defn faster-into
    [coll source]
    (persistent! (reduce conj! coll source)))

;使用可变容器的效率较高，不可变容器效率较低
(doseq [into_pro '(naive-into faster-into into)]
    (time 
        (do 
            (print into_pro)
            (into_pro #{} (range 1e6)))))

;persistent!修改的不再可用      
(nth (persistent! [1 2 3]) 0)



;利用reduce实现一个带初值的foreach
;assoc-in修改多维集合
(reduce 
    (fn[muti-vector, coordinate](assoc-in muti-vector coordinate "new")) 
    [[1 2] [3 4]] 
    [[0 0] [1 1]])
;多维数组获取
(get-in [[[1 2] [3 4]]]  [0 0])


;for 配合 :when
(for [dx [-1 0 1], dy [-1 0 1] :when (not= 0 dx dy)]
    [dx dy])


;repeat没有指定数量 返回一个无穷的lazy-seq
(repeat nil)
;返回长度为10的惰性序列
(repeat 10 nil)


;lazy-seq 使用变量实现无穷序列，这里实现了一个递增序列，计算第n个使用第n-1加1， 不会嵌套执行导致爆栈
(def x (lazy-seq (cons 1 (map inc x))))



;行转列，map多个序列长度不同会按照最短的来
(map vector (repeat 1) '(1 2 3 4) '(3 2 1))




;利用容器做函数直接过滤，因为不存在的会返回nil
(filter #{:on, :off} '(:on :off :offon :onoff :on))



;rand-nth随机选择集合中的一个
(rand-nth '(1 2 3))
(rand-nth '(1 2 3))


;使用assoc! 向transient map添加元素，因为8的时候从arrayMap 转为 HashMap，
;HashMap不指向自己定义的map，而是通过返回给出，导致只能加8个
(let [t (transient {})]
    (doseq [x (range 1 16)] (assoc! t x (rand-int x)))
    (persistent! t))
    
;reduce每次都会用新的返回值作为被加方，所以能成功
(persistent!
    (reduce 
        #(assoc! %1 (first %2) (second %2)) 
        (transient {}) 
        (for [x (range 1 16)] [x (rand-int x)])))
        

;true = 相当于java equal
(= (conj #{} 1) (conj #{} 1))
;false identical? 相当于java =
(identical? (conj #{} 1) (conj #{} 1))
;true这里应该被编译器优化成同一个了
(identical? #{} #{})

;嵌套seq的操作
(def nested-seq (map #(range % (+ % 5)) (range 5)))
(ffirst nested-seq)
(fnext nested-seq)
;(next (first x))
(nfirst nested-seq)
; (next (next x))
(nnext nested-seq)
;next rest区别在于next没有时候返回空， rest返回'()

;返回一个vector包含pred 为假，真两个seq子集
(split-with #(< (first %) 3) nested-seq)


;返回一个
(split-at 2 nested-seq)


;partition 产生相邻三个元素的序列集合，首尾不产生
(partition 3 1 (range 5))
;增加首尾元素
(partition 3 1 (concat [nil] (range 5) [nil]))

;any?有任意元素返回true
(any? '(false))
;some任意一个满足表达式为真的元素
(some identity '(false))
(some #(not %) '(false))

or 效果类似，or 全不为真返回false
every? 和 and和上面类同
not-every? not-any?效果类似



;数组
(def an-array (int-array 25000 (int 0)))
(amap ^ints an-array 
                   idx 
                   ret 
                   (+ (int 1) 
                      (aget ^ints an-array idx)))
                      
(areduce xs i ret (float 0)
                  (+ ret (aget xs i))))