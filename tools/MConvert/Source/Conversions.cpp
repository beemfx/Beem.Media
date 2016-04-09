#include "MConvert.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <windows.h>
#include <tchar.h>



int ExData::GetConversionInfo()
/*
	I can't beleive I got this to work!
*/
{
	#define MAX_LINELEN 100
	FILE *fin;
	char filename[] = "rates.inf";
	char line[MAX_LINELEN];
	int i=0;
	int offset;
	char tempConvRate[10];

	numentries=0;
	if(( fin=fopen(filename, "r") )==NULL)
		return 110;

	fgets(line, MAX_LINELEN, fin);
	int timesaround=(int)_ttoi(line);

	//while(!feof(fin)){
	for(int j=0;j<timesaround;j++){
		fgets(line, MAX_LINELEN, fin);
		i=0;
		while(line[i]!=','){
			countryName[numentries][i]=line[i];
			i++;
		}
		i++;
		offset=i;
		i=0;
		while(line[i+offset]!=','){
			countryCode[numentries][i]=line[i+offset];
			i++;
		}
		i++;
		offset=offset+i;
		i=0;
		while(line[i+offset]!='\n'){
			tempConvRate[i]=line[i+offset];
			i++;
		}
		exchangeRate[numentries]=atof(tempConvRate);
		//char buf[100];
		//sprintf(buf, "Conversion rate is %f", exchangeRate[numentries]);
		//MessageBox(NULL, buf, "NOTE", MB_OK);
		numentries++;
	}
	fclose(fin);
	return 0;
}