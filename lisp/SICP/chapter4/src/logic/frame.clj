(ns logic.frame)
;;;;;;;;;;;;;;;;;;; 框架和约束 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;框架是一组约束的表，约束为一个变量值 的 键值对
(defn binding-in-frame [variable frame]
    ;(println 'binding-in-frame variable frame)
  (let [variable-symbol (last variable)
        variable-value (variable-symbol frame)]
    (if variable-value
      (list variable-symbol variable-value))))

(defn make-binding [variable value]
  (list variable value))

(defn my-extend [variable value frame]
    ;(println frame)
  (let [variable-symbol (last variable)]
    (assoc frame variable-symbol value)))

(defn binding-value [binding]
  (second binding))

(defn binding-variable [binding]
  (first binding))

;(defn -main []
;  ;测试
;  (println (binding-in-frame 'x (extend 'x 1 {}))))