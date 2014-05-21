#include "StdAfx.h"
#include "GamePadData.h"



CGamePadData::CGamePadData(void)
{
	
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
		right=CENTER_GAMEPAD_UDP_NUM;
		left=CENTER_GAMEPAD_UDP_NUM;
		button=0;
	}
}

void CGamePadData::Direction(void)
{
	right=((double)(gamePad.R())-CENTER_GAMEPAD_NUM)/-CENTER_GAMEPAD_NUM;
	left=((double)(gamePad.Y())-CENTER_GAMEPAD_NUM)/-CENTER_GAMEPAD_NUM;
	button=gamePad.Buttons();

	//send—p•ÏŠ· 0~100
	right=(right+1)*CENTER_GAMEPAD_UDP_NUM;
	left =(left+1)*CENTER_GAMEPAD_UDP_NUM;
}
