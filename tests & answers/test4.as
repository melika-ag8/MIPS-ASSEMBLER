	lw	1,0,them
	addi	1,0,3
	lui	2,6
start	add	1,2,3
	sub	2,1,1
	beq	2,0,done
	jalr	1,2
	j	start
done	halt
them	.fill 	-5