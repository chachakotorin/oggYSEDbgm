#pragma once
#include "afxwin.h"


// CFilename ダイアログ

class CFilename : public CDialog
{
	DECLARE_DYNAMIC(CFilename)

public:
	CFilename(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CFilename();

// ダイアログ データ
	enum { IDD = IDD_FILENAME };
	playlistdata0 pc;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedOk2();
	CEdit m_name;
	CEdit m_alb;
	CEdit m_art;
	CEdit m_fol;
};
