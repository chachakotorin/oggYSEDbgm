// Ys12_1.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ogg.h"
#include "Ys12_1.h"


// CYs12_1 ダイアログ

IMPLEMENT_DYNAMIC(CYs12_1, CDialog)

CYs12_1::CYs12_1(CWnd* pParent /*=NULL*/)
	: CDialog(CYs12_1::IDD, pParent)
{

}

CYs12_1::~CYs12_1()
{
}

void CYs12_1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CYs12_1, CDialog)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
END_MESSAGE_MAP()


// CYs12_1 メッセージ ハンドラ
extern CString fnn;

char tiy121[][128]={
"YS1&2OP",
"ys100 Ys -Opening-",
"ys101 FEENA",
"ys102 FOUNTAIN OF LOVE",
"ys103 THE SYONIN",
"ys104 TEARS OF SYLPH",
"ys105 FIRST STEP TOWARDS WARS",
"ys106 PALACE",
"ys107 HOLDERS OF POWER",
"ys108 PALACE OF DESTRUCTION",
"ys109 BEAT OF THE TERROR",
"ys110 TOWER OF THE SHADOW OF DEATH",
"ys111 THE LAST MOMENT OF THE DARK",
"ys112 FINAL BATTLE",
"ys113 REST IN PEACE",
"ys114 THE MORNING GROW",
"ys115 SEE YOU AGAIN",
"ys134 DEVIL'S WIND",
"ys135 SO MUCH FOR TODAY",
"ys137 RODA",
"ys138 DEPARTURE",
"ys139 OPEN YOUR HEART",
"ys140 DREAMING",
"ys141 TENSION",
"ys142 CHASE OF SHADOW",
"★オープニング"
};

CString CYs12_1::Gett(int a){
	CString s,ss;
	s=tiy121[a];
	if(a!=0){
		ss=s.Left(5);ss.TrimRight();
	}else ss=s;
	fnn=s.Mid(6);
	return ss;
}

/////////////////////////////////////////////////////////////////////////////
// CZWEIII メッセージ ハンドラ
void CYs12_1::OnDblclkList1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CString s;	s=tiy121[m_list.GetItemData(m_list.GetCurSel())];
	if(m_list.GetItemData(m_list.GetCurSel())==0)
		ret=s;
	else{
		ret=s.Left(5); ret.TrimRight();
	}
	ret2=m_list.GetCurSel();
#if UNICODE
	if(s.Left(1)=="★"){
		fnn=s.Mid(1);
#else
	if(s.Left(2)=="★"){
		fnn=s.Mid(2);
#endif
	}else{
		if(m_list.GetItemData(m_list.GetCurSel())==0)
			fnn=s;
		else
			fnn=s.Mid(6);
	}
	EndDialog(1567);
}

BOOL CYs12_1::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	int dx;
	for(int i=0;i<(26);i++)
	{
		CString s;
		s=tiy121[i];if(s.Left(2)=="★"){}else{s="ZW2_";s=tiy121[i];}
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

