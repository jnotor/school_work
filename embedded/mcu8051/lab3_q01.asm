; **********************************************************************************************************************
; * Port01 test WRITE program   Ver 001
; * J. Notorgiacomo 10/07/2020
; * Description: This program causes an 8-bit port to turn on & off continuously
;
TOP:          ; A label. Labels are markers that allow program flow to jump to this point in the program.
MOV P1, #00H  ; Write all "0"s to Port 1. NOTE: No leading zero required. consuming 3 bytes
NOP           ; No operation. Effectively wastes 1 instruction cycles worth of time. NOTE: consumes 1 byte
MOV P1, #0FFH ; Write all "1"s to port 1. NOTE: leading '0' in the hex required for letter after #. consuming 3 bytes
SJMP TOP      ; Jump to "TOP". Behaves like "GOTO". NOTE: consumes 2 bytes. can go forward 127 bytes or back 128 bytes
.END          ; Preprocessor directive. Tells the compiler that nothing is compiled beyond this line.