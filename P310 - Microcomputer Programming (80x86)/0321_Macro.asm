; macro.asm
; Weston Gibson, CISP 310
; 21 March 2022

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
   l_intr  BYTE  "macro.asm", 0
   p_intr  BYTE  "Please enter integer numbers only.", 0
   
   ; input
   p_inp1  BYTE  "Enter number 1", 0
   p_inp2  BYTE  "Enter number 2", 0
   
   ; output
   l_calc  BYTE  "The product is", 0
   
   ; variables
   u_temp  BYTE  40 DUP(?)
   u_inp1  DWORD ?
   u_inp2  DWORD ?
   c_calc  BYTE  11 DUP (?), 0

; start of source code
.CODE

           ; calculate sum of two dword parameters and store in eax
 multiply  MACRO   num_1, num_2
           mov     ebx, num_1
           mov     ecx, num_2
           imul    eax, edx, ebx, ecx
           ENDM

_MainProc PROC
           
           ; introductory message
           output  l_intr, p_intr
           
           ; get number 1 from user
           input   p_inp1, u_temp, 40
           atod    u_temp
           mov     u_inp1, eax
           
           ; get number 2 from user
           input   p_inp2, u_temp, 40
           atod    u_temp
           mov     u_inp2, eax

           ; calculate sum
          multiply u_inp1, u_inp2

           ; display results
           dtoa    c_calc, eax
           output  l_calc, c_calc

           ; clear registers and exit program
           mov     eax, 0
           ret

_MainProc ENDP

; end of source code
END
