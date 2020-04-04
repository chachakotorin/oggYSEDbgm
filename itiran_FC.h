#if !defined(AFX_ITIRAN_FC_H__2D531ED5_FAAD_48BA_9B46_68C0E88F0F32__INCLUDED_)
#define AFX_ITIRAN_FC_H__2D531ED5_FAAD_48BA_9B46_68C0E88F0F32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// itiran_FC.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// Citiran_FC ダイアログ

class Citiran_FC : public CDialog
{
// コンストラクション
public:
	Citiran_FC(CWnd* pParent = NULL);   // 標準のコンストラクタ
	int ret,ret2;
	CString Gett(int a);
// ダイアログ データ
	//{{AFX_DATA(Citiran_FC)
	enum { IDD = IDD_SENTAKU1 };
	CListBox	m_list;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(Citiran_FC)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(Citiran_FC)
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_ITIRAN_FC_H__2D531ED5_FAAD_48BA_9B46_68C0E88F0F32__INCLUDED_)
