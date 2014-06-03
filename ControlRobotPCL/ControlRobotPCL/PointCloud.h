#pragma once

#include <iostream>
#include<stdexcept>
#include<opencv/cv.h>
#include<opencv/highgui.h>
#include<XnCppWrapper.h>
#include <pcl\point_types.h>
#include <pcl\visualization\cloud_viewer.h>
#include <pcl/io/pcd_io.h>

#define CONFIG_XML_PATH "./config.xml" //�ݒ�PATH

#define PIXEL_RANGE 0.001736 //1pixel�ӂ�̋���
#define IMAGE_WIDTH 640
#define IMAGE_HEIGHT 480

class CPointCloud
{
public:
	CPointCloud(void);
	~CPointCloud(void);
	void Run(void);
	void Save6D(int world_x,int world_y,double world_rad); //pointcloud�̕ۑ�
	void WritePCD(void);


private:
	xn::Context context;
	
	//���^�f�[�^
	xn::ImageMetaData imageMD;
	xn::DepthMetaData depthMD;
	IplImage *image;

	//�W�F�l���[�^
	xn::ImageGenerator imageGenerator;
	xn::DepthGenerator depthGenerator;

	XnMapOutputMode outputMode;
	IplImage *camera;

	pcl::visualization::CloudViewer *viewer;
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud;
	
	bool pcl_viewer_flag; //cloud����̂Ƃ��G���[�ɂȂ�Ȃ��悤��

};

