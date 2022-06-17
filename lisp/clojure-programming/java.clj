静态函数调用，clojure不需要使用try
Thread/sleep 1000

(.getTime (new Date))

异常，clojure不是必须
 (try (throw (Exception. "error")) (finally (println "final")))  
 (new Exception "sdf")
 (try (/ 3 0) (catch Exception e (println e)))  
 (assert true)  
 
 
doto 将第一个式子的结果加到后面每个列表的最后一个执行
(doto 1 (println 1 ) (println 2 ) (println 3))
doto 适合java对象操作
(object 1 (.setXxx 1 ) (.setXxx 2 ))


(def frame (java.awt.Frame.))
;匹配查找函数
(for [meth (.getMethods java.awt.Frame)
            :let [name (.getName meth)]
            :when (re-find #"Vis" name)] name)
            
(.setVisible frame true)
(.setSize frame (java.awt.Dimension. 200 200))
(def gfx (.getGraphics frame))
(.fillRect gfx 100 100 50 75)

(defn xors[max-x max-y]
    (for [x (range max-x) y (range max-y)]
        [x y (rem (bit-xor x y) 256)]))
        
(doseq [[x y xor] (xors 1000 1000)]
    (.setColor gfx (java.awt.Color. xor xor xor))
    (.fillRect gfx x y 1 1))
(.dispose frame)

;set! 反射setXxx效果
;bean返回bean map
(let [object (java.awt.Point. 1 2)]
        (set! (. object  -y) 8)
        (bean object)
        )

;也能遍历打印出来结果，比transient好用。。
(doto (java.util.HashMap.)
      (.put "a" 1)
      (.put "b" 2)
      (map println))
      
;java的作用范围有问题。。不能直接把.add作为函数
(reduce #(do (.add %1 %2) %1) (java.util.ArrayList.) (range 10))

(def x (java.util.ArrayList.))
(.add x 1)
;没办法作为流使用
(map #(do (.add x (inc %)) %) x)

;java的数据结构也能遍历
(map println (reduce #(do (.add %1 %2) %1) (java.util.ArrayList.) (range 10)))


;优先队列可以轻松的指定一个比较器
(doto (java.util.PriorityQueue. (fn[x,y](> x y)))
      (.add 3)
      (.add 5)
      (.add 1)
      (map #(.pop %)))
      

;实现接口 
(defrecord com-imp []
    java.util.Comparator
    (compare   [this i j] (if (> i j) 1 0)))
(.compare (com-imp.) 1 2)

(def graph [[4 5] [1 2] [4 3] [2 6] [1 3] [2 4] [3 5]])
(defn bfs[graph n]
	(let [visited (java.util.HashSet.)
	      queue (java.util.LinkedList.)
		  update (fn[_ v]
					(doseq[x (filter #(not (.contains visited %)) (graph v))]
						(do (.add queue x) (.add visited x) (println x)))) ]
		(doseq [v queue] (update nil v))
		;没办法作为流使用
		;(reduce update queue nil)
		;(map update queue nil)
		queue))
(bfs graph (count graph))