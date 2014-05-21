
// ControlRobotPCLDlg.h : �w�b�_�[ �t�@�C��
//

#pragma once

#define ROBOT_TIMER_ID 10
#define ROBOT_TIMER_MS 100
#define BRAIN_TIMER_ID 20
#define BRAIN_TIMER_MS 30

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

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
