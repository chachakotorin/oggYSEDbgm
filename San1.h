#pragma once


// CSan1 �_�C�A���O

class CSan1 : public CDialog
{
	DECLARE_DYNAMIC(CSan1)

public:
	CSan1(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CSan1();
	CString ret;
	int ret2;
	CListBox	m_list;
	CString Gett(int a);

// �_�C�A���O �f�[�^
	enum { IDD = IDD_SENTAKU23 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
