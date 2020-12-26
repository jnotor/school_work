INIT:
MOV A, #01h         ; Start with 1 in A
mov tmod, #01h	    ; init the timer mode and values
CLR C

RotateR:
RRC A
MOV P3, A           ; store right rotated A in P3
JB C, exitRLoop
                    ; init timer values
mov th0, #0ECh      ; 1110 1100 = 0xEC
mov tl0, #78h       ; 0111 1000 = 0x78
clr tf0             ; clear timer carry flag
mov th0, #0FFh      ; tester timer values
mov tl0, #0F6h
setb tr0            ; start timer
LCALL subDelay      ; delay 5ms
SJMP RotateR

exitRLoop:
CLR P2.0
                    ; init timer values
mov th0, #0ECh      ; 1110 1100 = 0xEC
mov tl0, #78h       ; 0111 1000 = 0x78
clr tf0             ; clear timer carry flag
mov th0, #0FFh      ; tester timer values
mov tl0, #0F6h
setb tr0            ; start timer
LCALL subDelay      ; delay 5ms
SETB P2.0
SJMP RotateL

RotateL:
RLC A
MOV P3, A           ; store left rotated A in P3
JB C, exitLLoop
                    ; init timer values
mov th0, #0ECh      ; 1110 1100 = 0xEC
mov tl0, #78h       ; 0111 1000 = 0x78
clr tf0             ; clear timer carry flag
mov th0, #0FFh      ; tester timer values
mov tl0, #0F6h
setb tr0            ; start timer
LCALL subDelay      ; delay 5ms
SJMP RotateL

exitLLoop:
CLR P2.1
                    ; init timer values
mov th0, #0ECh      ; 1110 1100 = 0xEC
mov tl0, #78h       ; 0111 1000 = 0x78
clr tf0             ; clear timer carry flag
mov th0, #0FFh      ; tester timer values
mov tl0, #0F6h
setb tr0            ; start timer
LCALL subDelay      ; delay 5ms
SETB P2.1
SJMP RotateR

subDelay:
jnb tf0, subDelay
ret

.END
