; 主引导程序
; --------------------------------
SECTION MBR vstart=0x7c00
    mov ax, cs
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov fs, ax
    mov sp, 0x7c00

; 清屏利用0x06号功能,上卷全部行,则可清屏
; ---------------------------------
; INT 0x10 功能号0x06 功能描述:上卷窗口, 光标位置不变
; ---------------------------------
; 输入:
; AH 功能号=0x06
; AL = 上卷的行数(如果为0, 表示全部)
; BH = 属性, 默认为07h(白色)
; (CL, CH) = 窗口左上角(X, Y)位置
; (DL, DH) = 窗口右下角(X, Y)位置
; 无返回值

    mov ax, 0x0600
    mov bx, 0x0700
    mov cx, 0           ; 左上角(0, 0)
    mov dx, 0x184f      ; 右下角(80, 25)
                        ; VGA文本模式中,一行只能容纳80个字符, 25行
                        ; 下标从0开始
    int 0x10

; 下面三行代码获取光标位置
    mov ah, 3           ; 3号子功能,获取光标位置
    mov bh, 0           ; 待获取光标的页号

    int 0x10

; 获取光标位置结束

; 打印字符串
    mov ax, message
    mov bp, ax
    mov cx, 5
    mov ax, 0x1301      ; 13号子功能 ah=13 al=01光标跟随到新位置
    mov bx, 0x2         ; bh=0页号, bl=02黑底绿字
    int 0x10
; 打印字符串结束

    jmp $

    message db "1 MBR"
    times 510-($-$$) db 0
    db 0x55, 0xaa