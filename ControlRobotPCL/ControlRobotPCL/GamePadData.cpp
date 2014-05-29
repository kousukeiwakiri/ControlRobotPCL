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
		right = 0;
		left = 0 ;
		int button = 0;
	}
}


void CGamePadData::Direction(void)
{
	button = gamePad.Buttons();
	right=((double)(gamePad.R())-CENTER_GAMEPAD_NUM)/-CENTER_GAMEPAD_NUM;
	left=((double)(gamePad.Y())-CENTER_GAMEPAD_NUM)/-CENTER_GAMEPAD_NUM;

}
