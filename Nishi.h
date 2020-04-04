#pragma once


// CNishi ダイアログ

class CNishi : public CDialog
{
	DECLARE_DYNAMIC(CNishi)

public:
	CNishi(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CNishi();
	CString ret;
	int ret2;
	CListBox	m_list;
	CString Gett(int a);

// ダイアログ データ
	enum { IDD = IDD_SENTAKU21 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
