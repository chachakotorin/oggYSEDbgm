#pragma once
#include "afxwin.h"


// CFilename �_�C�A���O

class CFilename : public CDialog
{
	DECLARE_DYNAMIC(CFilename)

public:
	CFilename(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CFilename();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_FILENAME };
	playlistdata0 pc;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedOk2();
	CEdit m_name;
	CEdit m_alb;
	CEdit m_art;
	CEdit m_fol;
};
