#pragma once


// CYs12_2 �_�C�A���O

class CYs12_2 : public CDialog
{
	DECLARE_DYNAMIC(CYs12_2)

public:
	CYs12_2(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CYs12_2();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_SENTAKU11 };

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
