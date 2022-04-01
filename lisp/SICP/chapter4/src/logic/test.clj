(ns logic.test
  (:require [logic.match :refer :all])
  (:require [logic.syntax :refer :all])
  (:require [logic.maintenance :refer :all])
  (:require [logic.stream :refer :all]))

;repl测试

(add-rule-or-assertion! (add-assertion-body '(assert! (ljl job programmer))))
(add-rule-or-assertion! (add-assertion-body '(assert! (agl job unknow))))
(add-rule-or-assertion! (add-assertion-body '(assert! (fq job teacher))))
(add-rule-or-assertion! (add-assertion-body '(assert! (ljl fk fq))))
(add-rule-or-assertion! (add-assertion-body '(assert! (ljl fk ysm))))

(def query-pattern (query-syntax-process '(and (?x job ?xx) (?y job ？yy) (?x fk ?y))))


(def start-stream (singleton-stream '({})))
(def data '(ljl job programmer))
(def empty-frame {})

(use-index? query-pattern)
(indexable? '(ljl job programmer))
(index-key-of '(ljl job programmer))
(get-stream 'ljl 'assertion-stream)

(fetch-assertions query-pattern empty-frame)
(pattern-match query-pattern data empty-frame)
(check-an-assertion data query-pattern empty-frame)
(find-assertions query-pattern empty-frame)
(singleton-stream (check-an-assertion data query-pattern empty-frame))


(qeval query-pattern start-stream)
(simple-query query-pattern start-stream)
(find-assertions query-pattern {})

(map
  (fn [frame] (instantiate query-pattern
                           frame
                           (fn [v f] (contract-question-mark v))))
  (qeval query-pattern (singleton-stream '({}))))


(def query-pattern1 (query-syntax-process '(?x job ?xx)))
(def query-pattern2 (query-syntax-process '(?y job ？yy)))
(simple-query query-pattern1 start-stream)

(def query-pattern (query-syntax-process '(ljl ?yy ?xx)))

(simple-query  query-pattern (singleton-stream '(ljl job unknow)))
(stream-flatmap #(qeval '(ljl ?yy ?xx) %) (singleton-stream '(ljl job unknow)))