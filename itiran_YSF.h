#if !defined(AFX_ITIRAN_YSF_H__3564AC0B_9DC0_4586_8C9B_0E8A3E5B6421__INCLUDED_)
#define AFX_ITIRAN_YSF_H__3564AC0B_9DC0_4586_8C9B_0E8A3E5B6421__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// itiran_YSF.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// Citiran_YSF �_�C�A���O

class Citiran_YSF : public CDialog
{
// �R���X�g���N�V����
public:
	Citiran_YSF(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^
	int ret,ret2;

// �_�C�A���O �f�[�^
	//{{AFX_DATA(Citiran_YSF)
	enum { IDD = IDD_SENTAKU2 };
	CListBox	m_list;
	//}}AFX_DATA
	void Gett(int a);

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(Citiran_YSF)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(Citiran_YSF)
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_ITIRAN_YSF_H__3564AC0B_9DC0_4586_8C9B_0E8A3E5B6421__INCLUDED_)
