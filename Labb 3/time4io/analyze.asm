  # analyze.asm
  # This file written 2015 by F Lundevall
  # Copyright abandoned - this file is in the public domain.

	.text
main:
	li	$s0,0x30        # 0x30 is 0 in ascii
loop:
	move	$a0,$s0		# copy from s0 to a0
	
	li	$v0,11
	syscall			# syscall with v0 = 11 will print out one byte from a0 to the Run I/O window

	addi	$s0,$s0,3	# what happens if the constant is changed? (it adds $s0 = $s0 + the constant, for this, I want every third, so 3)
	
	li	$t0,0x5d        # end in the right place according to ascii table in hexa
	bne	$s0,$t0,loop
	nop			# delay slot filler (just in case)

stop:	j	stop		# loop forever here
	nop			# delay slot filler (just in case)

