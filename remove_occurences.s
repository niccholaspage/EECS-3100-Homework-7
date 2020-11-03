	AREA removeOccurrences, CODE
	EXPORT remove_occurrences
	ALIGN

remove_occurrences	PROC
	PUSH {R4} ; push R4 to follow ARM calling procedure properly
	MOV R2, #0 ; Our index variable for the loop
	; Our index variable for the characters in
	; the string we are actually writing
	MOV R3, #0
loop
	LDRB R4, [R0, R2] ; Load a byte: R4 = *(str + R2)
	; If R0 is 0 (null terminator) exit since
	; we've finished going through the string
	CBZ R4, exit
	CMP R4, R1 ; Compare R4 to R1 (character to remove)
	ADD R2, #1 ; Increment our index variable by 1
	; if they are equal, loop again - we are not putting
	; this character in the string since its the one we
	; want to remove
	BEQ loop
	; At this point, we want to store the character we
	; are looking at into our string at index R3.
	STRB R4, [R0, R3]
	ADD R3, #1 ; Add 1 to R3 to be prepared for the next character.
	B loop
exit
	; we are almost done with the string! now we null
	; terminate the character at index R3 to properly
	; end it.
	MOV R4, #0
	STRB R4, [R0, R3]
	POP {R4} ; pop R4 to follow ARM calling procedure properly
	BX LR
	ENDP

	END
