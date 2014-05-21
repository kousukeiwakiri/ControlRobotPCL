#include "StdAfx.h"
#include "RobotMove.h"



CRobotMove::CRobotMove(void)
{
}


CRobotMove::~CRobotMove(void)
{
}

void CRobotMove::Manual(void)
{
	myRobot->setVel2((theApp.gamepad_left-CENTER_GAMEPAD_NUM)*ROBOT_MAX_SPEED/CENTER_GAMEPAD_NUM,(theApp.gamepad_right-CENTER_GAMEPAD_NUM)*ROBOT_MAX_SPEED/CENTER_GAMEPAD_NUM);
}

void CRobotMove::Automatic(void)
{
	;
}

void CRobotMove::Stop(void)
{
	myRobot->stop();
}