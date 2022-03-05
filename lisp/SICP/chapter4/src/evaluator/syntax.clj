(ns evaluator.syntax)

(defn make-lambda [parameters body]
  (cons 'lambda (cons parameters body)))

(defn get-lambda-parameters [exp] (second exp))
(defn get-lambda-body [exp] (rest (rest exp)))


(defn get-text-of-quotation [exp] (nth exp 1))

(defn get-assignment-variable [exp] (nth exp 1))
(defn get-assignment-value [exp] (nth exp 2))

(defn get-definition-variable [exp]
  (if (symbol? (second exp))
    ;这里是按照scheme解析的，第二个
    (second exp)
    (first (second exp))))

(defn get-definition-value [exp]
  (if (symbol? (second exp))
    (nth exp 2)                                             ;定义参数，后面是定义函数
    (make-lambda (rest (second exp))                        ;parameter
                 (rest (rest exp))                          ;body,这里用rest保留sequence结构
                 )))

(defn get-if-predicate [exp] (second exp))
(defn get-if-consequent [exp] (nth exp 2))
(defn get-if-alternative [exp] (nth exp 3))
(defn make-if [predicate consequent alternative]
  (list 'if predicate consequent alternative))


(defn get-begin-actions [exp] (rest exp))
(defn last-exp? [seq] (= (count seq) 1))
(defn get-first-exp [seq] (first seq))
(defn get-rest-exps [seq] (rest seq))

(defn make-begin [seq]
  (cons 'begin seq))
(defn sequence->exp [seq]
  (cond ((empty? seq) seq)
        ((last-exp? seq) (get-first-exp seq))
        :else (make-begin seq)))

(defn get-operator [exp] (first exp))
(defn get-operands [exp] (rest exp))
(defn no-operands? [ops] (empty? ops))
(defn get-first-operand [ops] (first ops))
(defn get-rest-operands [ops] (rest ops))

