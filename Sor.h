#pragma once


// CSor �_�C�A���O

class CSor : public CDialog
{
	DECLARE_DYNAMIC(CSor)

public:
	CSor(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CSor();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_SENTAKU13 };

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
