;注意这里对应3-12,1,2月份
(defn jm[n] ([2 5 0 3 5 1 4 6 2 4 0 3] (mod (+ n 9) 12)))
(defn gy[y](+ y (quot y 4) (- (quot y 100)) (quot y 400)))
(defn get-weekday[y m d]
    ;周日对应0
    (mod (+ (jm m) (gy y) d) 7))

 
(import  java.time.LocalDate)
(defn get-weekday-java[y m d]
    (->> (LocalDate/of y m d)
        (.getDayOfWeek)
        (.getCode)))

(get-weekday 1935 5 19)
(get-weekday-java 1935 5 19)