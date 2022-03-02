//-----------------------------------------------------------------------------
// SimpleController.cpp
// Simple controller support using XINPUT.
//-----------------------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------------------
#include <windows.h>  // for MS Windows
#include <stdio.h>
//-----------------------------------------------------------------------------
#include "SimpleController.h"
#include "app.h"

//-----------------------------------------------------------------------------
#if (_WIN32_WINNT >= 0x0602 /*_WIN32_WINNT_WIN8*/)
#include <XInput.h>
#pragma comment(lib,"xinput.lib")
#else
#include <XInput.h>
#pragma comment(lib,"xinput9_1_0.lib")
#endif
//-----------------------------------------------------------------------------
#define UPDATE_DZONE		// Define if you want a dead zone on the thumb stick analog inputs.
#define INPUT_DEADZONE  ( 0.10f * FLOAT(0x7FFF) )  // Default to 10% of the +/- 32767 range.   This is a reasonable default value but can be altered if needed.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Singleton
//-----------------------------------------------------------------------------
CSimpleControllers &CSimpleControllers::GetInstance()
{
	static CSimpleControllers theControllers;
	return theControllers;
}
//-----------------------------------------------------------------------------
void CSimpleControllers::Update()
{
    DWORD dwResult;
	int numControllers = 0;
    for( DWORD i = 0; i < MAX_CONTROLLERS; i++ )
    {
        // Simply get the state of the controller from XInput.
        dwResult = XInputGetState( i, &m_Controllers[i].m_state );

		if (dwResult == ERROR_SUCCESS)
		{
			m_Controllers[i].m_bConnected = true;
			numControllers++;
		}
        else
            m_Controllers[i].m_bConnected = false;
    }
	
	// No controllers so lets fake one using keyboard defines.
	if (numControllers == 0 )
	{
		m_Controllers[0].m_bConnected = true;
		WORD buttons = 0;
		m_Controllers[0].m_state.Gamepad.sThumbLX = 0;
		m_Controllers[0].m_state.Gamepad.sThumbLY = 0;
		m_Controllers[0].m_state.Gamepad.sThumbRX = 0;
		m_Controllers[0].m_state.Gamepad.sThumbRY = 0;
		m_Controllers[0].m_state.Gamepad.bLeftTrigger = 0;
		m_Controllers[0].m_state.Gamepad.bRightTrigger = 0;		

		if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_LEFT)) m_Controllers[0].m_state.Gamepad.sThumbLX = -32767;
		if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_RIGHT)) m_Controllers[0].m_state.Gamepad.sThumbLX = 32767;
		if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_UP)) m_Controllers[0].m_state.Gamepad.sThumbLY = -32767;
		if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_DOWN)) m_Controllers[0].m_state.Gamepad.sThumbLY = 32767;
		if (App::IsKeyPressed(APP_PAD_EMUL_BUTTON_ALT_A)) buttons |= XINPUT_GAMEPAD_A;
		if (App::IsKeyPressed(APP_PAD_EMUL_START)) buttons |= XINPUT_GAMEPAD_START;
		
		if (App::IsKeyPressed(APP_PAD_EMUL_RIGHT_THUMB_LEFT)) m_Controllers[0].m_state.Gamepad.sThumbRX = -32767;
		if (App::IsKeyPressed(APP_PAD_EMUL_RIGHT_THUMB_RIGHT)) m_Controllers[0].m_state.Gamepad.sThumbRX = 32767;
		if (App::IsKeyPressed(APP_PAD_EMUL_RIGHT_THUMB_UP)) m_Controllers[0].m_state.Gamepad.sThumbRY = -32767;
		if (App::IsKeyPressed(APP_PAD_EMUL_RIGHT_THUMB_DOWN)) m_Controllers[0].m_state.Gamepad.sThumbRY = 32767;

		if (App::IsKeyPressed(APP_PAD_EMUL_DPAD_UP))   buttons |= XINPUT_GAMEPAD_DPAD_UP;
		if (App::IsKeyPressed(APP_PAD_EMUL_DPAD_DOWN)) buttons |= XINPUT_GAMEPAD_DPAD_DOWN;
		if (App::IsKeyPressed(APP_PAD_EMUL_DPAD_LEFT)) buttons |= XINPUT_GAMEPAD_DPAD_LEFT;
		if (App::IsKeyPressed(APP_PAD_EMUL_DPAD_RIGHT))buttons |= XINPUT_GAMEPAD_DPAD_RIGHT;

		if (App::IsKeyPressed(APP_PAD_EMUL_BUTTON_BACK)) buttons |= XINPUT_GAMEPAD_BACK;

		if (App::IsKeyPressed(APP_PAD_EMUL_BUTTON_A)) buttons |= XINPUT_GAMEPAD_A;
		if (App::IsKeyPressed(APP_PAD_EMUL_BUTTON_B)) buttons |= XINPUT_GAMEPAD_B;
		if (App::IsKeyPressed(APP_PAD_EMUL_BUTTON_X)) buttons |= XINPUT_GAMEPAD_X;
		if (App::IsKeyPressed(APP_PAD_EMUL_BUTTON_Y)) buttons |= XINPUT_GAMEPAD_Y;

		if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_TRIGGER)) m_Controllers[0].m_state.Gamepad.bLeftTrigger = 255;
		if (App::IsKeyPressed(APP_PAD_EMUL_RIGHT_TRIGGER)) m_Controllers[0].m_state.Gamepad.bRightTrigger = 255;

		if (App::IsKeyPressed(APP_PAD_EMUL_BUTTON_LEFT_THUMB)) buttons |= XINPUT_GAMEPAD_LEFT_THUMB;
		if (App::IsKeyPressed(APP_PAD_EMUL_BUTTON_RIGHT_THUMB)) buttons |= XINPUT_GAMEPAD_RIGHT_THUMB;
		if (App::IsKeyPressed(APP_PAD_EMUL_BUTTON_LEFT_SHOULDER)) buttons |= XINPUT_GAMEPAD_LEFT_SHOULDER;
		if (App::IsKeyPressed(APP_PAD_EMUL_BUTTON_RIGHT_SHOULDER)) buttons |= XINPUT_GAMEPAD_RIGHT_SHOULDER;

		m_Controllers[0].m_state.Gamepad.wButtons = buttons;
	}

	for (DWORD i = 0; i < MAX_CONTROLLERS; i++)
	{
		if (m_Controllers[i].m_bConnected)
		{
#ifdef UPDATE_DZONE					
			m_Controllers[i].m_debouncedButtons = ~m_Controllers[i].m_lastButtons &m_Controllers[i].m_state.Gamepad.wButtons;
			m_Controllers[i].m_lastButtons = m_Controllers[i].m_state.Gamepad.wButtons;

			// Zero value if thumbsticks are within the dead zone 
			if ((m_Controllers[i].m_state.Gamepad.sThumbLX < INPUT_DEADZONE &&
				m_Controllers[i].m_state.Gamepad.sThumbLX > -INPUT_DEADZONE) &&
				(m_Controllers[i].m_state.Gamepad.sThumbLY < INPUT_DEADZONE &&
					m_Controllers[i].m_state.Gamepad.sThumbLY > -INPUT_DEADZONE))
			{
				m_Controllers[i].m_state.Gamepad.sThumbLX = 0;
				m_Controllers[i].m_state.Gamepad.sThumbLY = 0;
			}

			if ((m_Controllers[i].m_state.Gamepad.sThumbRX < INPUT_DEADZONE &&
				m_Controllers[i].m_state.Gamepad.sThumbRX > -INPUT_DEADZONE) &&
				(m_Controllers[i].m_state.Gamepad.sThumbRY < INPUT_DEADZONE &&
					m_Controllers[i].m_state.Gamepad.sThumbRY > -INPUT_DEADZONE))
			{
				m_Controllers[i].m_state.Gamepad.sThumbRX = 0;
				m_Controllers[i].m_state.Gamepad.sThumbRY = 0;
			}
#endif		
		}
	}
}