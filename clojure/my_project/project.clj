(defproject my-application "0.1.0-SNAPSHOT"
  :dependencies
  [[org.clojure/clojure "1.10.3"]
   [org.apache.httpcomponents/httpclient "4.5.3"]
   [com.alibaba/fastjson "1.2.83"]
   [http-kit "2.6.0"]
   [org.clojure/data.json "2.4.0"]]
  :repl-options {:init-ns web.m3u8-downloader})
