(defn infinite-randint-stream[upper]
    (cons (rand-int upper) (lazy-seq (infinite-randint-stream upper))))
(->> (infinite-randint-stream 100) (take 20))

;这里的点有可能重复
(defn gen-positions[n, upper] 
    (for [_ (range n)](list (rand-int upper) (rand-int upper))))
(gen-positions 10 100)
(distinct (gen-positions 100 3))

(defn gen-empty-graph[n] 
    (vec (repeat n #{})))
(gen-empty-graph 10)

(defn gen-empty-record[n] 
    (vec (repeat n 0)))
(gen-empty-record 10)

;生成每个节点为偶数的欧拉通路，这里只是关系，没有具体坐标
;返回的graph是vector，第n个set内容代表点n连接的点
(defn gen-euler-graph[n]
    (loop [graph (gen-empty-graph n)
          record (gen-empty-record n)
          left-set (set (range n))]
          ;(println record (sort left-set) graph )
            (if (= 0 (count left-set))
                graph
                  ;这里一定几率造成死循环，因为可以连接的点用完了，但是还有奇数度的点
                  ;n越小几率越大
                (let [point (first left-set)
                      ;与其连接的点
                      connected (first (filter #(and (not= point %) (not ((graph point) %)))  (infinite-randint-stream n)))
                      new-record (-> record (update point inc) (update connected inc))
                      new-graph (-> graph (update point #(conj % connected)) (update connected #(conj % point)))
                      p-record (new-record point)
                      c-record (new-record connected)
                      ;从连接的两个点确定删除还是保留
                      remove-points (filter #(and (even? (new-record %)) (not= (new-record %) 0)) (list point connected))
                      add-points (filter #(odd? (new-record %)) (list point connected))
                      t-left-set (reduce #(disj %1 %2) left-set remove-points)
                      new-left-set (reduce #(conj %1 %2)  t-left-set add-points)]
                      ;(println remove-points add-points  (sort t-left-set) (sort new-left-set))
                      (recur new-graph new-record new-left-set)))))
                        
(gen-euler-graph 10)

;获取欧拉回路，类似深度搜索
(defn remove-line[graph x y]
    (-> graph (update y #(disj % x)) (update x #(disj % y))))
    
(defn get-head-paths[graph, head]
    (let[next-points (graph head)]
        (if (empty? next-points) 
            (list (list head))
            (let [paths (mapcat #(get-head-paths (remove-line graph % head) %) next-points)]
                (map #(cons head %) paths)))))
        
(defn gen-euler-loop-path[graph]
    (let [line-num (/ (->> graph (map count) (reduce +)) 2)]
        (println line-num)
        (->> (range (count graph))
             (mapcat #(get-head-paths graph %))
             ;删掉没有全部走的通路
             (filter #(= (count %) (inc line-num)))
             first)))

(gen-euler-loop-path [#{1 2} #{0 3} #{0 3} #{1 2}]) 

(def graph (gen-euler-graph 4))
(gen-euler-loop-path graph) 

