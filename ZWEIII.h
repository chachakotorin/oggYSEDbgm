#if !defined(AFX_ZWEIII_H__78625D67_3C5E_471E_B566_115BE87D76A5__INCLUDED_)
#define AFX_ZWEIII_H__78625D67_3C5E_471E_B566_115BE87D76A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZWEIII.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CZWEIII �_�C�A���O

class CZWEIII : public CDialog
{
// �R���X�g���N�V����
public:
	CZWEIII(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^
	int ret,ret2;

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CZWEIII)
	enum { IDD = IDD_SENTAKU6 };
	CListBox	m_list;
		// ����: ClassWizard �͂��̈ʒu�Ƀf�[�^ �����o��ǉ����܂��B
	//}}AFX_DATA
	CString Gett(int a);


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CZWEIII)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CZWEIII)
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_ZWEIII_H__78625D67_3C5E_471E_B566_115BE87D76A5__INCLUDED_)
