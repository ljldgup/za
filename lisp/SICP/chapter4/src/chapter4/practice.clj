(ns chapter4.practice
  (:require [chapter4.my-eval :refer :all])
  (:require [chapter4.procedure :refer :all]))

;练习4.4,注意要判断空集表达式
(defn my-eval-or [exp env]
  (cond
    (empty? env) false
    (my-eval (first exp) env) true
    :else (my-eval-or (rest exp) env)))

(defn my-eval-and [exp env]
  (cond
    (empty? env) true
    (not (my-eval (first exp) env)) false
    :else (my-eval-and (rest exp) env)))

(defn let-combination [exp]
  (let [vars-exps (first exp)
        body (second exp)]
    (fn [env]
      (eval
        (make-procedure
          (map first vars-exps)
          body
          (map #(my-eval (second %) env) vars-exps))))))

(defn my-eval-let [exp env]
  ((let-combination exp) env))

;练习4.21, lambda 1 2 3 为从外到内的lambda
;lambda1返回的lambda2 执行的结果，不是返回过程
;lambda3 直接作为参数输入到lambda2
;lambda2 调用lambda3，将lambd3作为参数穿个lambda3，来实现lambda3 递归的过程
((fn [x]
   ((fn [fib] (fib fib x))
    (fn [fib n]
      (cond (= 0 n) 0
            (= 1 n) 1
            :else (+ (fib fib (- n 2)) (fib fib (- n 1)))))))
 40)


