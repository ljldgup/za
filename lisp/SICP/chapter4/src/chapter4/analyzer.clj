(ns chapter4.analyzer
  (:require [chapter4.syntax :refer :all])
  (:require [chapter4.environment :refer :all])
  (:require [chapter4.procedure :refer :all]))

;;解析和执行分开，返回的lambda中不能再有analyzer

(defmulti my-analyzer
          (fn [exp]
            (cond
              (or (number? exp) (string? exp)) 'self-eval
              (symbol? exp) 'variable
              :else (first exp))))

;块执行无法通过原来的递归实现,内部函数好像都会报黄
(defn analyzer-sequence [exps]
  ;sequentially将过程累积，并且使他们共享一个环境
  (defn sequentially [proc1 proc2]
    (fn [env] (proc1 env) (proc2 env)))
  (reduce sequentially (map my-analyzer exps)))


(defmethod my-analyzer 'self-eval [exp]
  (fn [env] exp))

(defmethod my-analyzer 'if [exp]
  (let [predict-proc (my-analyzer (get-if-predicate exp))
        consequent-proc (my-analyzer (get-if-consequent exp))
        alternative-proc (my-analyzer (get-if-alternative exp))]
    (fn [env]
      (if (predict-proc env)
        (consequent-proc env)
        (alternative-proc env)))))


(defmethod my-analyzer 'sequence [exp]
  (analyzer-sequence exp))

(defmethod my-analyzer 'set! [exp]
  (let [set-var (get-definition-variable exp)
        set-val-proc (my-analyzer (get-definition-value exp))]
    (fn [env]
      (set-variable-value! set-var
                           (set-val-proc env)
                           env)
      'ok)))

;定义设置，返回ok，防止返回环境导致无穷递归一类
(defmethod my-analyzer 'define [exp]
  (let [definition-var (get-definition-variable exp)
        definition-val-proc (my-analyzer (get-definition-value exp))]
    (fn [env]
      (define-variable! definition-var
                        (definition-val-proc env)
                        env)
      'ok)))

(defmethod my-analyzer 'quote [exp]
  (let [text (get-text-of-quotation exp)]
    (fn [env] text)))

(defmethod my-analyzer 'variable [exp]
  (fn [env] (look-up-variable exp env)))

(defmethod my-analyzer 'lambda [exp]
  (let [parameters (get-lambda-parameters exp)
        body-proc (analyzer-sequence (get-lambda-body exp))]
    (fn [env]
      (make-procedure parameters
                      body-proc                             ;函数交给,my-analyzer 'sequence,所以需要再包一层
                      env))))

(defmethod my-analyzer 'begin [exp]
  (analyzer-sequence exp))

(defmethod my-analyzer :default [exp]
  (defn application-execute [procedure arguments]
    (cond (primitive-procedure? procedure) (apply-primitive-procedure procedure arguments)
          (compound-procedure? procedure)
          ;注意这里body是个lambda，原来是表达式
          ((get-procedure-body procedure)
           (extend-environment
             (get-procedure-parameters procedure)
             arguments
             (get-procedure-environment procedure)))
          :else (Exception. (str "unknow procedure type" procedure))))

  (let [fproc (my-analyzer (get-operator exp))
        aproc (map my-analyzer (get-operands exp))]
    (fn [env] (application-execute (fproc env) (map #(% env) aproc)))))

(defn my-split-eval [exps env]
  "执行和分析分离"
  ((my-analyzer exps) env))