; ******************************************************************************
; * HW3 Q3   Ver 001
; * J. Notorgiacomo 11/08/2020
; * Description: Timer and DJNZ
INIT:
loopTracker EQU 30h
mov loopTracker, #09h
mov tmod, #01h
clr tr0
clr tf0

MAIN:
MOV P3, #05h
			; wait at least 20usec
LCALL wait4uSec
LCALL wait4uSec
LCALL wait4uSec
LCALL wait4uSec
LCALL wait4uSec

MOV P3, #0A2h
NOP
NOP
NOP
NOP

DJNZ looptracker, MAIN
SJMP ENDPROG

wait4uSec:		; note: setup consumes > 4usec b4 timer even starts
mov th0, #0FFh		; 1111 1111
mov tl0, #0FCh 		; 1111 1100
setb tr0		; start the timer
LCALL waiter
ret

waiter:			; timer will be overflowed by time we get here
jnb tf0, waiter
ret

ENDPROG: 
MOV P3, #01h
.END