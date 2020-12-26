; ******************************************************************************
; * Lab7 P4   Ver 001
; * J. Notorgiacomo 12/1/2020
; * Description: Counting 0-9 on 7 segment display

init:
    MOV DPTR, #TABLE1	 	; Set data pointer dptr to point at table1

    mov tmod, #01h      	; init timer
    clr tr0
    clr tf0

    loopTracker equ 30h		; init loop/iteration counter
    mov loopTracker, #09h

    mov a, #00h
    mov P2, a 			; store counter value

    MOVC A, @A+DPTR  	 	; Perform a lookup based on the table you created.
    XRL A, #0FFh		; invert the value because mcu's 0's zeroes are lit : (
    mov p1, a			; write it to the 7 segment
    mov a, p2			; return value in acc to OG value

main:
    lcall waitNcheck
    JNB P3.0, PAUSED 		; checks p3.0, paused, is set, in our case is closed

    djnz loopTracker, main 	; decrement the loop tracker so we loop ten times
    add a, #01h
    da a
    mov P2, a 			; store counter value

    ANL A, #0Fh			; Isolate the lower nibble; the upper nibble is zero
    MOVC A, @A+DPTR  	 	; Perform a lookup based on the table you created.
    XRL A, #0FFh		; invert the value because mcu's 0's zeroes are lit : (
    MOV P1, A			; Write the lookup value to the port with the 7-segment display
    MOV A, P2			; Reload your count value. The lookup value needs to be removed after you write it to the port

    mov loopTracker, #09h	; reset the loop/iteration counter
    SJMP main

waitNcheck:  			; init timer to 10ms wait
    mov th0, #0D8h  		; 1101 1000
    mov th0, #0F0h  		; 1111 0000
    setb tr0        		; start timer

    LCALL waiter
    ret

PAUSED:
    JNB P3.1, RESET		; checks p3.1 is set in our case, is closed
    djnz loopTracker, main 	; decrement the loop tracker so we loop ten times
    mov loopTracker, #09h	; reset the loop/iteration counter
    SJMP main

RESET:
    mov a, #00h
    djnz loopTracker, main 	; decrement the loop tracker so we loop ten times
    mov loopTracker, #09h	; reset the loop/iteration counter
    SJMP main

waiter:
    jnb tf0, waiter
    clr tf0
    ret

TABLE1:
.DB 0x3f
.DB 0x6
.DB 0x5b
.DB 0x4f
.DB 0x66
.DB 0x6d
.DB 0x7d
.DB 0x7
.DB 0x7f
.DB 0x67

.END
