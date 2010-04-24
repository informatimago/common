
(defconstant defaultX 
  [ 
   55
   1607813071.0 410442638.0  1521159381.0 471588148.0  1656306875.0 
   1877698854.0 1457017985.0 1885636224.0 2120983145.0 838865274.0  
   622391523.0  1599495796.0 1589420163.0 646358994.0  1902836023.0 
   294190104.0  528352961.0  810165570.0  2008068603.0 2064065124.0 
   148481515.0  1874022922.0 444511217.0  1229535568.0 1447190841.0 
   97924086.0   1532317171.0 1092420292.0 112366451.0  1855143102.0 
   1983737863.0 650553016.0  612584047.0  899301394.0  863131509.0  
   204748396.0  1301536603.0 1906202310.0 284925217.0  1675295776.0 
   619597367.0  965140710.0  413816387.0  831647212.0  960766755.0  
   2021366322.0 1709289321.0 745170552.0  719637471.0  174912226.0  
   524134565.0  1957015236.0 1065289589.0 490210922.0  644050577.0
   ] "A default state for my-random")

(defvar currentX (copy-sequence defaultX))


(defun my-random ()
  (let ((n (floor (aref currentX 0)))
        (current)
        (modulo  4294967296.0))

    (if (< n 79)
        (progn
          (setq current (mod (+ (aref currentX (- n 23))
                                (aref currentX (- n 54))) modulo))
          (aset currentX (- n 54) current)
          (aset currentX 0        (1+ n))
          )
      (progn
        (setq current (mod (+ (aref currentX (- n 78))
                              (aref currentX (- n 54))) modulo))
        (aset currentX (- n 54) current)
        (setq n (1+ n))
        (if (< 109 n)
            (setq n 55))
        (aset currentX 0 n)
        )
      )
    current);;let
  );;my-random

(defun print-u32 (val)
  (printf "%s " (string-replace (format "%S" val) "\\.0$" ""))
);;print-u32

(let ((i 0))
  (setq currentX (copy-sequence defaultX))
  (setq oldX (make-vector 101 nil))
  (while (< i 100) (setq i (1+ i))
         (progn
           (aset oldX i (copy-sequence currentX))
           (printf "\n")
           (print-u32 (my-random))
           (printf "\n")
           (mapc 'print-u32 currentX)
           (printf "\n")
           )
         ))


