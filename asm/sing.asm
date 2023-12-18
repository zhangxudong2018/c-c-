assume cs:codeseg,ds:dataseg,ss:stackseg
dataseg segment
mus_freq    dw 262,262,262,196,330,330,330,262
            dw 262,330,392,392,349,330,294
            dw 294,330,349,349,330,294,330,262
            dw 262,330,294,196,247,294,262,-1

mus_time    dw 3 dup(12,12,25,25),12,12,50
            dw 3 dup(12,12,25,25),12,12,50
dataseg ends

stackseg segment
    db 100h dup(0)
stackseg ends

codeseg segment

start:
    ;主程序
    mov ax,stackseg
    mov ss,ax
    mov sp,100h
    mov ax,dataseg
    mov ds,ax
    lea si,mus_freq
    lea di,mus_time
play:
    mov dx,[si]
    cmp dx,-1
    je end_play
    call sound
    add si,2
    add di,2
    jmp play
end_play:
    mov ax,4c00h
    int 21h

    ;子程序：演奏一个音符
sound:
    push ax
    push dx
    push cx

    ;8235芯片（定时/计数器）的设置
    mov al,0b6h         ;8253初始化
    out 43h,al          ;43H是8253芯片控制口的端口地址
    mov dx,12h
    mov ax,34dch
    div word ptr [si]   ;计算分频值，[si]中存放声音的频率值
    out 42h,al          ;先送低8位道计数器
    mov al,ah
    out 42h,al          ;后送高8位计数器

    ;设置8255芯片，控制扬声器的开/关
    in al,61h
    mov ah,al
    or al,3
    out 61h,al

    ;延时一定的时长
    mov dx,[di]
wait1:
    mov cx,28000
delay:
    nop
    loop delay
    dec dx
    jnz wait1

    ;恢复扬声器端口原值
    mov al,ah
    out 61h,al

    pop cx
    pop dx
    pop ax
    ret

codeseg ends
end start 