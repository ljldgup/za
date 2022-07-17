(def n 12345)


;小端
(->> (range 32) (map #(bit-and (bit-shift-left 1 %) n)) ); (reduce +))