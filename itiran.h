#if !defined(AFX_ITIRAN_H__4D82B777_FF66_428B_A3F1_2E5B6EF53309__INCLUDED_)
#define AFX_ITIRAN_H__4D82B777_FF66_428B_A3F1_2E5B6EF53309__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// itiran.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// itiran �_�C�A���O

class itiran : public CDialog
{
// �R���X�g���N�V����
public:
	itiran(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^
	int ret,ret2;
	CString Gett(int a);
// �_�C�A���O �f�[�^
	//{{AFX_DATA(itiran)
	enum { IDD = IDD_SENTAKU };
	CListBox	m_list;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(itiran)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(itiran)
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_ITIRAN_H__4D82B777_FF66_428B_A3F1_2E5B6EF53309__INCLUDED_)
