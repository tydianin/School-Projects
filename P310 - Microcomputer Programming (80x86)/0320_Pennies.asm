; pennies.asm
; Weston Gibson, CISP 310
; 20 March 2022
;
; input:
;   an integer number of days worked
;
; output:
;   the number of pennies earned, starting at 1 and doubling each day

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
   l_intr  BYTE  "pennies.asm", 0
   p_intr  BYTE  "Please enter integer numbers only.", 0
   
   ; input
   p_days  BYTE  "Number of Days Worked (1-31)", 0
   
   ; output
   l_pens  BYTE  "Pennies Earned", 0
   
   ; variables
   string  BYTE  40 DUP(?)
   c_pens  BYTE  11

; start of source code
.CODE
_MainProc PROC

           ; introductory message
           output  l_intr, p_intr
           
           ; get number of days worked from user
   valid:  input   p_days, string, 40
           atod    string
           
           ; validate that entry is 1 <= x <= 31
           cmp     eax, 1
           jl      valid
           cmp     eax, 31
           jg      valid   
           
           ; move values into place
           sub     ecx, 1
           mov     ecx, eax
           mov     eax, 1
           mov     ebx, 1

           ; loop calculation
    pens:  imul    ebx, 2
           add     eax, ebx
           loop    pens

           ; display
           dtoa    c_pens, eax
           output  l_pens, c_pens

           ; clear registers and exit program
           mov     eax, 0
           ret
_MainProc ENDP
; end of source code
END
