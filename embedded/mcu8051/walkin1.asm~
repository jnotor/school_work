INIT:
MOV A, #0FFh         ; Start with 1 in A
CLR C

RotateR:
RRC A
MOV P3, A           ; store right rotated A in P3
JNB C, exitRLoop

SJMP RotateR

exitRLoop:
CLR P2.0

SETB P2.0
SJMP RotateL

RotateL:
RLC A
MOV P3, A           ; store left rotated A in P3
JNB C, exitLLoop

SJMP RotateL

exitLLoop:
CLR P2.1

SETB P2.1
SJMP RotateR


.END

