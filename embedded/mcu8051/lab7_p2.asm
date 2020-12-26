; ******************************************************************************
; * Lab7 P2   Ver 001
; * J. Notorgiacomo 12/1/2020
; * Description: Counting 0-255 & resetting with timer delay with pause & reset

init:
mov tmod, #01h      ; init timer
clr tr0
clr tf0

counter equ 42h
mov counter, #00h

target equ 41h      ; init target to 0xFF == 255 in dec
mov target, #0FFh

mov P1, #0F0h       ; init P1 to be used for pause (P1.0) & reset (P1.1)

main:
mov P2, counter ; store counter value

lcall waitNcheck ; wait for specified delay of 10ms x 10 == 100ms
lcall waitNcheck
lcall waitNcheck
lcall waitNcheck
lcall waitNcheck
lcall waitNcheck
lcall waitNcheck
lcall waitNcheck
lcall waitNcheck
lcall waitNcheck

JB P1.0, PAUSED ; TODO check bit set is what we want for closed

inc counter
SJMP main

waitNcheck:  ; init timer to 10ms wait
mov th0, #0D8h  ; 1101 1000
mov th0, #0F0h  ; 1111 0000
setb tr0        ; start timer

LCALL waiter
ret

PAUSED:
JB P1.1, RESET
SJMP main

RESET:
mov counter, #00h
SJMP main


testtimer:
mov th0, #0FFh		; 1111 1111
mov tl0, #0FCh 		; 1111 1100
setb tr0		; start the timer
LCALL waiter
ret

waiter:
jnb tf0, waiter
clr tf0
ret


