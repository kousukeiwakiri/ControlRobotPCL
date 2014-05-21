
// RobotControlDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "RobotControl.h"
#include "RobotControlDlg.h"
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


// CRobotControlDlg ダイアログ




CRobotControlDlg::CRobotControlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRobotControlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRobotControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRobotControlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CRobotControlDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CRobotControlDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CRobotControlDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CRobotControlDlg::OnBnClickedButton4)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CRobotControlDlg メッセージ ハンドラー

BOOL CRobotControlDlg::OnInitDialog()
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
	robotControlFlag=CRobotMove::STOP;
	robotMove.connect_flag=false;
	SetTimer(ROBOT_TIMER_ID,ROBOT_TIMER_MS,NULL);
	SetTimer(KINECT_TIMER_ID,KINECT_TIMER_MS,NULL);
	old_h_count=0;
	com_error_detect=0;
	show_window.kinect_image.init();
	global_error_flag=false;

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CRobotControlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRobotControlDlg::OnPaint()
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
HCURSOR CRobotControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//malti thread
UINT CRobotControlDlg::ThreadProcStub(LPVOID pParam)
{
	CRobotControlDlg* pDlg = (CRobotControlDlg*) pParam;
	if(pDlg==NULL){
		return 0;
	}
	return pDlg->TheadProc();
}

UINT CRobotControlDlg::TheadProc(){
	while(1){
		if(robotControlFlag==CRobotMove::MANUAL)udpRecv.Recv();
	}
	return 0;
}



//Timer
void CRobotControlDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch(nIDEvent)
	{
	case ROBOT_TIMER_ID:
		if(robotMove.connect_flag==true){

			if(robotControlFlag==CRobotMove::STOP || global_error_flag==true)robotMove.Stop();
			else if(robotControlFlag==CRobotMove::MANUAL){
				if(udpRecv.udp_error_flag==true || com_error_detect>5){
					robotMove.Stop();					//5回連続通信がない場合はストップ
					global_error_flag=true;
				}
				if(old_h_count==theApp.h_count){
					com_error_detect++;
				}
				else{
					com_error_detect=0;
				}
				
				old_h_count=theApp.h_count;
				robotMove.Manual();
			}else if(robotControlFlag==CRobotMove::AUTOMATIC){
				robotMove.Automatic();
			}
		}
		break;
	case KINECT_TIMER_ID:
		show_window.Show();
		break;
	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}


//Manual Robot Control
void CRobotControlDlg::OnBnClickedButton1()
{
	robotControlFlag=CRobotMove::MANUAL;
}


//Automatic Robot Control
void CRobotControlDlg::OnBnClickedButton2()
{
	robotControlFlag=CRobotMove::AUTOMATIC;
}

//connect
void CRobotControlDlg::OnBnClickedButton3()
{
	//robot init
	robotMove.myRobot = new ArRobot();
	robotMove.myConnection = new ArSerialConnection();
	robotMove.mySonar = new ArSick();

	robotMove.myConnection->open();
	robotMove.myRobot->setDeviceConnection(robotMove.myConnection);
	robotMove.myRobot->addRangeDevice(robotMove.mySonar);

	if (robotMove.myRobot->blockingConnect()) {
		robotMove.myRobot->enableMotors();
		robotMove.myRobot->runAsync(false);
	}
	robotMove.connect_flag=true;
}


//disconnect
void CRobotControlDlg::OnBnClickedButton4()
{
	robotMove.myRobot->disconnect();
	robotMove.myConnection->close();
}


void CRobotControlDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	robotMove.myRobot->disconnect();
	robotMove.myConnection->close();
}
