;置换循环,模运算加法
(->> (iterate #(mod (+ %1 3) 11) 0) 
    (take 33) 
    (partition 11) 
    (map println))
    
(->> (iterate #(mod (* %1 3) 11) 1) 
    (take 33) 
    (partition 11) 
    (map println))