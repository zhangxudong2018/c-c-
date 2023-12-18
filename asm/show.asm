assume cs:codesg,ds:datasg
datasg segment
    db 'welcome to masm!'
datasg ends

codesg segment
start:  
        mov ax,datasg
        mov ds,ax
        mov ax,0B800h
        mov es,ax
        mov si,0
        mov di,160*12+80-16
        
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
codesg ends
end start