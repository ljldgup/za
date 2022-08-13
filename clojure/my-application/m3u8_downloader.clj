(defn get_base_url[url]
    (re-find #".+/(?=[^/]+$)", url))


(get_base_url "https://3bmmikh.life/new/hls/c6f169e6c2ff41109822d0187179eb69/index.m3u8")

(get_base_url "https://3bmmikh.life/new/hls/c6f169e6c2ff41109822d0187179eb69/700kb/hls/index.m3u8")

(defn get_base_name[url]
    (re-find #"[^/]+(?=/[^/]+$)", url))

(get_base_name "https://3bmmikh.life/new/hls/c6f169e6c2ff41109822d0187179eb69/index.m3u8")


(defn get_resolution_path[origin_url]
    (->> (slurp origin_url) (re-find #".+index.m3u8")))
    
(get_resolution_path "https://3bmmikh.life/new/hls/c6f169e6c2ff41109822d0187179eb69/index.m3u8") 

(defn get_ts_paths[resolution_url]
    (->> (slurp resolution_url) (re-seq #".+\.ts")))
(get_ts_paths "https://3bmmikh.life/new/hls/c6f169e6c2ff41109822d0187179eb69/700kb/hls/index.m3u8")

(defn get_ffmpeg_cmd[ts_paths dest]
    (format "ffmpeg -i \"%s\" -c copy %s.mp4" (str "concat:" (clojure.string/join "|" ts_paths)) dest))
(-> (get_ts_paths "https://3bmmikh.life/new/hls/c6f169e6c2ff41109822d0187179eb69/700kb/hls/index.m3u8")
    (get_ffmpeg_cmd  "test")
    println )
    
(defn download_m3u8[url]
    (let [resolution_base_url (get_base_url url)
          base_name (get_base_name url)
          resolution_path (get_resolution_path url)
          resolution_url (str resolution_base_url resolution_path)
          ts_base_url (get_base_url resolution_url)
          ts_paths (get_ts_paths resolution_url)]
          (println resolution_base_url resolution_url ts_base_url)
          (spit  (str base_name "_ts_url.txt") (clojure.string/join "\n" (map #(str "file " %) ts_paths)))
          (doseq [ts_path ts_paths]
            
            (if (not (.exists (java.io.File. ts_path)))
                (do
                    (println "downloading" ts_path)
                    (spit ts_path (slurp (str ts_base_url ts_path)))
                    (Thread/sleep 100))
                (println "downloaded" ts_path)))))
(download_m3u8 "https://3bmmikh.life/new/hls/c6f169e6c2ff41109822d0187179eb69/index.m3u8")
          
         