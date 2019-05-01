[org 0x7c00]

KERNEL_OFFSET equ 0x1000 ; address to load kernel

    mov [BOOT_DRIVE], dl ; BIOS stores boot drive in DL

    mov bp, 0x9000 ; set stack
    mov sp, bp

    mov bx, MSG_REAL_MODE
    call print_string

    call load_kernel

    call switch_to_pm

    jmp $

%include "print/print_string.asm"
%include "disk/disk_load.asm"
%include "pm/gdt.asm"
%include "pm/print_string_pm.asm"
%include "pm/switch_to_pm.asm"

[bits 16]

load_kernel:
    pusha
    mov bx, MSG_LOAD_KERNEL
    call print_string

    mov bx, KERNEL_OFFSET   ; memory address to store kernel
    mov dh, 15              ; 15 sectors to read (sector 1-15)
    mov dl, [BOOT_DRIVE]
    call disk_load

    mov bx, MSG_LOAD_KERNEL_SUCCESS
    call print_string

    popa
    ret


[bits 32]
BEGIN_PM:
    mov ebx, MSG_PROT_MODE
    call print_string_pm

    call KERNEL_OFFSET ; jump to the address of kernel code

    jmp $


BOOT_DRIVE db 0
MSG_REAL_MODE db "Started is 16-bit Read Mode", 0
MSG_PROT_MODE db "Successfully landed in 32-bit Protected Mode", 0
MSG_LOAD_KERNEL db "Loading kernel into memory", 0
MSG_LOAD_KERNEL_SUCCESS db "succeed loading kernel!", 0

times 510-($-$$) db 0
dw 0xaa55


