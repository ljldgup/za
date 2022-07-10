(ns evaluator.execise
  (:require [evaluator.evaluator :refer :all])
  (:require [evaluator.procedure :refer :all]))


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


