(ns util.apache-http-component)
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

(defn get_http [url]
  (let [httpGet (org.apache.http.client.methods.HttpGet. url)]
    (with-open [response (->> (.execute pooledClient httpGet) .getEntity .getContent)]
      (EntityUtils/toString ((.getEntity response), "utf-8")))))