#include "afxwin.h"
#if !defined(AFX_FOLDER_H__08EFA55A_7FC1_4B30_8B0F_7987E91B5FB7__INCLUDED_)
#define AFX_FOLDER_H__08EFA55A_7FC1_4B30_8B0F_7987E91B5FB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Folder.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CFolder ダイアログ

class CFolder : public CDialog
{
// コンストラクション
public:
	CFolder(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CFolder)
	enum { IDD = IDD_DIALOG1 };
	CEdit	m_8s;
	CEdit	m_7s;
	CEdit	m_6s;
	CButton	m_5;
	CEdit	m_5s;
	CEdit	m_4s;
	CEdit	m_3s;
	CEdit	m_2s;
	CEdit	m_1s;
	CButton	m_4;
	CButton	m_3;
	CButton	m_2;
	CButton	m_1;
	//}}AFX_DATA

	UINT GetOpenFolderName(HWND hWnd
                                    , LPCTSTR lpszDefaultFolder
                                    , LPTSTR lpszBuf
                                    , DWORD dwBufSize);

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CFolder)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CFolder)
	virtual BOOL OnInitDialog();
	afx_msg void On1();
	afx_msg void On2();
	afx_msg void On3();
	afx_msg void On4();
	afx_msg void On5();
	afx_msg void On6();
	afx_msg void OnButton20();
	afx_msg void OnButton22();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_9s;
	afx_msg void On9XA();
	CEdit m_10s;
	CEdit m_11s;
	CButton m_10;
	CButton m_11;
	afx_msg void OnBnClickedButton29();
	afx_msg void OnBnClickedButton30();
	CEdit m_12s;
	CButton m_12;
	afx_msg void OnBnClickedButton32();
	CEdit m_13s;
	afx_msg void OnBnClickedButton34();
	CEdit m_14s;
	afx_msg void OnBnClickedButton36();
	CEdit m_15s;
	afx_msg void OnBnClickedButton38();
	CEdit m_16s;
	CEdit m_17s;
	CEdit m_18s;
	CEdit m_19s;
	afx_msg void OnBnClickedButton40();
	afx_msg void OnBnClickedButton41();
	afx_msg void OnBnClickedButton42();
	afx_msg void OnBnClickedButton43();
	CEdit m_20s;
	afx_msg void OnBnClickedButton49();
	CEdit m_21s;
	afx_msg void OnBnClickedButton50();
	CEdit m_22s;
	afx_msg void OnBnClickedButton52();
	CEdit m_23s;
	afx_msg void OnBnClickedButton55();
	CEdit m_24s;
	afx_msg void OnBnClickedButton56();
	afx_msg void OnBnClickedButton25();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_FOLDER_H__08EFA55A_7FC1_4B30_8B0F_7987E91B5FB7__INCLUDED_)
