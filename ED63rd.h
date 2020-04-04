#if !defined(AFX_ED63RD_H__CAB5FA3D_0173_4137_ABBC_A52D8814CADE__INCLUDED_)
#define AFX_ED63RD_H__CAB5FA3D_0173_4137_ABBC_A52D8814CADE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ED63rd.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CED63rd ダイアログ

class CED63rd : public CDialog
{
// コンストラクション
public:
	CED63rd(CWnd* pParent = NULL);   // 標準のコンストラクタ
	int ret,ret2;
	CString Gett(int a);

// ダイアログ データ
	//{{AFX_DATA(CED63rd)
	enum { IDD = IDD_SENTAKU5 };
	CListBox	m_list;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CED63rd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CED63rd)
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_ED63RD_H__CAB5FA3D_0173_4137_ABBC_A52D8814CADE__INCLUDED_)
