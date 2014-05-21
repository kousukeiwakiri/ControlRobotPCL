
// SendDlg.h : �w�b�_�[ �t�@�C��
//
#include "UDPSend.h"

#pragma once

#define UDP_SEND_ID 10
#define UDP_SEND_TIMER 20
// CSendDlg �_�C�A���O
class CSendDlg : public CDialogEx
{
// �R���X�g���N�V����
public:
	CSendDlg(CWnd* pParent = NULL);	// �W���R���X�g���N�^�[

// �_�C�A���O �f�[�^
	enum { IDD = IDD_SEND_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �T�|�[�g


// ����
protected:
	HICON m_hIcon;
	CUDPSend udpSend;

	// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
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
