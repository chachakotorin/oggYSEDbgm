#pragma once


// CXA �_�C�A���O

class CXA : public CDialog
{
	DECLARE_DYNAMIC(CXA)

public:
	CXA(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CXA();
	int ret,ret2;

// �_�C�A���O �f�[�^
	enum { IDD = IDD_SENTAKU9 };
	CListBox	m_list;
	CString Gett(int a);
	int loop1,loop2;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
