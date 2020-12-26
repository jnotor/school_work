INIT:
MOV A, #0FEh        ; Start with 0xFE in the accumulator.
mov tmod, #01h
clr tr0
clr tf0

MAIN:
MOV P3, A           ; Write the contents of the accumulator to Port 3.
                    ; set up timer values
mov th0, #0ECh    ; 1110 1100 = 0xEC
mov tl0, #78h     ; 0111 1000 = 0x78
; mov th0, #0FFh      ; tester timer values
; mov tl0, #0F6h
setb tr0            ; start timer
LCALL subDelay      ; Delay 5 mSeconds subroutine.
RRC A               ; Rotate the value in the accumulator to the right.
SJMP MAIN           ; Repeat this process continuously.

subDelay:
jnb tf0, subDelay
ret

.END