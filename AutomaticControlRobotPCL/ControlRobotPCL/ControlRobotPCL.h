
// ControlRobotPCL.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CControlRobotPCLApp:
// このクラスの実装については、ControlRobotPCL.cpp を参照してください。
//

class CControlRobotPCLApp : public CWinApp
{
public:
	CControlRobotPCLApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CControlRobotPCLApp theApp;