#pragma once


// CYs12_1 �_�C�A���O

class CYs12_1 : public CDialog
{
	DECLARE_DYNAMIC(CYs12_1)

public:
	CYs12_1(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CYs12_1();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_SENTAKU10 };

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
