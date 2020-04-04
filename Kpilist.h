#pragma once
#include "afxcmn.h"
#include "ListCtrlA.h"

// CKpilist �_�C�A���O

class CKpilist : public CDialog
{
	DECLARE_DYNAMIC(CKpilist)

public:
	CKpilist(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CKpilist();
	void Init();
	void Save();
	int status;
// �_�C�A���O �f�[�^
	enum { IDD = IDD_KPI };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	CToolTipCtrl m_tooltip;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CListCtrl m_lc;
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL DestroyWindow();
};
