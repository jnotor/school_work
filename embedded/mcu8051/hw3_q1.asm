storage equ 34h

INIT:
mov storage, #00h

MAIN:
mov A, P1
LCALL subroutine
sjmp main

subroutine:
ANL A, #0Fh
Mov storage, A
Mov A, #00h
ret

.end

