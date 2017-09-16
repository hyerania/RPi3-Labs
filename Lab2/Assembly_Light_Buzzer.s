			.data
			.balign 4
red:		.int 3
green:		.int 7
blue:		.int 12
button:		.int 11
delay_time:	.int 1000
error:		.asciz "Error in intitializing\n"
OUTPUT		= 1
INPUT		= 0

before_loop:.asciz "Before loop\n"
during_loop:.asciz "During Loop: %d\n"
r5_value:	.asciz "VALUE: %d\n"
result:		.word 0

			.text
			.global main
			.extern printf
			.extern wiringPiSetupPhys
			.extern pinMode
			.extern digitalWrite
			.extern	digitalRead
			.extern	delay

main:
	push	{r12, lr}
	bl 		wiringPiSetupPhys
	mov		r1, #-1
	cmp		r0, r1
	bne		init
	ldr		r0, =error
	bl 		printf
	b 		exit


init:	
	ldr		r0, =button
	ldr		r0, [r0]
	mov		r1, #INPUT
	bl 		pinMode

	ldr		r4,	=red
	ldr		r4, [r4]
	mov		r6, #1

@While loop
loop:
@digitalRead Setup for (pin)
	ldr		r0, =button
	ldr		r0, [r0]
	bl 		digitalRead
	cmp		r0, r6
	bne		loop

@PinMode Setup for Light
lighton:
	mov		r0, r4
	mov		r1, #OUTPUT
	bl 		pinMode
@digitalWrite Setup for (pin, 1)
	mov		r0, r4
	mov		r1, #1
	bl 		digitalWrite

@delay(200)
	ldr		r0, =delay_time
	ldr		r0, [r0]
	bl 		delay
@digitalWrite Setup for (pin, 0)
	mov		r0, r4
	mov		r1, #0
	bl 		digitalWrite
colorLED:
	cmp		r4, #3
	beq		changeGreen
	cmp		r4, #7
	beq		changeBlue
	cmp		r4, #12
	beq		changeRed
changeGreen:
	ldr		r4, =green
	ldr		r4, [r4]
	b 		loop
changeBlue:
	ldr		r4, =blue
	ldr		r4, [r4]
	b 		loop
changeRed:
	ldr 	r4, =red
	ldr		r4, [r4]
	b 		loop
exit:
	pop {r12, pc}
