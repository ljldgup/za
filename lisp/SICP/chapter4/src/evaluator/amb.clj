(ns evaluator.amb
  (:require [evaluator.syntax :refer :all])
  (:require [evaluator.environment :refer :all])
  (:require [evaluator.procedure :refer :all]))

(defn amb-choice [exp]
  (rest exp))

(defmulti my-amb-analyze
          (fn [exp]
            (cond
              (or (nil? exp) (and (seq? exp) (empty? exp))) 'nothing
              (or (number? exp) (string? exp)) 'self-eval
              (symbol? exp) 'variable
              :else (first exp))))


(defn analyze-sequence [exps]
  (defn sequentially [proc1 proc2]
    (fn [env succeed fail]
      (proc1 env (fn [proc1-result fail2]
                   (proc2 env succeed fail2))
             fail)))

  (reduce sequentially (map my-amb-analyze exps)))


(defmethod my-amb-analyze 'nothing [exp]
  (fn [env succeed fail] (succeed "null" fail)))

(defmethod my-amb-analyze 'self-eval [exp]
  (fn [env succeed fail] (succeed exp fail)))

(defmethod my-amb-analyze 'if [exp]
  (let [pred-proc (my-amb-analyze (get-if-predicate exp))
        consequent-proc (my-amb-analyze (get-if-consequent exp))
        alternative-proc (my-amb-analyze (get-if-alternative exp))]
    (fn [env succeed fail]
      (pred-proc env
                 (fn [pred-result fail2]
                   (if (true? pred-result)
                     (consequent-proc env succeed fail2)
                     (alternative-proc env succeed fail2)))
                 fail))))


(defmethod my-amb-analyze 'sequence [exp]
  (analyze-sequence exp))

(defmethod my-amb-analyze 'begin [exp]
  (analyze-sequence (rest exp)))

(defmethod my-amb-analyze 'set! [exp]
  (let [set-var (get-definition-variable exp)
        set-val-proc (my-amb-analyze (get-definition-value exp))]
    (fn [env succeed fail]
      (set-val-proc env (fn [new-val fail2]
                          (let [old-val (look-up-variable set-var env)]
                            (set-variable-value! set-var new-val env)
                            (succeed 'ok (fn [] set-variable-value! set-var old-val env)
                                     (fail2)))))

      fail)))

(defmethod my-amb-analyze 'define [exp]
  (let [definition-var (get-definition-variable exp)
        definition-val-proc (my-amb-analyze (get-definition-value exp))]
    (fn [env succeed fail]
      (definition-val-proc env
                           (fn [val fail2]
                             (define-variable! definition-var val env)
                             (succeed 'ok fail2))
                           fail))))

(defmethod my-amb-analyze 'quote [exp]
  (let [text (get-text-of-quotation exp)]
    (fn [env succeed fail] (succeed text fail))))

(defmethod my-amb-analyze 'variable [exp]
  (fn [env succeed fail] (succeed (look-up-variable exp env) fail)))


; body-proc是 my-amb-analyze 'sequence 返回的函数，
;这里虽然也是用了make-procedure 但封装了过程,在apply中调用方式不同，来得到相同效果
(defmethod my-amb-analyze 'lambda [exp]
  (let [parameters (get-lambda-parameters exp)
        body-proc (analyze-sequence (get-lambda-body exp))]
    (fn [env succeed fail]
      (succeed (make-procedure parameters body-proc env) fail))))

(defmethod my-amb-analyze 'amb [exp]
  (let [cprocs (map my-amb-analyze (amb-choice exp))]
    (fn [env succeed fail]
      (defn try-next [choices]
        (if (empty? choices)
          (fail)
          ((first choices) env succeed (fn [] (try-next (rest choices))))))
      (try-next cprocs))))

(defn get-args [arg-procs env succeed fail]
  (if (empty? arg-procs)
    (succeed '() fail)
    ((first arg-procs) env (fn [arg fail2]
                             (get-args (rest arg-procs) env

                                       (fn [args fail3]
                                         (succeed (cons arg args)
                                                  fail3))
                                       fail2))
     fail)))


(defn execute-application [procedure arguments succeed fail]
  (cond (primitive-procedure? procedure)
        (succeed (apply-primitive-procedure procedure arguments) fail)
        (compound-procedure? procedure)
        ;注意这里body是个lambda，原来是表达式
        ((get-procedure-body procedure)
         (extend-environment
           (get-procedure-parameters procedure)
           arguments
           (get-procedure-environment procedure))
         succeed
         fail)
        :else (Exception. (str "unknow procedure" procedure))))

(defmethod my-amb-analyze :default [exp]

  (let [fproc (my-amb-analyze (get-operator exp))
        arg-procs (map my-amb-analyze (get-operands exp))]
    (fn [env succeed fail]
      (fproc env (fn [proc fail2]
                   (get-args arg-procs
                             env
                             (fn [args fail3]
                               (execute-application proc args succeed fail3))
                             fail2))
             fail))))





(defn amb-eval [exps env succeed fail]
  "执行和分析分离"
  ((my-amb-analyze exps) env succeed fail))



(defn -main []
  (defn internal-loop [try-again]
    (let [exps (read-string (read-line))]
      (if (= exps 'try-again)
        (try-again)
        (do (println "\nnew problem")
            (amb-eval exps
                      global-environment
                      ;succeed
                      (fn [val next-alternative]
                        (println val)
                        (internal-loop next-alternative))
                      ;fail
                      (fn []
                        (println "there are no more value of")
                        (println exps)
                        (-main)))))))
  (try
    (internal-loop (fn [] (println)
                     (println "\nnew problem") (-main)))
    (catch Exception e (println e)))
  (recur))