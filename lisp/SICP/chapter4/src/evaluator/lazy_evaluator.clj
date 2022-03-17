(ns evaluator.lazy-evaluator
  (:require [evaluator.thunk :refer :all])
  (:require [evaluator.syntax :refer :all])
  (:require [evaluator.environment :refer :all])
  (:require [evaluator.procedure :refer :all]))

(defmulti my-lazy-eval
          (fn [exp env]
            ;(println :my-lazy-eval)
            (cond
              (or (nil? exp) (and (seq? exp) (empty? exp))) 'nothing
              (or (number? exp) (string? exp)) 'self-eval
              (symbol? exp) 'variable
              :else (first exp))))


(def actual-value)

(defn delay-it [exp env]
  (make-thunk exp env))

;这里let中调用actual-value实现递归force,
(defn force-it [obj]
  (cond
    (thunk? obj)
    (let [result (actual-value (thunk-exp obj) (thunk-env obj))]
      (set-thunk! obj (list 'evaluated-thunk result))
      result)
    (evaluated-thunk? obj) (thunk-value obj)
    :else obj))

(defn actual-value [exp env]
  (force-it (my-lazy-eval exp env)))


(defn eval-sequence [exps env]
  (cond (last-exp? exps) (my-lazy-eval (get-first-exp exps) env)
        :else (do
                (my-lazy-eval (get-first-exp exps) env)
                (recur (rest exps) env))))

(defn get-list-of-args-values [exp env]
  (if (no-operands? exp)
    '()
    (cons (actual-value (get-first-operand exp) env)
          (get-list-of-args-values (get-rest-operands exp) env))))

(defn list-of-delayed-arguments [exp env]
  (if (no-operands? exp)
    '()
    (cons (delay-it (get-first-operand exp) env)
          (list-of-delayed-arguments (get-rest-operands exp) env))))

(defn my-apply [procedure arguments env]
  (if (not (primitive-procedure? procedure)) (println (get-procedure-body procedure)))
  (cond (primitive-procedure? procedure) (apply-primitive-procedure procedure (get-list-of-args-values arguments env))
        (compound-procedure? procedure)
        (eval-sequence (get-procedure-body procedure)
                       (extend-environment
                         (get-procedure-parameters procedure)
                         (list-of-delayed-arguments arguments env)
                         (get-procedure-environment procedure)))
        :else (println "unknow procedure type")))




(defn get-list-of-values [exp env]
  (if (no-operands? exp)
    '()
    (cons (my-lazy-eval (get-first-operand exp) env)
          (get-list-of-values (get-rest-operands exp) env))))

(defmethod my-lazy-eval 'nothing [exp env] "null")

(defmethod my-lazy-eval 'self-eval [exp env] exp)

(defmethod my-lazy-eval 'if [exp env]
  (if (actual-value (get-if-predicate exp) env)
    (my-lazy-eval (get-if-consequent exp) env)
    (my-lazy-eval (get-if-alternative exp) env)))


(defmethod my-lazy-eval 'sequence [exp env]
  (eval-sequence exp env))

(defmethod my-lazy-eval 'set! [exp env]
  (set-variable-value! (get-assignment-variable exp)
                       (my-lazy-eval (get-assignment-value exp) env)
                       env)
  'ok)
;定义设置，返回ok，防止返回环境导致无穷递归一类
(defmethod my-lazy-eval 'define [exp env]
  (define-variable! (get-definition-variable exp)
                    (my-lazy-eval (get-definition-value exp) env)
                    env)
  'ok)

(defmethod my-lazy-eval 'quote [exp env] (get-text-of-quotation exp))

(defmethod my-lazy-eval 'variable [exp env] (look-up-variable exp env))

(defmethod my-lazy-eval 'lambda [exp env] (make-procedure (get-lambda-parameters exp)
                                                          (get-lambda-body exp) ;函数交给,my-lazy-eval 'sequence,所以需要再包一层
                                                          env))

(defmethod my-lazy-eval 'begin [exp env]
  (eval-sequence (rest exp) env))


;练习4.4,注意要判断空集表达式
(defmethod my-lazy-eval 'or [exp env]
  (cond
    (empty? env) false
    (my-lazy-eval (first exp) env) true
    :else (recur (rest exp) env)))

(defmethod my-lazy-eval 'and [exp env]
  (cond
    (empty? env) true
    (not (my-lazy-eval (first exp) env)) false
    :else (recur (rest exp) env)))

;练习4.6
(defmethod my-lazy-eval 'let [exp env]
  (let [vars-exp (second exp)
        body (rest (rest exp))
        lambda (make-lambda (map first vars-exp) body)]
    (my-apply (actual-value (my-lazy-eval lambda env) env)
              (map #(my-lazy-eval (second %) env) vars-exp)
              env)))

(defmethod my-lazy-eval 'procedure [exp env] exp)

(defmethod my-lazy-eval :default [exp env]
  (let[ actual-operator (actual-value (get-operator exp) env)]
    (if (nil? actual-operator)
      (println "unknow procedure" (get-operator exp) "!!!")
      (my-apply  actual-operator (get-operands exp) env))))

;分析和执行在一起的估值器
(defn -main []
  (try
    (let [exps (read-string (read-line))]
      (let [output (actual-value exps global-environment)]
        ;返回的不是惰性序列基本就是直接求值
        ;(let [output (my-lazy-eval exps global-environment)]
        (println :output output)))
    (catch Exception e (println e)))
  (recur))



