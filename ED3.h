#pragma once


// CED3 ダイアログ

class CED3 : public CDialog
{
	DECLARE_DYNAMIC(CED3)

public:
	CED3(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CED3();
	CString ret;
	int ret2;
	CListBox	m_list;
	CString Gett(int a);

// ダイアログ データ
	enum { IDD = IDD_SENTAKU17 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
