(defn mkdirs[path]
    ;(println path)
    (let [dir (java.io.File. path)]
        (if (not (.exists dir))
            (.mkdirs dir))))
(mkdirs "sdf/sdf/sdf/sdf") 
 
(defn exists[path]
    ;(println path)
    (let [dir (java.io.File. path)]
        (.exists dir)))
        
(mkdirs "sdf/sdf/sdf/sdf")  


(defn get_related_path_name[url]
    (list (re-find #"(?<=hls/).+/(?=[^/]+$)", url) (re-find #"(?<=/)[^/]+$", url)))

(get_related_path_name "https://3bmmikh.life/new/hls/c6f169e6c2ff41109822d0187179eb69/index.m3u8")
(get_related_path_name "https://3bmmikh.life/new/hls/c6f169e6c2ff41109822d0187179eb69/700kb/hls/index.m3u8")

;slurp 处理二进制会出错
(defn binary_save[url]
    (let [net_url (java.net.URL. url)
          connection (clojure.core/cast java.net.HttpURLConnection (.openConnection net_url))
      [relate_path file_name] (get_related_path_name url)
      path_name (str relate_path file_name)]
      (mkdirs relate_path)
      (.connect connection)
      (if (not (exists  path_name))
          (with-open [os (clojure.java.io/output-stream (str relate_path file_name))
                      is (.getInputStream connection)]
                (clojure.java.io/copy is os))
          (println "exists" path_name))))
(binary_save "https://3bmmikh.life/new/hls/c6f169e6c2ff41109822d0187179eb69/700kb/hls/6qlS2hEV.ts")
(binary_save "https://3bmmikh.life/new/hls/c6f169e6c2ff41109822d0187179eb69/700kb/hls/6qlS2hEV.ts")


(defn slurp_save_then_return[url]
    (let [response (slurp url)
      [relate_path file_name] (get_related_path_name url)
      path_name (str relate_path file_name)]
      (mkdirs relate_path)
      (if (not (exists  path_name))
        (do
            (spit (str relate_path file_name) response)
            response)
        (do (println "exists" path_name)
            (slurp path_name)))))

(slurp_save_then_return "https://3bmmikh.life/new/hls/c6f169e6c2ff41109822d0187179eb69/700kb/hls/index.m3u8")
(slurp_save_then_return "https://3bmmikh.life/new/hls/c6f169e6c2ff41109822d0187179eb69/700kb/hls/index.m3u8")


(defn get_base_url[url]
    (re-find #".+/(?=[^/]+$)", url))


(get_base_url "https://3bmmikh.life/new/hls/c6f169e6c2ff41109822d0187179eb69/index.m3u8")
(get_base_url "https://3bmmikh.life/new/hls/c6f169e6c2ff41109822d0187179eb69/700kb/hls/index.m3u8")


(defn get_resolution_path[origin_url]
    (->> (slurp_save_then_return origin_url) (re-find #".+index.m3u8")))   
    
(get_resolution_path "https://3bmmikh.life/new/hls/c6f169e6c2ff41109822d0187179eb69/index.m3u8") 

(defn get_ts_paths[resolution_url]
    (->> (slurp_save_then_return resolution_url) (re-seq #".+\.ts")))
(get_ts_paths "https://3bmmikh.life/new/hls/c6f169e6c2ff41109822d0187179eb69/700kb/hls/index.m3u8")

(def ffmpeg_cmd "ffmpeg -i index.m3u8 -c copy ")
   
    
(defn download_m3u8[url]
    (let [resolution_base_url (get_base_url url)
          resolution_path (get_resolution_path url)
          resolution_url (str resolution_base_url resolution_path)
          ts_base_url (get_base_url resolution_url)
          ts_paths (get_ts_paths resolution_url)]
          (println resolution_base_url resolution_url ts_base_url)
          (doseq [ts_path ts_paths]    
                (binary_save (str ts_base_url ts_path)))))
(download_m3u8 "https://3bmmikh.life/new/hls/c6f169e6c2ff41109822d0187179eb69/index.m3u8")
          
         