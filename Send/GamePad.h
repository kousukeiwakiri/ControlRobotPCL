#pragma once

#include "mmsystem.h"

#pragma comment(lib, "winmm.lib")

class CGamePad
{
public:
	CGamePad(void);
	~CGamePad(void);

public:							//public‚É•Ï‚¦‚Ä‚Ý‚½
	JOYINFOEX info;
	JOYCAPS caps;

	void UpdateStatus();
	BOOL IsAvailable();

	UINT Buttons();
	UINT X();
	UINT Y();
	UINT Z();
	UINT R();
	UINT U();
	UINT V();
};
