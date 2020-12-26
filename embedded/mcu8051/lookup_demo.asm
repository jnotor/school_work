; *** *** *** *** *** *** *** *** *** ***
; *** Lookup table demo program. Doing things with small lookup tables.
;
; *** *** *** *** *** *** *** *** *** ***
; *** Variable Declaration
STORAGEVAR EQU 30H    ; declare a storage vaiable to work with.
; 
INIT:
MOV STORAGEVAR, #00H    ; Load 0x00 into STORAGE
MOV DPTR, #TABLE1       ; Set the Data Pointer DPTR to point at TABLE1
;
MOV A, #01H             ; Load 0x01 into the accumulator This will be
                        ; the index of the lookup table
MOVC A, @A+DPTR         ; The return value will be th entry in the lookup
                        ; table based on the index value. The result 
                        ; will be in the accumulator.
;
MOV DPTR, #TABLE2       ; Set the Data Pointer DPTR to point at TABLE2
MOV A, #03H             ; Load 0x03 into the accumulator This will be
                        ; the index of the lookup table
MOVC A, @A+DPTR         ; The return value will be the entry in the lookup
                        ; table based on the index value. The result 
                        ; will be in the accumulator.
; *** *** *** *** *** *** ***
; *** This example will sequentially read from the lookup table until
; *** it hits an 'escape value'. in this case 0x99. The escape value can
; *** be anything you like, but it must be unique in the sequence.
; *** Note that DPTR is still pointing at TABLE2 at the beginning of this
; *** routine.
;
THISLOOP:
MOV A, #00H             ; Load 0x00 into Acc.
MOVC A, @A+DPTR		; Load lookup table entry into acc.
MOV P2, A               ; Write value to port 2.
XRL A, #99H             ; XOR value with 0x99
JZ ENDITALL             ; if Acc == 0x99 we are done.
INC DPTR                ; Increment the data pointer now index 0 of the 
                        ; table points at the next entry in Table 2.
SJMP THISLOOP           ; Repeat this process.

ENDITALL:               ; Program rermination
SJMP ENDITALL

TABLE1:                 ; First lookup table. Just some random values
.DB 56H
.DB 9AH
.DB 0F3H
.DB 77H
;
TABLE2:                 ; Second lookup table. Note you can place ASCII
                        ; characters in a table using single quotes. ' '
.DB 'A'
.DB 'B'
.DB 'C'
.DB 'D'
.DB 99H                 ; The arbitrary 'escape value' 0x99
;
.END