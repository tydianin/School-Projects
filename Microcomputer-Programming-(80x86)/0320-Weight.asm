; w1421760-Assignment6.asm
; Weston Gibson, CISP 310
; 20 March 2022

; input:
;   an integer weight
;
; output:
;   the expected weight each month after 4 pounds of weight loss

; preprocessor directives
.586
.MODEL FLAT

; header file for input/output
include io.h

; reserve 4096 byte stack
.STACK 4096

; reserve storage for data
.DATA

   ; intro
   l_intr  BYTE  "w1421760-Assignment6.asm", 0
   p_intr  BYTE  "Please enter integer numbers only.", 0
   
   ; input
   p_wght  BYTE  "Current weight (whole pounds)", 0
   
   ; output
   l_wght  BYTE  "Weight", 0
   
   ; variables
   string  BYTE  40 DUP(?)
   c_wght  BYTE  11

; start of source code
.CODE
_MainProc PROC

           ; introductory message
           output  l_intr, p_intr
           
           ; get weight from user
           input   p_wght, string, 40
           atod    string
           
           ; loop calculation and display
           mov     ecx, 6
    loss:  sub     eax, 4
           dtoa    c_wght, eax
           output  l_wght, c_wght
           loop    loss

           ; clear registers and exit program
           mov     eax, 0
           ret

_MainProc ENDP

; end of source code
END