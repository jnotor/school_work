; **********************************************************************************************************************
; * HW2 Q3   Ver 001
; * J. Notorgiacomo 10/25/2020
; * Description: JZ Practice
STORAGE equ 30h         ; create storage container

INIT:
MOV P1, #043H           ; INIT P1 TO SOME VALUE

MAIN:
MOV STORAGE, P1         ; set storage to hold p1's value
MOV A, STORAGE          ; put storage's value in the accumulator, since jz references accumulator value
ANL A, #01H             ; bitwise AND Accumulator 0000 0001 so we store LSB.
JZ EVENNUM              ; if result of above is 0, even number found, else:
SJMP ODDNUM             ; jump to odd num label

EVENNUM:
MOV P3, #080H
SJMP MAIN

ODDNUM:
MOV P3, #07H
SJMP MAIN

.END