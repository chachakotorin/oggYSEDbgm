#if !defined(AFX_YSC1_H__4CC2A54C_7DB6_4129_A70B_423BDF1B3A05__INCLUDED_)
#define AFX_YSC1_H__4CC2A54C_7DB6_4129_A70B_423BDF1B3A05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// YsC1.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CYsC1 ダイアログ

class CYsC1 : public CDialog
{
// コンストラクション
public:
	CYsC1(CWnd* pParent = NULL);   // 標準のコンストラクタ
	CString ret;
	int ret2;

// ダイアログ データ
	//{{AFX_DATA(CYsC1)
	enum { IDD = IDD_SENTAKU7 };
	CListBox	m_list;
	//}}AFX_DATA
	CString Gett(int a);


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CYsC1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CYsC1)
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_YSC1_H__4CC2A54C_7DB6_4129_A70B_423BDF1B3A05__INCLUDED_)
