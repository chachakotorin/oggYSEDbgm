#pragma once


// CTUKI �_�C�A���O

class CTUKI : public CDialog
{
	DECLARE_DYNAMIC(CTUKI)

public:
	CTUKI(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CTUKI();
	CString ret;
	int ret2;
	CListBox	m_list;
	CString Gett(int a);

// �_�C�A���O �f�[�^
	enum { IDD = IDD_SENTAKU20 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
