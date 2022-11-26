(ns util.json_util)

(import com.alibaba.fastjson.JSONObject)
(import java.util.Map)
(defn println_then_return [obj]
  (println obj)
  obj)

(defn object_2_map [obj]
  (if (instance? Map obj)
    (into {} (for [k (keys obj)] {(keyword k) (object_2_map (get obj k))}))
    obj))

(defn json_2_clojure_map [json_string]
  (object_2_map (JSONObject/parse json_string)))

(defn -main []
  (println
    (->>
      (json_2_clojure_map "{\"retcode\":0,\"result\":{\"is_in_white_list\":false,\"rate\":1}}")
      println_then_return
      :result
      :rate)))