#pragma once


// CDino ダイアログ

class CDino : public CDialog
{
	DECLARE_DYNAMIC(CDino)

public:
	CDino(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CDino();

	CString ret;
	int ret2;
	CListBox	m_list;
	CString Gett(int a);
	int loop1,loop2;

	// ダイアログ データ
	enum { IDD = IDD_SENTAKU15 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
