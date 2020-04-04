// ListSyosai.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ogg.h"
#include "ListCtrlA.h"
#include "PlayList.h"
#include "ListSyosai.h"


// CListSyosai ダイアログ

IMPLEMENT_DYNAMIC(CListSyosai, CDialog)

CListSyosai::CListSyosai(CWnd* pParent /*=NULL*/)
	: CDialog(CListSyosai::IDD, pParent)
{

}

CListSyosai::~CListSyosai()
{
}

void CListSyosai::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_name);
	DDX_Control(pDX, IDC_EDIT2, m_id);
	DDX_Control(pDX, IDC_EDIT3, m_game);
	DDX_Control(pDX, IDC_EDIT4, m_art);
	DDX_Control(pDX, IDC_EDIT5, m_alb);
	DDX_Control(pDX, IDC_EDIT6, m_fol);
	DDX_Control(pDX, IDOK999, m_ok2);
	DDX_Control(pDX, IDC_EDIT11, m_cmt);
	DDX_Control(pDX, IDC_EDIT7, m_year);
	DDX_Control(pDX, IDC_EDIT9, m_track);
	DDX_Control(pDX, IDC_EDIT10, m_j);
}


BEGIN_MESSAGE_MAP(CListSyosai, CDialog)
	ON_BN_CLICKED(IDOK999, &CListSyosai::OnBnClickedOk2)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CListSyosai メッセージ ハンドラ
void CListSyosai::OnClose()
{
	EndDialog(0);
}

void CListSyosai::OnBnClickedOk2()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	CString s,ss;
	s=pc.fol;
	ss=s.Left(s.ReverseFind('\\'));
	ShellExecute(NULL, _T("open"), ss, _T(""), NULL, SW_SHOWNORMAL);

}

int CALLBACK EditWordBreakProc(LPTSTR lpch, int ichCurrent, int cch, int code);
#include "Id3tagv1.h"
#include "Id3tagv2.h"
BOOL CListSyosai::OnInitDialog()
{
	CDialog::OnInitDialog();
	TCHAR dy[256];
	// TODO:  ここに初期化を追加してください
	{
		CEdit * pEdit = (CEdit *)GetDlgItem(IDC_EDIT1);
		::SendMessage(pEdit->m_hWnd, EM_SETWORDBREAKPROC, 0, (LPARAM)EditWordBreakProc);
	}
	{
		CEdit * pEdit = (CEdit *)GetDlgItem(IDC_EDIT4);
		::SendMessage(pEdit->m_hWnd, EM_SETWORDBREAKPROC, 0, (LPARAM)EditWordBreakProc);
	}
	{
		CEdit * pEdit = (CEdit *)GetDlgItem(IDC_EDIT5);
		::SendMessage(pEdit->m_hWnd, EM_SETWORDBREAKPROC, 0, (LPARAM)EditWordBreakProc);
	}
	{
		CEdit * pEdit = (CEdit *)GetDlgItem(IDC_EDIT6);
		::SendMessage(pEdit->m_hWnd, EM_SETWORDBREAKPROC, 0, (LPARAM)EditWordBreakProc);
	}
	{
		CEdit * pEdit = (CEdit *)GetDlgItem(IDC_EDIT11);
		::SendMessage(pEdit->m_hWnd, EM_SETWORDBREAKPROC, 0, (LPARAM)EditWordBreakProc);
	}
	m_name.SetWindowText(pc.name);
	m_id.SetWindowText(_itot(pc.sub,dy,10));
	m_game.SetWindowText(pc.game);
	m_art.SetWindowText(pc.art);
	m_alb.SetWindowText(pc.alb);
	m_fol.SetWindowText(pc.fol);
	CString s;
	s=pc.fol;
	if(s.Find('\\',0)==-1) m_ok2.EnableWindow(FALSE);
	else{
		if((s.Right(4)==".mp3" || s.Right(4)==".MP3" || s.Right(4)==".mp2" || s.Right(4)==".MP2" ||
			s.Right(4)==".mp1" || s.Right(4)==".MP1" || s.Right(4)==".rmp" || s.Right(4)==".RMP")){
			CId3tagv1 ta1;
			CId3tagv2 ta2;
			int b=ta2.Load(pc.fol);
			s=ta2.GetYear();if(b==-1){ta1.Load(pc.fol); s=ta1.GetYear();} m_year.SetWindowText(s);
			s=ta2.GetTrackNo();if(b==-1) s=ta1.GetTrackNo(); m_track.SetWindowText(s);
			s=ta2.GetGenre();if(b==-1) s=ta1.GetGenre(); m_j.SetWindowText(s);
			s=ta2.GetComment();if(b==-1) s=ta1.GetComment(); m_cmt.SetWindowText(s);
			s=ta2.GetTitle();if(b==-1) s=ta1.GetTitle(); m_name.SetWindowText(s);
			s=ta2.GetAlbum();if(b==-1) s=ta1.GetAlbum(); m_alb.SetWindowText(s);
			s=ta2.GetArtist();if(b==-1) s=ta1.GetArtist(); m_art.SetWindowText(s);
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

//ワードラップを解除するためのコールバック関数
int CALLBACK EditWordBreakProc(LPTSTR lpch, int ichCurrent, int cch, int code)
{
	return (WB_ISDELIMITER == code) ? 0 : ichCurrent;
}