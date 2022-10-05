	lw	1,0,first
	sw	2,1,first
	nand	1,1,2
	ori	2,2,2
	add	2,2,3
start	sub	1,1,1
	beq	1,0,donec
	slti	2,2,4
	j	start
done	halt
first	.fill 	4