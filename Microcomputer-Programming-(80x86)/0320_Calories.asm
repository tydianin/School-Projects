; calories.asm
; Weston Gibson, CISP 310
; 20 March 2022
;
; calculates and outputs the number of calories burned over
;   5, 10, 15, 20, 25, and 30 seconds.

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
   l_intr  BYTE  "calories.asm", 0
   p_intr  BYTE  "This program will display calories burned.", 0
   
   ; output
   l_outp  BYTE  "Calories Burned", 0
   
   ; variables
   c_outp  BYTE  11

; start of source code
.CODE
_MainProc PROC

           ; introductory message
           output  l_intr, p_intr
           
           ; move values into place
           mov     eax, 0
           mov     ecx, 6
           
           ; loop calculation and display
    burn:  add     eax, 4
           dtoa    c_outp, eax
           output  l_outp, c_outp
           loop    burn

           ; clear registers and exit program
           mov     eax, 0
           ret
_MainProc ENDP
; end of source code
END
