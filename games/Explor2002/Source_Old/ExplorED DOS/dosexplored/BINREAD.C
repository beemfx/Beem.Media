#include <stdio.h>

void BinRead(FILE *fin);

main(int argc, char *argv[])
{
	FILE *fptr;
	char *filename;
	if (argv != NULL)
		filename=argv[1];
	else
		filename="new.map";
	fptr = fopen(filename, "rb");
	if(filename == NULL)
		printf("Failed to open %s", filename);
	else
		BinRead(fptr);
	fclose(fptr);
	return 0;
}

void BinRead(FILE *fin)
{
	int i;
	int x;
	i = 1;
	printf("Reading Binary\n");
	while(!feof(fin)){
		printf("%i: ", i);
		i++;
		fread(&x, sizeof(int), (size_t)1, fin);
		printf("%i\n", x);
		if(i==300)
			getch();
	}
}