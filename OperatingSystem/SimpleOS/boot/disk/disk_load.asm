disk_load:
    pusha

    push bx
    mov bx, MSG_DISK_LOAD_BEGIN
    call print_string
    pop bx

    push dx ; dh: sectors exprcted

    mov ah, 0x02 ; BISO read sector routine
    mov al, dh   ; read dh sectors
    mov ch, 0x00 ; cylinder 0
    mov dh, 0x00 ; head 0
    mov cl, 0x02 ; reading from the second sector, after the boot sector

    int 0x13

    jc disk_error ; jump if error (carry flog)

    pop dx
    cmp dh, al ; al: sectors read
    jne disk_error

    push bx
    mov bx, MSG_DISK_LOAD_SUCCESS
    call print_string
    pop bx

    popa
    ret

disk_error:
    mov bx, DISK_ERROR_MSG
    call print_string
    jmp $

DISK_ERROR_MSG db "disk read error!", 0
MSG_DISK_LOAD_BEGIN db "begin disk read...", 0
MSG_DISK_LOAD_SUCCESS db "disk read succeess!", 0
