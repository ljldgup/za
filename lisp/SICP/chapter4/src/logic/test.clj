;在repl中测试用

(ns logic.test
  (:require [logic.match :refer :all])
  (:require [logic.syntax :refer :all])
  (:require [logic.maintenance :refer :all])
  (:require [logic.stream :refer :all])
  (:require [logic.drive :refer :all]))

;repl测试

;把其他空间的数据重置
(require 'logic.test  :reload-all)

(->> '(assert! (rule (fk-by-same ?x) (and (?x fk ?y) (?x fk ?z)  (not   (lisp-value = ?z ?y)))))
        add-assertion-body
        query-syntax-process)

(defn add-to-database[assert-or-rule]
    (->> assert-or-rule
        add-assertion-body
        query-syntax-process
        add-rule-or-assertion!))
        
(add-to-database '(assert! (ljl job programmer)))
(add-to-database '(assert! (agl job unknow)))
(add-to-database '(assert! (fq job teacher)))
(add-to-database '(assert! (ljl fk fq)))
(add-to-database '(assert! (ljl fk ysm)))
(add-to-database '(assert! (rule (fk-by-same ?x) (and (?x fk ?y) (?x fk ?z)  (not (lisp-value = ?z ?y))))))


@DATABASE
@THE-ASSERTION


(def start-stream (singleton-stream {}))
(def data '(ljl job programmer))
(def empty-frame {})

;空的时候会直接打印出#object[clojure.core$map$fn这种形式
(defn print-result[pattern]
    (println "-----------------")
    (println "pattern:" pattern)
    (let [extend-pattern  (query-syntax-process pattern)]
        (doall (map #(println "match result" %)
                (map
                    (fn [frame]
                            ;(println extend-pattern frame)
                            (instantiate extend-pattern
                                             frame
                                             (fn [v f] (contract-question-mark v))))
                    (qeval extend-pattern start-stream))))))

(use-index? '(ljl job programmer))
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
    

(def query-pattern0 '(?y job ?yy))
(def query-pattern1 '(?x fk ?xx))
(def query-pattern2 '(and (?x job ?xx) (?y job ?yy) (?x fk ?y)))
(qeval  (query-syntax-process query-pattern0) start-stream)
(print-result query-pattern0)
(print-result query-pattern1)
(print-result query-pattern2)




@DATABASE
@THE-RULES
@THE-ASSERTION
(fetch-rules '(fk-by-same ljl) '())
(rename-variables-in (fetch-rules '(fk-by-same ljl) '()))
(new-rule-application-id)
(make-new-variable '(? x) (new-rule-application-id))

(qeval  (query-syntax-process '(fk-by-same ljl)) start-stream)
(qeval  (query-syntax-process '(and (fk-by-same ?x) (?x ?y ?z))) start-stream)
(print-result '(fk-by-same ljl))
(print-result '(and (fk-by-same ?x) (?x ?y ?z)))

(let [extend-pattern  (query-syntax-process '(and (fk-by-same ?x) (?x ?y ?z)))]
    (doall (map #(println "match result" %)
            (map
                (fn [frame] 
                        (instantiate extend-pattern
                                         frame
                                         (fn [v f] (contract-question-mark v))))
                (qeval extend-pattern start-stream)))))
                