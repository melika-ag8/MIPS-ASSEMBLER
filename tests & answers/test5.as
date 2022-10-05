	lw	1,0,three
	sw	1,2,off
off	slt	1,1,2
	addi	2,2,3
	sub	1,1,1
	beq	2,1,done
	j	start
done	halt
three	.fill 	5
off	.fill 	7
str	.fill	1
