
// ControlRobotPCLDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "ControlRobotPCL.h"
#include "ControlRobotPCLDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// �A�v���P�[�V�����̃o�[�W�������Ɏg���� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �_�C�A���O �f�[�^
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	// ����
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


// CControlRobotPCLDlg �_�C�A���O




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


// CControlRobotPCLDlg ���b�Z�[�W �n���h���[

BOOL CControlRobotPCLDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "�o�[�W�������..." ���j���[���V�X�e�� ���j���[�ɒǉ����܂��B

	// IDM_ABOUTBOX �́A�V�X�e�� �R�}���h�͈͓̔��ɂȂ���΂Ȃ�܂���B
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

	// ���̃_�C�A���O�̃A�C�R����ݒ肵�܂��B�A�v���P�[�V�����̃��C�� �E�B���h�E���_�C�A���O�łȂ��ꍇ�A
	//  Framework �́A���̐ݒ�������I�ɍs���܂��B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R���̐ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R���̐ݒ�

	// TODO: �������������ɒǉ����܂��B
	AfxBeginThread(ThreadProcStub,(LPVOID)this,THREAD_PRIORITY_IDLE);
	SetTimer(ROBOT_TIMER_ID,ROBOT_TIMER_MS,NULL);
	SetTimer(POINT_SAVE_ID,POINT_SAVE_MS,NULL);
	AllocConsole();					//�R���\�[���E�B���h�E�o�͐ݒ�
	freopen("con","w", stdout);
	robot_param.X = 0.0;
	robot_param.Y = 0.0;
	robot_param.Th = 0.0;
	return TRUE;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
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

// �_�C�A���O�ɍŏ����{�^����ǉ�����ꍇ�A�A�C�R����`�悷�邽�߂�
//  ���̃R�[�h���K�v�ł��B�h�L�������g/�r���[ ���f�����g�� MFC �A�v���P�[�V�����̏ꍇ�A
//  ����́AFramework �ɂ���Ď����I�ɐݒ肳��܂��B

void CControlRobotPCLDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N���C�A���g�̎l�p�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R���̕`��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ���[�U�[���ŏ��������E�B���h�E���h���b�O���Ă���Ƃ��ɕ\������J�[�\�����擾���邽�߂ɁA
//  �V�X�e�������̊֐����Ăяo���܂��B
HCURSOR CControlRobotPCLDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//�^�C�}�[
void CControlRobotPCLDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch(nIDEvent)
	{
	case ROBOT_TIMER_ID:

		break;
	case POINT_SAVE_ID:
		//�`��C�[�x���̍X�V
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


//���{�b�g�̏��
void CControlRobotPCLDlg::RobotState(int state_id)
{

	std::cout<<"�{�^��:"<<gamePadData.button;
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
		//�R���g���[���̌Ăяo��
		gamePadData.Update();
		//���{�b�g�̏�Ԍ���
		//RobotState(gamePadData.button);
		if(robot.connect_flag == true)
		{
			if(gamePadData.left > 0 && gamePadData.right > 0)robot.Move();
			else if(gamePadData.left > 0 && gamePadData.right < 0) robot.RightRoll();
			else if(gamePadData.left < 0 && gamePadData.right > 0) robot.LeftRoll();
			else if(gamePadData.left < 0 && gamePadData.right < 0) robot.Back();
			else robot.Stop();
			robot_param = robot.GetRobotPatam(); //���{�b�g�̌��݈ʒu�̍X�V
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
			cout<<"���{�b�g�������Ă��܂�"<<endl;
	}
}
