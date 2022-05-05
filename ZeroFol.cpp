// ZeroFol.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "ogg.h"
#include "ZeroFol.h"
#include "afxdialogex.h"


// CZeroFol �_�C�A���O

IMPLEMENT_DYNAMIC(CZeroFol, CDialog)

CZeroFol::CZeroFol(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_ZEROFOL, pParent)
{

}

CZeroFol::~CZeroFol()
{
}

void CZeroFol::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, m_fol);
}

#include "CImageBase.h"
BEGIN_MESSAGE_MAP(CZeroFol, CDialog)
	ON_BN_CLICKED(IDC_FOL, &CZeroFol::OnBnClickedFol)
	ON_BN_CLICKED(IDOK, &CZeroFol::OnBnClickedOk)
	cmn(CZeroFol);


// CZeroFol ���b�Z�[�W �n���h���[

extern save savedata;
void CZeroFol::OnBnClickedFol()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	CFileDialog f(TRUE, L"t_bgm._dt", NULL, 0, L"��̋O�Ճ��[�v�t�@�C��t_bgm._dt|t_bgm._dt");
	if (f.DoModal() == IDOK) {
		CString s = f.GetFolderPath()+L"\\"+f.GetFileTitle() + L"." + f.GetFileExt();
		m_fol.SetWindowText(s);
	}
}



BOOL CZeroFol::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: �����ɏ�������ǉ����Ă�������
	m_fol.SetWindowText(savedata.zero);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}


void CZeroFol::OnBnClickedOk()
{
	CString s;
	m_fol.GetWindowText(s);
	TCHAR *ss;
	ss = s.GetBuffer();
	_tcscpy(savedata.zero, ss);
	s.ReleaseBuffer();
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	CDialog::OnOK();
}
