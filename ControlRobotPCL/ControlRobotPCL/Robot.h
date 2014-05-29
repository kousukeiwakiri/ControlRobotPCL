#pragma once

#include "Aria.h"
#ifdef _DEBUG
#pragma comment(lib,"AriaDebugVC10.lib")
#else
#pragma comment(lib,"AriaVC10.lib")
#endif

class CRobot
{
public:
	CRobot(void);
	~CRobot(void);
	bool connect_flag;	//接続されているか
	void Init();
	void Close();	//終了

	//ロボット
	ArRobot *myRobot;
	ArSerialConnection *myConnection;
	ArSick *mySonar;
};

