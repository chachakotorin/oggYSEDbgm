#if !defined(AFX_YSC2_H__0F750E54_B5C3_450A_82BF_91EB2DB8D52A__INCLUDED_)
#define AFX_YSC2_H__0F750E54_B5C3_450A_82BF_91EB2DB8D52A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// YsC2.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CYsC2 �_�C�A���O

class CYsC2 : public CDialog
{
// �R���X�g���N�V����
public:
	CYsC2(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^
	CString ret;
	int ret2;

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CYsC2)
	enum { IDD = IDD_SENTAKU8 };
	CListBox	m_list;
	//}}AFX_DATA
	CString Gett(int a);


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CYsC2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CYsC2)
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_YSC2_H__0F750E54_B5C3_450A_82BF_91EB2DB8D52A__INCLUDED_)
