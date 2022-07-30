(defn gen-empty-graph[n] 
    (vec (repeat n #{})))
(gen-empty-graph 10)

(defn gen-edges[n]
    (for [x (range n) y (range x)](list x y (rand-int (* n n)))))
(gen-edges 10)

(defn gen-empty-map[n]
    (into {} (for [x (range n)] [ x #{}])))
(gen-empty-map 10)

(defn update-connected-map[connected-map x y]
    (let [set1 (connected-map x)
          set2 (connected-map y)]
          ;(println (= set1 set2))
          ;不知道为什么#{} 两个是相等的
         (if (and (identical? set1 set2) (not set1))
            connected-map
            (let [new-set (->> (clojure.set/union set1 set2) (clojure.set/union #{x y}))
                  update-fn (fn[x]new-set)
                  ;由于不可变，这边必须更新所有的相关的数据集，效率很低
                  ;可变不支持union，遍历等操作，实在太难用！！
                  new-connected-map (reduce #(update %1 %2 update-fn) connected-map new-set)]
                  ;(println 'update new-connected-map)
                  new-connected-map))))
(def (gen-empty-map 10))
(-> init-map  (update-connected-map 2 3) (update-connected-map 1 3))

    
;最小生成树
(defn prim[edges n]
    (loop [v-connected-map (gen-empty-set n)
          used-edges (transient [])
          sorted-edges (sort-by #(nth % 2) edges)
          left-lines (dec n)]
          (if (= 0  left-lines)
              (persistent! used-edges)
              (let [edge (first sorted-edges)
                    rest-sorted-edges (rest sorted-edges)
                    new-v-connected-map (update-connected-map v-connected-map (first edge) (second edge))]
                    (println 'prim new-v-connected-map (identical? new-v-connected-map v-connected-map))
                    (if (identical? new-v-connected-map v-connected-map)
                        (recur v-connected-map used-edges rest-sorted-edges left-lines)
                        (recur new-v-connected-map (conj! used-edges edge) rest-sorted-edges (dec left-lines)))))))
              
          
(def edges (gen-edges 10))
(prim edges 10)