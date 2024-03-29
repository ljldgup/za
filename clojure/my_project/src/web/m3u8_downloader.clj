(ns web.m3u8-downloader
  (:require [util.http_util :refer :all]))

(def piece_count_limit 1000)
(def rand_delay_limit 500)
(def out_put_file "cmd.txt")
(def out_put_expect_file "expect.txt")

(def basic_url "https://3bmmikh.life/new/hls")


(defn get_base_url [url]
  (println 'get_base_url url)
  (re-find #".+/(?=[^/]+$)", url))

;(get_base_url "https://3bmmikh.life/new/hls/c6f169e6c2ff41109822d0187179eb69/index.m3u8")
;(get_base_url "https://3bmmikh.life/new/hls/c6f169e6c2ff41109822d0187179eb69/700kb/hls/index.m3u8")



(defn get_url_name [url]
  (let [respose (cache_return_string url)]
    (list
      (re-find #"[^\"]+index.m3u8" respose)
      (re-find #"(?<=正在播放：)[^<]+", respose))))
;(get_url_name "https://3bmmnr0e.life/suoyoushipin/guochan/29796.html")



(defn get_vedio_path [origin_url]
  (println 'get_vedio_path origin_url)
  (->> (cache_return_string origin_url) (re-seq #".+index.m3u8") sort last))

;(get_vedio_path "https://3bmmikh.life/new/hls/c6f169e6c2ff41109822d0187179eb69/index.m3u8")

(defn get_ts_paths [vedio_url]
  (->> (cache_return_string vedio_url) (re-seq #".+\.ts")))
;(get_ts_paths "https://3bmmikh.life/new/hls/c6f169e6c2ff41109822d0187179eb69/700kb/hls/index.m3u8")

(defn get_ffmpeg_cmd [base_path title]
  (format "ffmpeg -i ./%sindex.m3u8 -c copy \"%s.mp4\"\r\n" base_path title))
(get_ffmpeg_cmd "sdfsd" "山擦")



(defn download_m3u8 [url]
  (let [vedio_base_url (get_base_url url)
        vedio_path (get_vedio_path url)
        vedio_url (str vedio_base_url vedio_path)
        ts_base_url (get_base_url vedio_url)
        ts_paths (get_ts_paths vedio_url)]
    (map println (list url vedio_base_url vedio_url ts_base_url))
    (if (< (count ts_paths) piece_count_limit)
      (do
        (doseq [ts_path ts_paths]
            ;;增加一个随机延迟避免被网站屏蔽
          ;(Thread/sleep (rand-int rand_delay_limit))
          (cache_return_string (str ts_base_url ts_path)))))))

;(download_m3u8 "https://3bmmikh.life/new/hls/c6f169e6c2ff41109822d0187179eb69/index.m3u8")

(defn download_mimei [url]
  (let [[relate_index_url title] (get_url_name url)
        index_url (str basic_url relate_index_url)
        [relate_path _] (get_related_path_name index_url)]
    (try
        (download_m3u8 index_url)
        (spit out_put_file (str "rem " url "\r\n") :append true)
        (spit out_put_file (str "\r\n") :append true)
        (spit out_put_file (get_ffmpeg_cmd relate_path title) :append true)
        (catch  Exception e 
        (do 
            (println (.getMessage e))
            (spit out_put_expect_file 
                (str url " " (.getMessage e)) :append true))))))

;(download_mimei "https://3bmmnr0e.life/suoyoushipin/guochan/29796.html")

(import (java.util.concurrent Executors ThreadPoolExecutor))
(import (java.io BufferedReader FileReader))

;线程池
(defonce the-executor
  (Executors/newFixedThreadPool
    (-> (Runtime/getRuntime)
        (.availableProcessors)
        (* 2))))
        
        
        
(defn clear_record[]
  (spit out_put_file "")
  (spit out_put_expect_file ""))

(def urls_file "url_list.txt")
(defn mimeis_from_file[]
  (clear_record)
  (with-open [rdr (BufferedReader. (FileReader. urls_file))]
    (doseq [url (line-seq rdr)] 
        ;future无法控制线程池。。
        ;(future (download_mimei url))
        (.submit the-executor #(download_mimei url)))))
;(mimeis_from_file)


(defn download_mimeis [url_list]
  (clear_record)
  (spit out_put_file "")
  (spit out_put_expect_file "")
  (doseq [url url_list] 
     (.submit the-executor #(download_mimei url))))
