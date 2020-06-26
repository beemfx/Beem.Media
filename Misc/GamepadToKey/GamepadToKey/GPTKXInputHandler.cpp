#include "GPTKXInputHandler.h"

#include <windows.h>
#include <xinput.h>

enum class xi_button 
{
	NONE   ,
	DUP    , // D-Pad
	DDOWN  , // D-Pad
	DLEFT  , // D-Pad
	DRIGHT , // D-Pad
	START  ,
	BACK   ,
	L3     , // Left Thumb (Stick)
	R3     , // Right Thumb (Stick)
	L1     , // Left Bumper (LB)
	R1     , // Right Bumper (RB)
	A      , // A or X
	B      , // B or Circle
	X      , // X or Square
	Y      , // Y or Triangle
	L2     , // Left Trigger (LT)
	R2     , // Right Trigger (RT)
	LUP    , // Left Stick Direction
	LDOWN  , // Left Stick Direction
	LLEFT  , // Left Stick Direction
	LRIGHT , // Left Stick Direction
	RUP    , // Right Stick Direction
	RDOWN  , // Right Stick Direction
	RLEFT  , // Right Stick Direction
	RRIGHT , // Right Stick Direction
	COUNT  ,
};

static const struct xiButtonToKey
{
	xi_button Button;
	DWORD     Key;
}
JOYSTICK_ButtonToKeyTable[] =
{
	{ xi_button::DUP    , 'W' },
	{ xi_button::DDOWN  , 'S' },
	{ xi_button::DLEFT  , 'A' },
	{ xi_button::DRIGHT , 'D' },
	{ xi_button::START  , VK_RETURN },
	{ xi_button::BACK   , VK_ESCAPE },
	{ xi_button::L3     , VK_NEXT },
	{ xi_button::R3     , VK_PRIOR },
	{ xi_button::L1     , VK_OEM_4 },
	{ xi_button::R1     , VK_OEM_6 },
	{ xi_button::A      , VK_CONTROL },
	{ xi_button::B      , 'Z' },
	{ xi_button::X      , 'X' },
	{ xi_button::Y      , 'C' },
	{ xi_button::L2     , VK_OEM_COMMA },
	{ xi_button::R2     , VK_OEM_PERIOD },
	{ xi_button::LUP    , 'W' },
	{ xi_button::LDOWN  , 'S' },
	{ xi_button::LLEFT  , 'A' },
	{ xi_button::LRIGHT , 'D' },
	{ xi_button::RUP    , VK_NUMPAD8 },
	{ xi_button::RDOWN  , VK_NUMPAD2 },
	{ xi_button::RLEFT  , VK_NUMPAD4 },
	{ xi_button::RRIGHT , VK_NUMPAD6 },
};

class GPTKXInputHandler
{
#define countof(b) (sizeof(b)/sizeof(0[(b)]))
private:

	DWORD m_ControllerIndex;
	float m_RightAxis[2];
	float m_LeftAxis[2];
	bool  m_ButtonsDownThisFrame[static_cast<unsigned>(xi_button::COUNT)];
	bool  m_ButtonsDown[static_cast<unsigned>(xi_button::COUNT)];
	bool  m_ButtonsPressed[static_cast<unsigned>(xi_button::COUNT)];
	bool  m_ButtonsReleased[static_cast<unsigned>(xi_button::COUNT)];

public:

	GPTKXInputHandler( DWORD ControllerIndex )
		: m_ControllerIndex( ControllerIndex )
	{
		zero( &m_RightAxis );
		zero( &m_LeftAxis );
		zero( &m_ButtonsDownThisFrame );
		zero( &m_ButtonsDown );
		zero( &m_ButtonsPressed );
		zero( &m_ButtonsReleased );
	}

	template<typename T>static void zero( T* Item ){ memset( Item , 0 , sizeof(*Item) ); };

	bool IsDown( xi_button Button )
	{
		unsigned Index = static_cast<unsigned>(Button);
		if( 0 <= Index && Index < countof(m_ButtonsDown) )
		{
			return m_ButtonsDown[Index];
		}
		return false;
	}

	bool WasPressed( xi_button Button )
	{
		unsigned Index = static_cast<unsigned>(Button);
		if( 0 <= Index && Index < countof(m_ButtonsPressed) )
		{
			return m_ButtonsPressed[Index];
		}
		return false;
	}

	bool WasReleased( xi_button Button )
	{
		unsigned Index = static_cast<unsigned>(Button);
		if( 0 <= Index && Index < countof(m_ButtonsReleased) )
		{
			return m_ButtonsReleased[Index];
		}
		return false;
	}

	void Update()
	{
		UpdateHeldButtons();
		UpdatePressesAndReleases();
	}

private:

	bool IsDownThisFrame( xi_button Button )
	{
		unsigned Index = static_cast<unsigned>(Button);
		if( 0 <= Index && Index < countof(m_ButtonsDownThisFrame) )
		{
			return m_ButtonsDownThisFrame[Index];
		}
		return false;
	}

	void SetDownThisFrame( xi_button Button , bool bSet )
	{
		unsigned Index = static_cast<unsigned>(Button);
		if( 0 <= Index && Index < countof(m_ButtonsDownThisFrame) )
		{
			m_ButtonsDownThisFrame[Index] = bSet;
		}
	}

	void SetDown( xi_button Button , bool bSet )
	{
		unsigned Index = static_cast<unsigned>(Button);
		if( 0 <= Index && Index < countof(m_ButtonsDown) )
		{
			m_ButtonsDown[Index] = bSet;
		}
	}

	void SetPressed( xi_button Button , bool bSet )
	{
		unsigned Index = static_cast<unsigned>(Button);
		if( 0 <= Index && Index < countof(m_ButtonsPressed) )
		{
			m_ButtonsPressed[Index] = bSet;
		}
	}

	void SetReleased( xi_button Button , bool bSet )
	{
		unsigned Index = static_cast<unsigned>(Button);
		if( 0 <= Index && Index < countof(m_ButtonsReleased) )
		{
			m_ButtonsReleased[Index] = bSet;
		}
	}

	void UpdateHeldButtons()
	{
		if( !(0<= m_ControllerIndex && m_ControllerIndex < XUSER_MAX_COUNT ) )
		{
			return;
		}

		// Helper functions.
		auto IsBetween = []( const auto& v1 , const auto& min , const auto& max) -> bool{ return (v1>=min) && (v1<=max); };

		XINPUT_STATE State;
		zero( &State );
		DWORD Res = XInputGetState( m_ControllerIndex , &State );

		bool bConnected = ERROR_SUCCESS == Res;

		zero( &m_RightAxis );
		zero( &m_LeftAxis );
		zero( &m_ButtonsDownThisFrame );



		if( bConnected )
		{
			//Get button states:
			//Regular buttons:
			if( 0 != (State.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_UP)        ){ SetDownThisFrame( xi_button::DUP , true ); }
			if( 0 != (State.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_DOWN)      ){ SetDownThisFrame( xi_button::DDOWN , true ); }
			if( 0 != (State.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_LEFT)      ){ SetDownThisFrame( xi_button::DLEFT , true ); }
			if( 0 != (State.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_RIGHT)     ){ SetDownThisFrame( xi_button::DRIGHT , true ); }
			if( 0 != (State.Gamepad.wButtons&XINPUT_GAMEPAD_START)          ){ SetDownThisFrame( xi_button::START , true ); }
			if( 0 != (State.Gamepad.wButtons&XINPUT_GAMEPAD_BACK)           ){ SetDownThisFrame( xi_button::BACK , true ); }
			if( 0 != (State.Gamepad.wButtons&XINPUT_GAMEPAD_LEFT_THUMB)     ){ SetDownThisFrame( xi_button::L3 , true ); }
			if( 0 != (State.Gamepad.wButtons&XINPUT_GAMEPAD_RIGHT_THUMB)    ){ SetDownThisFrame( xi_button::R3 , true ); }
			if( 0 != (State.Gamepad.wButtons&XINPUT_GAMEPAD_LEFT_SHOULDER)  ){ SetDownThisFrame( xi_button::L1 , true ); }
			if( 0 != (State.Gamepad.wButtons&XINPUT_GAMEPAD_RIGHT_SHOULDER) ){ SetDownThisFrame( xi_button::R1 , true ); }
			if( 0 != (State.Gamepad.wButtons&XINPUT_GAMEPAD_A)              ){ SetDownThisFrame( xi_button::A , true ); }
			if( 0 != (State.Gamepad.wButtons&XINPUT_GAMEPAD_B)              ){ SetDownThisFrame( xi_button::B , true ); }
			if( 0 != (State.Gamepad.wButtons&XINPUT_GAMEPAD_X)              ){ SetDownThisFrame( xi_button::X , true ); }
			if( 0 != (State.Gamepad.wButtons&XINPUT_GAMEPAD_Y)              ){ SetDownThisFrame( xi_button::Y , true ); }
			//Trigger buttons
			if( State.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD  ){ SetDownThisFrame( xi_button::L2 , true ); }
			if( State.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD ){ SetDownThisFrame( xi_button::R2 , true ); }
			//Left stick buttons:
			if( State.Gamepad.sThumbLX >  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ){ SetDownThisFrame( xi_button::LRIGHT , true ); }
			if( State.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ){ SetDownThisFrame( xi_button::LLEFT , true ); }
			if( State.Gamepad.sThumbLY >  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ){ SetDownThisFrame( xi_button::LUP , true ); }
			if( State.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ){ SetDownThisFrame( xi_button::LDOWN , true ); }
			//Right stick buttons:
			if( State.Gamepad.sThumbRX >  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ){ SetDownThisFrame( xi_button::RRIGHT , true ); }
			if( State.Gamepad.sThumbRX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ){ SetDownThisFrame( xi_button::RLEFT , true ); }
			if( State.Gamepad.sThumbRY >  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ){ SetDownThisFrame( xi_button::RUP , true ); }
			if( State.Gamepad.sThumbRY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ){ SetDownThisFrame( xi_button::RDOWN , true ); }

			m_RightAxis[0] = State.Gamepad.sThumbRX/32767.f;
			m_RightAxis[1] = State.Gamepad.sThumbRY/32767.f;

			m_LeftAxis[0] = State.Gamepad.sThumbLX/32767.f;
			m_LeftAxis[1] = State.Gamepad.sThumbLY/32767.f;

			if( IsBetween( State.Gamepad.sThumbRX, -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE , XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ) )
			{
				m_RightAxis[0] = 0;
			}
			if( IsBetween( State.Gamepad.sThumbRY, -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE , XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ) )
			{
				m_RightAxis[1] = 0;
			}
			if( IsBetween( State.Gamepad.sThumbLX, -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE , XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ) )
			{
				m_LeftAxis[0] = 0;
			}
			if( IsBetween( State.Gamepad.sThumbLY, -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE , XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ) )
			{
				m_LeftAxis[1] = 0;
			}
		}
	}

	void UpdatePressesAndReleases()
	{
		for( unsigned ButtonIndex = 0; ButtonIndex < static_cast<unsigned>(xi_button::COUNT); ButtonIndex++ )
		{
			xi_button Button = static_cast<xi_button>(ButtonIndex);
			bool bHeld = IsDownThisFrame( Button );

			if( bHeld )
			{
				//If the button wasn't down, set as pressed.
				SetPressed( Button , !IsDown(Button) );
				SetReleased( Button , false );
				SetDown( Button , true );
			}
			else
			{
				//If the button was already down, set the deactivated flags...
				SetReleased( Button , IsDown(Button) );
				SetDown( Button , false );
				SetPressed( Button , false );
			}
		}
	}

#undef countof
};


static GPTKXInputHandler GPTKXInputHandler_Player1XInput( 0 );

void GPTKXInputHandler_Init()
{
	XInputEnable( TRUE );
}

void GPTKXInputHandler_Deinit()
{
	XInputEnable( FALSE );
}

void GPTKXInputHandler_Update( float DeltaTime , GPTKKeyHandler Handler , void* CbExtra )
{
	GPTKXInputHandler_Player1XInput.Update();

	for( const xiButtonToKey& Mapping : JOYSTICK_ButtonToKeyTable )
	{
		if( GPTKXInputHandler_Player1XInput.WasPressed(Mapping.Button) )
		{
			Handler( Mapping.Key , WM_KEYDOWN , CbExtra );
		}

		if( GPTKXInputHandler_Player1XInput.WasReleased(Mapping.Button) )
		{
			Handler( Mapping.Key , WM_KEYUP , CbExtra );
		}
	}
}
