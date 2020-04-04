#if !defined(AFX_ZWEIII_H__78625D67_3C5E_471E_B566_115BE87D76A5__INCLUDED_)
#define AFX_ZWEIII_H__78625D67_3C5E_471E_B566_115BE87D76A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZWEIII.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CZWEIII ダイアログ

class CZWEIII : public CDialog
{
// コンストラクション
public:
	CZWEIII(CWnd* pParent = NULL);   // 標準のコンストラクタ
	int ret,ret2;

// ダイアログ データ
	//{{AFX_DATA(CZWEIII)
	enum { IDD = IDD_SENTAKU6 };
	CListBox	m_list;
		// メモ: ClassWizard はこの位置にデータ メンバを追加します。
	//}}AFX_DATA
	CString Gett(int a);


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CZWEIII)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CZWEIII)
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_ZWEIII_H__78625D67_3C5E_471E_B566_115BE87D76A5__INCLUDED_)
