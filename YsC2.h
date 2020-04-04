#if !defined(AFX_YSC2_H__0F750E54_B5C3_450A_82BF_91EB2DB8D52A__INCLUDED_)
#define AFX_YSC2_H__0F750E54_B5C3_450A_82BF_91EB2DB8D52A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// YsC2.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CYsC2 ダイアログ

class CYsC2 : public CDialog
{
// コンストラクション
public:
	CYsC2(CWnd* pParent = NULL);   // 標準のコンストラクタ
	CString ret;
	int ret2;

// ダイアログ データ
	//{{AFX_DATA(CYsC2)
	enum { IDD = IDD_SENTAKU8 };
	CListBox	m_list;
	//}}AFX_DATA
	CString Gett(int a);


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CYsC2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CYsC2)
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_YSC2_H__0F750E54_B5C3_450A_82BF_91EB2DB8D52A__INCLUDED_)
