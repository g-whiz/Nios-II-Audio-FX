.section .exceptions, "ax"
	rdctl r8, ctl4
	andi r9, r8, 0b01000000
	beq r0, r9, end_isr
	
	call on_codec_interrupt
	
end_isr:
	addi	ea, ea, -4
	eret


/*

.section text

.global ctl_enable_interrupts
ctl_enable_interrupts:
	movi r8, 0b01000000
	wrctl ctl3, r8
	
	rdctl r8, ctl0
	ori r8, r8, 0b01
	wrctl ctl0, r8
	
	ret
	
*/