(ns evaluator.split-analyze-eval
  (:require [evaluator.syntax :refer :all])
  (:require [evaluator.environment :refer :all])
  (:require [evaluator.procedure :refer :all]))

;;解析和执行分开，返回的lambda中不能再有analyze
;除了sequence其他就是把符号提取出来，lambda封装过程，递归analyze

(defmulti my-analyze
          (fn [exp]
            (cond
              (or (nil? exp) (and (seq? exp) (empty? exp))) 'nothing
              (or (number? exp) (string? exp)) 'self-eval
              (symbol? exp) 'variable
              :else (first exp))))

;块执行无法通过原来的递归实现,原来过程传递了环境这里
(defn analyze-sequence [exps]
  ;sequentially将过程累积，并且使他们共享一个环境
  (defn sequentially [proc1 proc2]
    (fn [env] (proc1 env) (proc2 env)))
  (reduce sequentially (map my-analyze exps)))


(defmethod my-analyze 'self-eval [exp]
  (fn [env] exp))

(defmethod my-analyze 'nothing [exp]
  (fn [env] "null"))

(defmethod my-analyze 'if [exp]
  (let [predict-proc (my-analyze (get-if-predicate exp))
        consequent-proc (my-analyze (get-if-consequent exp))
        alternative-proc (my-analyze (get-if-alternative exp))]
    (fn [env]
      (if (predict-proc env)
        (consequent-proc env)
        (alternative-proc env)))))


(defmethod my-analyze 'sequence [exp]
  (analyze-sequence exp))

(defmethod my-analyze 'set! [exp]
  (let [set-var (get-definition-variable exp)
        set-val-proc (my-analyze (get-definition-value exp))]
    (fn [env]
      (set-variable-value! set-var
                           (set-val-proc env)
                           env)
      'ok)))

(defmethod my-analyze 'define [exp]
  (let [definition-var (get-definition-variable exp)
        definition-val-proc (my-analyze (get-definition-value exp))]
    (fn [env]
      (define-variable! definition-var
                        (definition-val-proc env)
                        env)
      'ok)))

(defmethod my-analyze 'quote [exp]
  (let [text (get-text-of-quotation exp)]
    (fn [env] text)))

(defmethod my-analyze 'variable [exp]
  (fn [env] (look-up-variable exp env)))


; body-proc是 my-analyze 'sequence 返回的函数，
;这里虽然也是用了make-procedure 但封装了过程,在apply中调用方式不同，来得到相同效果
(defmethod my-analyze 'lambda [exp]
  (let [parameters (get-lambda-parameters exp)
        body-proc (analyze-sequence (get-lambda-body exp))]
    (fn [env]
      (make-procedure parameters
                      body-proc
                      env))))


;练习4.4
(defmethod my-analyze 'or [exp]
  (let [analyzers (map my-analyze exp)]
    (fn [env]
      (if (empty? env)
        false
        (some #(% env) analyzers)))))

(defmethod my-analyze 'and [exp]
  (let [analyzers (map my-analyze exp)]
    (fn [env]
      (if (empty? env)
        false
        (every? #(% env) analyzers)))))

;练习4.6
(defmethod my-analyze 'let [exp]
  (let [vars-exp (second exp)
        body (rest (rest exp))
        lambda-analyzer (my-analyze (make-lambda (map first vars-exp) body))
        args-analyzers (map #(my-analyze (second %)) vars-exp)]
    (fn [env]
      (let [procedure (lambda-analyzer env)]
        ((get-procedure-body procedure)
         (extend-environment
           (get-procedure-parameters procedure)
           (map #(% env) args-analyzers)
           env))))))

(defmethod my-analyze 'begin [exp]
  (analyze-sequence (rest exp)))

(defmethod my-analyze :default [exp]
  (defn application-execute [procedure arguments]
    (cond (primitive-procedure? procedure) (apply-primitive-procedure procedure arguments)
          (compound-procedure? procedure)
          ;注意这里body是个lambda，原来是表达式
          ((get-procedure-body procedure)
           (extend-environment
             (get-procedure-parameters procedure)
             arguments
             (get-procedure-environment procedure)))
          :else (println "unknow procedure type")))

  (let [fproc (my-analyze (get-operator exp))
        aproc (map my-analyze (get-operands exp))]
    (fn [env] (application-execute (fproc env) (map #(% env) aproc)))))

(defn my-split-eval [exps env]
  "执行和分析分离"
  ((my-analyze exps) env))

(defn -main []

  (try
    (let [exps (read-string (read-line))]
      ;(let [output (my-eval exps global-environment)]
      (let [output (my-split-eval exps global-environment)]
        (println :output output)))
    (catch Exception e (println e)))
  (recur))