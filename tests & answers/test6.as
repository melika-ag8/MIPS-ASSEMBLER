	lw	1,0,5
	lw	2,0,ajab
start	slt	1,1,2
	add	1,1,1
	slti	2,2,2
	beq	1,0,done1
	sw	2,2,ofset
	j	start
done1	halt
ajab	.fill	5
ofset	.fill	70000
