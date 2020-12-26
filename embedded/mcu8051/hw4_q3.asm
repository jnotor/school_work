; ******************************************************************************
; * HW4 Q3   Ver 001
; * J. Notorgiacomo 11/21/2020
; * Description: Multiple random access lookup tables

INIT:
Storage EQU 30h    	; init storage var
MOV Storage, #00h

; Write a program that does the following task continuously:
MAIN:
MOV A, P1 		    ; Read port 1
MOV DPTR, #TABLE1	; Set data pointer dptr to point at table1
    ANL A, #07H 	; Mask out all but the lowest 3 bits of the port read in.
    MOV Storage, A	; Store a copy of this value.
MOVC A, @A+DPTR 	; Do a lookup on the first table. The index cannot exceed 7. (range 0-7)
MOV P2, A 		    ; Write the result of the first lookup table to port 2

MOV A, Storage 		; Reload the read value FROM P1 MASKED
MOV DPTR, #TABLE2	; Set data pointer dptr to point at table2
MOVC A, @A+DPTR 	; Do a lookup on the second table. The index cannot exceed 7. (range 0-7)
MOV P3, A 		    ; Write the result of the first lookup table to port 3

SJMP MAIN		    ; loop-de-loop

TABLE1: 		    ; Count up from 0x01 to 0x08
.DB 0x01
.DB 0x02
.DB 0x03
.DB 0x04
.DB 0x05
.DB 0x06
.DB 0x07
.DB 0x08

TABLE2: 		    ; Count down from 0xFA to 0xF2
.DB 0xFA
.DB 0xF9
.DB 0xF8
.DB 0xF7
.DB 0xF6
.DB 0xF5
.DB 0xF4
.DB 0xF3
.DB 0xF2

.END