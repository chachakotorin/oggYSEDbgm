#pragma once


// CSor ダイアログ

class CSor : public CDialog
{
	DECLARE_DYNAMIC(CSor)

public:
	CSor(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CSor();

// ダイアログ データ
	enum { IDD = IDD_SENTAKU13 };

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
