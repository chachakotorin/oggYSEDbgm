// XA.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ogg.h"
#include "XA.h"

extern CString fnn;
// CXA ダイアログ

IMPLEMENT_DYNAMIC(CXA, CDialog)

CXA::CXA(CWnd* pParent /*=NULL*/)
	: CDialog(CXA::IDD, pParent)
{

}

CXA::~CXA()
{
}

void CXA::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_LIST1, m_list);
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CXA, CDialog)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
END_MESSAGE_MAP()


// CXA メッセージ ハンドラ
char tixa[][128]={
"003 Two love",
"000 LA VALSE POUR XANADU～XANADU NEXT OPENING",
"004 Harlech",
"010 LA VALSE POUR XANADU～XANADU NEXT FIELD",
"030 The Eternal Maze",
"020 Clover Ruins",
"100 LA VALSE POUR XANADU～XANADU NEXT BATTLE",
"040 Egret Mountains",
"050 The Treacherous Woods",
"330 LA VALSE POUR XANADU～XANADU NEXT INTERMISSION",
"070 Xanadu Labyrinth",
"340 The One",
"080 Time Crevice",
"110 Bump in the road",
"090 The Castle of Strange Rock",
"320 Beginning of the Rock",
"200 Devil adent",
"210 evildoer",
"310 True Intent",
"001 Two love～Eternity",
"002 White Lie in Black",
"350 Two live～Requiem",
"300 LA VALSE POUR XANADU～XANADU NEXT EVENT",
"060 The Eternal Maze",
"★ファルコムロゴ",
"★オープニング"
};

CString CXA::Gett(int a){
	CString s,ss;
	s=tixa[a];ss=s.Left(3);
	switch(_tstoi(ss)){
		case 0: loop1=0; loop2=0; break;
		case 1: loop1=0; loop2=0; break;
		case 2: loop1=0; loop2=0; break;
		case 3: loop1=22016; loop2=5321728; break;
		case 4: loop1=472448; loop2=7228160; break;
		case 10: loop1=8704; loop2=6857728; break;
		case 20: loop1=3007904; loop2=8934944; break;
		case 30: loop1=284744; loop2=6593758; break;
		case 40: loop1=220584; loop2=8246875; break;
		case 50: loop1=654680; loop2=7419711; break;
		case 60: loop1=0; loop2=0; break;
		case 70: loop1=235472; loop2=6463247; break;
		case 80: loop1=1102500; loop2=3946951; break;
		case 90: loop1=789439; loop2=7420378; break;
		case 100: loop1=613590; loop2=5551813; break;
		case 110: loop1=203538; loop2=7140808; break;
		case 200: loop1=1130472; loop2=6374367; break;
		case 210: loop1=1310208; loop2=8083968; break;
		case 300: loop1=292864; loop2=5549568; break;
		case 310: loop1=2844816; loop2=8254598; break;
		case 320: loop1=271460; loop2=5728835; break;
		case 330: loop1=0; loop2=0; break;
		case 340: loop1=551531; loop2=5644011; break;
		case 350: loop1=21120; loop2=3056830; break;
		default: loop1=0; loop2=0; break;
	}
	fnn=s.Mid(4);
	return s;
}

/////////////////////////////////////////////////////////////////////////////
// CZWEIII メッセージ ハンドラ
void CXA::OnDblclkList1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CString s;	s=tixa[m_list.GetItemData(m_list.GetCurSel())];
	ret=_tstoi(s.Left(3));
	ret2=m_list.GetCurSel();
	switch(ret){
		case 0: loop1=0; loop2=0; break;
		case 1: loop1=0; loop2=0; break;
		case 2: loop1=0; loop2=0; break;
		case 3: loop1=22016; loop2=5321728; break;
		case 4: loop1=472448; loop2=7228160; break;
		case 10: loop1=8704; loop2=6857728; break;
		case 20: loop1=3007904; loop2=8934944; break;
		case 30: loop1=284744; loop2=6593758; break;
		case 40: loop1=220584; loop2=8246875; break;
		case 50: loop1=654680; loop2=7419711; break;
		case 60: loop1=0; loop2=0; break;
		case 70: loop1=235472; loop2=6463247; break;
		case 80: loop1=1102500; loop2=3946951; break;
		case 90: loop1=789439; loop2=7420378; break;
		case 100: loop1=613590; loop2=5551813; break;
		case 110: loop1=203538; loop2=7140808; break;
		case 200: loop1=1130472; loop2=6374367; break;
		case 210: loop1=1310208; loop2=8083968; break;
		case 300: loop1=292864; loop2=5549568; break;
		case 310: loop1=2844816; loop2=8254598; break;
		case 320: loop1=271460; loop2=5728835; break;
		case 330: loop1=0; loop2=0; break;
		case 340: loop1=551531; loop2=5644011; break;
		case 350: loop1=21120; loop2=3056830; break;
		default: loop1=0; loop2=0; break;
	}
	if(ret2>24)
		ret=ret2;
#if UNICODE
	if(s.Left(1)=="★"){
		fnn=s.Mid(1);
#else
	if(s.Left(2)=="★"){
		fnn=s.Mid(2);
#endif
	}else{
		fnn=s.Mid(4);
	}
	EndDialog(1567);
}

BOOL CXA::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	int dx;
	for(int i=0;i<26;i++)
	{
		CString s;
		s=tixa[i];if(s.Left(2)=="★"){}else{s="XANA";s+=tixa[i];}
		dx= m_list.AddString(s);
		m_list.SetItemData(dx,i);	
	}

	m_list.SetCurSel(0);
	if(ret!=0) 
//		if(ret>65) m_list.SetCurSel(ret);
//		else m_list.SetCurSel(ret-1);
		m_list.SetCurSel(ret);
	m_list.SetFocus();
	return FALSE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}
