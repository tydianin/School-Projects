; Final.asm
; Weston Gibson, CISP 310
; 16 May 2022

; standard starting sequence
.586
.MODEL FLAT
include io.h
.STACK 4096
.DATA

  ; introduction
  intro_label   BYTE  "Weston Gibson Final", 0
  intro_prompt  BYTE  "This program will accept a key number and 10 search numbers.", 0

  ; base variable
  input_string  BYTE  40 DUP(?)

  ; settings
  array_limit   DWORD 10

  ; input key
  key_prompt    BYTE  "Enter the key number (11 digits max).", 0
  key_var       DWORD 0

  ; input numbers
  array_prompt  BYTE  "Enter the array of numbers to be searched (11 digits max each).", 0
  array_numbers DWORD 10 DUP(?)

  ; output
  hits_count    DWORD 0
  output_label  BYTE  "Successful hits.", 0
  output_prompt BYTE  11 DUP(?), 0

; start of source code
.CODE

; main program
_MainProc PROC

            ; prepare
            mov     eax, 0
            mov     esi, 0

            ; introduction
            output  intro_label, intro_prompt

            ; get key
            input   key_prompt, input_string, 40
            atod    input_string
            mov     key_var, eax

            ; main loop
    entry:  cmp     esi, array_limit
            jnl     yrtne

            ; obtain number
            input   array_prompt, input_string, 40
            atod    input_string

            ; store number and increment index
            mov     array_numbers[esi*4], eax
            inc     esi

            ; if hit, increment count
            cmp     eax, key_var
            jne     entry
            inc     hits_count
            jmp     entry

            ; output count of hits
    yrtne:  mov     eax, hits_count
            dtoa    output_prompt, eax
            output  output_label, output_prompt

            ; clear registers and exit program
            mov     eax, 0
            ret

; end of main program
_MainProc ENDP

; end of source code
END
