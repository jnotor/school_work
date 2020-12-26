; ******************************************************************************
; * Test1 Q5   Ver 001
; * J. Notorgiacomo 11/05/2020
; * Description: Make an assembly version of figure 1 (more or less)

storage EQU 31h		; declare storage var

INIT:
MOV storage, #00h 	; init var
SETB P3.7		; turn off READ LED; remember there is a not gate in front of the led
SETB P3.6		; turn off WRITE LED; remember there is a not gate in front of the led
SETB P2.1		; OE/19 P2.1 should be high (impedance mode); when its low it can do things
CLR P2.0		; 1/DIR should be low so Data B to Bus A

MAIN:
CLR P3.7		; Turn on READ LED
CLR P2.1		; set buffer to be able to read data again
MOV A, P1		; Read input from BUS7-0
SETB P3.7		; Turn off READ LED

MOV storage, A		; store a copy of the data bus data in memory
ANL A, #0F0h		; zero out bus3-bus0

CLR P3.6		; Turn on WRITE LED
CLR P2.1  		; note: have to set up the buffer to do below. we're doing it again to be sure
SWAP A			; write the data read from bus7-bus4 to bus0-bus3 and bus7-bus4 should have zeros
MOV P1, A
SETB P3.6		; Turn off WRITE LED

SETB P2.1		; OE/19 P2.1 should be high (impedance mode)
CLR P2.0		; 1/DIR should be low so Data B to Bus A

LCALL subDelay		; delay for at least 5uSec as a subroutine

SJMP MAIN

subDelay:
NOP
NOP
NOP
NOP
NOP
RET

.END