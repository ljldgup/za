(ns evaluator.thunk
  (:import (clojure.lang Atom)))
;惰性求值的槽位实现


(defn make-thunk[exp env]
  (atom (list 'thunk exp env)))

(defn thunk? [exp]
  (and
    (= Atom (type exp))
    (= 'thunk (first @exp))))

(defn thunk-env [exp]
  (rest (rest @exp)))

(defn thunk-exp [exp]
  (second @exp))

;已经被求值的槽位
(defn evaluated-thunk?[exp]
  (and
    (= Atom (type exp))
    (= 'evaluated-thunk (first @exp))))

(defn thunk-value[evaluated-thunk]
  (second @evaluated-thunk))

(defn set-thunk![obj exp]
  (reset! obj exp))




