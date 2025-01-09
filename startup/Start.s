.section ".text.boot"

.globl _start
.globl main
_start:
	csrr t0, mhartid
	li t1, 0
	bne t0, t1, _hlt # branch to _hlt if mhartid != 1
    .option push
    .option norelax
    la gp, __global_pointer$
    .option pop
    la sp, _stack_start
    call bss_start
    call main
_hlt:
	wfi
	j _hlt



.global memset
memset:
    # Save return address
    sd ra, 0(sp)
    addi sp, sp, -8  

    # Load arguments
    ld a0, 0(sp)   # Pointer to memory
    ld a1, 8(sp)   # Value to set
    ld a2, 16(sp)  # Number of bytes to set

    # Loop label
    loop:
        beqz a2, end  # Exit if no bytes left
        sb a1, 0(a0)  # Store byte
        addi a0, a0, 1  # Increment pointer
        addi a2, a2, -1 # Decrement byte count
        j loop

    # Restore stack and return
end:
    ld ra, 0(sp)
    addi sp, sp, 8
    ret                 # Return
