#include <stdio.h>
#include <conio.h>

#include "oedbx/examples/ex1.h"

int main( int argc , char* argv[] )
{
	printf( "DBX Exporter (c) 2016 Beem Media\n" );

	ExtractAllMessages( "../Might and Magic.dbx" , "../extraction.log" );

	printf( "Done.\n" );
	#if defined( _DEBUG )
	_getch();
	#endif
	return 0;
}