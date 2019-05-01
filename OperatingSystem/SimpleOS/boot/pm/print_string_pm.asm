[bits 32]

VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

print_string_pm:
    pusha
    mov edx, VIDEO_MEMORY ; set edx to the start address of video memory

print_string_pm_loop:
    mov al, [ebx] ; store char at ebx in al
    mov ah, WHITE_ON_BLACK ; store attriutes in ah

    cmp al, 0
    je print_string_pm_done

    mov [edx], ax ; store char and attributes at current character cell
    add ebx, 1 ; increment ebx to the next char in string
    add edx, 2 ; increment edx to the next cell in video memory

    jmp print_string_pm_loop

print_string_pm_done:
    popa
    ret
