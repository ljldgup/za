

;协议，不同协议下的同名函数貌似会相互覆盖
(defprotocol Matrix
    (lookup[matrix i j])
    (update [matrix i j value])
    (rows [matrix])
    (cols [matrix])
    (dims [matrix]))

(extend-protocol Matrix
    ;
    (type [])
    (lookup [vov i j] (get-in vov [i j])))
(lookup [[1] [2 3]] 1 1)

    
(extend-type nil
    Matrix
    (lookup [vov i j] 1e6))
(lookup nil 1 1)


;类型
(defrecord Point [x y])
(.x (Point. 3 4))
;map的操作，record都支持
(:x (Point. 3 4))
;默认值
(:z (Point. 3 4) -1)
(assoc (Point. 3 4) :x 4)
;可以新增字段
(assoc (Point. 3 4) :z [:a :b])

;不能作为函数操作
((Point. 3 4) :x)

;多参构造函数，等效(-> (Point. 3 4) (with-meta {:foo :bar}) (assoc :z 5))
(def p (Point. 3 4 {:foo :bar} {:z 5}))
(meta p)

;隐式工厂函数->xxx map->xxx xxx/create
(->Point 3 4)
(apply ->Point [5 6])

(map->Point {:x 3 :y 4})
(Point/create {:x 3 :y 4})

(defrecord NamedPoint [^String name ^long x ^long y])
(NamedPoint/getBasis)
;都是符号
(map type (NamedPoint/getBasis))
;tag+类型
(map meta (NamedPoint/getBasis))


;扩展类似继承,为类型添加动作
(extend Point 
    Matrix
    {:lookup (fn[this i j] [(:x this) (:y this)])})
(lookup (->Point 3 2) 1 1)

;也可以定义的时候直接实现协议
(defrecord Point [x y]
    Matrix
    (lookup [this i j] [(:x this) (:y this)]))

;查看扩展
(extenders  Matrix)

(extends?  Matrix Point)

;类似instanceof， 注意extends?是用在类型之间的，satisfies?这里是值和类型
(satisfies?  Matrix (->Point 3 2))

---------------------------------------------------------------------------------------------------
(defn dispatch [x] (:tag x))

;双冒号命名空间限定关键字
(derive ::checkbox ::checkable)
(derive ::input ::checkbox)
;继承能够传递
(isa? ::input ::checkable)

(defmulti fill 
    #'dispatch
    :default nil)
    
(defmethod fill ::checkable [x] (println (:tag x) "is" ::checkable))

;注意[...]在处理时被认为是一个vector元素
(defmethod fill [:input 1] [x] (println (:tag x) "is" '[:input 1]))
(defmethod fill :default [x] (println (:tag x) "is not" ::checkable))

;均能执行
(fill {:tag ::checkable})
(fill {:tag ::input})
(fill {:tag [:input 1]})

;不是checkable，这里应该已经通过:default nil关了默认函数，但是还是能执行，很奇怪
(fill {:tag ::radio})

(-> (make-hierarchy) (derive ::checkbox ::checkable) (derive ::input ::checkbox))