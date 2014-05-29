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
	bool connect_flag;	//�ڑ�����Ă��邩
	void Init();
	void Close();	//�I��

	//���{�b�g
	ArRobot *myRobot;
	ArSerialConnection *myConnection;
	ArSick *mySonar;
};

