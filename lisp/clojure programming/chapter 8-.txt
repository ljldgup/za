
*ns*

;切换明明空间后，除了特殊形式，其他均不可用


(in-ns 'ljl)
(+ 1 1)
(clojure.core/+ 1 1)

;通过clojure.core/refer 映射变量
(clojure.core/refer  'clojure.core :only '(+))
(+ 1 1)

;require用于加载 , 加载clojure.set并重命名
(clojure.core/require '[clojure.set :as set])
(set/union #{1 2 3} #{4 5})


;use = require + refer, 所以require能用的关键字，use都能用
(clojure.core/use 'clojure.core)

;import 之后可以直接用类名，否则要写全路径
(Date. ) (java.util.Date. )
(import java.util.Date)
(Date. )
(.getTime (new Date))

;一次import多个
(import '(java.util Arrays Collections))
(->> (map rand-int (range 10 20))
    (take 5)
    into-array
    Arrays/asList
    Collections/max)
    
== 数值比较
=  对象比较
