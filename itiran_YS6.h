#if !defined(AFX_ITIRAN_YS6_H__9E3AF8B8_AFD3_4030_8920_18FBC884E1CA__INCLUDED_)
#define AFX_ITIRAN_YS6_H__9E3AF8B8_AFD3_4030_8920_18FBC884E1CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// itiran_YS6.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// Citiran_YS6 �_�C�A���O

class Citiran_YS6 : public CDialog
{
// �R���X�g���N�V����
public:
	Citiran_YS6(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^
	int ret,ret2;

// �_�C�A���O �f�[�^
	//{{AFX_DATA(Citiran_YS6)
	enum { IDD = IDD_SENTAKU3 };
	CListBox	m_list;
	//}}AFX_DATA
	void Gett(int a);

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(Citiran_YS6)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(Citiran_YS6)
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_ITIRAN_YS6_H__9E3AF8B8_AFD3_4030_8920_18FBC884E1CA__INCLUDED_)
