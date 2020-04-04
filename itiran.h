#if !defined(AFX_ITIRAN_H__4D82B777_FF66_428B_A3F1_2E5B6EF53309__INCLUDED_)
#define AFX_ITIRAN_H__4D82B777_FF66_428B_A3F1_2E5B6EF53309__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// itiran.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// itiran ダイアログ

class itiran : public CDialog
{
// コンストラクション
public:
	itiran(CWnd* pParent = NULL);   // 標準のコンストラクタ
	int ret,ret2;
	CString Gett(int a);
// ダイアログ データ
	//{{AFX_DATA(itiran)
	enum { IDD = IDD_SENTAKU };
	CListBox	m_list;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(itiran)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(itiran)
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_ITIRAN_H__4D82B777_FF66_428B_A3F1_2E5B6EF53309__INCLUDED_)
