// DLL Test

#include "DLLTestBaseClass.h"
#include "DLLCoreLib.h"

void DLLTestBaseClass::BaseFunction()
{
	printf( "Base Function\n" );
	DLLCoreLib_DoSomething( "Hi From DLLTestBaseClass::BaseFunction" );
}

void DLLTestBaseClass::VirtualFunction()
{
	printf( "DLLTestBaseClass::VirtualFunction\n" );
	DLLCoreLib_DoSomething( "Hi From DLLTestBaseClass::VirtualFunction" );
}
