#pragma once

#include "Aria.h"
#ifdef _DEBUG
#pragma comment(lib,"AriaDebugVC10.lib")
#else
#pragma comment(lib,"AriaVC10.lib")
#endif

struct RobotParam{
	double X;
	double Y;
	double Th;
};


class CRobot
{
public:
	CRobot(void);
	~CRobot(void);
	bool connect_flag;	//接続されているか
	void Init();
	void Close();	//終了
	void Move();
	void Back();
	void RightRoll();
	void LeftRoll();
	void Stop();
	//ロボット
	ArRobot *myRobot;
	ArSerialConnection *myConnection;
	ArSick *mySonar;

	RobotParam GetRobotPatam(void);
	
};

