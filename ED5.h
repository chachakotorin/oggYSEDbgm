#pragma once


// CED5 �_�C�A���O

class CED5 : public CDialog
{
	DECLARE_DYNAMIC(CED5)

public:
	CED5(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CED5();
	CString ret;
	int ret2;
	CListBox	m_list;
	CString Gett(int a);

// �_�C�A���O �f�[�^
	enum { IDD = IDD_SENTAKU19 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};
