#pragma once

#include "atlimage.h"
#include "afxwin.h"

// CMp3Image ダイアログ

class CMp3Image : public CDialog
{
	DECLARE_DYNAMIC(CMp3Image)

public:
	CMp3Image(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CMp3Image();
CWnd* m_pParent;
// ダイアログ データ
	enum { IDD = IDD_IMAGE };

	CDC dc,*cdc0,dcsub;
	CBitmap bmp,*bmpsub;
	CImage img;
	RECT rcm;
	double xx,yy,x1,y1_,xx1,yy1_;
	int nnn;
	void Load(CString s);

protected:
	HICON m_hIcon;
	int x,y;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg int Create(CWnd *pWnd);
	afx_msg void OnNcDestroy();
	
	afx_msg void OnBnClickedOk();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	CStatic m_x;
	CStatic m_y;
	CButton m_close;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};
