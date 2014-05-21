#include "StdAfx.h"
#include "PointCloud.h"

CPointCloud::CPointCloud(void)
{
	//コンテキストの初期化
	context.InitFromXmlFile(CONFIG_XML_PATH);

	//各ジェネレータの作成
	context.FindExistingNode(XN_NODE_TYPE_IMAGE, imageGenerator);	// Imageジェネレータ
	context.FindExistingNode(XN_NODE_TYPE_DEPTH, depthGenerator);	// Depthジェネレータ

	//デプスの座標をイメージに合わせる
	depthGenerator.GetAlternativeViewPointCap().SetViewPoint(imageGenerator);

	//カメラサイズのイメージを作成(8ビットのRGB)
	imageGenerator.GetMapOutputMode(outputMode);
	camera=::cvCreateImage(cvSize(outputMode.nXRes,outputMode.nYRes),IPL_DEPTH_8U,3);
	image=::cvCreateImage(cvSize(outputMode.nXRes,outputMode.nYRes),IPL_DEPTH_8U,3);


	//PoiutCloudViewerの初期化
	viewer = new pcl::visualization::CloudViewer("Kinect Point Cloud");

	pcl_viewer_flag = false;
}


CPointCloud::~CPointCloud(void)
{
}

void CPointCloud::Run()
{
	//すべての更新を待ち、画像およびデプスデータを取得する
	context.WaitAndUpdateAll();
	//Metaデータの取得
	imageGenerator.GetMetaData(imageMD);
	depthGenerator.GetMetaData(depthMD);
	memcpy(camera->imageData , imageMD.RGB24Data(), camera->imageSize);

	cvCvtColor(camera,camera, CV_BGR2RGB);
	cvShowImage("image",camera);


	char key = cvWaitKey(10);
	if( key == 's' )
	{
		Save6D(0,0,0);
	}else if (key == 't')
	{
		//保存
		pcl::io::savePCDFileASCII("./PCD/pcd.pcd",*cloud);
	}
	if(pcl_viewer_flag == true){
		//ポイントクラウドを表示する
		viewer->showCloud(cloud);
	}
	
	return;
}

void CPointCloud::Save6D(int world_x,int world_y,double world_rad)
{
	//world_xはロボットの世界座標系での自己位置

	//PointCloud準備
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr points(new pcl::PointCloud<pcl::PointXYZRGB>);
	points->width = IMAGE_WIDTH;
	points->height = IMAGE_HEIGHT;

	//PointCloud
	for(int j=0 ; j<imageMD.YRes() ; j++)
	{
		for(int i=0; i<imageMD.XRes() ;i++)
		{
			if(depthMD(i,j)!=0)
			{
				double camera_x,camera_y,camera_z;
				pcl::PointXYZRGB point;
				camera_x =  PIXEL_RANGE * depthMD(i,j) * (i-(double)(imageMD.XRes())/2);
				camera_y =  PIXEL_RANGE * depthMD(i,j) * ((double)(imageMD.YRes())/2-j);
				camera_z =  depthMD(i,j) ;

				point.x = camera_x * cos(-world_rad) + camera_z * sin(-world_rad) + world_x;
				point.y = camera_y;
				point.z = -camera_x * sin(-world_rad) + camera_z * cos(-world_rad) + world_y;

				//テクスチャ
				point.b = camera->imageData[camera->widthStep*j+i*camera->nChannels];
				point.g = camera->imageData[camera->widthStep*j+i*camera->nChannels+1];
				point.r = camera->imageData[camera->widthStep*j+i*camera->nChannels+2];
		
				points->push_back(point);
			}
		}
	}
	if(pcl_viewer_flag == false){
		cloud = points;
		pcl_viewer_flag = true;
	}else{
		*cloud += *points;
	}
	
}