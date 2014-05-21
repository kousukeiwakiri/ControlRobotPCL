
// RobotControlDlg.h : �w�b�_�[ �t�@�C��
//
#include "UdpRecv.h"
#include "RobotMove.h"
#include "ShowWindow.h"

#pragma once

#define ROBOT_TIMER_ID 10
#define ROBOT_TIMER_MS 100
#define KINECT_TIMER_ID 20
#define KINECT_TIMER_MS 33


// CRobotControlDlg �_�C�A���O
class CRobotControlDlg : public CDialogEx
{
	// �R���X�g���N�V����
public:
	CRobotControlDlg(CWnd* pParent = NULL);	// �W���R���X�g���N�^�[

	// �_�C�A���O �f�[�^
	enum { IDD = IDD_ROBOTCONTROL_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �T�|�[�g

	//�}���`�X���b�h�p
	static UINT ThreadProcStub(LPVOID pParam);
	UINT TheadProc();



	// ����
protected:
	HICON m_hIcon;

	// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CUdpRecv udpRecv;
	CRobotMove robotMove;
	CRobotMove::RobotControlFlag robotControlFlag;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnDestroy();
	int old_h_count;
	CShowWindow show_window;
	int com_error_detect;
	bool global_error_flag;
};
