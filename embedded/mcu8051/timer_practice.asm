mov tmod, #01h

clr tr0
clr tf0

mov tl0, #30h
mov th0, #0F8h
setb tr0

wastetimeloop:
jnb tf0, wastetimeloop

nop

clr tr0
clr tf0

endloop:
sjmp endloop

.end