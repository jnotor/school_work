; **********************************************************************************************************************
; * HW2 Q2   Ver 001
; * J. Notorgiacomo 10/25/2020
; * Description: JB Practice
MOV P1, #044H           ; INIT P1 TO SOME VALUE

MAIN:
JB P1.2, HIGHBIT        ; jump if bit set to HIGHBIT
SJMP LOWBIT             ; else jump to LOWBIT

HIGHBIT:
MOV P3, #077H
SJMP MAIN

LOWBIT:
MOV P3, #088H
SJMP MAIN

.END