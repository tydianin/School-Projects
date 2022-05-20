; february.asm
; Weston Gibson, CISP 310
; 19 March 2022

; input:
;	  an integer year
;
; output:
;   the number of days in February of that year

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
	l_intr	BYTE	"february.asm", 0
	p_intr	BYTE	"Please enter integer numbers only.", 0

	; input
	p_year  BYTE	"What year would you like to check?", 0

	; output
	l_year	BYTE	"Number of days in February", 0
  l_norm  BYTE  "28", 0
  l_leap  BYTE  "29", 0

	; variables
	string	BYTE	40 DUP(?)
  u_year  DWORD	0
  c_hund  DWORD 100
  c_fhun  DWORD 400
  c_four  DWORD 4

; start of source code
.CODE
_MainProc PROC

	            ; introductory message
	            output	l_intr, p_intr

	            ; get year from user
	            input	  p_year, string, 40
	            atod	  string
              mov	    u_year, eax

              ; check if year % 100 == 0
              cdq
              idiv    c_hund
              cmp	    edx, 0
              jnz	    CheckFour

              ; check if year % 400 == 0
              mov     eax, u_year
              cdq
              idiv    c_fhun
              cmp	    edx, 0
              jz	    LeapYear
              jnz     NormalYear

              ; check if year % 4 == 0
  CheckFour:  mov     eax, u_year
              cdq
              idiv    c_four
              cmp	    edx, 0
              jz	    LeapYear

              ; catch normal years
  NormalYear: output	l_year, l_norm
              jmp     Exit

              ; catch leap years
  LeapYear:   output	l_year, l_leap
	
	; clear registers and exit program
	Exit:       mov		  eax, 0
	            ret

_MainProc ENDP

; end of source code
END
