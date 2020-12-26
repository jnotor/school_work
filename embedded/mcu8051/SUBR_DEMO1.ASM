; *** *** *** *** *** *** *** ***
; *** Subroutine Demo program.
; *** One subroutine calls another and then everything goes
; *** back to the main module. Pay attention to the stack,
; *** the Stack Pointer (SP), and Program Counter (PC)
; *** value when simulating.
;
; === === === === === === === === ===
; === Variable Declaration
STOREIT EQU 30H         ; Temporary Storage variable
;
; *** *** *** *** ***
; *** Main module
.ORG 0000H              ; We have looked at .ORG before. It's a preprocessor
                        ; command that tells the compiler where to put things
                        ; in PROGRAM MEMORY
INIT:
   MOV STOREIT, #00H    ; initialize the memory we are using.
;
MAIN:
   LCALL READIT         ; Program flow will jump to READIT and execute the
                        ; next instruction after this command when it returns
   ;LCALL ADDSTORE      ; Uncomment this and comment the identical command
                        ; in READIT to change how the subroutines are called.
   SJMP MAIN            ; back to the top.
;
.ORG 1234H              ; FOR DEMO PURPOSES ONLY. DON'T ACTUALLY DO THIS!
; *** *** *** *** *** *** *** ***
; *** Reads port 1 into the accumulator 
; *** optional: can call the other subroutine
READIT:
   MOV P1, #0FFH        ; Write all 1's to set up port for reading.
   MOV A, P1            ; read the port into the accumulator.
   LCALL ADDSTORE       ; Comment this out and uncomment the one in MAIN
   RET                  ; end of subroutine.
;
; *** *** *** *** *** *** *** ***
; *** Adds 0x05 to whatever value is in the accumulator, and 
; *** stores the result in RAM location 0x30
ADDSTORE:
   ADD A, #05H          ; Accumulator = Accumulator + 0x05
   MOV STOREIT, A       ; Store Accumulator value in RAM location 0x30
   RET                  ; End of subroutine
.END