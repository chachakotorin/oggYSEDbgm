#pragma once


// CED4 �_�C�A���O

class CED4 : public CDialog
{
	DECLARE_DYNAMIC(CED4)

public:
	CED4(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CED4();
	CString ret;
	int ret2;
	CListBox	m_list;
	CString Gett(int a);

// �_�C�A���O �f�[�^
	enum { IDD = IDD_SENTAKU18 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
