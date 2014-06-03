#pragma once

#include <iostream>
#include<stdexcept>
#include<opencv/cv.h>
#include<opencv/highgui.h>
#include<XnCppWrapper.h>
#include <pcl\point_types.h>
#include <pcl\visualization\cloud_viewer.h>
#include <pcl/io/pcd_io.h>

#define CONFIG_XML_PATH "./config.xml" //設定PATH

#define PIXEL_RANGE 0.001736 //1pixel辺りの距離
#define IMAGE_WIDTH 640
#define IMAGE_HEIGHT 480

class CPointCloud
{
public:
	CPointCloud(void);
	~CPointCloud(void);
	void Run(void);
	void Save6D(int world_x,int world_y,double world_rad); //pointcloudの保存
	void WritePCD(void);


private:
	xn::Context context;
	
	//メタデータ
	xn::ImageMetaData imageMD;
	xn::DepthMetaData depthMD;
	IplImage *image;

	//ジェネレータ
	xn::ImageGenerator imageGenerator;
	xn::DepthGenerator depthGenerator;

	XnMapOutputMode outputMode;
	IplImage *camera;

	pcl::visualization::CloudViewer *viewer;
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud;
	
	bool pcl_viewer_flag; //cloudが空のときエラーにならないように

};

