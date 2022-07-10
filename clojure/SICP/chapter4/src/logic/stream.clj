(ns logic.stream)
(def the-empty-stream '())

(defn singleton-stream [x]
  (lazy-seq (list x)))

(defn my-extend-interleave [s1 s2]
  (cond (empty? s1) s2
        (empty? s2) s1
        :else (cons (first s1)
                    (cons (first s2)
                          (my-extend-interleave (rest s1) (rest s2))))))

;这里是flatten + clojure的interleave有一个为空据不会在继续出结果
(defn interleave-flatten [stream]
  (if (empty? stream)
    the-empty-stream
    ;
    (my-extend-interleave
      (first stream)
      (lazy-seq (interleave-flatten (rest stream))))))

(defn stream-flatmap [proc s]
  (interleave-flatten (map proc s)))
  
  
(defn stream-flatmap [proc s]
  (interleave-flatten (map proc s)))

;interleave-delayed可以直接用clojure中的interleave
;stream-append-delayed 可以直接用 concat