#include "stdafx.h"
#include "ogg.h"
#include "afxdialogex.h"
#include "CDailog1.h"

extern save savedata;
extern CImageBase* Games;
BEGIN_MESSAGE_MAP(CDailog1, CDialog)
	ON_WM_CREATE()
	ON_WM_MOVING()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_WM_NCACTIVATE()
END_MESSAGE_MAP()




#include "CImageBase.h"
extern save savedata;
extern CImageBase* Games;
int CDailog1::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: ここに特定な作成コードを追加してください。
	if (savedata.aero == 1) {
		ModifyStyleEx(0, WS_EX_LAYERED);

		// レイヤードウィンドウの不透明度と透明のカラーキー
		SetLayeredWindowAttributes(RGB(255, 0, 0), 0, LWA_COLORKEY);

		// 赤色のブラシを作成する．
		m_brDlg.CreateSolidBrush(RGB(255, 0, 0));
	}
	SetTimer(500,200, NULL);
	return 0;
}


void CDailog1::OnMoving(UINT fwSide, LPRECT pRect)
{
	CDialog::OnMoving(fwSide, pRect);
	CRect r;
	GetWindowRect(&r);
	if(Games)
	Games->MoveWindow(&r);
	// TODO: ここにメッセージ ハンドラー コードを追加します。
}


HBRUSH CDailog1::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: ここで DC の属性を変更してください。
	if (savedata.aero == 1) {
		if (nCtlColor == CTLCOLOR_DLG)
		{
			return m_brDlg;
		}
		if (nCtlColor == CTLCOLOR_STATIC)
		{
			SetBkMode(pDC->m_hDC, TRANSPARENT);
			return m_brDlg;
		}
	}
	// TODO: 既定値を使用したくない場合は別のブラシを返します。
	return hbr;
}


void CDailog1::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	KillTimer(500);
	Games = new CImageBase;
	Games->oya = this;
	Games->Create(this);
	CRect r;
	GetWindowRect(&r);
	if (Games)
		Games->MoveWindow(&r);
	::SetWindowPos(Games->m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	::SetWindowPos(m_hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	CDialog::OnTimer(nIDEvent);
}


BOOL CDailog1::OnNcActivate(BOOL bActive)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	SetTimer(500, 30, NULL);
	return CDialog::OnNcActivate(bActive);
}
