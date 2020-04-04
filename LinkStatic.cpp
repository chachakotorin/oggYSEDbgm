// LinkStatic.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "LinkStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	OUT_COLOR	RGB(0, 0, 255)		// �ʏ�̃����N�F
#define	OVER_COLOR	RGB(255, 128, 0)	// �����N��Ƀ}�E�X���������̐F

/////////////////////////////////////////////////////////////////////////////
// CLinkStatic

// �����ݒ�
CLinkStatic::CLinkStatic()
{
	m_bClick = FALSE;
	
	// �w�̃J�[�\���ǂݍ���
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
// CLinkStatic ���b�Z�[�W �n���h��

// �����N�̐F�̕ύX
HBRUSH CLinkStatic::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// �ŏ��ɌĂ΂ꂽ�������t�H���g�̐ݒ������i�����������j
	if(!m_font.m_hObject)
	{
		LOGFONT lf;
		GetFont()->GetLogFont(&lf);
		lf.lfUnderline = TRUE;
		m_font.CreateFontIndirect(&lf);
		SetFont(&m_font, FALSE);
		Invalidate();
	}

	// �F��ݒ�
	pDC->SetTextColor(m_text);
	pDC->SetBkColor(::GetSysColor(COLOR_3DFACE));
	return m_brush;
}

// �}�E�X�������N�̏�ɂ������J�[�\����ύX
BOOL CLinkStatic::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	::SetCursor(m_hCursor);
	return TRUE;
}

// �J�[�\���������N��ɂ������̐F�̕ύX
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

// �����N��ɃW�����v
void CLinkStatic::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// �����N���N���b�N�����Ƃ����t���O�̃Z�b�g
	m_bClick = TRUE;
	CStatic::OnLButtonDown(nFlags, point);
}
void CLinkStatic::OnLButtonUp(UINT nFlags, CPoint point) 
{
	RECT rect;

	// �N���b�N�t���O��ON�̎�
	if(m_bClick)
	{
		::ReleaseCapture();
		GetClientRect(&rect);

		// �����N��Ń}�E�X�������ꂽ��
		if(PtInRect(&rect, point))
		{
			// �L���v�V������URL���擾
			CString strJump;
			GetWindowText(strJump);

			// �����L���v�V������":"�̕�����������΃��[���A�h���X�Ƃ݂Ȃ�
			if(strJump.Find(':') == -1)
				strJump = _T("mailto:") + strJump;

			// �u���E�U�i�������̓��[���[�j���N�����W�����v
//			::ShellExecute(NULL, _T("open"), strJump, NULL, NULL, SW_SHOWNORMAL);
			::ShellExecute(NULL, NULL , strJump, NULL, NULL, SW_SHOWNORMAL);

			// �u���E�U�N�����Ƀ}�E�X�������N�O�ɏo���Ƃ��ׂ̈̏���
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

// �F�����ɖ߂��čĕ\��
void CLinkStatic::ReSetColor()
{
	m_text = OUT_COLOR;
	Invalidate();
}