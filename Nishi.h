#pragma once


// CNishi �_�C�A���O

class CNishi : public CDialog
{
	DECLARE_DYNAMIC(CNishi)

public:
	CNishi(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CNishi();
	CString ret;
	int ret2;
	CListBox	m_list;
	CString Gett(int a);

// �_�C�A���O �f�[�^
	enum { IDD = IDD_SENTAKU21 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
