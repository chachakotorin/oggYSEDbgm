#pragma once
#include "afxwin.h"


// CPVI �_�C�A���O

class CPVI : public CDialog
{
	DECLARE_DYNAMIC(CPVI)

public:
	CPVI(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CPVI();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_PVI };

	void regsave(CString key,CString value);
	CString regload(CString key);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	CToolTipCtrl m_tooltip;
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_pvi;
	CButton m_ok;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit1();
};
