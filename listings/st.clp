(defglobal ?*RATING* = 0)
(defglobal ?*cfMATERIALS* = 100 )
(defglobal ?*cfDEMO* = 100 )
(defglobal ?*cfREALMONEY* = 100 )
(defglobal ?*cfRISKY* = 100 )
(defglobal ?*cfINITMONEY* = 100 )
(defglobal ?*cfCURRENCIES* = 100 )


(defrule DEMO-input
 (declare (salience 100 ) )
 (initial-fact)
 =>
 (printout t "Есть ли на платформе демо аккаунт? (1-Да, 2-Нет ) ")
 (bind ?string (read))
 (if (= ?string 2)
   then (assert (DEMO "no"))
   else
      (printout t "Демо аккаунт платный или бесплатный? (1-Платный, 2-Бесплатный ) ")
      (bind ?string (read))
      (assert (DEMO (if (= ?string 1) then "free" else "paid")))
  )
  (printout t "На сколько % Вы уверены? ")
  (bind ?*cfDEMO* (read))
)

(defrule MATERIALS-input
 (declare (salience 100 ) )
 (initial-fact)
 =>
 (printout t "Есть ли на платформе обучающие материалы? (1-Да, 2-Нет ) ")
 (bind ?string (read))
 (assert (MATERIALS (= ?string 1)))
 (printout t "На сколько % Вы уверены? " )
 (bind ?*cfMATERIALS* (read )  )
)

(defrule REALMONEY-input
  (declare (salience 100 ) )
  (initial-fact)
  =>
  (printout t "Должны ли советники использовать реальные деньги? (1-Да, 2-Нет ) ")
  (bind ?string (read))
  (assert (REALMONEY (= ?string 1)))
  (printout t "На сколько % Вы уверены? " )
  (bind ?*cfREALMONEY* (read )  )
)

(defrule RISKY-input
  (declare (salience 100 ) )
  (initial-fact)
  =>
  (printout t "Какой % советников с большим риском? ")
  (bind ?string (read))
  (assert (RISKY ?string))
  (printout t "На сколько % Вы уверены? " )
  (bind ?*cfRISKY* (read ))
)

(defrule INITMONEY-input
  (declare (salience 100 ) )
  (initial-fact)
  =>
  (printout t "Какой размер начального депозита? (1-Маленький, 2-Средний, 3-Большой) ")
  (bind ?string (read))
  (assert (INITMONEY
    (if (= ?string 1)
      then "little"
      else (if (= ?string 2)
              then "middle"
              else "much"))))
  (printout t "На сколько % Вы уверены? " )
  (bind ?*cfINITMONEY* (read ))
)

(defrule CURRENCIES-input
  (declare (salience 100 ))
  (initial-fact)
  =>
  (printout t "Какое количество валют поддерживает платформа? (1-Мало, 2-Много) ")
  (bind ?string (read))
  (assert (CURRENCIES (= ?string 2)))
  (printout t "На сколько % Вы уверены? " )
  (bind ?*cfCURRENCIES* (read))
)

(deffunction sum (?cf )
   (if (< ?cf 0 )
  then (sum 1 )
  else (bind ?*RATING* (- (+ ?*RATING* ?cf ) (/ (* ?*RATING* ?cf ) 100 ) ) ) ) )

(defrule PAID_DEMO
 (DEMO "paid" )
 =>
 (sum (/ ?*cfDEMO* 4) )
)

(defrule FREE_DEMO
 (DEMO "free" )
 =>
 (sum (/ ?*cfDEMO* 2) )
)

(defrule NO_DEMO
  (DEMO "no")
  =>
  (sum (/ (- 100 ?*cfDEMO*) 4))
)

(defrule HAS_MATERIALS
 (MATERIALS TRUE )
 =>
 (sum (/ ?*cfMATERIALS* 2) )
)

(defrule NO_MATERIALS
 (MATERIALS FALSE)
 =>
 (sum (/ (- 100 ?*cfMATERIALS*) 4) )
)

(defrule MUST_USE_REALMONEY
  (REALMONEY TRUE)
  =>
  (sum (/ ?*cfREALMONEY* 2) )
)

(defrule NOT_ONLY_REALMONEY
  (REALMONEY FALSE)
  =>
  (sum (/ (- 100 ?*cfREALMONEY*) 4) )
)

(defrule LITTLE_RISKY
  (RISKY ?val)
  (test (<= ?val 70))
  =>
  (sum (/ ?*cfRISKY* 2) )
)

(defrule VERY_RISKY
  (RISKY ?val)
  (test (> ?val 70))
  =>
  (sum (/ (- 100 ?*cfRISKY*) 4))
)

(defrule LITTLE_INITMONEY
  (INITMONEY "little")
  =>
  (sum (/ ?*cfINITMONEY* 2) )
)

(defrule MIDDLE_INITMONEY
  (INITMONEY "middle")
  =>
  (sum (/ ?*cfINITMONEY* 4) )
)

(defrule MUCH_INITMONEY
  (INITMONEY "much")
  =>
  (sum (/ (- 100 ?*cfINITMONEY*) 4))
)

(defrule FEW_CURRENCIES
  (CURRENCIES FALSE)
  =>
  (sum (/ (- 100 ?*cfCURRENCIES*) 4))
)

(defrule MANY_CURRENCIES
  (CURRENCIES TRUE)
  =>
  (sum (/ ?*cfCURRENCIES* 2) )
)

(defrule mainRes
      =>
     (printout t "Рейтинг платформы: " ?*RATING* crlf) )
