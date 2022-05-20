; primes.asm
; Weston Gibson, CISP 310
; 10 April 2022
;
; calculates and displays the first 100 prime numbers
;
; a_array  c_computed  l_label  o_option  p_print

; standard starting sequence
.586
.MODEL FLAT
include io.h
.STACK 4096
.DATA

  ; introduction
  l_intro   BYTE  "primes.asm", 0
  p_intro   BYTE  "This program will display the first 100 prime numbers.", 0

  ; output
  l_output  BYTE  "Prime", 0
  c_output  BYTE  11 DUP(?), 0

  ; variables
  a_primes  DWORD 100 DUP(?)
  o_limit   DWORD 99  ; must be a_primes - 1
  c_count   DWORD 1

; start of source code
.CODE

; main program
_MainProc PROC

  ; initialize
  ; registers
            mov     eax, 0
            mov     ebx, 0
            mov     ecx, 0
            mov     edx, 0
            mov     esi, 0

  ; first two primes
            ; store first prime, increment
            mov     a_primes[4*esi], 2
            inc     esi

            ; store second prime, increment
            mov     a_primes[4*esi], 3
            inc     esi

  ; rest of array
            ; if at end of array, break
  iniLoop:  cmp     esi, o_limit
            je      outLoop

            ; store 0 at index, increment, and loop
            mov     a_primes[4*esi], 0
            inc     esi
            jmp     iniLoop

  ; main loop
  ; adds a discovered prime to the array
            ; if count >= limit, break
  outLoop:  mov     esi, c_count
            cmp     esi, o_limit
            jge     endOut

            ; ecx = array[count] + 2
            mov     ecx, a_primes[4*esi]
            add     ecx, 2

  ; inner loop
  ; checks if the number in question is a prime number
            ; reset esi on first run, increment on iteration
            mov     esi, 0
   inLoop:  inc     esi
            mov     eax, ecx

            ; if index > count, break
            cmp     esi, c_count
            jg      endIn

            ; check if number is divisible by element
            mov     ebx, a_primes[4*esi]
            cdq
            div     ebx

            ; if remainder != 0, check next element (maybe prime)
            cmp     edx, 0
            jnz     inLoop

            ; if remainder = 0, check next number (not prime)
            add     ecx, 2
            mov     esi, 0
            jmp     inLoop

            ; if no elements left, save and output (prime)
    endIn:  mov     a_primes[4*esi], ecx
            mov     c_count, esi
            jmp     outLoop
    
  ; output
            ; introduction
   endOut:  output  l_intro, p_intro

            ; reset and loop esi for index
            mov     esi, 0
  loopOut:  cmp     esi, o_limit
            jg      endLoop

            ; print each array element
            mov     eax, a_primes[4*esi]
            dtoa    c_output, eax
            output  l_output, c_output
            inc     esi
            jmp     loopOut

            ; clear registers and exit program
  endLoop:  mov     eax, 0
            ret

; end of main program
_MainProc ENDP

; end of source code
END
