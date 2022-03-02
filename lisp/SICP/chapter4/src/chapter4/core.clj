(ns chapter4.core
  (:require [chapter4.my-eval :refer :all])
  (:require [chapter4.analyzer :refer :all])
  (:require [chapter4.environment :refer :all])
  (:require [chapter4.procedure :refer :all]))

(def global-environment
  (extend-environment
    primitives-procedures
    the-empty-environment))


(defn -main []

  (try
    (let [exps (read-string (read-line))]
      ;(let [output (my-eval exps global-environment)]
      (let [output (my-split-eval exps global-environment)]
        (println :output output)))
    (catch Exception e (println e)))
  (recur))
    
    
    
    
    
    
    
    
    
    
    
    