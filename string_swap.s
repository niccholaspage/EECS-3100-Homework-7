	AREA stringSwap, CODE
	EXPORT string_swap
	ALIGN
string_swap	PROC
	; Since R0 and R1 are just pointers to
	; pointers, this procedure is very simple.
	LDR R2, [R0] ; Load the value R0 points to into R2
	LDR R3, [R1] ; Load the value R1 points to into R3
	STR R3, [R0] ; Store the value R3 to into R0
	STR R2, [R1] ; Finally, store the value R2 into R1
	; This completes the string swap, now
	; we can just go back to the caller.
	BX LR
	ENDP
	END