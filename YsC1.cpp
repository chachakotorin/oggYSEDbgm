// YsC1.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "ogg.h"
#include "YsC1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CYsC1 ダイアログ


CYsC1::CYsC1(CWnd* pParent /*=NULL*/)
	: CDialog(CYsC1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CYsC1)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}


void CYsC1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CYsC1)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CYsC1, CDialog)
	//{{AFX_MSG_MAP(CYsC1)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CYsC1 メッセージ ハンドラ
extern CString fnn;


char tiyc1[][128]={
"p_00ys1 [PC88] Ys -Opening-",
"p_01ys1 [PC88] FEENA",
"p_02ys1 [PC88] FOUNTAIN OF LOVE",
"p_03ys1 [PC88] THE SYONIN",
"p_04ys1 [PC88] TEARS OF SYLPH",
"p_05ys1 [PC88] FIRST STEP TOWARDS WARS",
"p_06ys1 [PC88] PALACE",
"p_07ys1 [PC88] HOLDERS OF POWER",
"p_08ys1 [PC88] PALACE OF DESTRUCTION",
"p_09ys1 [PC88] BEAT OF THE TERROR",
"p_10ys1 [PC88] TOWER OF THE SHADOW OF DEATH",
"p_11ys1 [PC88] THE LAST MOMENT OF THE DARK",
"p_12ys1 [PC88] FINAL BATTLE",
"p_13ys1 [PC88] REST IN PEACE",
"p_14ys1 [PC88] THE MORNING GROW",
"p_15ys1 [PC88] SEE YOU AGAIN",
"p_34ys1 [PC88] DEVIL'S WIND",
"p_35ys1 [PC88] SO MUCH FOR TODAY",
"p_37ys1 [PC88] RODA",
"p_38ys1 [PC88] DEPARTURE",
"p_39ys1 [PC88] OPEN YOUR HEART",
"p_40ys1 [PC88] DREAMING",
"p_41ys1 [PC88] TENSION",
"p_42ys1 [PC88] CHASE OF SHADOW",
"o_00ys1 [Eternal] Ys -Opening-",
"o_01ys1 [Eternal] FEENA",
"o_02ys1 [Eternal] FOUNTAIN OF LOVE",
"o_03ys1 [Eternal] THE SYONIN",
"o_04ys1 [Eternal] TEARS OF SYLPH",
"o_05ys1 [Eternal] FIRST STEP TOWARDS WARS",
"o_06ys1 [Eternal] PALACE",
"o_07ys1 [Eternal] HOLDERS OF POWER",
"o_08ys1 [Eternal] PALACE OF DESTRUCTION",
"o_09ys1 [Eternal] BEAT OF THE TERROR",
"o_10ys1 [Eternal] TOWER OF THE SHADOW OF DEATH",
"o_11ys1 [Eternal] THE LAST MOMENT OF THE DARK",
"o_12ys1 [Eternal] FINAL BATTLE",
"o_13ys1 [Eternal] REST IN PEACE",
"o_14ys1 [Eternal] THE MORNING GROW",
"o_15ys1 [Eternal] SEE YOU AGAIN",
"o_34ys1 [Eternal] DEVIL'S WIND",
"o_35ys1 [Eternal] SO MUCH FOR TODAY",
"o_37ys1 [Eternal] RODA",
"o_38ys1 [Eternal] DEPARTURE",
"o_39ys1 [Eternal] OPEN YOUR HEART",
"o_40ys1 [Eternal] DREAMING",
"o_41ys1 [Eternal] TENSION",
"o_42ys1 [Eternal] CHASE OF SHADOW",
"ys100_44 [Chronicles] Ys -Opening-",
"ys101_44 [Chronicles] FEENA",
"ys102_44 [Chronicles] FOUNTAIN OF LOVE",
"ys103_44 [Chronicles] THE SYONIN",
"ys104_44 [Chronicles] TEARS OF SYLPH",
"ys105_44 [Chronicles] FIRST STEP TOWARDS WARS",
"ys106_44 [Chronicles] PALACE",
"ys107_44 [Chronicles] HOLDERS OF POWER",
"ys108_44 [Chronicles] PALACE OF DESTRUCTION",
"ys109_44 [Chronicles] BEAT OF THE TERROR",
"ys110_44 [Chronicles] TOWER OF THE SHADOW OF DEATH",
"ys111_44 [Chronicles] THE LAST MOMENT OF THE DARK",
"ys112_44 [Chronicles] FINAL BATTLE",
"ys113_44 [Chronicles] REST IN PEACE",
"ys114_44 [Chronicles] THE MORNING GROW",
"ys115_44 [Chronicles] Victory!!",
"ys134_44 [Chronicles] DEVIL'S WIND",
"ys135_44 [Chronicles] SO MUCH FOR TODAY",
"ys137_44 [Chronicles] RODA",
"ys138_44 [Chronicles] DEPARTURE",
"ys139_44 [Chronicles] OPEN YOUR HEART",
"ys140_44 [Chronicles] DREAMING",
"ys141_44 [Chronicles] TENSION",
"ys142_44 [Chronicles] CHASE OF SHADOW",
"★オープニング[PC88]",
"★オープニング[Eternal]",
"★オープニング[Chronicles]"
};

CString CYsC1::Gett(int a){
	CString s,ss;
	s=tiyc1[a];
	ss=s.Left(8);ss.TrimRight();
	fnn=s.Mid(8); fnn.TrimRight();
	return ss;
}

/////////////////////////////////////////////////////////////////////////////
// CZWEIII メッセージ ハンドラ
void CYsC1::OnDblclkList1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CString s;	s=tiyc1[m_list.GetItemData(m_list.GetCurSel())];
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
		fnn=s.Mid(8); fnn.TrimRight();
	}
	EndDialog(1567);
}

BOOL CYsC1::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	int dx;
	for(int i=0;i<(75);i++)
	{
		CString s;
		s=tiyc1[i];if(s.Left(2)=="★"){}else{s="ZW2_";s=tiyc1[i];}
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
