  # hexmain.asm
  # Written 2015-09-04 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

	.text
main:
	li	$a0, 17 	# change this to test different values

	jal	hexasc		# call hexasc
	nop			# delay slot filler (just in case)	

	move	$a0,$v0		# copy return value to argument register

	li	$v0,11		# syscall with v0 = 11 will print out, why
	syscall			# one byte from a0 to the Run I/O window
	
stop:	j	stop		# stop after one run
	nop			# delay slot filler (just in case)

  # You can write your own code for hexasc here
  #
hexasc:
	andi	$t0, $a0, 0xf	        # taking the 4 least significant bits

	slti	$t1,$a0,10		# checks if $t0 < 9 (set if less than immediate & compare a0 to 10)
	bne	$t1,$zero,number	# if $t0 <= t0, goes to number (branch if not equal)
	
	slti	$t1,$a0,16		# checks if $t0 < 15
	bne	$t1,$zero,letter	# if $t0 <= t0, goes to letter

number:
		addi	$v0,$t0, 0x30   # 0x30 = 0 in ascii for conversion from numbers to ascii
		jr $ra  
		nop		
letter:
		addi	$v0,$t0, 0x37	# same as above but 0x37 converts letters
		jr $ra
		nop
