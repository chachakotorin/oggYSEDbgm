#include "afxdialogex.h"
#include "afxwin.h"
#include "afxcmn.h"
#if !defined(AFX_RENDER_H__F5FB1AA1_8545_4B26_80A3_4E0FA43C0548__INCLUDED_)
#define AFX_RENDER_H__F5FB1AA1_8545_4B26_80A3_4E0FA43C0548__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Render.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CRender ダイアログ

class CRender : public CDialogEx
{
// コンストラクション
public:
	CRender(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CRender)
	enum { IDD = IDD_Render };
	CComboBox	m_1;
	//}}AFX_DATA
	DECLARE_DYNAMIC(CRender);

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CRender)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

	BOOL MySetFileType(LPCTSTR lpExt, LPCTSTR lpDocName, LPCTSTR lpDocType, LPCTSTR lpPath, LPCTSTR lpPath1);
	static BOOL CALLBACK DSEnumCallback(LPGUID p_guid, LPCWSTR psz_desc, LPCWSTR psz_mod, LPVOID data);
// インプリメンテーション
protected:
	CToolTipCtrl m_tooltip;
	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CRender)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CButton m_evr;
	virtual INT_PTR OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CButton m_con;
	CButton m_a;
	CButton m_ffd;
	afx_msg void OnBnClickedCancel2();
	CButton m_l;
	CButton m_vob;
	CButton m_haali;
	afx_msg void Onspc2x();
	afx_msg void Onspc4x();
	afx_msg void Onspc8x();
	CButton m_spc2x;
	CButton m_spc4x;
	CButton m_spc8x;
	afx_msg void Onspc1x();
	CButton m_spc1x;
	afx_msg void Onspc16x();
	CButton m_spc16x;
	CButton m_mp31;
	CButton m_mp315;
	CButton m_mp32;
	CButton m_mp325;
	CButton m_mp33;
	afx_msg void Onmp31();
	afx_msg void Onmp315();
	afx_msg void Onmp32();
	afx_msg void Onmp325();
	afx_msg void Onmp33();
	CButton m_kpi10;
	CButton m_kpi15;
	CButton m_kpi20;
	CButton m_kpi25;
	CButton m_kpi30;
	afx_msg void Onkpi10();
	afx_msg void Onkpi15();
	afx_msg void Onkpi20();
	afx_msg void Onkpi25();
	afx_msg void Onkpi30();
	afx_msg void Onkpi();
	CButton m_kpi;
	afx_msg void OnFontMain();
	afx_msg void OnFontList();
	CButton m_mp3orig;
	CButton m_audiost;
	CButton m_24;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClicked24bit();
	CButton m_m4a;
	afx_msg void OnBnClickedCheck50();
	afx_msg void OnBnClickedCancel4();
	CButton m_32bit;
	CSliderCtrl m_ms;
	CStatic m_ms2;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CSliderCtrl m_hyouji2;
	CStatic m_hyouji3;
	CComboBox m_soundlist;
	afx_msg void OnCbnSelchangeCombo2();
	CButton m_ao;
	afx_msg void OnBnClickedButton1();
	CComboBox m_Hz;
	afx_msg void OnCbnSelchangeCombo3();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_RENDER_H__F5FB1AA1_8545_4B26_80A3_4E0FA43C0548__INCLUDED_)
