#pragma once
#include "afxwin.h"
#include "BtnST.h"
#include "afxcmn.h"
// CPlayList ダイアログ

struct playlistdata{
	TCHAR name[1024];
	TCHAR art[1024];
	TCHAR alb[1024];
	TCHAR fol[1024];
	int sub;
	int loop1;
	int loop2;
	int ret2;
	int time;
	int res2;
};

#include "ListCtrlA.h"

class CPlayList : public CDialog
{
	DECLARE_DYNAMIC(CPlayList)

public:
	CPlayList(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CPlayList();
	CWnd* m_pParent;
// ダイアログ データ
	enum { IDD = IDD_PLAYLIST };
	CImageList il;
	playlistdata0 *pc;
	void OnList();
	int nnn;
	int pnt,pnt1;

	void SIcon(int i);
	void SIconTimer(int i);
	int Add(CString name,int sub,int loop1,int loop2,CString art,CString alb,CString fol,int ret,int time,BOOL f=TRUE,BOOL ff=TRUE);
	void Del();
	void Load();
	void Save();
	int chk(CString name,int sub,CString art,CString fol,int ret);
	void Fol(CString fname);
	void plug(CString ff,KMPMODULE *mod);
	void plugs(CString ext1,playlistdata *p,TCHAR* kpi);
	void Get(int i);

	void OnDrag(int x,int y);
	void OnEndDrag();
	void OnXCHG(int i,int j);
	int m_lDragTopItem;
	int m_lDragTopItemt;
	HIMAGELIST  m_hDragImage;
	BOOL w_flg;


	HICON m_hIcon;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	CToolTipCtrl m_tooltip;

	DECLARE_MESSAGE_MAP()
public:

	CString UTF8toSJIS(const char* a);
	CString UTF8toUNI(const TCHAR* a);

	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CButtonST m_lsup;
	CButtonST m_lup;
	CButtonST m_lsdown;
	CButtonST m_ldown;
	afx_msg void OnNcDestroy();
	virtual BOOL DestroyWindow();
	afx_msg int Create(CWnd *pWnd);
	afx_msg void OnClose();
	afx_msg void OnBnClickedOk();
	CListCtrlA m_lc;
	afx_msg void OnUP();
	afx_msg void OnSUP();
	afx_msg void OnSDOWN();
	afx_msg void OnDOWN();
	afx_msg void OnLvnKeydownList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
#if WIN64
	afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
	afx_msg void OnTimer(UINT nIDEvent);
#endif
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	CEdit m_e;
	CButton m_renzoku;
	CButton m_loop;
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnBnClickedCheck1();
	CButton m_tool;
	afx_msg void OnLvnBegindragList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLvnGetdispinfoList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	CButton m_saisyo;
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnPop32787();
	CEdit m_find;
	afx_msg void OnFindUp();
	afx_msg void OnFindDown();
	CButtonST m_findup;
	CButtonST m_finddown;
	CButton m_savecheck;
	CButton m_save_mp3;
	CButton m_save_kpi;
	afx_msg void OnBnClickedCheck6mp3();
	afx_msg void OnBnClickedCheck7dshow();
};
