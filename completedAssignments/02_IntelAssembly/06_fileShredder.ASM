TITLE SHREDDER
.MODEL	SMALL
.STACK 	100H
.DATA
PROMPT		DB 	'FILENAME:$'
MSG		DB	'YOUR FILE HAS BEEN SHREDDED.$'
CRLF		DB	0DH, 0AH, '$'
NULL		DW	'0'
PATH		DB	'A:\'
FILENAME	DB	30 DUP (0)
BYTES		DW	?
BUFFER		DB	512 DUP (0)
HANDLE		DW	?
OPENERR		DB	0DH, 0AH, 'OPEN ERROR - CODE'
ERRCODE		DB	30H, '$'

.CODE
MAIN	PROC
	MOV	AX, @DATA
	MOV	DS, AX			;initialize DS
	MOV	ES, AX			;and ES
	CALL	GET_NAME		;read filename
	LEA	DX, FILENAME		;DX has filename offset
	MOV	AL, 2			;access code for read/write
	CALL	OPEN			;open file
	JC	OPEN_ERROR		;exit if error
	MOV	HANDLE, AX		;save handle
READ_LOOP:
	LEA	DX, BUFFER		;DX pts to buffer
	MOV	BX, HANDLE		;get handle
	CALL	READ			;read file. AX = Bytes read
	OR	AX, AX			;end of file?
	JE	SHRED			;yes, exit
	MOV	CX, AX			;CX gets no. of bytes read
	
	MOV	BYTES, AX
	JMP 	READ_LOOP		;exit
OPEN_ERROR:
	LEA	DX, OPENERR		;get error message
	ADD	ERRCODE, AL		;convert error code to ASCII
	MOV	AH, 9
	INT	21H			;display error message
	JMP	EXIT
SHRED:
	CALL	MOV_PTR
	MOV	CX, BYTES
SHREDDER:
	CALL	WRITE
	LOOP	SHREDDER

	MOV	AH, 9			;carriage return/line feed
	LEA	DX, CRLF
	INT	21H

	LEA	DX, MSG			;message
	MOV	AH, 9
	INT	21H
EXIT:
	MOV	BX, HANDLE		;get handle
	CALL	CLOSE			;close file
	MOV	AH, 41H
	LEA	DX, FILENAME		;DX has filename offset
	INT	21H
	MOV	AH, 4CH			
	INT	21H			;dos exit
MAIN	ENDP

GET_NAME	PROC	NEAR
;reads and stores filename
;input: none
;output: filename stored as ASCIIZ string
	PUSH	AX			;save registers used
	PUSH	CX
	PUSH	DX
	PUSH	DI
	PUSH	SI
	MOV	AH, 9			;display string function
	LEA	DX, PROMPT	
	INT	21H			;display data prompt
	CLD
	LEA	SI, PATH
	LEA	DI, FILENAME		;DI pts to filename
	MOV	CX, 3
	REP	MOVSB
	MOV	AH, 1			;read char function
READ_NAME:
	INT	21H			;get a char
	CMP	AL, 0DH			;CR?
	JE	DONE			;yes, exit
	STOSB				;no, store in string
	JMP	READ_NAME		;keep reading
DONE:
	MOV	AL, 0
	STOSB				;store 0 byte
	POP	SI			;restore registers
	POP	DI
	POP	DX
	POP	CX
	POP	AX
	RET
GET_NAME	ENDP

OPEN	PROC	NEAR
;opens file
;input: DS:DX filename
;	AL access code
;output: if successful, AX handle
;	if unsuccessful, CF = 1, AX = error code
	MOV	AH, 3DH			;open file fcn
	MOV	AL, 2			;input/output
	INT	21H			;open file
	RET
OPEN	ENDP

READ	PROC	NEAR
;reads a file sector
;input: BX file handle
;	CX bytes to read (512)
;	DS:DX buffer
;output: if successful, sector in buffer
;	AX number of bytes read
;	if unsuccessful, CF = 1
	PUSH	CX
	MOV	AH, 3FH			;read file fcn
	MOV	CX, 512			;512 bytes
	INT	21H			;read file into buffer
	POP	CX
	RET
READ	ENDP

WRITE	PROC	NEAR
	PUSH	CX
	MOV	AH, 40H			;write file fcn
	MOV	CX, 1			
	LEA	DX, NULL
	INT	21H			
	POP	CX
	RET
WRITE	ENDP

MOV_PTR	PROC	NEAR
;moves file pointer to eof
;input: BX = file handle
;output: DX:AX = pointer position from beginning
	MOV	AH, 42H			;move ptr funciton
	XOR	CX, CX  		;0 bytes
	XOR	DX, DX			;from end of file
	MOV	AL, 0			;movement code
	INT	21H			;move ptr
	RET
MOV_PTR	ENDP

DISPLAY	PROC	NEAR
;displays memory on screen
;input: BX = handle (1)
;	CX = bytes to display
;	DS:DX = data address
;output: AX = bytes displayed
	PUSH	BX
	MOV	AH, 40H			;write file fcn
	MOV	BX, 1			;handle for screen
	INT	21H			;display file
	POP	BX
	RET	
DISPLAY	ENDP

CLOSE	PROC	NEAR
;closes a file
;input: BX = handle
;output: if CF = 1, error code in AX
	MOV	AH, 3EH			;close file fcn
	INT	21H			;close file
	RET
CLOSE	ENDP

	END	MAIN