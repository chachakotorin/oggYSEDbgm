#if !defined(AFX_YSC1_H__4CC2A54C_7DB6_4129_A70B_423BDF1B3A05__INCLUDED_)
#define AFX_YSC1_H__4CC2A54C_7DB6_4129_A70B_423BDF1B3A05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// YsC1.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CYsC1 �_�C�A���O

class CYsC1 : public CDialog
{
// �R���X�g���N�V����
public:
	CYsC1(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^
	CString ret;
	int ret2;

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CYsC1)
	enum { IDD = IDD_SENTAKU7 };
	CListBox	m_list;
	//}}AFX_DATA
	CString Gett(int a);


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CYsC1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CYsC1)
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_YSC1_H__4CC2A54C_7DB6_4129_A70B_423BDF1B3A05__INCLUDED_)
