	lw	1,0,checkf
	lw	4,0,checks
	or	1,1,4
	addi	1,1,4
	slt	2,1,2
start	beg	2,1,finish
	sub	2,1,1
	j	start
finish	halt
checkf	.fill 	8
checks	.fill 	4