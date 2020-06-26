#pragma once
#include <windows.h>

typedef void ( * GPTKKeyHandler )( DWORD Key , UINT Msg , void* Extra );

void GPTKXInputHandler_Init();
void GPTKXInputHandler_Deinit();
void GPTKXInputHandler_Update( float DeltaTime , GPTKKeyHandler Handler  , void* CbExtra );