// CImageBase.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ogg.h"
#include "afxdialogex.h"
#include "CImageBase.h"

#include "OSVersion.h"

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
	ON_WM_CTLCOLOR()
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()


// CImageBase メッセージ ハンドラー


BOOL CImageBase::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: ここに初期化を追加してください
	COSVersion os;
	os.GetVersionString();
	if (os.in.dwMajorVersion >= 10 && os.in.dwBuildNumber >= 18363)
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
				ACCENTPOLICY policy = { 3, 2, 0x77bb9999, 0 }; // ACCENT_ENABLE_BLURBEHIND=3...
				WINCOMPATTRDATA data = { 19, &policy, sizeof(ACCENTPOLICY) }; // WCA_ACCENT_POLICY=19
				extern save savedata;
				if (savedata.aero == 1)
					SetWindowCompositionAttribute(m_hWnd, &data);
			}
			FreeLibrary(hModule);
		}
	}
	if (os.in.dwMajorVersion == 6) {
		HMODULE hDLL;
		typedef DWORD(WINAPI* PFUNC)(HWND, MARGINS*);
		PFUNC pFunc;
		hDLL = ::LoadLibrary(_T("Dwmapi"));
		pFunc = (PFUNC)::GetProcAddress(hDLL, "DwmExtendFrameIntoClientArea");
		MARGINS margin = { -1, -1, -1, -1 };
		if (pFunc) {
			pFunc(m_hWnd, &margin);
		}
		::FreeLibrary(hDLL);

	}

	brush.CreateSolidBrush(RGB(0, 0, 0));
	SetTimer(10, 200, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}
extern save savedata;
int CImageBase::Create(CWnd* pWnd)
{
	m_pParent = NULL;

	const BOOL bret = CDialog::Create(CImageBase::IDD, this);
	RECT r = { 0,0,0,0 };
	MoveWindow(&r);
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
	m_bMoving_ = FALSE;
	::SetWindowPos(m_hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	::SetWindowPos(oya->m_hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CImageBase::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	m_bMoving_ = TRUE;
	SetCapture();
	m_pointOld_ = point;
	::SetWindowPos(m_hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	::SetWindowPos(oya->m_hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
//	oya->SendMessage(WM_LBUTTONDOWN, nFlags, MAKELPARAM(point.x, point.y));
	oya->SendMessage(WM_NCACTIVATE, TRUE, NULL);
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CImageBase::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	if (0) {
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
		::SetWindowPos(m_hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
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
	RECT r = { 0,0,0,0 };
	MoveWindow(&r);
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
	RECT r;
	GetWindowRect(&r);
	//	r.left += 5;
	//	r.right -= 10;
	//	r.bottom -= 1;
	//	MoveWindow(&r);
	if (nType == SIZE_MINIMIZED) {
		ShowWindow(SW_HIDE);
	}
	else {
		ShowWindow(SW_SHOWNORMAL);
	}

}

void CImageBase::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	CDialogEx::OnTimer(nIDEvent);
}


HBRUSH CImageBase::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: ここで DC の属性を変更してください。

	// TODO: 既定値を使用したくない場合は別のブラシを返します。
	return hbr;
}

LRESULT CImageBase::OnNcHitTest(CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	::SendMessage(oya->m_hWnd, WM_NCHITTEST, HTTRANSPARENT, MAKELPARAM(point.x, point.y));
	return CDialogEx::OnNcHitTest(point);
}
