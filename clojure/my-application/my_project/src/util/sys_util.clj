(ns util.sys_util)

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
    
(defn mv[src dest]
  ;(println path)
  (let [old_file (java.io.File. src)
        new_file (java.io.File. dest)]
        (if (not (.exists new_file)) 
            (.renameTo old_file new_file)
            (println (str "mv " src " " dest ", " dest " exists" )))))

;(mkdirs "sdf/sdf/sdf/sdf")