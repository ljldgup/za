(ns evaluator.environment
  (:require [evaluator.procedure :refer :all]))


(defn make-frame
  [vars-vals]
  (atom (into {} vars-vals)))


(defn get-first-frame [env]
  (first env))
(defn get-rest-env [env]
  (rest env))

;这里改用map存放 变量绑定
(defn get-frame-variables [frame]
  (keys frame))
(defn get-frame-values [frame]
  (vals frame))
(defn add-binding-to-frame! [my_var value frame]
  (swap! frame assoc my_var value))

(defn extend-environment
  ([vars-vals base-env]
   (cons (make-frame vars-vals) base-env))
  ([vars vals base-env]
   (let [vars-vals (into {} (map #(vector %1 %2) vars vals))]
     (cons (make-frame vars-vals) base-env))))

;;var是关键字，这里改成my_var
(defn look-up-variable [my_var env]
  (let [frame (first (filter #(my_var @%) env))]
    ;(println 'look-up-variable my_var)
    (if (not (nil? frame))
      (my_var @frame)
      (println "unknow varible" my_var))))

(defn set-variable-value! [my_var val env]
  (let [frame (first (filter #(my_var @%) env))]
    (if (not (nil? frame))
      (swap! frame assoc my_var val))))

(defn define-variable! [my_var val env]
  (let [first-frame (get-first-frame env)]
    (add-binding-to-frame! my_var val first-frame)))


(def the-empty-environment '())

(def global-environment
  (extend-environment
    primitives-procedures
    the-empty-environment))

