// CImageBase.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ogg.h"
#include "afxdialogex.h"
#include "CImageBase.h"
#include "oggDlg.h"
// CImageBase ダイアログ

IMPLEMENT_DYNAMIC(CImageBase, CDialogEx)

CImageBase::CImageBase(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IMAGEBASE, pParent)
{
	oya = NULL;
}

CImageBase::~CImageBase()
{
}

void CImageBase::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CImageBase, CDialogEx)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CImageBase メッセージ ハンドラー


BOOL CImageBase::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: ここに初期化を追加してください
		{
		const HINSTANCE hModule = LoadLibrary(TEXT("user32.dll"));
		if (hModule)
		{
			struct ACCENTPOLICY
			{
				int nAccentState;
				int nFlags;
				int nColor;
				int nAnimationId;
			};
			struct WINCOMPATTRDATA
			{
				int nAttribute;
				PVOID pData;
				ULONG ulDataSize;
			};
			typedef BOOL(WINAPI* pSetWindowCompositionAttribute)(HWND, WINCOMPATTRDATA*);
			const pSetWindowCompositionAttribute SetWindowCompositionAttribute = (pSetWindowCompositionAttribute)GetProcAddress(hModule, "SetWindowCompositionAttribute");
			if (SetWindowCompositionAttribute)
			{
				ACCENTPOLICY policy = { 3, 2, 0x99bbbbbb, 0}; // ACCENT_ENABLE_BLURBEHIND=3...
				WINCOMPATTRDATA data = { 19, &policy, sizeof(ACCENTPOLICY) }; // WCA_ACCENT_POLICY=19
				extern save savedata;
				if(savedata.aero == 1)
				SetWindowCompositionAttribute(m_hWnd, &data);
			}
			FreeLibrary(hModule);
		}
	}
		SetTimer(10, 200, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}
extern save savedata;
int CImageBase::Create(CWnd* pWnd)
{
	m_pParent = NULL;

	const BOOL bret = CDialog::Create(CImageBase::IDD, this);

	if (bret == TRUE && savedata.aero == 1)
		ShowWindow(SW_SHOW);
	return bret;
}

BOOL CImageBase::DestroyWindow()
{
	// TODO: ここに特定なコードを追加するか、もしくは基底クラスを呼び出してください。
	BOOL rr = CDialog::DestroyWindow();
	delete this;
	return rr;
}

void CImageBase::move() {

}

void CImageBase::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。

	if (m_bMoving_ == TRUE) {
		// ドラッグ中だった場合
		m_bMoving_ = FALSE;
		::ReleaseCapture();
	}
	::SetWindowPos(oya->m_hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CImageBase::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	m_bMoving_ = TRUE;
	SetCapture();
	m_pointOld_ = point;
	::SetWindowPos(oya->m_hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	oya->SendMessage(WM_LBUTTONDOWN,nFlags, MAKELPARAM(point.x, point.y));
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CImageBase::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	if (m_bMoving_ == TRUE) {
		CRect rect;
		GetWindowRect(&rect);
		rect.left += (point.x - m_pointOld_.x);
		rect.right += (point.x - m_pointOld_.x);
		rect.top += (point.y - m_pointOld_.y);
		rect.bottom += (point.y - m_pointOld_.y);
		SetWindowPos(NULL, rect.left, rect.top,
			rect.right - rect.left, rect.bottom - rect.top,
			SWP_NOOWNERZORDER);
		oya->MoveWindow(&rect);
		::SetWindowPos(oya->m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);


	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CImageBase::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: ここにメッセージ ハンドラー コードを追加します。
					   // 描画メッセージで CDialogEx::OnPaint() を呼び出さないでください。
	RECT rect;
	GetClientRect(&rect);
	CBrush brush(RGB(0, 0, 0));
	GetDC()->FillRect(&rect, &brush);
}


int CImageBase::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: ここに特定な作成コードを追加してください。

	return 0;
}


BOOL CImageBase::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ここに特定なコードを追加するか、もしくは基底クラスを呼び出してください。
//	cs.style &= ~WS_SIZEBOX;
//	cs.style &= ~WS_BORDER;
	return CDialogEx::PreCreateWindow(cs);
}


void CImageBase::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	// TODO: ここにメッセージ ハンドラー コードを追加します。
}

extern COggDlg* og;
void CImageBase::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	CDialogEx::OnTimer(nIDEvent);
}
