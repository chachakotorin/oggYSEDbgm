#if !defined(AFX_ITIRAN_YSO_H__F841A12C_910F_4514_A04E_E7F05AF189F1__INCLUDED_)
#define AFX_ITIRAN_YSO_H__F841A12C_910F_4514_A04E_E7F05AF189F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// itiran_YSO.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// Citiran_YSO ダイアログ

class Citiran_YSO : public CDialog
{
// コンストラクション
public:
	Citiran_YSO(CWnd* pParent = NULL);   // 標準のコンストラクタ
	int ret,ret2;

// ダイアログ データ
	//{{AFX_DATA(Citiran_YSO)
	enum { IDD = IDD_SENTAKU4 };
	CListBox	m_list;
	//}}AFX_DATA
	CString Gett(int a);

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(Citiran_YSO)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(Citiran_YSO)
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_ITIRAN_YSO_H__F841A12C_910F_4514_A04E_E7F05AF189F1__INCLUDED_)
