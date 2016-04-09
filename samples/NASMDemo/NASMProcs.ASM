;----------------------------------------------------
;--- NASMProcs.ASM                                ---
;---    Examples of how to declare procedures     ---
;---    within NASM using standard C/C++ calling  ---
;---    conventions (__cdecl). And standard Win32 ---
;---    calling conventions (__stdcall).          ---
;---                                              ---
;--- Copyright (c) 2003 Blaine Myers              ---
;----------------------------------------------------

[BITS 32] ;Set 32 bit code generation.

[SECTION .code] ;Section containing code.

;Sybols to export.
global _power2_ASM;
global _power2_ASMSTD@8

;_power2_ASM is __cdecl which means the caller
;pops the parameters from the stack, so
;the function only needs to use them.

_power2_ASM:         ;Function is __cdecl
	mov eax, [esp+4]    ;Get num from params (stack + 4)
	mov cl, [esp+8]     ;Get power from params (stack + 8)
	shl eax, cl         ;Left-shift by cl (in effect eax = eax * (2 ^ cl)).
	ret                 ;Return with result in eax.

;_power2_ASMSTD@8 is __stdcall which means the
;procedure needs to pop the parameters from
;the stack.

_power2_ASMSTD@8: ;Function is __stdcall
	mov eax, [esp+4] ;Get pointers to parameters.
	mov ecx, [esp+8]
	shl eax, cl     ;Left-shift by cl (in effect eax = eax * (2 ^ cl)).
	ret 8           ;Return with result in eax, note that we pass 8 to clear the stack.
