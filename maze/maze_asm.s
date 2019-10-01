	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text

	#------You can declare additional functions here
	.align	1
	.globl	your_funct
	.type	your_funct, @function
your_funct:
	addi	sp, sp, -40
	sd	ra, 32(sp)
	sd	a1, 24(sp)
	sd	a2, 16(sp)
	sd	a3, 8(sp)
	sd	a4, 0(sp)

	addi	t3, zero, 20
	bge	a3, t3, fail
	blt	a1, zero, fail
	blt	a2, zero, fail
	bge	a1, s1, fail
	bge	a2, s2, fail
	mul	t3, a2, s1
	add	t3, t3, a1
	addi	t5, zero, 8
	mul	t3, t3, t5
	add	t4, s0, t3
	ld	t3, 0(t4)
	addi	t4, zero, 1
	beq	t3, t4, fail

	
	addi	t3, s1, -1
	bne	a1, t3, L1
	addi	t3, s2, -1
	bne	a2, t3, L1

	add	a0, a3, zero
	ld	a4, 0(sp)
	ld	a3, 8(sp)
	ld	a2, 16(sp)
	ld	a1, 24(sp)
	ld	ra, 32(sp)
	addi	sp, sp, 40
	jr	ra

fail:
	addi	a0, zero, -1
	ld	a4, 0(sp)
	ld	a3, 8(sp)
	ld	a2, 16(sp)
	ld	a1, 24(sp)
	ld	ra, 32(sp)
	addi	sp, sp, 40
	jr	ra

L1:
	addi	s3, zero, -1

	addi	t3, zero, 3
	beq	a4, t3, left
	addi	a2, a2, -1
	addi	a3, a3, 1
	addi	a4, zero, 0
	jal	ra, your_funct
	add	s3, a0, zero
	ld	a4, 0(sp)
	ld	a3, 8(sp)
	ld	a2, 16(sp)
	ld	a1, 24(sp)
	ld	ra, 32(sp)
	addi	sp, sp, 40
	addi	sp, sp, -40
	sd	ra, 32(sp)
	sd	a1, 24(sp)
	sd	a2, 16(sp)
	sd	a3, 8(sp)
	sd	a4, 0(sp)
left:
	addi	t3, zero, 2
	beq	a4, t3, right
	addi	a1, a1, -1
	addi	a3, a3, 1
	addi	a4, zero, 1
	jal	ra, your_funct
	add	s4, a0, zero
	ld	a4, 0(sp)
	ld	a3, 8(sp)
	ld	a2, 16(sp)
	ld	a1, 24(sp)
	ld	ra, 32(sp)
	addi	sp, sp, 40
	addi	sp, sp, -40
	sd	ra, 32(sp)
	sd	a1, 24(sp)
	sd	a2, 16(sp)
	sd	a3, 8(sp)
	sd	a4, 0(sp)
	blt	s4, zero, right
	blt	s3, zero, left1
	bge	s4, s3, right
left1:
	add	s3, s4, zero	

right:
	addi	t3, zero, 1
	beq	a4, t3, down
	addi	a1, a1, 1
	addi	a3, a3, 1
	addi	a4, zero, 2
	jal	ra, your_funct
	add	s4, a0, zero
	ld	a4, 0(sp)
	ld	a3, 8(sp)
	ld	a2, 16(sp)
	ld	a1, 24(sp)
	ld	ra, 32(sp)
	addi	sp, sp, 40
	addi	sp, sp, -40
	sd	ra, 32(sp)
	sd	a1, 24(sp)
	sd	a2, 16(sp)
	sd	a3, 8(sp)
	sd	a4, 0(sp)
	blt	s4, zero, down
	blt	s3, zero, right1
	bge	s4, s3, down
right1:
	add	s3, s4, zero	

down:
	add	t3, zero, zero
	beq	a4, t3, R1
	addi	a2, a2, 1
	addi	a3, a3, 1
	addi	a4, zero, 3
	jal	ra, your_funct
	add	s4, a0, zero
	ld	a4, 0(sp)
	ld	a3, 8(sp)
	ld	a2, 16(sp)
	ld	a1, 24(sp)
	ld	ra, 32(sp)
	addi	sp, sp, 40
	addi	sp, sp, -40
	sd	ra, 32(sp)
	sd	a1, 24(sp)
	sd	a2, 16(sp)
	sd	a3, 8(sp)
	sd	a4, 0(sp)
	blt	s4, zero, R1
	blt	s3, zero, down1
	bge	s4, s3, R1
down1:
	add	s3, s4, zero	

R1:
	add	a0, s3, zero
	addi	sp, sp, 40
	#Ret
	jr	ra
	.size	your_funct, .-your_funct

	#------Your code ends here


	.align	1
	.globl	solve_maze
	.type	solve_maze, @function
solve_maze:
	#------Your code starts here------
	#maze: a0, width: a1, height: a2
	add	s0, a0, zero
	add	s1, a1, zero
	add	s2, a2, zero

	addi	sp, sp, -8
	sd	ra, 0(sp)
	
	addi	s5, zero, 0

	add	a0, zero, zero
	add	a1, zero, zero
	add	a2, zero, zero
	add	a3, zero, zero
	addi	a4, zero, 3
	
	jal	ra, your_funct
	ld	ra, 0(sp)
	addi	sp, sp, 8
	#Load return value to reg a0
	#------Your code ends here------
	#Ret
	jr	ra
	.size	solve_maze, .-solve_maze


	.ident	"GCC: (GNU) 9.2.0"