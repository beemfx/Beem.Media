/* Filename: Main.c */

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

void MasmSub(char *, short *, long *);

int __cdecl power2(int num, char power);

#ifdef __cplusplus
}
#endif

char chararray[4]="abc";
short shortarray[3]={1,2,3};
long longarray[3]={32768, 32769, 32770};

int main(void)
{
	printf("%s\n", chararray);
	printf("%d %d %d\n", shortarray[0], shortarray[1], shortarray[2]);
	printf("%ld %ld %ld\n", longarray[0], longarray[1], longarray[2]);
	MasmSub(chararray, shortarray, longarray);
	printf("%s\n", chararray);
	printf("%d %d %d\n", shortarray[0], shortarray[1], shortarray[2]);
	printf("%ld %ld %ld\n", longarray[0], longarray[1], longarray[2]);
	
	//printf("The result is: %i\n", power2(3, 5));
	return 0;
}