
// RobotControl.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CRobotControlApp:
// このクラスの実装については、RobotControl.cpp を参照してください。
//

class CRobotControlApp : public CWinApp
{
public:
	CRobotControlApp();

	// グローバルで扱いたいもの
	int h_count;					//ヘルシーカウンタ
	int gamepad_right;	//0～100
	int gamepad_left;	//0～100
	int gamepad_button;
// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CRobotControlApp theApp;