; ******************************************************************************
; * Lab7 P1   Ver 001
; * J. Notorgiacomo 12/1/2020
; * Description: Counting 0-255 and resetting with timer delay

init:
mov tmod, #01h      ; init timer
clr tr0
clr tf0

counter equ 42h
mov counter, #00h

main:
mov P2, counter ; store counter value

lcall wait50msTimer ; wait for specified delay x 2
lcall wait50msTimer

inc counter

SJMP main

wait50msTimer:  ; init timer to 50ms wait
mov th0, #0F8h  ; 1111 1000
mov th0, #094h  ; 1001 0100
setb tr0        ; start timer

LCALL waiter
ret

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

