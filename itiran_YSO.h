#if !defined(AFX_ITIRAN_YSO_H__F841A12C_910F_4514_A04E_E7F05AF189F1__INCLUDED_)
#define AFX_ITIRAN_YSO_H__F841A12C_910F_4514_A04E_E7F05AF189F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// itiran_YSO.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// Citiran_YSO �_�C�A���O

class Citiran_YSO : public CDialog
{
// �R���X�g���N�V����
public:
	Citiran_YSO(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^
	int ret,ret2;

// �_�C�A���O �f�[�^
	//{{AFX_DATA(Citiran_YSO)
	enum { IDD = IDD_SENTAKU4 };
	CListBox	m_list;
	//}}AFX_DATA
	CString Gett(int a);

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(Citiran_YSO)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(Citiran_YSO)
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_ITIRAN_YSO_H__F841A12C_910F_4514_A04E_E7F05AF189F1__INCLUDED_)
