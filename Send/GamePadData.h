#pragma once

#include "GamePad.h"

#define CENTER_GAMEPAD_UDP_NUM 50
#define CENTER_GAMEPAD_NUM 32767

class CGamePadData
{
public:
	CGamePadData(void);
	~CGamePadData(void);
	void Update();
	double left;			//左スティック
	double right;			//右スティック
	int button;

private:
	CGamePad gamePad;
	void Direction();

};

