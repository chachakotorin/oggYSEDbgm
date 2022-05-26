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

	// TODO: �����ɓ���ȍ쐬�R�[�h��ǉ����Ă��������B
	if (savedata.aero == 1) {
		ModifyStyleEx(0, WS_EX_LAYERED);

		// ���C���[�h�E�B���h�E�̕s�����x�Ɠ����̃J���[�L�[
		SetLayeredWindowAttributes(RGB(255, 0, 0), 0, LWA_COLORKEY);

		// �ԐF�̃u���V���쐬����D
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
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����܂��B
}


HBRUSH CDailog1::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: ������ DC �̑�����ύX���Ă��������B
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
	// TODO: ����l���g�p�������Ȃ��ꍇ�͕ʂ̃u���V��Ԃ��܂��B
	return hbr;
}


void CDailog1::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
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
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	SetTimer(500, 30, NULL);
	return CDialog::OnNcActivate(bActive);
}
