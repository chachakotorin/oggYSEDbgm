#pragma once


// CZeroFol ダイアログ

class CZeroFol : public CDialog
{
	DECLARE_DYNAMIC(CZeroFol)

public:
	CZeroFol(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CZeroFol();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ZEROFOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_fol;

	afx_msg void OnBnClickedFol();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};


