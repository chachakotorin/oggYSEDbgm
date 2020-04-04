#pragma once


// CZwei ダイアログ

class CZwei : public CDialog
{
	DECLARE_DYNAMIC(CZwei)

public:
	CZwei(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CZwei();

// ダイアログ データ
	enum { IDD = IDD_SENTAKU12 };

	CString ret;
	int ret2;
	CListBox	m_list;
	CString Gett(int a);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
