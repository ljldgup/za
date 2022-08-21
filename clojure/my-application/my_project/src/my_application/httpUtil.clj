(ns my-application.httpUtil
  (:require [my-application.SysUtil :refer :all]))

;使用apache httpclient :dependencies [[org.apache.httpcomponents/httpclient "4.5.3"]]
(import
  org.apache.http.impl.conn.PoolingHttpClientConnectionManager
  org.apache.http.client.config.RequestConfig
  ;引入同包下多个
  (org.apache.http.impl.client CloseableHttpClient HttpClients)
  java.util.concurrent.TimeUnit)

(import org.apache.http.client.methods.HttpGet)
(import org.apache.http.client.methods.HttpPost)
(import org.apache.http.util.EntityUtils)

(def connectionManager (PoolingHttpClientConnectionManager. 3 (TimeUnit/MINUTES)))
(doto connectionManager
  (.setMaxTotal 50)
  (.setDefaultMaxPerRoute 5))

(def requestConfig
  (.build
    (doto (RequestConfig/custom)
      (.setConnectionRequestTimeout 5000)
      (.setConnectTimeout 5000)
      (.setSocketTimeout 12000))))

(def pooledClient
  (.build
    (doto (HttpClients/custom)
      (.setConnectionManager connectionManager)
      (.setDefaultRequestConfig requestConfig))))


(defn get_related_path_name [url]
  (let
    [relate_path (re-find #"(?<=//).+/(?=[^/]*$)", url)
     file_name (re-find #"(?<=/)[^/]+$", url)]
    (if (nil? file_name)
      (list relate_path "index.html")
      (list relate_path file_name))))
;(get_related_path_name "https://www.baidu.com/")

(defn get_http [url]
  (let [httpGet (HttpGet. url)]
    (with-open [response (->> (.execute pooledClient httpGet) .getEntity .getContent)]
      (EntityUtils/toString ((.getEntity response), "utf-8")))))


(defn get_with_cache [url]
  (println 'binary_save url)

  (let [[relate_path file_name] (get_related_path_name url)
        path_name (str relate_path file_name)]
    (if (not (exists path_name))
      (do
        (mkdirs relate_path)
        (let [httpGet (HttpGet. url)]
          (println "write into " path_name)
          (with-open [response (->> (.execute pooledClient httpGet) .getEntity .getContent)
                      os (clojure.java.io/output-stream (str relate_path file_name))]
            (clojure.java.io/copy response os))))
      (println "exists" path_name))
    path_name))

(defn cache_return_string [url]
  (slurp (get_with_cache url)))

;(cache_return_string "https://www.baidu.com/")