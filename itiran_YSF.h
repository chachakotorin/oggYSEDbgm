#if !defined(AFX_ITIRAN_YSF_H__3564AC0B_9DC0_4586_8C9B_0E8A3E5B6421__INCLUDED_)
#define AFX_ITIRAN_YSF_H__3564AC0B_9DC0_4586_8C9B_0E8A3E5B6421__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// itiran_YSF.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// Citiran_YSF ダイアログ

class Citiran_YSF : public CDialog
{
// コンストラクション
public:
	Citiran_YSF(CWnd* pParent = NULL);   // 標準のコンストラクタ
	int ret,ret2;

// ダイアログ データ
	//{{AFX_DATA(Citiran_YSF)
	enum { IDD = IDD_SENTAKU2 };
	CListBox	m_list;
	//}}AFX_DATA
	void Gett(int a);

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(Citiran_YSF)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(Citiran_YSF)
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_ITIRAN_YSF_H__3564AC0B_9DC0_4586_8C9B_0E8A3E5B6421__INCLUDED_)
