// ZeroFol.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ogg.h"
#include "ZeroFol.h"
#include "afxdialogex.h"


// CZeroFol ダイアログ

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


// CZeroFol メッセージ ハンドラー

extern save savedata;
void CZeroFol::OnBnClickedFol()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CFileDialog f(TRUE, L"t_bgm._dt", NULL, 0, L"零の軌跡ループファイルt_bgm._dt|t_bgm._dt");
	if (f.DoModal() == IDOK) {
		CString s = f.GetFolderPath()+L"\\"+f.GetFileTitle() + L"." + f.GetFileExt();
		m_fol.SetWindowText(s);
	}
}



BOOL CZeroFol::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: ここに初期化を追加してください
	m_fol.SetWindowText(savedata.zero);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}


void CZeroFol::OnBnClickedOk()
{
	CString s;
	m_fol.GetWindowText(s);
	TCHAR *ss;
	ss = s.GetBuffer();
	_tcscpy(savedata.zero, ss);
	s.ReleaseBuffer();
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CDialog::OnOK();
}
