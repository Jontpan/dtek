  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #

.global delay
.global time2string

.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm

  #
  # Please add your own code below this line
  #

.data
.text

hexasc:
	move	$v0, $a0
	addi	$v0, $v0, 48
	jr	$ra
	nop

delay:
	blez	$a0, quit
	nop
	sub	$a0, $a0, 1
	li	$t0, 3
loop:
	sub	$t0, $t0, 1
	bnez	$t0, loop
	nop
	b	delay
	nop
quit:
	jr	$ra
	nop

time2string:
	PUSH 	$ra			# Push return adress to stack
	PUSH 	$s0			# Push value of s0 to stack
	PUSH 	$s1
	move	$s0, $a0		# Save memory adress in s0
	move	$s1, $a1
	andi	$a0, $s1, 0xf000	# Put encoded bits in a0
	srl	$a0, $a0, 12		# Bitshift to only get the most significant 4 bits
	jal	hexasc			# Call hexasc
	nop
	move	$a0, $v0
	PUSH 	$a0			# Push a0 to stack
	andi	$a0, $s1, 0x0f00
	srl	$a0, $a0, 8
	jal	hexasc
	nop
	POP	$a0
	sll	$v0, $v0, 8
	or	$a0, $a0, $v0
	li	$t0, 0x3a0000
	or	$a0, $a0, $t0		# Insert colon character
	PUSH	$a0
	andi	$a0, $s1, 0x00f0
	srl	$a0, $a0, 4
	jal	hexasc
	nop
	sll	$v0, $v0, 24
	POP	$a0
	or	$a0, $a0, $v0
	sw	$a0, ($s0)		# Store one word (4 byte) to memory adress stored in s0
	andi	$a0, $s1, 0x000f
	jal	hexasc
	nop
	move	$a0, $v0
	sw	$a0, 4($s0)		# Store last character
	POP	$s1
	POP	$s0
	POP	$ra
	jr	$ra
	nop
