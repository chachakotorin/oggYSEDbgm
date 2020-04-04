#pragma once


// CBr4 ダイアログ

class CBr4 : public CDialog
{
	DECLARE_DYNAMIC(CBr4)

public:
	CBr4(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CBr4();
	CString ret;
	int ret2;
	CListBox	m_list;
	CString Gett(int a);

// ダイアログ データ
	enum { IDD = IDD_SENTAKU16 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
