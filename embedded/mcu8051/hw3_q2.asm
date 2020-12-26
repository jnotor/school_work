; ******************************************************************************
; * HW3 Q2   Ver 001
; * J. Notorgiacomo 11/08/2020
; * Description: Timer and subroutine practice

INIT_timer:
mov tmod, #01h
clr tr0
clr tf0

Main:
SETB P3.4
			; set the timer up to count for 2ms before overflow
mov th0, #0F8h		; 1111 1000
mov tl0, #30h 		; 0011 0000
setb tr0		; start the timer
LCALL subR2ms		; go to time waster subroutine

clr tr0			; clean up the timer real quick
clr tf0

CLR P3.4
			; set the timer up to count for 8ms before overflow
mov th0, #0E0h		; 1110 0000
mov tl0, #0C0h 		; 1100 0000
setb tr0		; start the timer
LCALL subR8ms		; go to time waster subroutine

SJMP Main

subR2ms:
jnb tf0, subR2ms
ret


subR8ms:
jnb tf0, subR8ms
ret

.END