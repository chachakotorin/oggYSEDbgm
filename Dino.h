#pragma once


// CDino �_�C�A���O

class CDino : public CDialog
{
	DECLARE_DYNAMIC(CDino)

public:
	CDino(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CDino();

	CString ret;
	int ret2;
	CListBox	m_list;
	CString Gett(int a);
	int loop1,loop2;

	// �_�C�A���O �f�[�^
	enum { IDD = IDD_SENTAKU15 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
