#include "StdAfx.h"
#include "GamePadData.h"



CGamePadData::CGamePadData(void)
{
	right = 0;
	left = 0 ;
	button = 0;
	center_num = CENTER_GAMEPAD_NUM;
}


CGamePadData::~CGamePadData(void)
{
}

void CGamePadData::Update(void)
{
	if(gamePad.IsAvailable())
	{
		gamePad.UpdateStatus();
		Direction();
	}else{
		right = 0;
		left = 0 ;
		button = 0;
	}
}


void CGamePadData::Direction(void)
{
	//button = gamePad.Buttons();

	switch(gamePad.Buttons())
	{
	case 0:
		button = 0;
		break;
	case 1:
		button = 1;
		break;
	case 2:
		button = 2;
		break;
	case 4:
		button = 3;
		break;
	case 8:
		button = 4;
		break;
	case 16:
		button = 5;
		break;
	case 32:
		button = 6;
		break;
	case 64:
		button = 7;
		break;
	case 128:
		button = 8;
		break;
	case 256:
		button = 9;
		break;
	case 512:
		button = 10;
		break;

	default:
		button = 0;
		break;
	}

	right=((double)(gamePad.R())-center_num)*-1;
	left=((double)(gamePad.Y())-center_num)*-1;

}

void CGamePadData::SetCenterNum(void)
{
	center_num = gamePad.R();
}