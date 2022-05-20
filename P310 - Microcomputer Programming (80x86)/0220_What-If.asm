; What-If.asm
; Weston Gibson, CISP 310
; 20 February 2022

; preprocessor directives
.586
.MODEL FLAT

; header file for input/output
include io.h

; reserve 4096 byte stack
.STACK 4096

; reserve storage for data
.DATA

; prompts
prompt1 BYTE  "Student name?", 0
prompt2 BYTE  "Student major?", 0
prompt3 BYTE  "Major units required?", 0
prompt4 BYTE  "Major units completed?", 0

; labels
u_lbl   BYTE  "Units Needed", 0

; variables
string  BYTE   40 DUP(?)
s_name  BYTE   40
s_major BYTE   40
u_req   DWORD  ?
u_comp  DWORD  ?
u_need  BYTE   11

; start of source code
.CODE
_MainProc PROC

  ; get student name and major
  input  prompt1, s_name, 40
  input  prompt2, s_major, 40

  ; get major units required
  input  prompt3, string, 40
  atod   string
  mov    u_req, eax

  ; get major units completed
  input  prompt4, string, 40
  atod   string
  mov    u_comp, eax

  ; calculate major units needed
  mov    eax, u_req
  sub    eax, u_comp
  dtoa   u_need, eax
  output u_lbl, u_need

  ; exit program
  mov    eax, 0
  ret
_MainProc ENDP

; end of source code
END
