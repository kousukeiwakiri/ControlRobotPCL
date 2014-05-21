
// ControlRobotPCLDlg.h : ヘッダー ファイル
//

#pragma once

#include "PointCloud.h"
#define ROBOT_TIMER_ID 10
#define ROBOT_TIMER_MS 100
#define KINECT_TIMER_ID 20
#define KINECT_TIMER_MS 30

// CControlRobotPCLDlg ダイアログ
class CControlRobotPCLDlg : public CDialogEx
{
// コンストラクション
public:
	CControlRobotPCLDlg(CWnd* pParent = NULL);	// 標準コンストラクター

// ダイアログ データ
	enum { IDD = IDD_CONTROLROBOTPCL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート

// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	
	//マルチスレッド用
	static UINT ThreadProcStub(LPVOID pParam);
	UINT TheadProc();
	CPointCloud pointCloud;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
