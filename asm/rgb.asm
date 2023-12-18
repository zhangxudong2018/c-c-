assume cs:codeseg,ds:dataseg

dataseg segment 
    db 'welcome to masm!'
dataseg ends

codeseg segment
start:
    ;初始化寄存器
    mov ax,dataseg
    mov ds,ax
    mov ax,0b800h
    mov es,ax
    mov si,0
    mov di,160*12+80-16

    ;显示字符串
    mov cx,16
w:  mov al,[si]
    mov es:[di],al
    inc di
    mov al,71h
    mov es:[di],al
    inc si
    inc di
    loop w

    mov ax,4c00h
    int 21h
codeseg ends
end start