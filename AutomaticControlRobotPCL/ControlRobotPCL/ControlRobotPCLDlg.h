
// ControlRobotPCLDlg.h : �w�b�_�[ �t�@�C��
//

#pragma once

#include "PointCloud.h"
#include "GamePadData.h"
#include "Robot.h"
#include "DataBase.h"

#define ROBOT_TIMER_ID 10
#define ROBOT_TIMER_MS 100
#define POINT_SAVE_ID 20
#define POINT_SAVE_MS 2000


// CControlRobotPCLDlg �_�C�A���O
class CControlRobotPCLDlg : public CDialogEx
{
// �R���X�g���N�V����
public:
	CControlRobotPCLDlg(CWnd* pParent = NULL);	// �W���R���X�g���N�^�[

// �_�C�A���O �f�[�^
	enum { IDD = IDD_CONTROLROBOTPCL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �T�|�[�g

// ����
protected:
	HICON m_hIcon;

	// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	
	//�}���`�X���b�h�p
	static UINT ThreadProcStub(LPVOID pParam);
	UINT TheadProc();
	CPointCloud pointCloud;

	//���{�b�g�̏�ԗp
	void RobotState(int state_id);
	CGamePadData gamePadData;

	CRobot robot;
	CDataBase dataBase;

	RobotParam robot_param;

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
