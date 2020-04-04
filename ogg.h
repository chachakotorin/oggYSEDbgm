// ogg.h : OGG アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_OGG_H__9EE5937A_A5CC_4F89_8C40_77FE882D687F__INCLUDED_)
#define AFX_OGG_H__9EE5937A_A5CC_4F89_8C40_77FE882D687F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// COggApp:
// このクラスの動作の定義に関しては ogg.cpp ファイルを参照してください。
//

class COggApp : public CWinApp
{
public:
	COggApp();
	void convert();
// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(COggApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(COggApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_OGG_H__9EE5937A_A5CC_4F89_8C40_77FE882D687F__INCLUDED_)
