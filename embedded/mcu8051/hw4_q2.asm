; ******************************************************************************
; * HW4 Q2   Ver 001
; * J. Notorgiacomo 11/21/2020
; * Description: Lookup tables sequential reads

INIT:
MOV P2, #00h         ; Init P2 to some known, non-0xFF value
MOV DPTR, #TABLE1	 ; Set data pointer dptr to point at table1

Storage EQU 30h    ; init storage var
MOV Storage, #00h


; Write a program that does the following task and then terminates:
Main:
MOV A, #00h         ; init acc
MOVC A, @A+DPTR  	 ; get  value from table
MOV Storage, A    	; SAVE VALUE JUST IN CASE, BEFORE WE XOR ACC

XRL A, #0FFh        	; TODO: DOUBLE CHECK THIS LOGIC
JZ Terminate            ; IF VALUE IN ACC == 0XFF, "TERMINATE"

MOV P2, Storage	        ; ELSE: Write to Port 2 the table values until 0xFF
INC DPTR                ; increment data pointer index

SJMP MAIN

Terminate:
SJMP Terminate      ; Not really terminating but this is from class example of termination

TABLE1: 		; Table data values:
.DB 0x01
.DB 0x02
.DB 0x04
.DB 0x08
.DB 0x10
.DB 0x20
.DB 0x40
.DB 0x80
.DB 0xFF
.DB 0x99
.DB 0x98

.END