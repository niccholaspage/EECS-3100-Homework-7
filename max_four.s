	AREA maxFour, CODE
	EXPORT max4
	ALIGN
max4	PROC
	CMP R0, R1 ; Compare the first two integers to each other
	MOVLT R0, R1 ; If R0 is less than R1, set R0 = R1
	CMP R2, R3 ; Compare the last two integers to each other
	MOVLT R2, R3 ; If R2 is less than R3, set R2 = R3
	CMP R0, R2 ; Compares the two king integers to each other
	MOVLT R0, R2 ; If R0 is less than R2, set R0 = R2
	BX LR ; go back to the caller
	ENDP
	END