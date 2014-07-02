#include "StdAfx.h"
#include "GamePad.h"


CGamePad::CGamePad(void)
{
}


CGamePad::~CGamePad(void)
{
}

void CGamePad::UpdateStatus()
{
	 joyGetPosEx(JOYSTICKID1,&info);
}

BOOL CGamePad::IsAvailable()
{
    if (joyGetDevCaps(JOYSTICKID1, &caps, sizeof(JOYCAPS)) == JOYERR_NOERROR)
    {
        return true;
    }
    else
    {
        return false;
    }
}

UINT CGamePad::Buttons()
{
	return info.dwButtons;
}

UINT CGamePad::X()
{
	return info.dwXpos;
}

UINT CGamePad::Y()
{
	return info.dwYpos;
}

UINT CGamePad::Z()
{
	return info.dwZpos;
}

UINT CGamePad::R()
{
	return info.dwRpos;
}

UINT CGamePad::U()
{
	return info.dwUpos;
}

UINT CGamePad::V()
{
	return info.dwVpos;
}
