#pragma once


// CYs12_2 ダイアログ

class CYs12_2 : public CDialog
{
	DECLARE_DYNAMIC(CYs12_2)

public:
	CYs12_2(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CYs12_2();

// ダイアログ データ
	enum { IDD = IDD_SENTAKU11 };

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
