#if !defined(AFX_DOUGA_H__27DB31FC_C694_448B_A81D_4F617F04BC9C__INCLUDED_)
#define AFX_DOUGA_H__27DB31FC_C694_448B_A81D_4F617F04BC9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Douga.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CDouga フレーム

class CDouga : public CFrameWnd
{
	DECLARE_DYNCREATE(CDouga)
protected:
	afx_msg void OnContextMenu(CWnd*, CPoint point);
public:
	CDouga();           // 動的生成に使用されるプロテクト コンストラクタ。
	BOOL Create(HWND);
	void play(int,CString str = L"");
	void plays(TCHAR* s);
	void plays2();
	void stops();
	void stop();
	void pause(int a);
	void seek(LONGLONG l);
	int SeekPoint(int file_bytes, float percent);
	void Filtersdown(IGraphBuilder *pGraph,WCHAR *filter=NULL);
	void Filtervideooff(IGraphBuilder *pGraph,WCHAR *filter=NULL);
	void Filtervideooff2(IGraphBuilder *pGraph, WCHAR *filter = NULL);
	void Filtervideooff3(IGraphBuilder *pGraph, WCHAR *filter = NULL);
	void Filtervideooff4(IGraphBuilder *pGraph);
	HRESULT EnumFilters (IGraphBuilder *pGraph,int no) ;
	BYTE toc[100];
	int filesize;
	double aa;
	CDC *cdc0,dc;
	CBitmap bmp;
	int pcnt;
// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDouga)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void PostNcDestroy();
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CDouga();

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDouga)
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnMenuitem32771();
	afx_msg void OnMenuitem32772();
	afx_msg void OnMenuitem32773();
	afx_msg void OnMenuitem32774();
	afx_msg void OnST1();
	afx_msg void OnST2();
	afx_msg void OnST3();
	afx_msg void OnST4();
	afx_msg void OnST5();
	afx_msg void OnST6();
	afx_msg void OnST7();
	afx_msg void OnST8();
	afx_msg void OnST9();
	afx_msg void OnST10();
	afx_msg void OnMV1();
	afx_msg void OnMV2();
	afx_msg void OnMV3();
	afx_msg void OnMV4();
	afx_msg void OnMV5();
	afx_msg void OnMV6();
	afx_msg void OnMV7();
	afx_msg void OnMV8();
	afx_msg void OnMV9();
	afx_msg void OnMV10();
	afx_msg void OnETC1();
	afx_msg void OnETC2();
	afx_msg void OnETC3();
	afx_msg void OnETC4();
	afx_msg void OnETC5();
	afx_msg void OnETC6();
	afx_msg void OnETC7();
	afx_msg void OnETC8();
	afx_msg void OnETC9();
	afx_msg void OnETC10();
	afx_msg void OnPaint();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
#if WIN64
	afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
	afx_msg void OnTimer(UINT nIDEvent);
#endif
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcRButtonDown(UINT nHitTest, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	afx_msg void On32775();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg void OnNcDestroy();
	afx_msg void OnNcRButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DOUGA_H__27DB31FC_C694_448B_A81D_4F617F04BC9C__INCLUDED_)
