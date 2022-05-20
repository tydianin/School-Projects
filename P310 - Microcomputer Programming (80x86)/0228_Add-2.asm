; add-2.asm
; Weston Gibson, CISP 310
; 28 February 2022

; preprocessor directives
.586
.MODEL FLAT

; header file for input/output
INCLUDE io.h

; reserve 4096 byte stack
.STACK 4096

; reserve storage for data
.DATA
    number1 DWORD   ?
    number2 DWORD   ?
    prompt1 BYTE    "Enter first number", 0
    prompt2 BYTE    "Enter second number", 0
    string  BYTE    40 DUP (?)
    result  BYTE    11 DUP (?), 0
    r_lbl   BYTE    "The sum is", 0

.CODE
_MainProc PROC
    
    ; get first number, convert to int, store in number1
    input prompt1, string, 40
    atod string
    mov number1, eax

    ; get second number, convert to int, store in ecx
    input prompt2, string, 40
    atod string
    mov number2, eax

    ; push both numbers to the stack
    push number2
    push number1

    ; call procedure
    call add2

    ; remove parametrs from stack
    add esp, 8

    ; convert result to ascii, store in eax
    dtoa result, eax

    ; output
    output r_lbl, result
_MainProc ENDP

; add two dwords passed on the stack
add2   PROC

    ; save EBP
    push   ebp

    ; establish stack frame
    mov    ebp,esp

    ; copy first parameter value
    mov    eax,[ebp+8]

    ; add second parameter value
    add    eax,[ebp+12]

    ; restore EBP
    pop    ebp

    ; return
    ret
add2   ENDP
END
