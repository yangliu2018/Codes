; dw: define word, 2 bytes
; dd: define double words, 4 bytes

gdt_start:

gdt_null: ; mandatory null descriptor
    dd 0x0
    dd 0x0

gdt_code: ; code segment descriptor
    dw 0xffff    ; limit
    dw 0x0       ; base
    db 0x0       ; base
    db 10011010b ; 1st flags, type flags
    db 11001111b ; 2th flags, limit
    db 0x0       ; base

gdt_data: ; data segment descriptor
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0

gdt_end:


gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; size of GDT
    dd gdt_start ; start address of GDT

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

