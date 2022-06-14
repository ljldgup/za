(def frame (doto (javax.swing.JFrame.)
    (.setTitle "GUI 程序")
    (.setSize 400 200)
    (.setVisible true)))
    
(def panel  (doto (javax.swing.JPanel.)
    (.setBackground java.awt.Color/yellow)
    (.setVisible true)))
    
(let [contentPane (.getContentPane frame)]
    (.add contentPane panel))
    
(let [g (.getGraphics panel)]
    (doto (.getGraphics panel)
            (.drawOval 100, 70, 30, 30)
            (.drawRect 105, 100, 20, 30)
            (.drawLine 105, 100, 75, 120)
            (.drawLine 125, 100, 150, 120)
            (.drawLine 105, 130, 75, 150)
            (.drawLine 125, 130, 150, 150)))