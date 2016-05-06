	.file	1 "start.c"
	.text
	.align	2
	.globl	_start
	.ent	_start
_start:
	li	$sp,5242880			# 0x500000
	addi	$sp,$sp,-1024
	la	$gp,_gp
	jal	main
	nop
	jal	_exit
	nop
	.end	_start
