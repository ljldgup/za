
;;自己正则写的property读取，没有用java的load-props来的方便
;property-pattern 要用多行匹配模式
(defn k-v-processer [filename, property-pattern]
    (into {} 
        (for 
            [str-seq (re-seq  property-pattern (slurp filename))] 
            [(nth str-seq 1)  (nth str-seq 2)])))

(defn load-props 
    [file-name] 
    (with-open [^java.io.Reader reader (clojure.java.io/reader file-name)] 
        (let [props (java.util.Properties.)]
            (.load props reader)
            ;props实现了map接口
            (into {} props))))


;替换nacos配置   
(defn java-nacos-replacer [filename property-map]
    (def replace-pattern #"@Na[^$]+\$\{([^:\}]+):*([^}]*)\}.+([^;]+)")
    (def file-content (slurp filename))
    ;用reduce连续替换文本内容
    (reduce 
        #(clojure.string/replace 
            %1 
            (first %2) 
            (clojure.string/join  "=" [(nth %2 3) (or (property-map (nth %2 1) (nth %2 2)))])) ;第二部分是默认值，如果传进来的配置没有，就考虑默认值
        file-content
        (re-seq replace-pattern file-content)))

;String 增加双引号
(defn java-string-replacer [content]
    (def replace-pattern #"String[^=]+=\s*([^\s;].*[^\s;]|[^\s;])\s*")
    (reduce 
        #(clojure.string/replace 
            %1 
            (first %2) 
            (clojure.string/replace  
                (first %2)
                (second %2)
                (str \" (second %2) \")))
        content
        (re-seq replace-pattern content)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;



;使用 从配置文件中读出nacos配置 替换java文件
(def property-file "atm.conf.txt")
(def java-file "NacosConfig.java")
(def target-file "new-NacosConfig.txt")   
(->> (load-props property-file)
     ;(k-v-processer property-file property-pattern)
     (java-nacos-replacer java-file)
     (java-string-replacer)
     ;spit写入文件
     (spit target-file))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;测试

;模式key:value value中间可能有空格,强制指定结尾
;这里要用多行模式，否则^$没办法正确生效
(import [java.util.regex Pattern]) 
(def property-pattern 
    (Pattern/compile "^([^#\\s]+)\\s*:\\s*(\\S.*\\S|\\S)\\s*$" Pattern/MULTILINE))


(re-seq  
    property-pattern 
    (slurp  "atm.conf.txt"))
 
(k-v-processer "atm.conf.txt" property-pattern)
        
(load-props property-file)

(def property-map (k-v-processer  "atm.conf.txt" property-pattern2))
    
(filter #(not (property-map %)) (keys (load-props  property-file )))
    
(->> "NacosConfig.java"
    #(slurp %)
    #(re-seq  #"@Na[^$]+\$\{([^:\}]+):*([^}]*)\}.+([^;]+)"  %) 
    (map #(clojure.string/join  "=" [(nth % 3) (or (property-map (nth % 1) (nth % 2)))])))


     

        