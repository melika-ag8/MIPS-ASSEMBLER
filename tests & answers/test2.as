	lw	1,0,mandam
	lw	2,0,second
	lw	3,0,andiod
	beq	3,1,finish
	add	2,2,4
start	sub	1,2,1
	beq	2,0,finish
	j	start
finish	halt
mandam	.fill 	5
second	.fill 	10
andiod	.fill 	6