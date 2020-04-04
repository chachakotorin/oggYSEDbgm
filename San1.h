#pragma once


// CSan1 ダイアログ

class CSan1 : public CDialog
{
	DECLARE_DYNAMIC(CSan1)

public:
	CSan1(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CSan1();
	CString ret;
	int ret2;
	CListBox	m_list;
	CString Gett(int a);

// ダイアログ データ
	enum { IDD = IDD_SENTAKU23 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
