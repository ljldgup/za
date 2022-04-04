;在repl中测试用

(ns logic.test
  (:require [logic.match :refer :all])
  (:require [logic.syntax :refer :all])
  (:require [logic.maintenance :refer :all])
  (:require [logic.stream :refer :all])
  (:require [logic.drive :refer :all]))

;repl测试

(add-rule-or-assertion! (add-assertion-body '(assert! (ljl job programmer))))
(add-rule-or-assertion! (add-assertion-body '(assert! (agl job unknow))))
(add-rule-or-assertion! (add-assertion-body '(assert! (fq job teacher))))
(add-rule-or-assertion! (add-assertion-body '(assert! (ljl fk fq))))
(add-rule-or-assertion! (add-assertion-body '(assert! (ljl fk ysm))))

@DATABASE
@THE-ASSERTION


(def start-stream (singleton-stream {}))
(def data '(ljl job programmer))
(def empty-frame {})
(defn print-result[pattern]
    (println "pattern:" pattern)
    (let [extend-pattern (query-syntax-process pattern)]
        (println "extendpattern:" extend-pattern )
        (println "match result")
        (map println
                (map
                    (fn [frame] (instantiate extend-pattern
                                             frame
                                             (fn [v f] (contract-question-mark v))))
                    (qeval extend-pattern start-stream)))))

(use-index? query-pattern)
(indexable? '(ljl job programmer))
(index-key-of '(ljl job programmer))
(get-stream 'ljl 'assertion-stream)

(def extend-query-pattern (query-syntax-process '(and (?x job ?xx) (?y job ?yy) (?x fk ?y))))
(fetch-assertions extend-query-pattern empty-frame)
(pattern-match extend-query-pattern data empty-frame)
(check-an-assertion data extend-query-pattern empty-frame)
(find-assertions extend-query-pattern empty-frame)
(singleton-stream (check-an-assertion data extend-query-pattern empty-frame))
(qeval extend-query-pattern start-stream)
(simple-query extend-query-pattern start-stream)
(find-assertions extend-query-pattern {})

(print-result query-pattern)
    

(def query-pattern0 '(?y job ?yy)))
(def query-pattern1 '(?x fk ?xx)))
(def query-pattern2 '(and (?x job ?xx) (?y job ?yy) (?x fk ?y)))
(simple-query query-pattern1 start-stream)
(print-result query-pattern0)
(print-result query-pattern1)
(print-result query-pattern2)


(def rule1 
'(assert! (rule (fk-by-same ?x ?y ?z) (and (?x fk ?y) (?x fk ?z)  (not (lisp-value = ?z ?y))))))


(->> rule1
	query-syntax-process
	add-assertion-body 
	add-rule!)
@DATABASE
@THE-RULES

(fetch-rules '(fk-by-same ljl ?z ?y) '())
(rename-variables-in (fetch-rules '(fk-by-same ljl ?z ?y) '()))
(new-rule-application-id)
(make-new-variable '(? x) (new-rule-application-id))

(println-result '(fk-by-same ljl))
(println-result '(and (fk-by-same ?x) (?x ?y ?z)))

(map
    (fn [frame] (instantiate '(and (fk-by-same ?x) (?x ?y ?z))
                             frame
                             (fn [v f] (contract-question-mark v))))
    (qeval (query-syntax-process '(and (fk-by-same ?x) (?x ?y ?z))) start-stream))
