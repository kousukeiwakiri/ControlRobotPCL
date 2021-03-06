
// ControlRobotPCLDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ControlRobotPCL.h"
#include "ControlRobotPCLDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// ダイアログ データ
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CControlRobotPCLDlg ダイアログ




CControlRobotPCLDlg::CControlRobotPCLDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CControlRobotPCLDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CControlRobotPCLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CControlRobotPCLDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CControlRobotPCLDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CControlRobotPCLDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CControlRobotPCLDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CControlRobotPCLDlg メッセージ ハンドラー

BOOL CControlRobotPCLDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。
	AfxBeginThread(ThreadProcStub,(LPVOID)this,THREAD_PRIORITY_IDLE);
	SetTimer(ROBOT_TIMER_ID,ROBOT_TIMER_MS,NULL);
	SetTimer(POINT_SAVE_ID,POINT_SAVE_MS,NULL);
	AllocConsole();					//コンソールウィンドウ出力設定
	freopen("con","w", stdout);
	robot_param.X = 0.0;
	robot_param.Y = 0.0;
	robot_param.Th = 0.0;
	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CControlRobotPCLDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CControlRobotPCLDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CControlRobotPCLDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//タイマー
void CControlRobotPCLDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch(nIDEvent)
	{
	case ROBOT_TIMER_ID:

		break;
	case POINT_SAVE_ID:
		//描画，深度情報の更新
		pointCloud.Run();
		if(robot.connect_flag == true){
			pointCloud.Save6D(robot_param.Y, robot_param.X , robot_param.Th * 3.1415 / 180.0);
		}
		break;
	default:
		break;
	}


	CDialogEx::OnTimer(nIDEvent);
}


//ロボットの状態
void CControlRobotPCLDlg::RobotState(int state_id)
{

	std::cout<<"ボタン:"<<gamePadData.button;
	std::cout<<" ,right:" << gamePadData.right;
	std::cout<<" ,left:" << gamePadData.left <<std::endl;
	switch(state_id){
	case 0:
		break;
	case 1:
		if(robot.connect_flag == false)
		{
			pointCloud.WritePCD();
		}
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		//dataBase.Insert();
		break;
	case 9:
		break;
	case 10:

		if(robot.connect_flag == false)
		{
			gamePadData.SetCenterNum();
			robot.Init();
		}else
		{
			robot.Close();
		}

		break;
	default:
		break;
	}


}

//malti thread
UINT CControlRobotPCLDlg::ThreadProcStub(LPVOID pParam)
{
	CControlRobotPCLDlg* pDlg = (CControlRobotPCLDlg*) pParam;
	if(pDlg==NULL){
		return 0;
	}
	return pDlg->TheadProc();
}

UINT CControlRobotPCLDlg::TheadProc(){
	while(1){
		//コントローラの呼び出し
		gamePadData.Update();
		//ロボットの状態決定
		//RobotState(gamePadData.button);
		if(robot.connect_flag == true)
		{
			if(gamePadData.left > 0 && gamePadData.right > 0)robot.Move();
			else if(gamePadData.left > 0 && gamePadData.right < 0) robot.RightRoll();
			else if(gamePadData.left < 0 && gamePadData.right > 0) robot.LeftRoll();
			else if(gamePadData.left < 0 && gamePadData.right < 0) robot.Back();
			else robot.Stop();
			robot_param = robot.GetRobotPatam(); //ロボットの現在位置の更新
		}
		Sleep(150);
	}
	return 0;
}



void CControlRobotPCLDlg::OnBnClickedButton1()
{
	gamePadData.SetCenterNum();
	robot.Init();

}


void CControlRobotPCLDlg::OnBnClickedButton2()
{
	robot.Close();
}


void CControlRobotPCLDlg::OnBnClickedButton3()
{
	if(robot.connect_flag == false)
		{
			pointCloud.WritePCD();
		}else{
			cout<<"ロボットが動いています"<<endl;
	}
}
