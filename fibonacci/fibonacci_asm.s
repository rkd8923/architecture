	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	1
	.globl	fibonacci
	.type	fibonacci, @function
fibonacci:
	#------Your code starts here------
	#LHS: a0, RHS: a1
	add		t3, zero, zero
	add		t6, zero, zero
	addi	t3, t3, 1
	sd		t3, (a0)
	addi	t6, a0, 8
	sd		t3, (t6)
	addi	t5, zero, 2
Fibo:
	ld		t3, (t6)
	ld		t4, -8(t6)
	add		t3, t3, t4
	addi	t6, t6, 8
	sd		t3, (t6)
	addi	t5, t5, 1
	bne		t5, a1, Fibo
	
	#Load return value to reg a0
	#------Your code ends here------

	#Ret
	jr	ra
	.size	fibonacci, .-fibonacci
	.ident	"GCC: (GNU) 9.2.0"
