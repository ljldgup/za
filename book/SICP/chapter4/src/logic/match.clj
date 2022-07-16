(ns logic.match
  (:require [logic.stream :refer :all])
  (:require [logic.syntax :refer :all])
  (:require [logic.frame :refer :all])
  (:require [logic.maintenance :refer :all]))
;;;;;;;;;;;;;;;;;模式匹配找出断言

(defmulti qeval (fn [query frame]
                  ;(println (first query))
                  (first query)))

;不存在变量则简单extend，存在则递归调用pattern match，这里是双向调用
(def pattern-match)
(defn extend-if-consistent [var dat frame]
;(println 'extend-if-consistent var dat frame)
  (let [binding (binding-in-frame var frame)]
    (if binding
      (pattern-match (binding-value binding) dat frame)
      (my-extend var dat frame))))

;这里的frame是个约束，pat和dat在frame的约束上进行匹配，并且扩充frame
(defn pattern-match [pat dat frame]
  ;(println pat dat)
  ;(println frame)
  ;(println)
  (cond (= frame 'failed) 'failed
        (= pat dat) frame
        (variable? pat) (extend-if-consistent pat dat frame)
        (and (seq? pat) (seq? dat) (not (empty? pat)) (not (empty? dat)))
        (pattern-match
          (first pat)
          (first dat)
          (pattern-match
            (rest pat)
            (rest dat)
            frame))
        :else 'failed))


;返回符合模式的数据对象流
(defn check-an-assertion [assertion query-pat query-frame]
  (let [match-result (pattern-match query-pat assertion query-frame)]
    (if (= match-result 'failed)
      the-empty-stream
      (singleton-stream match-result))))


;根据匹配模式对框架进行过冲
(defn find-assertions [pattern frame]
  (stream-flatmap (fn [datum]
                    (check-an-assertion datum pattern frame))
                  (fetch-assertions pattern frame)))

(defn always-true [ignore frame-stream] frame-stream)

;执行的表达式类似(> 1 2)
;predicate获得符号，eval获得符号对应的函数，args得到变量列表
(defn execute [exp]
  (apply (eval (predicate exp)) (args exp)))

(def instantiate)
(defn lisp-value [call frame-stream]
  (stream-flatmap (fn [frame] (if (execute
                                    (instantiate
                                      call
                                      frame
                                      (fn [v f] (println "unkown pat var -- lisp-value" v))))
                                (singleton-stream frame)
                                the-empty-stream))
                  frame-stream))
;not
(defn negate [operands frame-stream]
  (stream-flatmap
    (fn [frame] (if (empty?
                      (qeval
                        (negated-query operands)
                        (singleton-stream frame)))
                  (singleton-stream frame)
                  the-empty-stream))
    frame-stream))


;or
(defn disjoin [disjuncts frame-stream]
  (if (empty-disjunction? disjuncts)
    the-empty-stream
    (my-extend-interleave
      (qeval (first-disjunct disjuncts) frame-stream)
      (lazy-seq (disjoin
                  (rest-disjuncts disjuncts)
                  frame-stream)))))

;and 递归将限制框架加到流中
(defn conjoin [conjuncts frame-stream]
  (if (empty-conjunction? conjuncts)
    frame-stream
    (let [first-result-frame (qeval (first-conjunct conjuncts) frame-stream)]
      (conjoin
        (rest-conjuncts conjuncts)
        first-result-frame))))

;练习4.76 and的每个查询单独查询，在合并框架流, 这种情况not lisp-value依赖于别的约束的会出错
(defn my-conjoin [conjuncts frame-stream]
  (if (empty-conjunction? conjuncts)
    frame-stream
    (reduce 
        merge-frame-stream 
        (map #(qeval % frame-stream) conjuncts)))) 



(def apply-rules)
(defn simple-query [query-pattern frame-stream]
  (mapcat (fn [frame]
            (concat
              (find-assertions query-pattern frame)
              (lazy-seq (apply-rules query-pattern frame))))
          frame-stream))



(defmethod qeval 'and [query frame-stream] (conjoin (contents query) frame-stream))
(defmethod qeval 'or [query frame-stream] (disjoin (contents query) frame-stream))
(defmethod qeval 'not [query frame-stream] (negate (contents query) frame-stream))
(defmethod qeval 'lisp-value [query frame-stream] (lisp-value (contents query) frame-stream))
(defmethod qeval 'always-true [query frame-stream] (always-true (contents query) frame-stream))
(defmethod qeval :default [query frame-stream] (simple-query query frame-stream))


;实例化表达式
(defn instantiate [exp frame unbound-var-handler]
;(println 'instantiate exp frame unbound-var-handler)
  (defn copy [exp]
    (cond (variable? exp)
          (let [binding (binding-in-frame exp frame)]
            (if binding
              (copy (binding-value binding))
              (unbound-var-handler exp frame)))
          (and (seq? exp) (not (empty? exp)))
          (cons
            (copy (first exp))
            (copy (rest exp)))
          :else exp))
  (copy exp))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;规则合一;;;;;;;;;;;;;;;;;;;;
;exp中是否存在var
(defn depends-on? [exp var frame]
;(println 'depends-on? exp var frame)
  (defn tree-walk [e]
    (cond
      (variable? e)
      (if (= var e)
        true
        (let [b (binding-in-frame e frame)]
          (if b
            (tree-walk (binding-value b))
            false)))
      (seq? e) (or (tree-walk (first e)) (tree-walk (rest e)))))
  (tree-walk exp))

;双向调用都先定义个空变量

(def unify-match)
(defn extend-if-possible [var val frame]
    ;(println 'extend-if-possible var val frame)
  (let [binding (binding-in-frame var frame)]
    (cond
      binding (unify-match (binding-value binding) val frame)
      (variable? val)
      (let [binding (binding-in-frame val frame)]
        (if binding
          (unify-match var (binding-value binding) frame)
          ;规则外部的变量会被绑定到重命名的变量，比如x (? 49x)
          (my-extend var val frame)))
      (depends-on? val var frame) 'failed
      :else (my-extend var val frame))))


(defn unify-match [p1 p2 frame]
    ;(println (= p1 p2))
    ;(println 'unify-match p1 p2 frame)
  (cond
    (= frame 'failed) 'failed
    (= p1 p2) frame
    (variable? p1) (extend-if-possible p1 p2 frame)
    (variable? p2) (extend-if-possible p2 p1 frame)
    (and (seq? p1) (seq? p2))
    (unify-match (first p1) (first p2) (unify-match (rest p1) (rest p2) frame))
    :else 'failed))


;重命名变量避免重复，这里其实可以用map
(defn rename-variables-in [rule]
  (let [rule-application-id (new-rule-application-id)]
  ;(println 'exp rule)
    (defn tree-walk [exp]
      (cond
        (variable? exp) (make-new-variable exp rule-application-id)
        (and (seq? exp) (not (empty? exp)))
            (cons (tree-walk (first exp)) (tree-walk (rest exp)))
        :else exp)))
  (tree-walk rule))

(defn apply-a-rule [rule query-pattern query-frame]
    ;(println 'apply-a-rule rule query-pattern query-frame)
  (let [clean-rule (rename-variables-in rule)]
    ;(println 'clean-rule clean-rule (conclusion clean-rule))
    (let [unify-result (unify-match query-pattern
                                    (conclusion clean-rule)
                                    query-frame)]
      ;(println unify-result)
      (if (= unify-result 'failed)
        the-empty-stream
        (qeval (rule-body clean-rule)
               (singleton-stream unify-result))))))




(defn apply-rules [pattern frame]
    ;(println 'apply-rules pattern frame)
  (mapcat (fn [rule] (apply-a-rule rule pattern frame))
          (fetch-rules pattern frame)))
