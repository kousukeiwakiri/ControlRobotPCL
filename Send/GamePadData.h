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
	double left;			//���X�e�B�b�N
	double right;			//�E�X�e�B�b�N
	int button;

private:
	CGamePad gamePad;
	void Direction();

};

