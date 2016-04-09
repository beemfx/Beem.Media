;Filename: MASMSub.asm
;Assemble options needed for ML: /c /Cx /coff

.386
.MODEL flat, C
.CODE

_power2:
	mov eax, [esp+4]
	mov ecx, [esp+8]
	shl eax, cl
	ret

MasmSub PROC uses esi, \
	arraychar:PTR,      \
	arrayshort:PTR,     \
	arraylong:PTR
	mov esi, arraychar ;Load ESI with the address of the char array.
	mov BYTE PTR [esi],   "x";Since a char is 1 byte long, each 
	mov BYTE PTR [esi+1], "y";successive element can be accessed
	mov BYTE PTR [esi+2], "z";by adding 1 more to esi.
	mov esi, arrayshort ;Load ESI with the address of teh short array.
	add WORD PTR [esi],   7  ;Since a short is 2 bytes long, each
	add WORD PTR [esi+2], 7  ;successive element can be accessed
	add WORD PTR [esi+4], 7  ;by adding 2 more to esi.
	mov esi, arraylong ;Load ESI with the address of teh long array.
	inc DWORD PTR [esi]      ;Since a long is 4 bytes long, each
	inc DWORD PTR [esi+4]    ;successive element can be accessed
	inc DWORD PTR [esi+8]    ;by adding 4 more to esi.
	ret
MasmSub ENDP
END