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

	#Load return value to reg a0
	#------Your code ends here------

	#Ret
	jr	ra
	.size	solve_maze, .-solve_maze


	.ident	"GCC: (GNU) 9.2.0"
