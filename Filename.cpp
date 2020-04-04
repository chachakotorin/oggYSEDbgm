// Filename.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ogg.h"
#include "ListCtrlA.h"
#include "PlayList.h"
#include "Filename.h"


// CFilename ダイアログ

IMPLEMENT_DYNAMIC(CFilename, CDialog)

CFilename::CFilename(CWnd* pParent /*=NULL*/)
	: CDialog(CFilename::IDD, pParent)
{

}

CFilename::~CFilename()
{
}

void CFilename::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_name);
	DDX_Control(pDX, IDC_EDIT2, m_art);
	DDX_Control(pDX, IDC_EDIT3, m_alb);
	DDX_Control(pDX, IDC_EDIT4, m_fol);
}


BEGIN_MESSAGE_MAP(CFilename, CDialog)
	ON_BN_CLICKED(ID_OK, &CFilename::OnBnClickedOk)
	ON_BN_CLICKED(IDOK, &CFilename::OnBnClickedOk2)
END_MESSAGE_MAP()


// CFilename メッセージ ハンドラ

BOOL CFilename::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ここに初期化を追加してください
	m_name.SetWindowText(pc.name);
	m_art.SetWindowText(pc.art);
	m_alb.SetWindowText(pc.alb);
	m_fol.SetWindowText(pc.fol);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

void CFilename::OnBnClickedOk()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	CString s;
	m_name.GetWindowText(s);
	_tcscpy(pc.name,s);
	m_art.GetWindowText(s);
	_tcscpy(pc.art,s);
	m_alb.GetWindowText(s);
	_tcscpy(pc.alb,s);
	m_fol.GetWindowText(s);
	_tcscpy(pc.fol,s);
	OnOK();
}

void CFilename::OnBnClickedOk2()
{
	
}