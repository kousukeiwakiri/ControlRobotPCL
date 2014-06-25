#include "StdAfx.h"
#include "PointCloud.h"

CPointCloud::CPointCloud(void)
{
	//�R���e�L�X�g�̏�����
	context.InitFromXmlFile(CONFIG_XML_PATH);

	//�e�W�F�l���[�^�̍쐬
	context.FindExistingNode(XN_NODE_TYPE_IMAGE, imageGenerator);	// Image�W�F�l���[�^
	context.FindExistingNode(XN_NODE_TYPE_DEPTH, depthGenerator);	// Depth�W�F�l���[�^

	//�f�v�X�̍��W���C���[�W�ɍ��킹��
	depthGenerator.GetAlternativeViewPointCap().SetViewPoint(imageGenerator);

	//�J�����T�C�Y�̃C���[�W���쐬(8�r�b�g��RGB)
	imageGenerator.GetMapOutputMode(outputMode);
	camera=::cvCreateImage(cvSize(outputMode.nXRes,outputMode.nYRes),IPL_DEPTH_8U,3);
	image=::cvCreateImage(cvSize(outputMode.nXRes,outputMode.nYRes),IPL_DEPTH_8U,3);


	//PoiutCloudViewer�̏�����
	viewer = new pcl::visualization::CloudViewer("Kinect Point Cloud");

	pcl_viewer_flag = false;
}


CPointCloud::~CPointCloud(void)
{
}

void CPointCloud::Run()
{
	//���ׂĂ̍X�V��҂��A�摜����уf�v�X�f�[�^���擾����
	context.WaitAndUpdateAll();
	//Meta�f�[�^�̎擾
	imageGenerator.GetMetaData(imageMD);
	depthGenerator.GetMetaData(depthMD);
	memcpy(camera->imageData , imageMD.RGB24Data(), camera->imageSize);

	cvCvtColor(camera,camera, CV_BGR2RGB);
	cvShowImage("image",camera);

	
	char key = cvWaitKey(10);
	
	return;
}

void CPointCloud::WritePCD(void)
{
<<<<<<< HEAD
	std::cout<<"�ۑ����c�c�c�c�c�c�c�c�c"<<std::endl;
	pcl::io::savePCDFileASCII("./PCD/pcd.pcd",*cloud);
	std::cout<<"�ۑ�����!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
=======
	std::cout<<"�ۑ����c"<<std::endl;
	pcl::io::savePCDFileASCII("./PCD/pcd.pcd",*cloud);
	std::cout<<"�ۑ�����"<<std::endl;
>>>>>>> origin/master
}


void CPointCloud::Save6D(int r_world_x,int r_world_y,double r_world_rad)
{
	//world_x�̓��{�b�g�̐��E���W�n�ł̎��Ȉʒu

	//PointCloud����
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
				//camera_x�̓��{�b�g����̎��_�̋���
				camera_x =  PIXEL_RANGE * depthMD(i,j) * (i-(double)(imageMD.XRes())/2);
				camera_y =  PIXEL_RANGE * depthMD(i,j) * ((double)(imageMD.YRes())/2-j);
				camera_z =  depthMD(i,j);

				//world.x�͐��E���W�n
				double world_x = camera_x * cos(r_world_rad) - camera_z * sin(r_world_rad) + r_world_x;
				double world_y = camera_x * sin(r_world_rad) + camera_z * cos(-r_world_rad) + r_world_y;
				double world_z =  camera_y;

				//point.x
				point.x = world_x;
				point.y = world_z;
				point.z = - world_y;

				//�e�N�X�`��
				point.b = camera->imageData[camera->widthStep*j+i*camera->nChannels];
				point.g = camera->imageData[camera->widthStep*j+i*camera->nChannels+1];
				point.r = camera->imageData[camera->widthStep*j+i*camera->nChannels+2];
		
				points->push_back(point);
			}
		}
	}
	if(pcl_viewer_flag == false)
	{
		cloud = points;
		pcl_viewer_flag = true;
	}else{
		*cloud += *points;
	}
	viewer->showCloud(cloud);
}