#ifndef _MCONVERT_H_
#define _MCONVERT_H_

#define MAX_NAMELEN 255
#define MAX_CODELEN 3
#define MAX_ENTRIES 12 //This must change

class ExData
{
	public:
		int GetConversionInfo();
		char countryName[MAX_ENTRIES][MAX_NAMELEN];
		char countryCode[MAX_ENTRIES][MAX_CODELEN];
		double exchangeRate[MAX_ENTRIES];
		int numentries;
};
#endif