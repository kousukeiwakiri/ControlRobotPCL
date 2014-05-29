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
private:
	double left;			//���X�e�B�b�N
	double right;			//�E�X�e�B�b�N

	CGamePad gamePad;
	void Direction();

};
