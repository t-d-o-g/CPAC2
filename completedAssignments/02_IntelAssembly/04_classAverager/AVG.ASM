
AVG PROC

	XOR	AX, AX			;AX holds the sum
	LEA	SI, W
	MOV	CX, 10			;CX has number of elements

ADDNOS:	
	ADD	Ax, [SI]		;sum = sum + element
	ADD	SI, 2			;index next element
	LOOP	ADDNOS			;loop until done
	XOR	DX, DX
	DIV	TEN
    	RET

AVG	ENDP




	