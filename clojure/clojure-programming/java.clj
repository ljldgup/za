
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

;set! 相当于 obj.setXxx
(let [object (java.awt.Point. 1 2)]
        (set! (. object  -y) 8)
        (bean object)
        )