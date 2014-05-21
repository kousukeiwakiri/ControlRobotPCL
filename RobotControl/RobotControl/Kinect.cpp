#include "StdAfx.h"
#include "Kinect.h"


CKinect::CKinect(void)
{
}


CKinect::~CKinect(void)
{
}

void CKinect::init(void)
{
	try{
		const char *CONFIG_XML_PATH="config.xml";
		//コンテキストの初期化
		rc=context.InitFromXmlFile(CONFIG_XML_PATH);
		if(rc!=XN_STATUS_OK){
			throw std::runtime_error(xnGetStatusString(rc));
		}

		//イメージジェネレータの生成
		rc= context.FindExistingNode(XN_NODE_TYPE_IMAGE,image);
		if(rc!=XN_STATUS_OK){
			throw std::runtime_error(xnGetStatusString(rc));
		}

		//カメラサイズのイメージを作成(8ビットのRGB)
		image.GetMapOutputMode(outputMode);
		camera=::cvCreateImage(cvSize(outputMode.nXRes,outputMode.nYRes),IPL_DEPTH_8U,3);
		if(!camera){
			throw std::runtime_error("error:cvCreateImage");
		}
	}catch(std::exception&){}
}

IplImage *CKinect::CameraImage(void){
	context.WaitOneUpdateAll(image);
	image.GetMetaData(imageMD);

	memcpy(camera->imageData,imageMD.RGB24Data(),camera->imageSize);

	return camera;
	
}

