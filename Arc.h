#pragma once


// CArc ダイアログ

class CArc : public CDialog
{
	DECLARE_DYNAMIC(CArc)

public:
	CArc(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CArc();
	CString ret;
	int ret2;
	CListBox	m_list;
	CString Gett(int a);

// ダイアログ データ
	enum { IDD = IDD_SENTAKU22 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
