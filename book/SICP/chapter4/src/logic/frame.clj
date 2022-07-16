(ns logic.frame
  (:require [logic.stream :refer :all]))
;;;;;;;;;;;;;;;;;;; 框架和约束 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;框架是一组约束的表，约束为一个变量值 的 键值对
(defn binding-in-frame [variable frame]
    ;(println 'binding-in-frame variable frame)
  (let [variable-symbol (last variable)
        variable-value (variable-symbol frame)]
    (if variable-value
      (list variable-symbol variable-value))))

(defn make-binding [variable value]
  (list variable value))

(defn my-extend [variable value frame]
    ;(println frame)
  (let [variable-symbol (last variable)]
    (assoc frame variable-symbol value)))

(defn binding-value [binding]
  (second binding))

(defn binding-variable [binding]
  (first binding))

;(defn -main []
;  ;测试
;  (println (binding-in-frame 'x (extend 'x 1 {}))))

(defn merge-frame[frame1 frame2]
    ;(println frame1)
    ;(println frame2)
    (let [same-keys (filter #(contains? frame2 %) (keys frame1))
          to-be-added-keys (filter #(not (contains? frame1 %)) (keys frame2))]
         ;any?是不为空就返回ture，some是任意一个表达式为真返回true
        (if (some #(not (= (% frame1) (% frame2))) same-keys)
            the-empty-stream
            (reduce #(assoc %1 %2 (%2 frame2)) frame1  to-be-added-keys ))))
            
;(def map1 {:a 1 :b 2})
;(def map2 {:c 1 :b 2})


;(let [same-keys (filter #(contains? map2 %) (keys map1))
;      to-be-added-keys (filter #(not (contains? map1 %)) (keys map2))]
;        (println (some #(not (= (% map1) (% map2))) same-keys))
;        (println to-be-added-keys)
;        (println (reduce #(assoc %1 %2 (%2 map2)) map1 to-be-added-keys )))
            
(defn merge-frame-stream[frame-stream1 frame-stream2]
    (if (or (empty? frame-stream1) (empty? frame-stream2))
        the-empty-stream
        (let [first-frame1 (first frame-stream1)
              first-frame2 (first frame-stream2)]
                ;利用流的延时过滤掉空结果
                (filter
                    #(not (empty? %))
                    (cons (merge-frame first-frame1 first-frame2) 
                    (lazy-cat
                        (merge-frame-stream (rest frame-stream1) frame-stream2)
                        (merge-frame-stream frame-stream1 (rest frame-stream2))))))))
                    
                    
;(def map1 {:a 1 :b 2})
;(def map2 {:a 2 :b 3})
;(def map3 {:c 4 :b 2})
;(def map4 {:c 5 :b 3})
           
;(merge-frame-stream (list map1 map2) (list map3 map4))

;(reduce merge-frame-stream (list (list map1 map2) (list map3 map4)))
