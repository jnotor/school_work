INIT:
MOV A, #0FEh        ; Start with 0xFE in the accumulator.
mov tmod, #01h	    ; init the timer mode and values
clr tr0

MAIN:
MOV P3, A           ; Write the contents of the accumulator to Port 3.
                  ; set up timer
mov th0, #0ECh    ; 1110 1100 = 0xEC
mov tl0, #78h     ; 0111 1000 = 0x78
clr tf0

JNB P0.1, switch2Low ; Read switch 2, If the switch(2) is pulled low
SJMP switch2High

switch2Low:
setb tr0            ; start timer
LCALL subDelay      ; Delay 5 mSeconds subroutine
SJMP switch1Main

switch2High:
setb tr0            ; start timer
LCALL subDelay      ; Delay 5 mSeconds subroutine

mov th0, #0ECh    ; 1110 1100 = 0xEC
mov tl0, #78h     ; 0111 1000 = 0x78
clr tf0

setb tr0            ; start timer
LCALL subDelay      ; Delay 5 mSeconds subroutine
SJMP switch1Main

switch1Main:
JNB P0.0, switch1Low ; Read switch 1, If the switch(1) is pulled low
SJMP switch1High

switch1Low:         ; Rotate the value in the accumulator to the right.
RRC A
SJMP MAIN           ; Repeat this process continuously.

switch1High:        ; Rotate the value in the accumulator to the left
RLC A
SJMP MAIN           ; Repeat this process continuously.

subDelay:
jnb tf0, subDelay
ret