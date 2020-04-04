#pragma once
#include "afxwin.h"


// CAudioSelect ダイアログ

class CAudioSelect : public CDialog
{
	DECLARE_DYNAMIC(CAudioSelect)

public:
	CAudioSelect(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CAudioSelect();

// ダイアログ データ
	enum { IDD = IDD_AUDIOSELECT };
	void select();
	int no;

protected:
	CToolTipCtrl m_tooltip;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnLbnDblclkList1();
	afx_msg void OnBnClickedOk();
	CListBox m_lb;
	virtual BOOL OnInitDialog();
};
