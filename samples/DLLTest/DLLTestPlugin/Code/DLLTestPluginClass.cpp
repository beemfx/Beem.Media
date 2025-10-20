// DLL Test

#include "DLLTestPluginClass.h"
#include "DLLCoreLib.h"

void DLLTestPluginClass::VirtualFunction()
{
	DLLTestBaseClass::VirtualFunction();

	BaseFunction();

	printf( "DLLTestPluginClass::VirtualFunction\n" );

	DLLCoreLib_DoSomething( "Hi From DLLTestPluginClass::VirtualFunction" );
}
