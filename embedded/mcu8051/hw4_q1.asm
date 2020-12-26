; ******************************************************************************
; * HW4 Q1   Ver 001
; * J. Notorgiacomo 11/21/2020
; * Description: Lookup tables random access reads

INIT:
MOV DPTR, #TABLE1	 ; Set data pointer dptr to point at table1

; Write a program that does the following task continuously:
Main:
MOV A, P1 		; Read port 1
ANL A, #07h 		; Mask out all but the lowest 3 bits of the port read in
MOVC A, @A+DPTR 	; Do a lookup using the table data provided. The index cannot exceed 7. (range 0-7)

MOV P2, A 		; Write the result to port 2
SJMP MAIN

TABLE1: 		; Table data values:
.DB 0x01
.DB 0xFE
.DB 0xA1
.DB 0xE0
.DB 0xA5
.DB 0x5A
.DB 0x77
.DB 0x42
.DB 0xFF

.END