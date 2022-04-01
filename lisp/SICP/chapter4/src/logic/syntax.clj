(ns logic.syntax)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;查询语法;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;将(? variable)转回?variable的字符串， str直接返回相加结果
(defn contract-question-mark [variable]
  (symbol
    (str "?"
         (if (number? (second variable))
           (str (nth variable 2) "-" (second variable))
           (second variable)))))


(defn make-new-variable [var rule-application-id]
  (cons '? (list rule-application-id (second var))))


(def rule-counter (atom 0))

(defn new-rule-application-id []
  (swap! rule-counter #(+ 1 %)))

(defn constant-symbol? [exp] (and (symbol? exp) (not (= (subs (str exp) 0 1) "?"))))


;变量被替换成了 ('? xxxx)
(defn variable? [exp]
  (and
    (seq? exp)
    (= (first exp) '?)))

;变量被替换成了 ('? xxxx)
(defn variable-symbol [exp]
  (second exp))

;symbol是关键字, subs同substr
(defn expand-question-mark [the-symbol]
  (let [chars (str the-symbol)]
    (if (= (subs chars 0 1) "?")
      (list '? (symbol (subs chars 1)))
      the-symbol)))



;递归映射符号?xx为 (? xx)
(defn map-over-symbols [proc exp]
  (cond
    (and (seq? exp) (not (empty? exp)))
    (cons (map-over-symbols proc (first exp))
          (map-over-symbols proc (rest exp)))
    (symbol? exp) (proc exp)
    :else exp))



(defn query-syntax-process [exp]
  (map-over-symbols expand-question-mark exp))




(defn rule-body [rule]
  (let [the-rule (-> rule rest rest)]
    (if (empty? the-rule)
      '(always-true)
      (first the-rule))))

(defn conclusion [rule]
  (second rule))

(defn rule? [statement] (and (seq? statement) (= (first statement) 'rule)))

(defn args [exps] (rest exps))

(defn predicate [exps] (first exps))

(defn negated-query [exps] (first exps))

(defn first-disjunct [exps] (first exps))

(defn rest-disjuncts [exps] (rest exps))

(defn first-conjunct [exps] (first exps))

(defn empty-conjunction? [exps] (empty? exps))

(defn rest-conjuncts [exps] (rest exps))

(defn first-conjunct [exps] (first exps))

(defn empty-disjunction? [exps] (empty? exps))


(defn contents [exp]
  (if (seq? exp)
    (rest exp)
    (println "unknown expression contents" exp)))

(defn add-assertion-body [exp]
  (first (contents exp)))

(defn my_type [exp]
  (if (seq? exp)
    (first exp)
    (println "unknown expression type" exp)))

(defn assertion-to-be-added? [exp]
  (= (my_type exp) 'assert!))

;(defn -main []
;
;
;  ;测试
;  (println (variable? '(? 1)))
;  (println (variable? 1))
;  (println (variable? "sdf"))
;
;
;  ;测试
;  (println (expand-question-mark "?sdf"))
;  (println (expand-question-mark "sdf"))
;
;  ;测试
;  (println (query-syntax-process '(?sdf sdf 1 (xx ?yy)))))
