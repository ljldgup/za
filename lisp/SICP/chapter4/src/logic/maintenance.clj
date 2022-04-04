(ns logic.maintenance
  (:require [logic.stream :refer :all])
  (:require [logic.syntax :refer :all])
  (:require [logic.frame :refer :all])
  (:require [logic.maintenance :refer :all]))
;;;;;;;;;;;;;;;;;;数据库索引等维护;;;;;;;;;;;;;;;;
(def DATABASE (atom {}))

(def THE-ASSERTION (atom the-empty-stream))

(defn my-put [key1 key2 item]
  (if (contains? @DATABASE key2)
    (let [data (key2 @DATABASE)]
      (swap! DATABASE
             #(assoc % key2 (assoc data key1 item))))
    (swap! DATABASE
           #(assoc % key2 {key1 item})))
  ;(println @DATABASE)
  )


(defn my-get [key1 key2]
  (key1 (key2 @DATABASE)))

(defn get-stream [key1 key2]
  (let [s (my-get key1 key2)]
    (if s s the-empty-stream)))

(defn use-index? [pat]
  (constant-symbol? (first pat)))

(defn index-key-of [pat]
  (let [key (first pat)]
    (if (variable? key) '? key)))

;第一个元素是符号或者变量才能索引
(defn indexable? [pat]
  (or (constant-symbol? (first pat))
      (variable? (first pat))))



(defn store-rule-in-index [rule]
  (let [pattern (conclusion rule)]
    (if (indexable? pattern)
      (let [key (index-key-of pattern)]
        (let [current-rule-stream (get-stream key 'rule-stream)]
          (my-put key
                  'rule-stream
                  (cons rule current-rule-stream)))))))

(defn store-assertion-in-index [assertion]
  (if (indexable? assertion)
    (let [key (index-key-of assertion)]
      (let [current-assertion-stream (get-stream key 'assertion-stream)]
        (my-put key
                'assert-stream
                (cons assertion current-assertion-stream))))))

(def THE-RULES (atom the-empty-stream))

(defn add-rule! [rule]
  (store-rule-in-index rule)
  (swap! THE-RULES #(cons rule %))
  'ok)


(defn add-assertion! [assertion]
  (store-assertion-in-index assertion)
  (swap! THE-ASSERTION #(cons assertion %))
  ;(println 'THE-ASSERTION @THE-ASSERTION)
  'ok)

(defn add-rule-or-assertion! [assertion]
	;(println assertion)
  (if (rule? assertion)
    (add-rule! assertion)
    (add-assertion! assertion)))


(defn get-stream [key1 key2]
  (let [s (my-get key1 key2)]
    (if s s the-empty-stream)))

(defn get-all-rules [] @THE-RULES)

;concat 代替stream-append
(defn get-indexed-rules [pattern]
  (concat
    (get-stream (index-key-of pattern) 'rule-stream)
    (get-stream '? 'rule-stream)))


(defn fetch-rules [pattern frame]
  (if (use-index? pattern)
    (get-indexed-rules pattern)
    (get-all-rules)))





(defn get-all-assertions [pattern] @THE-ASSERTION)

(defn get-indexed-assertions [pattern]
  (get-stream (index-key-of pattern) 'assert-stream))

(defn fetch-assertions [pattern frame]
  ;(println (get-all-assertions nil))
  (if (use-index? pattern)
    (get-indexed-assertions pattern)
    (get-all-assertions pattern)))

;(defn -main []
;  (my-put :aa :bb 1)
;  (println (my-get :aa :bb)))