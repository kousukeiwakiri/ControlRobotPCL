#pragma once
#include "Kinect.h"

class CShowWindow
{
private:
	IplImage *image;

public:
	CShowWindow(void);
	~CShowWindow(void);
	CKinect kinect_image;
	void Show();
};

