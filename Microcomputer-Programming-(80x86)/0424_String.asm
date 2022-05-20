; string.asm
; Weston Gibson, CISP 310
; 10 April 2022
;
; Displays a concatenated string
;
; l_label  p_prompt  s_string

; startup
.586
.MODEL FLAT
include io.h
.STACK 4096
.DATA

  ; introduction
  l_intro   BYTE  "string.asm", 0
  p_intro   BYTE  "This program will accept two strings and output the concatenated string.", 0

  ; input prompts
  l_input1  BYTE  "Enter the first string: ", 0
  l_input2  BYTE  "Enter the second string: ", 0

  ; output prompt
  l_output  BYTE  "The concatenated string is: ", 0

  ; input strings
  s_input   BYTE  100 DUP(?)
  s_output  BYTE  100 DUP(?)

; start of source code
.CODE

; main program
_MainProc PROC

          ; introduction
          output  l_intro, p_intro

          ; get first string
          input   l_input1, s_input, 100
          lea     esi, s_input
          lea     edi, s_output
          push    esi
          push    edi
          cld
  
          ; add characters from string one until null
  valid1: cmp     BYTE PTR [esi], 0
          je      input2
          movsb
          loop    valid1
  
          ; get second string
  input2: input   l_input2, s_input, 100
          lea     esi, s_input
  
          ; add characters from string two until null
  valid2: cmp     BYTE PTR [esi], 0
          je      dilav
          movsb
          loop    valid2
  
          ; concat the strings
   dilav: mov     BYTE PTR [edi], 0
          pop     esi
          pop     edi

          ; output concatenated string
          output  l_output, s_output

          ; clear eax and exit program
          mov eax, 0
          ret

; end of main program
_MainProc ENDP

; end of source code
END
