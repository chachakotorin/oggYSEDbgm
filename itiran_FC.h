#if !defined(AFX_ITIRAN_FC_H__2D531ED5_FAAD_48BA_9B46_68C0E88F0F32__INCLUDED_)
#define AFX_ITIRAN_FC_H__2D531ED5_FAAD_48BA_9B46_68C0E88F0F32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// itiran_FC.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// Citiran_FC �_�C�A���O

class Citiran_FC : public CDialog
{
// �R���X�g���N�V����
public:
	Citiran_FC(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^
	int ret,ret2;
	CString Gett(int a);
// �_�C�A���O �f�[�^
	//{{AFX_DATA(Citiran_FC)
	enum { IDD = IDD_SENTAKU1 };
	CListBox	m_list;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(Citiran_FC)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(Citiran_FC)
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_ITIRAN_FC_H__2D531ED5_FAAD_48BA_9B46_68C0E88F0F32__INCLUDED_)
