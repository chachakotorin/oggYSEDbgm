// Ys12_2.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ogg.h"
#include "Ys12_2.h"


// CYs12_2 ダイアログ

IMPLEMENT_DYNAMIC(CYs12_2, CDialog)

CYs12_2::CYs12_2(CWnd* pParent /*=NULL*/)
	: CDialog(CYs12_2::IDD, pParent)
{

}

CYs12_2::~CYs12_2()
{
}

void CYs12_2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CYs12_2, CDialog)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
END_MESSAGE_MAP()


// CYs12_2 メッセージ ハンドラ
extern CString fnn;

char tiy122[][128]={
"01ys248 TO MAKE THE END OF BATTLE",
"02ys236 LILIA",
"03ys205 TOO FULL WITH LOVE",
"04ys225 APATHETIC STORY",
"05ys226 MAY I HELP YOU",
"06ys228 FEEL BLUE",
"07ys201 RUINS OF MOONDORIA",
"08ys220 NOBLE DISTRICT OF TOAL",
"09ys249 REST IN PEACE",
"10ys241 CAVERN OF RASTEENIE",
"11ys244 PROTECTERS",
"12ys242 ICE RIDGE OF NOLTIA",
"13ys203 INSIDE OF THE ICE WALL",
"14ys243 MOAT OF BURNEBLESS",
"15ys232 TENDER PEOPLE",
"16ys240 PALACE OF SALMON",
"17ys233 SUBTERRANEAN CANAL",
"18ys245 COMPANILE OF LANE",
"19ys223 PRESSURE ROAD",
"20ys235 DON'T GO SO SMOOTHLY!",
"21ys234 FEENA",
"22ys246 TERMINATION",
"23ys221 A STILL TIME",
"24ys207 STAY WITH ME FOREVER",
"25ys218 SO MUCH FOR TODAY",
"26ysn001COLONY OF LAVA",
"27ysi001OPEN YOUR HEART",
"28yss003FEENA",
"29ys124 BATTLE GROUND",
"30ys121 OVER DRIVE",
"31ys116 FAIR WIND",
"★オープニング1",
"★オープニング2"
};

CString CYs12_2::Gett(int a){
	CString s,ss;
	s=tiy122[a];
	ss=s.Left(8);ss.TrimRight();
	fnn=s.Mid(8);fnn.TrimRight();
	return ss;
}

/////////////////////////////////////////////////////////////////////////////
// CZWEIII メッセージ ハンドラ
void CYs12_2::OnDblclkList1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CString s;	s=tiy122[m_list.GetItemData(m_list.GetCurSel())];
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

BOOL CYs12_2::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	int dx;
	for(int i=0;i<(33);i++)
	{
		CString s;
		s=tiy122[i];if(s.Left(2)=="★"){}else{s="ZW2_";s=tiy122[i];}
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

