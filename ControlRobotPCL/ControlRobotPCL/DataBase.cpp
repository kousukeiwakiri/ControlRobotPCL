#include "StdAfx.h"
#include "DataBase.h"


CDataBase::CDataBase(void)
{
}


CDataBase::~CDataBase(void)
{
}

void CDataBase::Insert(){

	//データベースの初期設定
	CDatabase db;
	CString strCon = _T("Driver={SQL Server};SERVER=(local);DATABASE=TestDB;UID=sa;PWD=k1952620");
	db.OpenEx( strCon ,CDatabase::noOdbcDialog);
	

	//読み込みファイルの初期設定
	std::ifstream fin("./PCD/pcd.pcd");
	float pcd_x,pcd_y,pcd_z,pcd_rgb;
	int x,y,z;
	uint8_t r, g, b;
	uint32_t rgb;
	time_t time1, time2;


	char str[64];
	char sqlc[150];
	CString sqlstr;
	unsigned long id_count = 0;

	//最初の12行は飛ばしたい
	for(int i=0;i<10;i++)
	{
		fin.getline(str,sizeof(str));
	}
	
	
	//トランザクション処理
	std::cout<<"トランザクション開始・・・"<<std::endl;
	time(&time1);
	db.BeginTrans(); //トランザクション開始
	while(fin.getline(str,sizeof(str))){
		id_count++;
		fin >> pcd_x >> pcd_y >> pcd_z >> pcd_rgb;
		x = pcd_x;
		y = pcd_y + 1100;
		z = pcd_z;
		*reinterpret_cast<float*>(&rgb) = pcd_rgb;
		r = (rgb >> 16) & 0x0000ff;
		g = (rgb >> 8 ) & 0x0000ff;
		b = (rgb >> 0 ) & 0x0000ff;
		sprintf(sqlc,"INSERT INTO Table_test1(ID,X,Y,Z,R,G,B) VALUES (%d,%d,%d,%d,%d,%d,%d)",id_count,x,y,z,r,g,b);
		sqlstr = sqlc;
		db.ExecuteSQL(sqlstr);    // 登録
	}
	//db.ExecuteSQL(_T("DELETE FROM Table_test1"));    //全削除
	time(&time2);
	printf("保存回数:%d  時間：%f[s]",id_count,difftime(time2,time1));
	db.CommitTrans();//トランザクションの完了
	std::cout<<"トランザクションの完了"<<std::endl;

	db.Close();

}
