#ifndef _SIMPLECONTROLLER_H
#define _SIMPLECONTROLLER_H

#if (_WIN32_WINNT >= 0x0604 /*_WIN32_WINNT_WIN8*/)
#include <XInput.h>
#pragma comment(lib,"xinput.lib")
#else
#include <XInput.h>
#pragma comment(lib,"xinput9_1_0.lib")
#endif

#define MAX_CONTROLLERS 4  // XInput handles up to 4 controllers 

class CController
{
public:
	friend class CSimpleControllers;
	CController() : m_lastButtons(0), m_debouncedButtons(0), m_bConnected(false)
	{
		ZeroMemory(&m_state, sizeof(XINPUT_STATE));
	}	

	bool CheckButton(int button, bool onPress = true ) const
	{
		if (onPress)
		{
			return (m_debouncedButtons & button) != 0;
		}
		else
		{
			return (m_lastButtons & button) != 0;
		}
	}

	float GetLeftThumbStickX() const
	{
		return (float)m_state.Gamepad.sThumbLX / 32768.0f;
	}
	float GetLeftThumbStickY(int pad = 0) const
	{
		return m_state.Gamepad.sThumbLY / 32768.0f;
	}
	float GetRightThumbStickX(int pad = 0) const
	{
		return (float)m_state.Gamepad.sThumbRX / 32768.0f;
	}
	float GetRightThumbStickY(int pad = 0) const
	{
		return m_state.Gamepad.sThumbRY / 32768.0f;
	}
	float GetLeftTrigger(int pad = 0) const
	{
		return (float)m_state.Gamepad.bLeftTrigger / 255.0f;
	}
	float GetRightTrigger(int pad = 0) const
	{
		return m_state.Gamepad.bRightTrigger / 255.0f;
	}
protected:
	XINPUT_STATE m_state;
	WORD m_lastButtons;
	WORD m_debouncedButtons;
	bool m_bConnected;
};

class CSimpleControllers
{
public:
	static CSimpleControllers &GetInstance();
	void Update();
	const CController &GetController(int pad = 0)
	{
		if (pad >= MAX_CONTROLLERS) pad = 0;
		return m_Controllers[pad];
	}
private:
	CController m_Controllers[MAX_CONTROLLERS];
};
#endif