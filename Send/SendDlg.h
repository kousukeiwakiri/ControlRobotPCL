
// SendDlg.h : ヘッダー ファイル
//
#include "UDPSend.h"

#pragma once

#define UDP_SEND_ID 10
#define UDP_SEND_TIMER 20
// CSendDlg ダイアログ
class CSendDlg : public CDialogEx
{
// コンストラクション
public:
	CSendDlg(CWnd* pParent = NULL);	// 標準コンストラクター

// ダイアログ データ
	enum { IDD = IDD_SEND_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;
	CUDPSend udpSend;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	bool udp_send_flag;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
