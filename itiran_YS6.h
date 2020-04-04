#if !defined(AFX_ITIRAN_YS6_H__9E3AF8B8_AFD3_4030_8920_18FBC884E1CA__INCLUDED_)
#define AFX_ITIRAN_YS6_H__9E3AF8B8_AFD3_4030_8920_18FBC884E1CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// itiran_YS6.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// Citiran_YS6 ダイアログ

class Citiran_YS6 : public CDialog
{
// コンストラクション
public:
	Citiran_YS6(CWnd* pParent = NULL);   // 標準のコンストラクタ
	int ret,ret2;

// ダイアログ データ
	//{{AFX_DATA(Citiran_YS6)
	enum { IDD = IDD_SENTAKU3 };
	CListBox	m_list;
	//}}AFX_DATA
	void Gett(int a);

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(Citiran_YS6)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(Citiran_YS6)
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_ITIRAN_YS6_H__9E3AF8B8_AFD3_4030_8920_18FBC884E1CA__INCLUDED_)
