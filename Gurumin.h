#pragma once


// CGurumin �_�C�A���O

class CGurumin : public CDialog
{
	DECLARE_DYNAMIC(CGurumin)

public:
	CGurumin(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CGurumin();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_SENTAKU14 };

	CString ret;
	int ret2;
	CListBox	m_list;
	CString Gett(int a);
	int loop1,loop2;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
