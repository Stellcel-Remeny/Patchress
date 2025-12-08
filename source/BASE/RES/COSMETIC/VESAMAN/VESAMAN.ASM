 ;Falco Software 2000
;Cx-233=7.8 sec
;AMD-460=2.7 sec
.286
MANDEL SEGMENT
assume cs:mandel,ds:mandel,ss:mandel
org 100h
  START:

            mov ax,0a000h
            mov es,ax
            mov ax,4f02h
            mov bx,105h
            int 10h

            fld dword ptr [initb]
            fstp dword ptr [b]
            mov word ptr[loop1],0
            jmp @A1
    @L1:
            inc word ptr [loop1]
    @A1:
            fld dword ptr[b]
            fadd dword ptr[lp]
            fstp dword ptr[b]
            fld dword ptr[inita]
            fstp dword ptr[a]
            mov word ptr[loop2],0
            jmp @A2
    @L2:
            inc word ptr [loop2]
    @A2:
            fld dword ptr[a]
            fadd dword ptr[lp2]
            fstp dword ptr[a]
              CALL ITERATE

            cmp bx,word ptr [maxi]
            jae @NOPUT
            CALL PUTPIXEL
   @NOPUT:
            cmp word ptr[loop2],1023
            jne @L2
            cmp word ptr[loop1],767
            jne @L1

            xor ax,ax
            int 16h
            mov ax,3
            int 10h
            mov ax,4c00h
  INT 21h


  ITERATE PROC
            fld dword ptr [a]
            fld dword ptr [b]
            fild dword ptr [bout]
            xor bx,bx
            fldz
            fldz
            fldz
            fldz
    @ITER:
            fmul st,st(3)
            fadd st,st(0)
            fadd st,st(5)
            fincstp
            fsub st,st(1)
            fadd st,st(5)
            fst  st(2)
            fmul st,st(0)
            inc  bx
            fst  st(6)
            fdecstp
            fst  st(2)
            fmul st(2),st
            fdecstp
            fadd st,st(3)
            fcomp st(5)
            fnstsw ax
            and ah,41h
            jz @OK
            cmp bx,word ptr[maxi]
            jb @ITER
    @OK:
            finit
            ret
  ITERATE ENDP


  PUTPIXEL PROC
            push dx
            mov ax,1024
            mul word ptr[loop1]
            mov di,ax
            add di,word ptr[loop2]
                     ;Result=dx:ax
                     ;Since 1024*64 is exactly on the segment border (64k)
                     ;you dont have to check the x length.In other cases
                     ;insert this: adc dx,0
            pop cx
            cmp dx,cx
            je @NOPAGING
            push bx
            mov ax,4f05h   ;Lap number=dx
            mov bx,00h     ;bh=function(0) bl=window(0)
            int 10h
            pop bx
   @NOPAGING:
            add bl,byte ptr[color]
            mov es:[di],bl
            ret
  PUTPIXEL ENDP




  b    :DD ?
  a    :DD ?
  loop1:DW ?
  loop2:DW ?
  initb:DD -1.2
  inita:DD -2.4
  lp   :DD 0.003125
  lp2  :DD 0.003125
  bout :DD 4
  maxi :DW 150
  color:DB -2


  MANDEL ENDS
END START