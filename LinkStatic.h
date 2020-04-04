#if !defined(AFX_LINKSTATIC_H__8E6FCCDA_144A_4380_9195_02E9428E656D__INCLUDED_)
#define AFX_LINKSTATIC_H__8E6FCCDA_144A_4380_9195_02E9428E656D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LinkStatic.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CLinkStatic ウィンドウ

class CLinkStatic : public CStatic
{
// コンストラクション
public:
	CLinkStatic();

// アトリビュート
public:

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CLinkStatic)
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CLinkStatic();

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CLinkStatic)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	void ReSetColor();
	BOOL m_bClick;		// リンク上でクリックされたかのフラグ
	HICON m_hCursor;	// 指のカーソルを保存
	CFont m_font;		// 下線を引いたフォントを設定する
	COLORREF m_text;	// 動的にリンクの色を変える為のカラー値
	CBrush m_brush;		// 色を設定する為のブラシ
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_LINKSTATIC_H__8E6FCCDA_144A_4380_9195_02E9428E656D__INCLUDED_)
