(ns evaluator.environment
  (:require [evaluator.procedure :refer :all]))

; 一个frame是一个map，包含一系列不重复的键值对，来保存变量
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

;这里返回了一个新环境，对其他环境使用者不会有影响
;由于这里新环境是一次性生成的在，所以clojure let那种可以使用上面定义的变量的效果没法实现
;如果要实现这种效果，可以考虑将表达式解释为嵌套的let
(defn extend-environment
  ([vars-vals base-env]
   (cons (make-frame vars-vals) base-env))
  ([vars vals base-env]
   (let [vars-vals (into {} (map #(vector %1 %2) vars vals))]
     (cons (make-frame vars-vals) base-env))))

;;var是关键字，这里改成my_var
(defn look-up-variable [my_var env]
  ;这里查找的变量如果是false也会导致找不到！！！ 只能改成这样
  (let [frame (first (filter #(not (nil? (my_var @%))) env))]
    (print 'look-up-variable my_var " ")
    (if (not (nil? frame))
      (let [val (my_var @frame)]
        ;调试用
        (if (and (seq? val) (> (count val) 2))
          (println (first val) (second val) )
          (println val))
        val)
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

