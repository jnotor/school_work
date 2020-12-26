; ******************************************************************************
; * HW2 Q1   Ver 001
; * J. Notorgiacomo 10/25/2020
; * Description: Store P1 val's upper and lower nibs seperately
UPPERNIB EQU 30h        ; create storage variables at target memory locations
LOWERNIB EQU 31h

INIT:
MOV UPPERNIB, #00H      ; init values of storage variables to 0
MOV LOWERNIB, #00H
MOV P1, #042H           ; INIT P1 TO SOME VALUE

MAIN:
MOV A, P1        	; put p1's value into lower storage variable and accumulator
MOV LOWERNIB, P1
ANL A, #0F0H     	; bit wise AND A for upper with 1111 0000 to save only upper nib
SWAP A			    ; reverse bit order for preferred format
MOV UPPERNIB, A		; store it in var
ANL LOWERNIB, #00FH     ; bit wise AND lower storage with 0000 1111 to save only lower nib

SJMP MAIN
.END