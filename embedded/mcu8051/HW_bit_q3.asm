; **********************************************************************************************************************
; * HW2 Q3   Ver 001
; * J. Notorgiacomo 10/25/2020
; * Description: JNB Practice
INIT:
MOV P1, #044H           ; INIT P1 TO SOME VALUE

MAIN:
JNB P1.2, LOWBIT        ; jump if bit P1.2 not set to LOWBIT Label
SJMP HIGHBIT            ; else jump to HIGHBIT Label

HIGHBIT:
MOV P3, #055H
SJMP MAIN

LOWBIT:
MOV P3, #0AAH
SJMP MAIN

.END