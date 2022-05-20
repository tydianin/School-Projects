; expenses.asm
; Weston Gibson, CISP 310
; 28 February 2022

; input monthly expenses:
;	  rent/mortgage
;	  utility
;	  phone
;	  cable
;
; output total expenses:
;	  monthly
;	  annual

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
	l_intr	BYTE	"expenses.asm", 0
	p_intr	BYTE	"Please enter expenses rounded to the nearest dollar.", 0

	; input prompts
	p_rent	BYTE	"Monthly Rent/Mortgage?", 0
	p_util	BYTE	"Monthly Utilities?", 0
	p_phon	BYTE	"Monthly Phone Bill?", 0
	p_cabl	BYTE	"Monthly Cable Bill?", 0
	
	; output labels
	l_year	BYTE	"Total Yearly Expenses", 0
	l_mont	BYTE	"Total Monthly Expenses", 0

	; constants
	year		DWORD	12
	
	; variables
	string	BYTE	40 DUP(?)
	u_rent	DWORD	?
	u_util	DWORD	?
	u_phon	DWORD	?

	; output
	c_mont	BYTE	11
	c_year	BYTE	11

; start of source code
.CODE
_MainProc PROC

	; introductory message
	output	l_intr, p_intr

	; get rent/mortgage expense
	input		p_rent, string, 40
	atod		string
	mov			u_rent, eax

	; get utilities expense
	input		p_util, string, 40
	atod		string
	mov			u_util, eax

	; get phone expense
	input		p_phon, string, 40
	atod		string
	mov			u_phon, eax

	; get cable expense
	input		p_cabl, string, 40
	atod		string

	; calculate total monthly expenses
	add			eax, u_rent
	add			eax, u_util
	add			eax, u_phon

	; output monthly expenses
	dtoa		c_mont, eax
	output	l_mont, c_mont

	; calculate total yearly expenses
	mul			year

	; output yearly expenses
	dtoa		c_year, eax
	output	l_year, c_year

	; clear registers and exit program
	mov			eax, 0
	ret

_MainProc ENDP

; end of source code
END
