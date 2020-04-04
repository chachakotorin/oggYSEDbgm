// LinkStatic.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "LinkStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	OUT_COLOR	RGB(0, 0, 255)		// 通常のリンク色
#define	OVER_COLOR	RGB(255, 128, 0)	// リンク上にマウスが着た時の色

/////////////////////////////////////////////////////////////////////////////
// CLinkStatic

// 初期設定
CLinkStatic::CLinkStatic()
{
	m_bClick = FALSE;
	
	// 指のカーソル読み込み
	OSVERSIONINFO in;ZeroMemory(&in,sizeof(in));in.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);GetVersionEx(&in);
	TCHAR lpWinDir[MAX_PATH];
	::GetWindowsDirectory(lpWinDir, MAX_PATH - 13);
	if(in.dwMajorVersion<=5){
		_tcscat(lpWinDir, _T("\\winhlp32.exe"));
		HINSTANCE hInstHelp = ::LoadLibrary(lpWinDir);
		if(hInstHelp)
		{
			m_hCursor = CopyCursor(::LoadCursor(hInstHelp, MAKEINTRESOURCE(106)));
			::FreeLibrary(hInstHelp);
		}
		else
			m_hCursor = ::LoadCursor(NULL, IDC_ARROW);
	}else{
		TCHAR tmp[1024];
		DWORD r=ExpandEnvironmentStrings( _T("%windir%") , tmp,1024);
		CString s;s=tmp;s+="\\cursors\\aero_link.cur";
		if(r!=0)
			m_hCursor = CopyCursor(::LoadCursorFromFile(s));
		else
			m_hCursor = ::LoadCursor(NULL, IDC_ARROW);
	}
	m_text = OUT_COLOR;
	m_brush.CreateSolidBrush(::GetSysColor(COLOR_3DFACE));
}

CLinkStatic::~CLinkStatic()
{
}


BEGIN_MESSAGE_MAP(CLinkStatic, CStatic)
	//{{AFX_MSG_MAP(CLinkStatic)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLinkStatic メッセージ ハンドラ

// リンクの色の変更
HBRUSH CLinkStatic::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// 最初に呼ばれた時だけフォントの設定をする（下線を引く）
	if(!m_font.m_hObject)
	{
		LOGFONT lf;
		GetFont()->GetLogFont(&lf);
		lf.lfUnderline = TRUE;
		m_font.CreateFontIndirect(&lf);
		SetFont(&m_font, FALSE);
		Invalidate();
	}

	// 色を設定
	pDC->SetTextColor(m_text);
	pDC->SetBkColor(::GetSysColor(COLOR_3DFACE));
	return m_brush;
}

// マウスがリンクの上にきた時カーソルを変更
BOOL CLinkStatic::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	::SetCursor(m_hCursor);
	return TRUE;
}

// カーソルがリンク上にきた時の色の変更
void CLinkStatic::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(GetCapture() == NULL)
	{
		m_text = OVER_COLOR;
		Invalidate();
		SetCapture();
	}

	RECT rect;
	GetClientRect(&rect);
	if(!PtInRect(&rect, point) && !m_bClick)
	{
		ReSetColor();
		::ReleaseCapture();
	}
	CStatic::OnMouseMove(nFlags, point);
}

// リンク先にジャンプ
void CLinkStatic::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// リンクをクリックしたというフラグのセット
	m_bClick = TRUE;
	CStatic::OnLButtonDown(nFlags, point);
}
void CLinkStatic::OnLButtonUp(UINT nFlags, CPoint point) 
{
	RECT rect;

	// クリックフラグがONの時
	if(m_bClick)
	{
		::ReleaseCapture();
		GetClientRect(&rect);

		// リンク上でマウスが離された時
		if(PtInRect(&rect, point))
		{
			// キャプションのURLを取得
			CString strJump;
			GetWindowText(strJump);

			// もしキャプションに":"の文字が無ければメールアドレスとみなす
			if(strJump.Find(':') == -1)
				strJump = _T("mailto:") + strJump;

			// ブラウザ（もしくはメーラー）を起動しジャンプ
//			::ShellExecute(NULL, _T("open"), strJump, NULL, NULL, SW_SHOWNORMAL);
			::ShellExecute(NULL, NULL , strJump, NULL, NULL, SW_SHOWNORMAL);

			// ブラウザ起動中にマウスがリンク外に出たときの為の処理
			GetWindowRect(&rect);
			::GetCursorPos(&point);
			if(!PtInRect(&rect, point))
				ReSetColor();
		}
		else
			ReSetColor();

		m_bClick = FALSE;
	}
	CStatic::OnLButtonUp(nFlags, point);
}

// 色を元に戻して再表示
void CLinkStatic::ReSetColor()
{
	m_text = OUT_COLOR;
	Invalidate();
}