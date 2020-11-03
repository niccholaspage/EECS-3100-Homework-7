	AREA removeOccurrences, CODE
	EXPORT remove_occurrences ; fixed - strcpy needs to be exported so its visible from the C code
	ALIGN

remove_occurrences	PROC
	BX LR
	ENDP

	END
