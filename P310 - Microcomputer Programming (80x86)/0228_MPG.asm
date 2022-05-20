; mpg.asm
; Weston Gibson, CISP 310
; 28 February 2022

; input:
;	  tank size (gallons)
;   miles on a full tank
;
; output:
;   average miles per gallon

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
	l_intr	BYTE	"mpg.asm", 0
	p_intr	BYTE	"Please enter estimates rounded to the nearest unit.", 0

	; input prompts
	p_tank  BYTE	"Gas tank size (in gallons)?", 0
	p_mile	BYTE	"Miles on a full tank?", 0

	; output labels
	l_avrg	BYTE	"Average Miles per Gallon", 0

	; variables
	string	BYTE	40 DUP(?)
	u_tank	DWORD	?

	; output
	c_avrg	BYTE	11

; start of source code
.CODE
_MainProc PROC

	; introductory message
	output	l_intr, p_intr

	; get gas tank size
	input	  p_tank, string, 40
	atod	  string
	mov		  u_tank, eax
	
	; get maximum miles per tank
	input	  p_mile, string, 40
	atod	  string
	
	; calculate average gas mileage
	cdq
	div		  u_tank
	
	; convert to ascii and output
	dtoa	  c_avrg, eax
	output	l_avrg, c_avrg
	
	; clear registers and exit program
	mov		  eax, 0
	ret

_MainProc ENDP

; end of source code
END
