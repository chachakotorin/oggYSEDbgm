#pragma once


// CED3 �_�C�A���O

class CED3 : public CDialog
{
	DECLARE_DYNAMIC(CED3)

public:
	CED3(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CED3();
	CString ret;
	int ret2;
	CListBox	m_list;
	CString Gett(int a);

// �_�C�A���O �f�[�^
	enum { IDD = IDD_SENTAKU17 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
