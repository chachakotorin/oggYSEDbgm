// YsC2.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "ogg.h"
#include "YsC2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CYsC2 ダイアログ


CYsC2::CYsC2(CWnd* pParent /*=NULL*/)
	: CDialog(CYsC2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CYsC2)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}


void CYsC2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CYsC2)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CYsC2, CDialog)
	//{{AFX_MSG_MAP(CYsC2)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CYsC2 メッセージ ハンドラ
extern CString fnn;


char tiyc2[][128]={
"p_01ys2 [PC88] TO MAKE THE END OF BATTLE",
"p_02ys2 [PC88] LILIA",
"p_03ys2 [PC88] TOO FULL WITH LOVE",
"p_04ys2 [PC88] APATHETIC STORY",
"p_05ys2 [PC88] MAY I HELP YOU",
"p_06ys2 [PC88] FEEL BLUE",
"p_07ys2 [PC88] RUINS OF MOONDORIA",
"p_08ys2 [PC88] NOBLE DISTRICT OF TOAL",
"p_09ys2 [PC88] REST IN PEACE",
"p_10ys2 [PC88] CAVERN OF RASTEENIE",
"p_11ys2 [PC88] PROTECTERS",
"p_12ys2 [PC88] ICE RIDGE OF NOLTIA",
"p_13ys2 [PC88] INSIDE OF THE ICE WALL",
"p_14ys2 [PC88] MOAT OF BURNEBLESS",
"p_15ys2 [PC88] TENDER PEOPLE",
"p_16ys2 [PC88] PALACE OF SALMON",
"p_17ys2 [PC88] SUBTERRANEAN CANAL",
"p_18ys2 [PC88] COMPANILE OF LANE",
"p_19ys2 [PC88] PRESSURE ROAD",
"p_20ys2 [PC88] DON'T GO SO SMOOTHLY!",
"p_21ys2 [PC88] FEENA",
"p_22ys2 [PC88] TERMINATION",
"p_23ys2 [PC88] A STILL TIME",
"p_24ys2 [PC88] STAY WITH ME FOREVER",
"p_25ys2 [PC88] SO MUCH FOR TODAY",
"p_26ys2 [PC88] COLONY OF LAVA",
"p_27ys2 [PC88] OPEN YOUR HEART",
"p_28ys2 [PC88] FEENA",
"p_29ys2 [PC88] BATTLE GROUND",
"p_30ys2 [PC88] OVER DRIVE",
"p_31ys2 [PC88] FAIR WIND",
"o_01ys2 [Eternal] TO MAKE THE END OF BATTLE",
"o_02ys2 [Eternal] LILIA",
"o_03ys2 [Eternal] TOO FULL WITH LOVE",
"o_04ys2 [Eternal] APATHETIC STORY",
"o_05ys2 [Eternal] MAY I HELP YOU",
"o_06ys2 [Eternal] FEEL BLUE",
"o_07ys2 [Eternal] RUINS OF MOONDORIA",
"o_08ys2 [Eternal] NOBLE DISTRICT OF TOAL",
"o_09ys2 [Eternal] REST IN PEACE",
"o_10ys2 [Eternal] CAVERN OF RASTEENIE",
"o_11ys2 [Eternal] PROTECTERS",
"o_12ys2 [Eternal] ICE RIDGE OF NOLTIA",
"o_13ys2 [Eternal] INSIDE OF THE ICE WALL",
"o_14ys2 [Eternal] MOAT OF BURNEBLESS",
"o_15ys2 [Eternal] TENDER PEOPLE",
"o_16ys2 [Eternal] PALACE OF SALMON",
"o_17ys2 [Eternal] SUBTERRANEAN CANAL",
"o_18ys2 [Eternal] COMPANILE OF LANE",
"o_19ys2 [Eternal] PRESSURE ROAD",
"o_20ys2 [Eternal] DON'T GO SO SMOOTHLY!",
"o_21ys2 [Eternal] FEENA",
"o_22ys2 [Eternal] TERMINATION",
"o_23ys2 [Eternal] A STILL TIME",
"o_24ys2 [Eternal] STAY WITH ME FOREVER",
"o_25ys2 [Eternal] SO MUCH FOR TODAY",
"o_26ys2 [Eternal] COLONY OF LAVA",
"o_27ys2 [Eternal] OPEN YOUR HEART",
"o_28ys2 [Eternal] FEENA",
"o_29ys2 [Eternal] BATTLE GROUND",
"o_30ys2 [Eternal] OVER DRIVE",
"o_31ys2 [Eternal] FAIR WIND",
"01ys248 [Chronicles] TO MAKE THE END OF BATTLE",
"02ys236 [Chronicles] LILIA",
"03ys205 [Chronicles] TOO FULL WITH LOVE",
"04ys225 [Chronicles] APATHETIC STORY",
"05ys226 [Chronicles] MAY I HELP YOU",
"06ys228 [Chronicles] FEEL BLUE",
"07ys201 [Chronicles] RUINS OF MOONDORIA",
"08ys220 [Chronicles] NOBLE DISTRICT OF TOAL",
"09ys249 [Chronicles] REST IN PEACE",
"10ys241 [Chronicles] CAVERN OF RASTEENIE",
"11ys244 [Chronicles] PROTECTERS",
"12ys242 [Chronicles] ICE RIDGE OF NOLTIA",
"13ys203 [Chronicles] INSIDE OF THE ICE WALL",
"14ys243 [Chronicles] MOAT OF BURNEBLESS",
"15ys232 [Chronicles] TENDER PEOPLE",
"16ys240 [Chronicles] PALACE OF SALMON",
"17ys233 [Chronicles] SUBTERRANEAN CANAL",
"18ys245 [Chronicles] COMPANILE OF LANE",
"19ys223 [Chronicles] PRESSURE ROAD",
"20ys235 [Chronicles] DON'T GO SO SMOOTHLY!",
"21ys234 [Chronicles] FEENA",
"22ys246 [Chronicles] TERMINATION",
"23ys221 [Chronicles] A STILL TIME",
"24ys207 [Chronicles] In Adventure World",
"25ys218 [Chronicles] SO MUCH FOR TODAY",
"26ysn001[Chronicles] COLONY OF LAVA",
"27ysi001[Chronicles] OPEN YOUR HEART",
"28yss003[Chronicles] FEENA",
"29ys124 [Chronicles] BATTLE GROUND",
"30ys121 [Chronicles] OVER DRIVE",
"31ys116 [Chronicles] FAIR WIND",
"★オープニング[PC88]",
"★オープニング[Eternal]",
"★オープニング[Chronicles]",
"★エンディング1a[PC88]",
"★エンディング1a[Eternal]",
"★エンディング1a[Chronicles]",
"★エンディング1b[PC88]",
"★エンディング1b[Eternal]",
"★エンディング1b[Chronicles]"
};

CString CYsC2::Gett(int a){
	CString s,ss;
	s=tiyc2[a];
	ss=s.Left(8);ss.TrimRight();
	fnn=s.Mid(8);fnn.TrimRight();
	return ss;
}

/////////////////////////////////////////////////////////////////////////////
// CZWEIII メッセージ ハンドラ
void CYsC2::OnDblclkList1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CString s;	s=tiyc2[m_list.GetItemData(m_list.GetCurSel())];
	ret=s.Left(8); ret.TrimRight();
	ret2=m_list.GetCurSel();
#if UNICODE
	if(s.Left(1)=="★"){
		fnn=s.Mid(1);
#else
	if(s.Left(2)=="★"){
		fnn=s.Mid(2);
#endif
	}else{
		fnn=s.Mid(8);fnn.TrimRight();
	}
	EndDialog(1567);
}

BOOL CYsC2::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	int dx;
	for(int i=0;i<(102);i++)
	{
		CString s;
		s=tiyc2[i];if(s.Left(2)=="★"){}else{s="ZW2_";s=tiyc2[i];}
		dx= m_list.AddString(s);
		m_list.SetItemData(dx,i);	
	}

	m_list.SetCurSel(0);
	if(ret2!=0) 
//		if(ret>65) m_list.SetCurSel(ret);
//		else m_list.SetCurSel(ret-1);
		m_list.SetCurSel(ret2);
	m_list.SetFocus();
	return FALSE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}
