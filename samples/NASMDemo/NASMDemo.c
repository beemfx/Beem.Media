#include <stdio.h>


/* Declarations for the ASM within NASM functions. */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int __cdecl power2_ASM(unsigned long num, char power);
int __stdcall power2_ASMSTD(unsigned long num, char power);

#ifdef __cplusplus
}
#endif /* __cplusplus */


/* power2C power2 C version. */
int __cdecl power2_C(unsigned long num, char power)
{
	return num<<power;
}

/* power2C power2 ASM within C version. */
int __cdecl power2_CASM(unsigned long num, char power)
{
   __asm
   {
      mov eax, num    /* Get first argument. */
      mov cl, power   /* Get second argument. */
      shl eax, cl     /* EAX = EAX * ( 2 to the power of CL ) */
	}
   /* Return with result in EAX. */
}

int __cdecl main(int argc, char** argv, char** envp)
{
	int nResult=0;

	printf("The function is power2(3, 5)...\n\n");

	printf("Doing assembly (__cdecl): %i\n", power2_ASM(3, 5));
	printf("Doing assembly (__stdcall): %i\n", power2_ASMSTD(3, 5));
	printf("Doing C (__cdecl): %i\n", power2_C(3, 5));
	printf("Doing assembly within C (__cdecl): %i\n", power2_CASM(3, 5));

	/* Calling C function within assembly, as __cdecl */
	__asm
	{
		/* Push the params onto the stack. */
		push 5 /* We push a 32-bit value because all parameters are passed as 32-bit. */
		push 3 /* "                                                                 " */
		/* Call the function now that the params are in place. */
		call power2_C
		/* Save the result. */
		mov nResult, eax
		/* Pop the parameters off the stack.  Becuase call is __cdecl. */
		pop ebx /* Pop the parameters off the stack. */
		pop ebx /* "                               " */
	}
	printf("Calling C within assembly (__cdecl): %i\n", nResult);

	return 0;
}
