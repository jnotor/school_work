; ******************************************************************************
; * Lab8 P1   Ver 001
; * J. Notorgiacomo 12/5/2020
; * Description:  create a counter that will count from 0 to 99, and repeat, on
; *               the text LCD display plus write name. Pause and reset
; *               functionality using Port 1.6 for Pause & Port 1.7 for Reset
; *
; * OUTPUT: The first line should have the count. (0 – 99). On the second line
; *         put your first name and last name initial on the screen.
; *             Ex 1: (Bob Happy)
; *                             04
; *                             Bob H.


PROG_INIT:
    	MOV DPTR, #TABLE1	 	; Set data pointer dptr to point at table1

    	mov tmod, #01h      		; init timer
        clr tr0
        clr tf0

        loopTracker equ 30h		; init loop/iteration counter
        mov loopTracker, #09h


INIT_LCD:
        mov p2, #0C0h      		; Set the DDRAM address to 2nd line so we take care of name first
        clr p1.1            		; Turn off the control lines
        clr p1.2
        clr p1.0

        nop

        mov p2, #38h  		        ; Init procedure from Hantronix Datasheet
        lcall enable_pulse
        mov p2, #0fh
        lcall enable_pulse
        mov p2, #01h
        lcall enable_pulse
        mov P2, #06h
        lcall enable_pulse

        mov p2, #0C0h       		; Set the DDRAM address to 2nd line so we take care of name first
        lcall enable_pulse
        setb P1.2         		; Set the LCD to write to the screen (DDRAM)

        lcall lcd_name_init

        lcall cursor_reset

        mov a, #00h
        MOVC A, @A+DPTR  		; Perform a lookup based on the table you created.
        mov p2, a			; write 0
        lcall enable_pulse
        mov p2, a			; write 0
        lcall enable_pulse

        lcall cursor_reset

        mov a, #00h			; return value in acc to OG value


MAIN:
        lcall waitNcheck
        JNB P1.6, PAUSED 		; checks p3.0, paused, is set, in our case is closed

        djnz loopTracker, MAIN 		; decrement the loop tracker so we loop ten times

        lcall write_num_to_lcd
        lcall cursor_reset

        mov loopTracker, #09h		; reset the loop/iteration counter
        SJMP MAIN


PAUSED:
        JNB P1.7, RESET			; checks p3.1 is set in our case, is closed
        djnz loopTracker, main 		; decrement the loop tracker so we loop ten times
        mov loopTracker, #09h		; reset the loop/iteration counter
        SJMP MAIN


RESET:
        mov a, #00h
        djnz loopTracker, main 		; decrement the loop tracker so we loop ten times
        mov loopTracker, #09h		; reset the loop/iteration counter
        SJMP MAIN


lcd_name_init:
        mov P2, #'J'        		; Write the Character ‘J’ to the LCD
        lcall enable_pulse
        mov P2, #'o'
        lcall enable_pulse
        mov P2, #'h'
        lcall enable_pulse
        mov P2, #'n'
        lcall enable_pulse
        mov P2, #' '
        lcall enable_pulse
        mov P2, #'N'
        lcall enable_pulse
        mov P2, #'.'
        lcall enable_pulse

        ret


cursor_reset:
        mov p2, #80h
        clr p1.2
        clr p1.0
        lcall enable_pulse

        setb P1.2 			; Set the LCD to write to the screen (DDRAM)
        ret


enable_pulse:               		; Enable Pulse. Data is clocked on
        setb p1.0           		; The falling edge
        nop
        clr p1.0
        nop
        ret


waitNcheck:  			        ; init timer to 10ms wait
        mov th0, #0D8h  		; 1101 1000
        mov th0, #0F0h  		; 1111 0000
        setb tr0        		; start timer

        LCALL waiter
        ret


waiter:
        jnb tf0, waiter
        clr tf0
        ret


write_num_to_lcd:
        add a, #01h         		; increment counter
        da a                		; bcd convert
        mov P0, a 			; store counter value

        ; FIXME: UPPER Messed up
        ; take care of tens place digit
        ANL A, #0F0h			; Isolate the upper nibble
        SWAP A
        MOVC A, @A+DPTR  		; Perform a lookup based on the table you created.
        MOV P2, A			; Write the lookup value to the port with the 7-segment display
        lcall enable_pulse

        MOV A, P0			; Reload your count value. The lookup value needs to be removed after you write it to the port

        ; take care of ones place digit
        ANL A, #0Fh			; Isolate the lower nibble
        MOVC A, @A+DPTR  		; Perform a lookup based on the table you created.
        MOV P2, A			; Write the lookup value to the port with the 7-segment display
        lcall enable_pulse

        MOV A, P0			; Reload your count value. The lookup value needs to be removed after you write it to the port
        ret


TABLE1:
        .DB '0'
        .DB '1'
        .DB '2'
        .DB '3'
        .DB '4'
        .DB '5'
        .DB '6'
        .DB '7'
        .DB '8'
        .DB '9'

.END