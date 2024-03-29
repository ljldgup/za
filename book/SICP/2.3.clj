(defn make_leaf [symbol weight]
    (list 'leaf symbol weight))

;;用符号来标志类型
(defn leaf? [object]
    (= 'leaf (first object)))
    
(defn symbol_leaf[x]
    (second x))

(defn weight_leaf[x]
    (nth x 2))

(defn symbol_tree[x]
    (nth x 2))

(defn weight_tree[x]
    (nth x 3))
    
(defn left_branch[x]
    (first x))

(defn right_branch[x]
    (second x))
    
(defn weight [tree]
    (if (leaf? tree) 
        (weight_leaf tree)
        (weight_tree tree)))

(defn symbols [tree]
    (if (leaf? tree) 
        (list (symbol_leaf tree))
        (symbol_tree tree)))        
    
(defn make_code_tree [left right]
    (list 
        left 
        right
        (concat (symbols left) (symbols right))
        (+ (weight left) (weight right))))
        

(def sample_tree 
    (make_code_tree 
        (make_leaf "A" 4) 
        (make_code_tree  
            (make_leaf "B" 2) 
            (make_code_tree  
                (make_leaf "C" 2) 
                (make_leaf "D" 1)))))    

(defn print_code_tree [tree]
    (defn print_helper[cols, current_tree]
        (println cols (symbols current_tree) (weight current_tree))
        ;这里if只有一个分支
        (if (not (leaf? current_tree))
            (do 
                ;没找到字符串相加的办法，暂时用format "   %s" cols
                (print_helper (.concat "  " cols) (left_branch current_tree))
                (print_helper (.concat "  " cols) (right_branch current_tree)))))
    (print_helper "" tree))

(print_code_tree sample_tree) 

(defn chose_branch [bit branch]
    ;(println bit)
    (cond 
        (= bit 0) (left_branch branch)
        (= bit 1) (right_branch branch)
        :else (throw (new Exception "invalid bit")))) 

(defn decode [bits tree]
    (defn helper [bits  current_branch]
        (if (empty? bits) 
            '()
            (let [next_branch (chose_branch (first bits) current_branch)]
                (if (leaf? next_branch)
                    ;一个字符解码完成，重新开始
                     (do
                        ;(println (symbol_leaf next_branch) "finished")
                        (cons (symbol_leaf next_branch) (helper (rest bits) tree)))
                     (helper (rest bits) next_branch)))))
                     
    (helper bits tree))
    


(defn list_contains [a_list x]
    ;(println a_list x)
    (cond
        (empty? a_list) false
        (= (first a_list) x) true
        :else (recur (rest a_list) x)))

;;symbol是关键字
(defn encode_symbol[x tree]
    (if (not (leaf? tree))
        (cond 
            (list_contains (symbols (left_branch tree)) x)
                (cons 0 (encode_symbol x (left_branch tree)))
            (list_contains (symbols (right_branch tree)) x)
                (cons 1 (encode_symbol x (right_branch tree)))
            :else '())))
            
            

(defn encode [message tree]
    ;(println message)
    (if (empty? message)
        '()
        (concat 
            (encode_symbol (first message) tree)
            (encode (rest message) tree))))

(def sample_bits '(0 1 1 0 0 1 0 1 0 1 1 1 0))
(def sample_messge (decode sample_bits sample_tree))            
(encode sample_messge sample_tree)