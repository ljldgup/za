(ns evaluator.procedure)
(defn make-procedure [parameter body env]
  (list 'procedure parameter body env))

(defn compound-procedure? [exp]
  (= (first exp) 'procedure))

(defn get-procedure-parameters [exp]
  (second exp))

(defn get-procedure-body [exp]
  (nth exp 2))

(defn get-procedure-environment [exp]
  (nth exp 3))
;要先判断集合，才能判断空集，否则会报错
(def primitives-procedures {'car first, 'cdr rest, 'cons cons, 'null? #(or (nil? %1) (and (seq? %1) (empty? %1)))
                            '+   +, '- -, '* *, '/ /, '= =, '> >, '< <, '% mod, 'list list, 'println println, 'not not})

(def primitives-procedures-reverse (into #{} (vals primitives-procedures)))

(defn primitive-procedure? [proc]
  (contains? primitives-procedures-reverse proc))

(defn apply-primitive-procedure [proc args]
  (apply proc args))








