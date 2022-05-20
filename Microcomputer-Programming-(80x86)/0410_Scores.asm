; scores.asm
; Weston Gibson, CISP 310
; 10 April 2022
;
; accepts up to 10 test scores 0-100
; displays count of 100's
;
; a_array  c_computed  l_label  o_option  p_print

; standard starting sequence
.586
.MODEL FLAT
include io.h
.STACK 4096
.DATA

  ; introduction
  l_intro   BYTE  "scores.asm", 0
  p_intro   BYTE  "This program will accept up to 10 test scores between 0 and 100 points, then show how many perfect scores were entered.", 0

  ; input
  l_input   BYTE  "Enter a test score 0-100", 0
  u_input   BYTE  40 DUP(?)

  ; output
  l_output  BYTE  "Perfect Scores", 0
  c_output  BYTE  11 DUP(?), 0
  c_no_out  BYTE  "No perfect scores were entered.", 0

  ; validation
  l_valid   BYTE  "Invalid Input", 0
  p_valid   BYTE  "Please enter a test score between 0 and 100.", 0

  ; variables
  a_tests   WORD 10 DUP(?)
  o_limit   DWORD 10  ; must be a_tests - 1
  c_count   DWORD 0

; start of source code
.CODE

; main program
_MainProc PROC

  ; initialize registers
            mov     eax, 0
            mov     ebx, 0
            mov     ecx, 0
            mov     edx, 0
            mov     esi, 0

  ; introduction
            output  l_intro, p_intro

  ; main loop
    entry:  cmp     esi, o_limit
            jnl     yrtne

            ; obtain test score
            input   l_input, u_input, 40
            atod    u_input

            ; validate test score
            cmp     eax, 0
            jl      valid
            cmp     eax, 100
            jg      valid

            ; store test score and increment index
            mov     a_tests[esi*2], ax
            inc     esi

            ; if perfect, increment count
            cmp     eax, 100
            jne     entry
            inc     c_count
            jmp     entry
  
  ; input validation
    valid:  output  l_valid, p_valid
            mov     eax, 0
            jmp     entry

  ; output
    yrtne:  cmp     c_count, 0
            je      none

            ; output count of perfect scores
            mov     eax, c_count
            dtoa    c_output, eax
            output  l_output, c_output
            jmp     ending

            ; no perfect scores
     none:  output  l_output, c_no_out

            ; clear registers and exit program
   ending:  mov     eax, 0
            ret

; end of main program
_MainProc ENDP

; end of source code
END
