#pragma once

#include<iostream>
#include<stdexcept>
#include<opencv/cv.h>
#include<opencv/highgui.h>
#include<XnCppWrapper.h>

class CKinect
{
private:
	XnStatus rc;
	xn::Context context;
	xn::ImageGenerator image;
	XnMapOutputMode outputMode;


	xn::ImageMetaData imageMD;
public:
	CKinect(void);
	~CKinect(void);
	void init();
	IplImage *CameraImage();
	IplImage *camera;
};

