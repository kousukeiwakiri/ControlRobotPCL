
// RobotControlDlg.h : ヘッダー ファイル
//
#include "UdpRecv.h"
#include "RobotMove.h"
#include "ShowWindow.h"

#pragma once

#define ROBOT_TIMER_ID 10
#define ROBOT_TIMER_MS 100
#define KINECT_TIMER_ID 20
#define KINECT_TIMER_MS 33


// CRobotControlDlg ダイアログ
class CRobotControlDlg : public CDialogEx
{
	// コンストラクション
public:
	CRobotControlDlg(CWnd* pParent = NULL);	// 標準コンストラクター

	// ダイアログ データ
	enum { IDD = IDD_ROBOTCONTROL_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート

	//マルチスレッド用
	static UINT ThreadProcStub(LPVOID pParam);
	UINT TheadProc();



	// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
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
