
mov p2, #0C0h ; Set the DDRAM address
clr p1.1 ; Turn off the control lines
clr p1.2
clr p1.0
nop
mov p2, #38h ; Init procedure from Hantronix Datasheet
lcall enable_pulse
mov p2, #0fh
lcall enable_pulse
mov p2, #01h
lcall enable_pulse
Mov P2, #06h
lcall enable_pulse
mov p2, #0C0h ; Setting the DDRAM address again (Location 0x00)
lcall enable_pulse
setb P1.2 ; Set the LCD to write to the screen (DDRAM)
mov P2, #'J' ; Write the Character ‘j’ to the LCD
lcall enable_pulse


mov p2, #80h
clr p1.2
clr p1.0
lcall enable_pulse

setb P1.2 ; Set the LCD to write to the screen (DDRAM)
mov p2, #'D'
lcall enable_pulse

endit: ; Program termination
sjmp endit
enable_pulse: ; Enable Pulse. Data is clocked on
setb p1.0 ; The falling edge
nop
clr p1.0
nop
ret
