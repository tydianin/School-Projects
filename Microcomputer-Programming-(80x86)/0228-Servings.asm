; w1421760-Assignment4-3.asm
; Weston Gibson, CISP 310
; 28 February 2022

; conditions:
;   30 cookies per bag
;   10 servings per bag
;   240 calories per serving
;
; input:
;   cookies eaten
;
; output:
;   total calories consumed

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
	l_intr	BYTE	"w1421760-Assignment4-3.asm", 0
	p_intr	BYTE	"This program will calculate the number of calories consumed.", 0

	; input prompts
	p_coki	BYTE	"How many cookies did you eat?", 0
	
	; output labels
	l_calo	BYTE	"Total Calories Consumed", 0

	; constants
	servin	DWORD	3
	calori	DWORD	240
	
	; variables
	string	BYTE	40 DUP(?)

	; output
	c_calo	BYTE	11

; start of source code
.CODE
_MainProc PROC

	; introductory message
	output	l_intr, p_intr

	; get number of cookies eaten
	input		p_coki, string, 40
	atod		string

	; calculate number of servings consumed
	cdq
	div			servin

	; move full servings to ecx for later
	mov			ebx, eax
	
	; calculate and move partial calories
	mov			eax, edx
	mul			calori
	cdq
	div			servin
	mov			ecx, eax

	; calculate total calories
	mov			eax, ebx
	mul			calori
	add			eax, ecx

	; output total calories consumed
	dtoa		c_calo, eax
	output	l_calo,	c_calo

	; clear registers and exit program
	mov			eax,	0
	ret

_MainProc ENDP

; end of source code
END