#include "StdAfx.h"
#include "ShowWindow.h"


CShowWindow::CShowWindow(void)
{
}


CShowWindow::~CShowWindow(void)
{
}

void CShowWindow::Show(void)
{
		image = kinect_image.CameraImage();
		::cvCvtColor(image,image,CV_BGR2RGB);
		::cvShowImage("KinectImage",image);
	
}