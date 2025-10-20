// DLL Test

#include "DLLCoreLib.h"
#include <stdio.h>
#include <string>
#include <format>
#include <Windows.h>

DLLCORELIB_API void DLLCoreLib_DoSomething(const char* InMsg)
{
	static int CallCount = 0;
	CallCount++;

	printf( "Calling in DLL Core Lib: %s" , InMsg );

	std::string Msg = std::format("Calling in DLL Core Lib: {0}, Count={1}\r\n", InMsg, CallCount);
	// Msg += InMsg;
	// Msg += " Count=";
	// Msg += CallCount;
	// Msg += "\r\n";

	OutputDebugStringA(Msg.c_str());
}