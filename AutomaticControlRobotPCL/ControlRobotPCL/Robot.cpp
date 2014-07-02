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

void CRobot::Move(void){
	myRobot->setVel2(200,200);
}

void CRobot::Back(void){
	myRobot->setVel2(-200,-200);
}

void CRobot::RightRoll(void){
	myRobot->setVel2(100,-100);
}

void CRobot::LeftRoll(void){
	myRobot->setVel2(-100,100);
}

void CRobot::Stop(void){
	myRobot->setVel2(0,0);
}

RobotParam CRobot::GetRobotPatam(void)
{
	RobotParam robot_param;
	robot_param.Y = -1 * myRobot->getY();
	robot_param.X = myRobot->getX();
	robot_param.Th = myRobot->getTh();
	return robot_param;
}