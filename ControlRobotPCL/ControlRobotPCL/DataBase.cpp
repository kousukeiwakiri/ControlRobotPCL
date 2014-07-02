#include "StdAfx.h"
#include "DataBase.h"


CDataBase::CDataBase(void)
{
}


CDataBase::~CDataBase(void)
{
}

void CDataBase::Insert(){

	//�f�[�^�x�[�X�̏����ݒ�
	CDatabase db;
	CString strCon = _T("Driver={SQL Server};SERVER=(local);DATABASE=PointCloudData;UID=sa;PWD=nabeficsnabe");
	db.OpenEx( strCon ,CDatabase::noOdbcDialog);
	

	//�ǂݍ��݃t�@�C���̏����ݒ�
	std::ifstream fin("./PCD/73pcd.pcd");
	float pcd_x,pcd_y,pcd_z,pcd_rgb;
	int x,y,z;
	uint8_t r, g, b;
	uint32_t rgb;
	time_t time1, time2;


	char str[64];
	char sqlc[150];
	CString sqlstr;
	unsigned long id_count = 0;

	//�ŏ���12�s�͔�΂�����
	for(int i=0;i<10;i++)
	{
		fin.getline(str,sizeof(str));
	}
	
	
	//�g�����U�N�V��������
	std::cout<<"�g�����U�N�V�����J�n�E�E�E"<<std::endl;
	time(&time1);
	db.BeginTrans(); //�g�����U�N�V�����J�n
	while(fin.getline(str,sizeof(str))){
		id_count++;
		fin >> pcd_x >> pcd_y >> pcd_z >> pcd_rgb;
		x = pcd_x;
		y = pcd_y;
		z = pcd_z;
		*reinterpret_cast<float*>(&rgb) = pcd_rgb;
		r = (rgb >> 16) & 0x0000ff;
		g = (rgb >> 8 ) & 0x0000ff;
		b = (rgb >> 0 ) & 0x0000ff;
		sprintf(sqlc,"INSERT INTO Table_1(ID,X,Y,Z,R,G,B) VALUES (%d,%d,%d,%d,%d,%d,%d)",id_count,x,y,z,r,g,b);
		sqlstr = sqlc;
		db.ExecuteSQL(sqlstr);    // �o�^
	}
	//db.ExecuteSQL(_T("DELETE FROM Table_test1"));    //�S�폜
	time(&time2);
	printf("�ۑ���:%d  ���ԁF%f[s]",id_count,difftime(time2,time1));
	db.CommitTrans();//�g�����U�N�V�����̊���
	std::cout<<"�g�����U�N�V�����̊���"<<std::endl;

	db.Close();

}
