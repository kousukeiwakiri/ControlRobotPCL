#include "StdAfx.h"
#include "Robot.h"


CRobot::CRobot(void)
{
	connect_flag=false;
}


CRobot::~CRobot(void)
{
}


//robot init
void CRobot::Init(void){
	if(connect_flag == false){
		myRobot = new ArRobot();
		myConnection = new ArSerialConnection();
		mySonar = new ArSick();

		myConnection->open();
		myRobot->setDeviceConnection(myConnection);
		myRobot->addRangeDevice(mySonar);

		if (myRobot->blockingConnect()) {
			myRobot->enableMotors();
			myRobot->runAsync(false);
		}
	}
	connect_flag=true;


}

//I—¹
void CRobot::Close(void){
	if(connect_flag == true){
		myRobot->disconnect();
		myConnection->close();
	}
	connect_flag=false;
}