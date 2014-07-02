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
	bool connect_flag;	//�ڑ�����Ă��邩
	void Init();
	void Close();	//�I��
	void Move();
	void Back();
	void RightRoll();
	void LeftRoll();
	void Stop();
	//���{�b�g
	ArRobot *myRobot;
	ArSerialConnection *myConnection;
	ArSick *mySonar;

	RobotParam GetRobotPatam(void);
	
};

