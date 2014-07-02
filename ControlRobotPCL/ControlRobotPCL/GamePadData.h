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
	double left;			//���X�e�B�b�N
	double right;			//�E�X�e�B�b�N
private:

	CGamePad gamePad;
	void Direction();

};

