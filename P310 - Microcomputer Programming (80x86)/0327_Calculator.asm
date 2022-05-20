; calculator.asm
; Weston Gibson, CISP 310
; 27 March 2022
;
; input:
;   mathematical operator, two numbers
;
; output:
;   result of the operation

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
  l_intro      BYTE  "calculator.asm", 0
  p_intro      BYTE  "To end the program, enter 'e' at any prompt.", 0

  ; standard input/output
  u_input      BYTE  40 DUP(?)
  c_output     BYTE  11 DUP(?), 0

  l_output     BYTE  "Result", 0
  l_divide     BYTE  "Remainder", 0

  ; operator
  p_operator   BYTE  "Enter the operation you would like to perform: (+ - * /).", 0
  u_operator   BYTE  1 DUP(?)

  el_operator  BYTE  "Error: operator not valid.", 0
  ep_operator  BYTE  "Please enter a valid operator: (+ - * /).", 0

  ; number
  u_number1    DWORD ?
  u_number2    DWORD ?

  p_number1    BYTE  "Enter the first number.", 0
  p_number2    BYTE  "Enter the second number.", 0

; start of source code
.CODE

; main program
_MainProc PROC

            ; introductory message
            output  l_intro, p_intro

            ; main program loop
  validate: input   p_operator, u_operator, 2

            ; end program if input = e
            cmp     u_operator, 'e'
            je      close

            ; input validation
            cmp     u_operator, '+'
            je      valid
            cmp     u_operator, '-'
            je      valid
            cmp     u_operator, '*'
            je      valid
            cmp     u_operator, '/'
            je      valid

            ; error message
            output  el_operator, ep_operator
            jmp     validate

            ; get numbers
  valid:    input   p_number1, u_input, 40
            atod    u_input
            mov     u_number1, eax

            input   p_number2, u_input, 40
            atod    u_input
            mov     u_number2, eax

            ; call the appropriate procedure
            cmp     u_operator, '+'
            je      add2
            cmp     u_operator, '-'
            je      sub2
            cmp     u_operator, '*'
            je      mul2
            cmp     u_operator, '/'
            je      div2
  
  add2:     push    u_number2
            push    u_number1
            call    Add2
            jmp     clean

  sub2:     push    u_number2
            push    u_number1
            call    Sub2
            jmp     clean

  mul2:     push    u_number2
            push    u_number1
            call    Mul2
            jmp     clean

  div2:     push    u_number2
            push    u_number1
            call    Div2
            jmp     clean

            ; clean up the stack
  clean:    add     esp, 8

            ; print result
  print:    dtoa    c_output, eax
            output  l_output, c_output

            ; if dividing, print remainder
            cmp     u_operator, '/'
            jne     restart
            dtoa    c_output, edx
            output  l_divide, c_output

            ; loop
  restart:  mov     ecx, 0
            dec     ecx
            jnz     validate
  
            ; clear registers and exit program
  close:    mov     eax, 0
            ret

_MainProc ENDP

; add two numbers
Add2 PROC
  ; prepare the stack
  push  ebp
  mov   ebp, esp

  ; variables
  mov   eax, [ebp+8]
  add   eax, [ebp+12]

  ; calculate, cleanup, and return
  pop   ebp
  ret
Add2 ENDP

; subtract two numbers
Sub2 PROC
  ; prepare the stack
  push  ebp
  mov   ebp, esp
  push  ebx

  ; variables
  mov   eax, [ebp+8]
  mov   ebx, [ebp+12]

  ; calculate
  sub   eax, ebx

  ; calculate, cleanup, and return
  pop   ebx
  pop   ebp
  ret
Sub2 ENDP

; multiply two numbers
Mul2 PROC
  ; prepare the stack
  push  ebp
  mov   ebp, esp
  push  ebx

  ; variables
  mov   eax, [ebp+8]
  mov   ebx, [ebp+12]

  ; calculate
  mul  eax

  ; calculate, cleanup, and return
  pop   ebx
  pop   ebp
  ret
Mul2 ENDP

; divide two numbers
Div2 PROC
  ; prepare the stack
  push  ebp
  mov   ebp, esp
  push  ebx

  ; variables
  mov   eax, [ebp+8]
  mov   ebx, [ebp+12]

  ; calculate
  cdq
  div  ebx
  mov  ebx, edx

  ; calculate, cleanup, and return
  pop   ebx
  pop   ebp
  ret
Div2 ENDP

; end of source code
END
