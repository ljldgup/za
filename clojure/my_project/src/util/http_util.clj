(ns util.http_util
  (:require [util.apache-http-component :refer :all])
  (:require [util.sys_util :refer :all])
  (:require [org.httpkit.client :as http]))
(import org.apache.http.client.methods.HttpGet)

(defn get_related_path_name [url]
  (let
    [relate_path (re-find #"(?<=//).+/(?=[^/]*$)", url)
     file_name (re-find #"(?<=/)[^/]+$", url)]
    (if (nil? file_name)
      (list relate_path "index.html")
      (list relate_path file_name))))
;(get_related_path_name "https://www.baidu.com/")


(defn get_with_apache [url, path_name]
  (let [httpGet (HttpGet. url)
        tmp_path_name (str path_name ".tmp")]
    (with-open [response (->> (.execute pooledClient httpGet) .getEntity .getContent)
                os (clojure.java.io/output-stream tmp_path_name)]
      (clojure.java.io/copy response os))
    (mv tmp_path_name path_name)))

(defn get_with_http_kit[url, path_name]
  (let [tmp_path_name (str path_name ".tmp")]
    (with-open [os (clojure.java.io/output-stream tmp_path_name)]
      (http/get  url {:as :stream}
                 (fn [{:keys [status headers body error opts]}]
                   (print 'get_with_http_kit headers status)
                   (clojure.java.io/copy body os)
                   ))
      )
    (mv tmp_path_name path_name)))

;(def http_get #'get_with_apache)
(def http_get #'get_with_http_kit)

(defn get_with_cache [url]
  ;(println 'binary_save url)

  (let [[relate_path file_name] (get_related_path_name url)
        path_name (str relate_path file_name)]
    (if (not (exists path_name))
      (do
        (println "download into " path_name)
        (mkdirs relate_path)
        (@http_get url path_name))
      (println "exists" path_name))
    path_name))




(defn cache_return_string [url]
  (slurp (get_with_cache url)))

;(cache_return_string "https://www.baidu.com/")