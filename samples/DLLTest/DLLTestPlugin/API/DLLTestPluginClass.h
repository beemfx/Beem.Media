// DLL Test

#pragma once

#include "DLLTestBaseClass.h"

class DLLTESTPLUGIN_API DLLTestPluginClass : public DLLTestBaseClass
{
public:
	
	virtual void VirtualFunction() override;
};
