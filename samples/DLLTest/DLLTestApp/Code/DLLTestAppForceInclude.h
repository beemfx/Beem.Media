// DLL Test

#pragma once

#include "DLLTestCore.h"

#define DLLTESTENGINE_API __declspec(dllimport)
#define DLLTESTPLUGIN_API __declspec(dllimport)
#define DLLCORELIB_API __declspec(dllimport)
