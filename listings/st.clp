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
 (printout t "���� �� �� ��������� ���� �������? (1-��, 2-��� ) ")
 (bind ?string (read))
 (if (= ?string 2)
   then (assert (DEMO "no"))
   else
      (printout t "���� ������� ������� ��� ����������? (1-�������, 2-���������� ) ")
      (bind ?string (read))
      (assert (DEMO (if (= ?string 1) then "free" else "paid")))
  )
  (printout t "�� ������� % �� �������? ")
  (bind ?*cfDEMO* (read))
)

(defrule MATERIALS-input
 (declare (salience 100 ) )
 (initial-fact)
 =>
 (printout t "���� �� �� ��������� ��������� ���������? (1-��, 2-��� ) ")
 (bind ?string (read))
 (assert (MATERIALS (= ?string 1)))
 (printout t "�� ������� % �� �������? " )
 (bind ?*cfMATERIALS* (read )  )
)

(defrule REALMONEY-input
  (declare (salience 100 ) )
  (initial-fact)
  =>
  (printout t "������ �� ��������� ������������ �������� ������? (1-��, 2-��� ) ")
  (bind ?string (read))
  (assert (REALMONEY (= ?string 1)))
  (printout t "�� ������� % �� �������? " )
  (bind ?*cfREALMONEY* (read )  )
)

(defrule RISKY-input
  (declare (salience 100 ) )
  (initial-fact)
  =>
  (printout t "����� % ���������� � ������� ������? ")
  (bind ?string (read))
  (assert (RISKY ?string))
  (printout t "�� ������� % �� �������? " )
  (bind ?*cfRISKY* (read ))
)

(defrule INITMONEY-input
  (declare (salience 100 ) )
  (initial-fact)
  =>
  (printout t "����� ������ ���������� ��������? (1-���������, 2-�������, 3-�������) ")
  (bind ?string (read))
  (assert (INITMONEY
    (if (= ?string 1)
      then "little"
      else (if (= ?string 2)
              then "middle"
              else "much"))))
  (printout t "�� ������� % �� �������? " )
  (bind ?*cfINITMONEY* (read ))
)

(defrule CURRENCIES-input
  (declare (salience 100 ))
  (initial-fact)
  =>
  (printout t "����� ���������� ����� ������������ ���������? (1-����, 2-�����) ")
  (bind ?string (read))
  (assert (CURRENCIES (= ?string 2)))
  (printout t "�� ������� % �� �������? " )
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
     (printout t "������� ���������: " ?*RATING* crlf) )
