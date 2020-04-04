#pragma once


// CXA ダイアログ

class CXA : public CDialog
{
	DECLARE_DYNAMIC(CXA)

public:
	CXA(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CXA();
	int ret,ret2;

// ダイアログ データ
	enum { IDD = IDD_SENTAKU9 };
	CListBox	m_list;
	CString Gett(int a);
	int loop1,loop2;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
