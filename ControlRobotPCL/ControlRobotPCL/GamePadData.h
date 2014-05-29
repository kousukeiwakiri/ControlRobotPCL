#pragma once

#include "GamePad.h"

#define CENTER_GAMEPAD_NUM 32767

class CGamePadData
{
public:
	CGamePadData(void);
	~CGamePadData(void);
	void Update();
	int button;
	double left;			//左スティック
	double right;			//右スティック
private:

	CGamePad gamePad;
	void Direction();

};

