; *** *** *** *** *** *** *** *** *** *** ***
; *** Virtual hardware demo / prelab assignment
; *** This program uses some of the virtual hardware available in
; *** MCU8051 to multiplex 2 digits. One counts up while the other
; *** counts down.
; ***
; *** The problem is that the lookup table is broken and incomplete.
; *** Fix the table and set up the virtual hardware so that this program
; *** works as intended.
; ***
;
; variable declaration
counter equ 40h
index1 equ 41h
index2 equ 42h

init:
   mov counter, #10H	; 16 decimal for 16 entries...
   mov index1, #00H	; count up index
   mov index2, #0fH	; count down index
   mov dptr, #table	; Set the data pointer to the top of the lookup table
   clr p2.0		; turn off both display enable transistors
   clr p2.1
main:
   mov a, index1	; load the count up index into Acc
   movc a, @a+dptr	; get lookup table value
   clr p2.1		; turn off the count down transistor

   mov p0, a		; write lookup table value to port 0
   setb p2.0		; turn on count up transistor.
   inc index1		; move its index up one.
   lcall smalldel	; delay here. on real hardware this would be in the
   			; millisecond range

   mov a, index2	; load the count down index
   movc a, @a+dptr	; get the lookup table value
   clr p2.0		; turn off count up transistor
   mov p0, a		; write lookup value to port 0
   setb p2.1		; turn on count down transistor
   dec index2		; move its index down one.
   lcall smalldel	; delay. same rules as mentioned above
   
   djnz counter, main	; we are going to end this loop after 16
   			; iterations.

sjmp init		; start all over again.

; !!! !!! !!! !!! !!! !!! !!! !!! !!! !!!
; !!! With real hardware we need a bigger delay than this that would involve
; !!! the timer. A typical multiplexing delay would be 2-10msec
; !!! The virtual Hardware slows things down SIGNIFICANTLY. 
smalldel:
   nop
   nop
   nop
   ret

; !!! Do not let the program flow beyond this point. It will try to execute
; !!! the data created. This is not desirable.
table:
	;		MSB						LSB
	;		g	f	e	d	c	b	a
.db 3FH	;	0	0	1	1	1	1	1	1	0x3F
.db 06H	;	1	0	0	0	0	1	1	0	0x06
.db 5BH	;	2	1	0	1	1	0	1	1	0x5B
.db 4FH	;	3	1	0	0	1	1	1	1	0x4F
.db 00h	;	4
.db 6DH	;	5	1	1	0	1	1	0	1	0x6D
.db 00h	;	6
.db 00h	;	7
.db 7FH	;	8	1	1	1	1	1	1	1	0x7F
.db 6FH	;	9	1	1	0	1	1	1	1	0x6F
.db 77H	;	A	1	1	1	0	1	1	1	0x77
.db 7CH	;	b	1	1	1	1	1	0	0	0x7C
.db 0FH	;	c	0	0	0	1	1	1	1	0x0F (*)
.db 7EH ;	d	1	0	1	1	1	1	0	0x7E (*)
.db 79H	;	E	1	1	1	1	0	0	1	0x79
.db 71H	;	F	1	1	1	0	0	0	1	0x71
.db 0FFH ; just in case value. This should never be read back from a MOVC.

; !!! Also very important: Do not walk off the lookup table!
; !!! The returned result will be undefined. 
.end