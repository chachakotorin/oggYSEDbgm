#pragma once
#include "afxwin.h"


// CPVI ダイアログ

class CPVI : public CDialog
{
	DECLARE_DYNAMIC(CPVI)

public:
	CPVI(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CPVI();

// ダイアログ データ
	enum { IDD = IDD_PVI };

	void regsave(CString key,CString value);
	CString regload(CString key);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	CToolTipCtrl m_tooltip;
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_pvi;
	CButton m_ok;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit1();
};
