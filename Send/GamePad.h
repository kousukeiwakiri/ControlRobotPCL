#pragma once

#include "mmsystem.h"

#pragma comment(lib, "winmm.lib")

class CGamePad
{
public:
	CGamePad(void);
	~CGamePad(void);

public:							//publicに変えてみた
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
