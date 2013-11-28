TITLE SERIAL
.MODEL SMALL
.STACK 100H
.DATA
PROMPT	 	DB	'Number of serial ports: $'
CRLF	DB	0DH, 0AH, '$'
.CODE

MAIN PROC
	MOV	AX, @DATA
	MOV	DS, AX			;initialize DS
;invoke equipment check int
	INT	11H
;display prompt
        MOV	AH, 9			;carriage return/line feed
	LEA	DX, CRLF
	INT	21H
	LEA	DX, PROMPT		;prompt
	MOV	AH, 9
	INT	21H
;bit shift and mask
	MOV	CL, 9
	SHR	AX, CL			;shift 9 places
	AND	AX, 0007H		;mask all bits but 0,1,2
	CALL	OUTDEC			;display decimal value
	MOV	AH, 9			;carriage return/line feed
	LEA	DX, CRLF
	INT	21H
;exit
	MOV AH, 4CH
	INT	21H
MAIN	ENDP
INCLUDE PGM9_1.ASM
	END	MAIN