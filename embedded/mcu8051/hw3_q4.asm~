; ******************************************************************************
; * HW3 Q4  Ver 001
; * J. Notorgiacomo 11/08/2020
; * Description: RLC, JNB, JB and Carryflag practice

MAIN:
MOV A, #08H
MOV P3, #55H


SHIFTER:
RLC A
JNB C, SHIFTER
JB C, WRITER

WRITER: 
MOV P3, #00h
CLR C
SJMP MAIN

.END