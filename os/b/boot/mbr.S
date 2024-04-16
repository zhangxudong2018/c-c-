; 主引导程序
;
; LOADER_BASE_ADDR equ 0xA000
; LOADER_START_SECTOR equ 0x2
; ---------------------------------------------
SECTION MBR vstart=0x7c00
    mov ax, cs
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov fs, ax
    mov sp, 0x7c00
    mov ax, 0xb800
    mov gs, ax

; 清屏
; 利用0x06号功能，上卷全部行，则可清屏
; -----------------------------------------------
; INT 0x10 功能号: 0x06
; 输入:
;   AL = 0x06
;   BH = 0x00
;   CX = 行数
;   DX = 列数
; -----------------------------------------------
    mov ax, 0600h
    mov bx, 0700h
    mov cx, 0
    mov dx, 184fh
    int 10h

    ; 输出背景色绿色，前景色红色，并且跳动的字符串"1 MBR"

    mov byte [gs:0x00], '1'
    mov byte [gs:0x01], 0xA4    ; A表示绿色背景闪烁,4表示前景色为红色

    mov byte [gs:0x02], ' '
    mov byte [gs:0x03], 0xA4

    mov byte [gs:0x04], 'M'
    mov byte [gs:0x05], 0xA4

    mov byte [gs:0x06], 'B'
    mov byte [gs:0x07], 0xA4

    mov byte [gs:0x08], 'R'
    mov byte [gs:0x09], 0xA4

; 显示字符串
    jmp $

    message db "1 MBR"
    times 510-($-$$) db 0
    db 0x55, 0xaa