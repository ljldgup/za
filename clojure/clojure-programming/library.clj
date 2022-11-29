(ns example
  (:require [clojure.data.json :as json]))

(json/write-str {:a 1 :b 2})
;;=> "{\"a\":1,\"b\":2}"

(json/read-str "{\"a\":1,\"b\":2}")
;;=> {"a" 1, "b" 2}

(json/read-str "{\"a\":1,\"b\":2}"
               :key-fn keyword)
;;=> {:a 1, :b 2}

(json/write-str {:a 1 :b 2}
                :key-fn #(.toUpperCase %))
;;=> "{\"A\":1,\"B\":2}"


(json/read-str "{\"number\":42,\"date\":\"2012-06-02\"}"
                ;;这个函数传入的key value,key已经被key-fn处理过了
               :value-fn #(symbol (str %1) (str %2))
               :key-fn #(subs % 1))
;;=>{"umber" 42, "ate" 2012-06-02}