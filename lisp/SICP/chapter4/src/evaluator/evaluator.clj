(ns evaluator.evaluator
  (:require [evaluator.syntax :refer :all])
  (:require [evaluator.environment :refer :all])
  (:require [evaluator.procedure :refer :all]))

(defmulti my-eval
          (fn [exp env]
            ;(println :my-eval)
            (cond
              (or (number? exp) (string? exp)) 'self-eval
              (symbol? exp) 'variable
              :else (first exp))))


(defn eval-sequence [exps env]
  (cond (last-exp? exps) (my-eval (get-first-exp exps) env)
        :else (do
                (my-eval (get-first-exp exps) env)
                (recur (rest exps) env))))


(defn my-apply [procedure arguments]
  (cond (primitive-procedure? procedure) (apply-primitive-procedure procedure arguments)
        (compound-procedure? procedure)
        (eval-sequence (get-procedure-body procedure)
                       (extend-environment
                         (get-procedure-parameters procedure)
                         arguments
                         (get-procedure-environment procedure)))
        :else (Exception. (str "unknow procedure type " procedure))))




(defn get-list-of-values [exp env]
  (if (no-operands? exp)
    '()
    (cons (my-eval (get-first-operand exp) env)
          (get-list-of-values (get-rest-operands exp) env))))


(defmethod my-eval 'self-eval [exp env] exp)

(defmethod my-eval 'if [exp env]
  (if (my-eval (get-if-predicate exp) env)
    (my-eval (get-if-consequent exp) env)
    (my-eval (get-if-alternative exp) env)))


(defmethod my-eval 'sequence [exp env]
  (eval-sequence exp env))

(defmethod my-eval 'set! [exp env]
  (set-variable-value! (get-assignment-variable exp)
                       (my-eval (get-assignment-value exp) env)
                       env)
  'ok)
;定义设置，返回ok，防止返回环境导致无穷递归一类
(defmethod my-eval 'define [exp env]
  (define-variable! (get-definition-variable exp)
                    (my-eval (get-definition-value exp) env)
                    env)
  'ok)

(defmethod my-eval 'quote [exp env] (get-text-of-quotation exp))

(defmethod my-eval 'variable [exp env] (look-up-variable exp env))

(defmethod my-eval 'lambda [exp env] (make-procedure (get-lambda-parameters exp)
                                                     (get-lambda-body exp) ;函数交给,my-eval 'sequence,所以需要再包一层
                                                     env))

(defmethod my-eval 'begin [exp env]
  (eval-sequence (rest exp) env))


;练习4.4,注意要判断空集表达式
(defmethod my-eval 'or [exp env]
  (cond
    (empty? env) false
    (my-eval (first exp) env) true
    :else (recur (rest exp) env)))

(defmethod my-eval 'and [exp env]
  (cond
    (empty? env) true
    (not (my-eval (first exp) env)) false
    :else (recur (rest exp) env)))

;练习4.6
(defmethod my-eval 'let [exp env]
  (let [vars-exp (second exp)
        body (rest (rest exp))
        lambda (make-lambda (map first vars-exp) body)]
    (my-apply (my-eval lambda env)
              (map #(my-eval (second %) env) vars-exp))))

(defmethod my-eval :default [exp env]
  (my-apply (my-eval (get-operator exp) env)
            (get-list-of-values (get-operands exp) env)))

;分析和执行在一起的估值器
(defn -main []
  (try
    (let [exps (read-string (read-line))]
      (let [output (my-eval exps global-environment)]
        (println :output output)))
    (catch Exception e (println e)))
  (recur))

