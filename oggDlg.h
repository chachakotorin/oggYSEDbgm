// oggDlg.h : ヘッダー ファイル
//
#include "afxmt.h"
//#include "afxcmn.h"

#if !defined(AFX_OGGDLG_H__6E748E56_5CF6_4ADE_8B4F_7FE83E42DCFA__INCLUDED_)
#define AFX_OGGDLG_H__6E748E56_5CF6_4ADE_8B4F_7FE83E42DCFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/////////////////////////////////////////////////////////////////////////////
// COggDlg ダイアログ
#include "LinkStatic.h"
#include "afxwin.h"
#include "afxcmn.h"

class COggDlg : public CDialog
{
// 構築
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	COggDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

	void gamen(int uu);
	void gamenkill();
	void dougaplay(int uu,CString str = L"");
	DWORD GetVol();
	void Speana();
	void moji(CString s,int x,int y,COLORREF rgb);
	int  mojisub(CString s,int x,int y,COLORREF rgb);
	CString UTF8toSJIS(const char* a);
	CString UTF8toUNI(const TCHAR* a);
	void Resize();
	void Closeds();
	void timerp();
	void Vol(int vol);
	void dp(CString a);
	LRESULT dp1(WPARAM, LPARAM);
	LRESULT dp2(WPARAM, LPARAM);
	void SetAdd(CString fnn,int mode,int loop1,int loop2,CString filen,int ret2,REFTIME time);

	CString mp3file;
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	IMMDeviceEnumerator *deve;
	IMMDevice *dev;
	IAudioEndpointVolume *audio;
	void dsdload(CString&filen, CString&tagfile, CString&tagname, CString&tagalbum, ULONGLONG&po, int flg);
	void dsdclose();
	BOOL ReleaseDXSound();
	CString init(HWND hwnd,int sm=44100);
	int WASAPIInit();
	void WASAPIChange(WAVEFORMATEX* pwfx);
	static UINT wavread(LPVOID);
	CEvent timer;
#if _UNICODE
	void _CreateShellLink(LPWSTR pszArguments, LPWSTR pszTitle, IShellLink **ppsl, int iconindex, bool WA,BOOL wa2=TRUE);
#else
	void _CreateShellLink(LPSTR pszArguments, LPSTR pszTitle, IShellLink **ppsl, int iconindex, bool WA,BOOL wa2=TRUE);
#endif
	CBrush *m_pDlgColor;


	KMPMODULE *mod;
	HKMP kmp,kmp1;
	HINSTANCE hDLLk;
	pfnGetKMPModule pFunck;
	SOUNDINFO sikpi;
	TCHAR kpi[512];

	CBrush m_brDlg;

	CFont* m_newFont;
	CFont* m_newFont1;
	// ダイアログ データ
	//{{AFX_DATA(COggDlg)
	enum { IDD = IDD_OGG_DIALOG };
	CButton	m_ysc2;
	CButton	m_ysc1;
	CStatic	m_dsvols;
	CSliderCtrl	m_dsval;
	CButton	m_zweiii;
	CButton	m_ed6tc;
	CButton	m_yso;
	CSliderCtrl	m_time;
	CEdit	m_kaisuu;
	CButton	m_junji;
	CButton	m_random;
	CButton	m_sita;
	CButton	m_ue;
	CButton	m_ed6sc;
	CButton	m_ed6fc;
	CButton	m_ysf;
	CButton	m_ys6;
	CButton	m_st;
	CButton	m_supe;
	CStatic	m_sokudos;
	CStatic	m_onteis;
	CSliderCtrl	m_sokudo;
	CSliderCtrl	m_ontei;
	CButton	m_ps;
	CStatic	m_vol;
	CSliderCtrl	m_sl;
	CButton	m_dou;
	CButton	m_c2;
	CStatic	m_11;
	//}}AFX_DATA
	void play();
	void stop();
	void stop1();
	static void Modec();
CWinThread * m_thread;
CWinThread* m_thread1;
	void rl(int);
	afx_msg void OnPause();
	void plug(CString ff,KMPMODULE *mod);
	void plugloop(CString ff);
//	void mcopy(char* a,char* b,int len);
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(COggDlg)
	public:
	virtual BOOL DestroyWindow();
	afx_msg void OnRestart();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL
// インプリメンテーション
protected:
	CToolTipCtrl m_tooltip;
	HICON m_hIcon;
	int randomf;
	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(COggDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDropFiles(HDROP hDropInfo);
#if WIN64
	afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
	afx_msg void OnTimer(UINT nIDEvent);
#endif
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	virtual void OnOK();
	afx_msg void OnButton5();
	afx_msg void OnButton6_FC();
	afx_msg void OnButton7_YSF();
	afx_msg void OnButton8_YS6();
	afx_msg void OnButton9_Folder();
	afx_msg void OnButton12();
	afx_msg void OnCheck5();
	afx_msg void OnCheck6();
	afx_msg void OnButton14();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnYso();
	afx_msg void OnButton17_ED6TC();
	afx_msg void OnZWEIII();
	afx_msg void OnButton21();
	afx_msg void OnYsC1();
	afx_msg void OnYsC2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton25();
	CButton m_xa;
	afx_msg void OnBnClickedButton27();
	afx_msg void OnBnClickedButton28();
	afx_msg void OnBnClickedButton31();
	CButton m_ys121;
	CButton m_ys122;
	CButton m_sor;
	afx_msg void OnBnClickedButton33();
	CButton m_zwei;
	CButton m_gurumin;
	afx_msg void OnBnClickedButton35();
	CButton m_rund;
	afx_msg void OnBnClickedButton37();
	CButton m_dino;
	CButton m_saisai;
	afx_msg void OnNMReleasedcaptureSlider2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton39();
	CButton m_br4;
	afx_msg void OnBnClickedButton44();
	afx_msg void OnBnClickedButton45();
	afx_msg void OnBnClickedButton46();
	CButton m_ed3;
	CButton m_ed4;
	CButton m_ed5;
	CButton d_ys6;
	CButton d_ys3;
	CButton d_yso;
	CButton d_ed6fc;
	CButton d_ed6sc;
	CButton d_ed6tc;
	CButton d_z2;
	CButton d_ysc1;
	CButton d_ysc2;
	CButton d_xa;
	CButton d_ys1;
	CButton d_ys2;
	CButton d_sor;
	CButton d_z1;
	CButton d_guru;
	CButton d_dino;
	CButton d_br4;
	CButton d_ed3;
	CButton d_ed4;
	CButton d_ed5;
	afx_msg void OnBnClickedButton47();
	CButton d_tuki;
	CButton d_nishi;
	afx_msg void OnBnClickedButton48();
	CButton d_arc;
	afx_msg void OnBnClickedButton51();
	CButton d_san1;
	afx_msg void OnBnClickedButton53();
	CButton d_san2;
	afx_msg void OnBnClickedButton54();
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	LRESULT OnHotKey(WPARAM wp, LPARAM);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CButton m_playlist;
	afx_msg void OnPlayList();
	afx_msg void OnBnmp3jake();
	CButton m_mp3jake;
	CStatic m_OS;
	CSliderCtrl m_kakuVol;
	CStatic m_kakuVolval;
	CStatic m_cpu;

	CStatic m_os3;
	afx_msg void OnDestroy();
	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_OGGDLG_H__6E748E56_5CF6_4ADE_8B4F_7FE83E42DCFA__INCLUDED_)
