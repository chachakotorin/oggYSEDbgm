#pragma once


// CED5 ダイアログ

class CED5 : public CDialog
{
	DECLARE_DYNAMIC(CED5)

public:
	CED5(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CED5();
	CString ret;
	int ret2;
	CListBox	m_list;
	CString Gett(int a);

// ダイアログ データ
	enum { IDD = IDD_SENTAKU19 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};
