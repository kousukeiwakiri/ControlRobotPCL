#pragma once

#include "Aria.h"
#include "UdpRecv.h"

#ifdef _DEBUG
#pragma comment(lib,"AriaDebugVC10.lib")
#else
#pragma comment(lib,"AriaVC10.lib")
#endif
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"advapi32.lib")

#define ROBOT_MAX_SPEED 50 //[mm/s]
#define CENTER_GAMEPAD_NUM 50




class CRobotMove
{
public:
	CRobotMove(void);
	~CRobotMove(void);
	enum RobotControlFlag{
		AUTOMATIC,
		MANUAL,
		STOP,
	};
	bool connect_flag;

	//control type
	void Manual();
	void Automatic();
	void Stop();



	//ÉçÉ{ÉbÉg
	ArRobot *myRobot;
	ArSerialConnection *myConnection;
	ArSick *mySonar;
};