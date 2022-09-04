(ns my-application.sys_util)

(defn mkdirs[path]
  ;(println path)
  (let [dir (java.io.File. path)]
    (if (not (.exists dir))
      (.mkdirs dir))))
;(mkdirs "sdf/sdf/sdf/sdf")

(defn exists[path]
  ;(println path)
  (let [dir (java.io.File. path)]
    (.exists dir)))

;(mkdirs "sdf/sdf/sdf/sdf")