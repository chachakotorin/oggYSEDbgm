#pragma once


// CZwei �_�C�A���O

class CZwei : public CDialog
{
	DECLARE_DYNAMIC(CZwei)

public:
	CZwei(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CZwei();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_SENTAKU12 };

	CString ret;
	int ret2;
	CListBox	m_list;
	CString Gett(int a);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
