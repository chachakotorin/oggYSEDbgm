#pragma once


// CZeroFol �_�C�A���O

class CZeroFol : public CDialog
{
	DECLARE_DYNAMIC(CZeroFol)

public:
	CZeroFol(CWnd* pParent = NULL);   // �W���R���X�g���N�^�[
	virtual ~CZeroFol();

// �_�C�A���O �f�[�^
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ZEROFOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_fol;

	afx_msg void OnBnClickedFol();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};


