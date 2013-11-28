
GET_SCORES PROC

	PUSH	SI
	LEA	DX, PROMPT
	MOV	AH, 9
	INT	21H

	MOV	AH, 9			;carriage return/line feed
	LEA	DX, CRLF
	INT	21H

	XOR	AX, AX
	LEA	SI, W
	MOV	CX, 10
INPUT:
	CALL	INDEC
	MOV	[SI], AX
	ADD	SI, 2
	MOV	AH, 9			;carriage return/line feed
	LEA	DX, CRLF
	INT	21H
	LOOP	INPUT	
	POP	SI
	RET

GET_SCORES	ENDP