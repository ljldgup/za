(def piece_count_limit 1000)
(def rand_delay_limit 1000)
(def out_put_file "cmd.txt")


(def basic_url "https://3bmmikh.life/new/hls")
(defn get_url_name[url]
    (let [respose (slurp_save_then_return url)]
        (list 
            (re-find #"[^\"]+index.m3u8"  respose) 
            (re-find #"(?<=正在播放：)[^<]+", respose))))
(get_url_name "https://3bmmnr0e.life/suoyoushipin/guochan/29796.html")
        
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
        
(mkdirs "sdf/sdf/sdf/sdf")  


(defn get_related_path_name[url]
    (list 
        (re-find #"(?<=//[^/]{0,100}/).+/(?=[^/]+$)", url) 
        (re-find #"(?<=/)[^/]+$", url)))

(get_related_path_name "https://3bmmikh.life/new/hls/c6f169e6c2ff41109822d0187179eb69/index.m3u8")
(get_related_path_name "https://3bmmikh.life/new/hls/c6f169e6c2ff41109822d0187179eb69/700kb/hls/index.m3u8")



;slurp 处理二进制会出错
(defn binary_save[url]
    (println 'binary_save url)
    (let [net_url (java.net.URL. url)
          connection (clojure.core/cast java.net.HttpURLConnection (.openConnection net_url))
      [relate_path file_name] (get_related_path_name url)
      path_name (str relate_path file_name)]
      (if (not (exists  path_name))
        (do     
            (mkdirs relate_path)
            (doto connection 
                (.setConnectTimeout 5000) 
                (.setReadTimeout 8000)
                (.connect)) 
              (with-open [os (clojure.java.io/output-stream (str relate_path file_name))
                          is (.getInputStream connection)]
                    (clojure.java.io/copy is os))
              (println "exists" path_name)))))
(binary_save "https://3bmmikh.life/new/hls/c6f169e6c2ff41109822d0187179eb69/700kb/hls/6qlS2hEV.ts")
(binary_save "https://3bmmikh.life/new/hls/c6f169e6c2ff41109822d0187179eb69/700kb/hls/6qlS2hEV.ts")


(defn slurp_save_then_return[url]
    (println 'slurp_save_then_return url)
    (let [[relate_path file_name] (get_related_path_name url)
           path_name (str relate_path file_name)]
      (if (not (exists path_name))
        (let [response (slurp url)]
            (mkdirs relate_path)
            (spit (str relate_path file_name) response)
            response)
        (do (println "exists" path_name)
            (slurp path_name)))))

(slurp_save_then_return "https://3bmmikh.life/new/hls/c6f169e6c2ff41109822d0187179eb69/700kb/hls/index.m3u8")
(slurp_save_then_return "https://3bmmikh.life/new/hls/c6f169e6c2ff41109822d0187179eb69/700kb/hls/index.m3u8")


(defn get_base_url[url]
    (println 'get_base_url url)
    (re-find #".+/(?=[^/]+$)", url))


(get_base_url "https://3bmmikh.life/new/hls/c6f169e6c2ff41109822d0187179eb69/index.m3u8")
(get_base_url "https://3bmmikh.life/new/hls/c6f169e6c2ff41109822d0187179eb69/700kb/hls/index.m3u8")


(defn get_vedio_path[origin_url]
    (println 'get_vedio_path origin_url)
    (->> (slurp_save_then_return origin_url) (re-find #".+index.m3u8")))   
    
(get_vedio_path "https://3bmmikh.life/new/hls/c6f169e6c2ff41109822d0187179eb69/index.m3u8") 

(defn get_ts_paths[vedio_url]
    (->> (slurp_save_then_return vedio_url) (re-seq #".+\.ts")))
(get_ts_paths "https://3bmmikh.life/new/hls/c6f169e6c2ff41109822d0187179eb69/700kb/hls/index.m3u8")

(defn get_ffmpeg_cmd [base_path title]
    (format "ffmpeg -i ./%sindex.m3u8 -c copy %s.mp4\r\n" base_path title))
(get_ffmpeg_cmd "sdfsd" "山擦")

          

(defn download_m3u8[url title]
     (let [vedio_base_url (get_base_url url)
          [local_path _] (get_related_path_name url)
          vedio_path (get_vedio_path url)
          vedio_url (str vedio_base_url vedio_path)
          ts_base_url (get_base_url vedio_url)
          ts_paths (get_ts_paths vedio_url)]
          (map println (list url vedio_base_url vedio_url ts_base_url))
          (if (< (count ts_paths) piece_count_limit)
              (do 
                (spit out_put_file (get_ffmpeg_cmd local_path title) :append true)
                (doseq [ts_path ts_paths]  
                    ;(Thread/sleep (rand-int rand_delay_limit))
                    (binary_save (str ts_base_url ts_path)))))))
    
(defn download_mimei[url]
    (let [[relate_index_url title] (get_url_name url)
          index_url (str basic_url relate_index_url)]
          (download_m3u8 index_url title)))
          
;(download_mimei "https://3bmmnr0e.life/suoyoushipin/guochan/29796.html")
;(download_m3u8 "https://3bmmikh.life/new/hls/c6f169e6c2ff41109822d0187179eb69/index.m3u8")  
(def url_list [])
(spit out_put_file "")
(doseq [url url_list] (download_mimei url))