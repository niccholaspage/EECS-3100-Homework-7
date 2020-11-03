	AREA stringCopy, CODE
	EXPORT strcpy ; fixed - strcpy needs to be exported so its visible from the C code
	ALIGN

strcpy	PROC
loop	LDRB r2, [r1] ; Load a byte, r1 = *src
	STRB r2, [r0] ; Store a byte, r0 = *dst
	ADD r1, #1 ; Increase memory pointer
	ADD r0, #1 ; Increase memory pointer
	CMP r2, #0 ; Zero terminator
	BNE loop ; Loop if not null terminator
	BX LR ; fixed - return back to the caller
	ENDP

	END
