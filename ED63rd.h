#if !defined(AFX_ED63RD_H__CAB5FA3D_0173_4137_ABBC_A52D8814CADE__INCLUDED_)
#define AFX_ED63RD_H__CAB5FA3D_0173_4137_ABBC_A52D8814CADE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ED63rd.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CED63rd �_�C�A���O

class CED63rd : public CDialog
{
// �R���X�g���N�V����
public:
	CED63rd(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^
	int ret,ret2;
	CString Gett(int a);

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CED63rd)
	enum { IDD = IDD_SENTAKU5 };
	CListBox	m_list;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CED63rd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CED63rd)
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_ED63RD_H__CAB5FA3D_0173_4137_ABBC_A52D8814CADE__INCLUDED_)
