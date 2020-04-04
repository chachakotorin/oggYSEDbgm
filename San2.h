#pragma once


// CSan2 ダイアログ

class CSan2 : public CDialog
{
	DECLARE_DYNAMIC(CSan2)

public:
	CSan2(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CSan2();
	CString ret;
	int ret2;
	CListBox	m_list;
	CString Gett(int a);

// ダイアログ データ
	enum { IDD = IDD_SENTAKU24 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
