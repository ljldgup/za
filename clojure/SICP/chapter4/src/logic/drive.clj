(ns logic.drive
  (:require [logic.match :refer :all])
  (:require [logic.syntax :refer :all])
  (:require [logic.maintenance :refer :all])
  (:require [logic.stream :refer :all]))
;;;;;;;;;;;;;;;;;;;;;;;;;驱动循环
(defn logic-repl []

    (let [q (query-syntax-process (read-string (read-line)))]
      (if (not (= q 'exit))
        (try
          (cond
            (assertion-to-be-added? q)
            (do (add-rule-or-assertion! (add-assertion-body q))
                (println)
                (println "Added to data base"))
            :else
            (do
              (println)
              (doall (map println
                          (map
                            (fn [frame] (println q frame)
                                        (instantiate q
                                                     frame
                                                     (fn [v f] (contract-question-mark v))))
                            (qeval q (singleton-stream {})))))))
          (catch Exception e (println e))))
    (recur)))
