// itiran_YS6.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "ogg.h"
#include "itiran_YS6.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Citiran_YS6 ダイアログ

extern CString fnn;

Citiran_YS6::Citiran_YS6(CWnd* pParent /*=NULL*/)
	: CDialog(Citiran_YS6::IDD, pParent)
{
	//{{AFX_DATA_INIT(Citiran_YS6)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}


void Citiran_YS6::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Citiran_YS6)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Citiran_YS6, CDialog)
	//{{AFX_MSG_MAP(Citiran_YS6)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Citiran_YS6 メッセージ ハンドラ

char tiys6[][128]={
"01.タイトル/ロード",
"02.オープニング(動画あり)",
"03.Ｆｉｎ",
"04.レダの集落",
"05.ショップ",
"06.クアテラ樹海",
"07.中ボス一般",
"08.海底参道",
"09.リモージュの港町",
"10.カナン平原",
"11.グラナヴァリス",
"12.忘却の遺跡",
"13.ゼメスの聖地",
"14.鍾乳洞・地下湖",
"15.襲撃",
"16.占拠中",
"17.ロムン軍艦（通常）",
"18.ロムン軍艦（脱出）",
"19.アルマの墳墓",
"20.ガルヴァ＝ロア戦",
"21.エルンスト戦",
"22.ナピシュテムの匣,螺旋回廊",
"23.ナピ核戦<第１段階>（ラスボス）",
"24.ナピ核戦<第２段階>（ラスボス）",
"25.スタッフロール",
"26.ムービー1（渦消滅～ロムン襲来）(動画あり)",
"27.ムービー2（ナピ復活）(動画あり)",
"28.ムービー3（ナピ崩壊）(動画あり)",
"29.ムービー4（エンディング1）(動画あり)",
"30.ゲームオーバー",
"30.ゲームオーバー"
};

void Citiran_YS6::OnDblclkList1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CString s,ss;	s=tiys6[m_list.GetItemData(m_list.GetCurSel())];
	ss=s.Left(2);ret=_tstoi(ss)-1;
	fnn=s.Mid(3);
	EndDialog(1567);
}

void Citiran_YS6::Gett(int a){
	CString s,ss;
	s=tiys6[a];
	ss=s.Left(6);ss.TrimRight();
	fnn=s.Mid(3);
}

BOOL Citiran_YS6::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	int dx;
	for(int i=0;i<(30);i++)
	{
		CString s;
		s=tiys6[i];if(s.Left(2)=="★"){}else{s="ZW2_";s=tiys6[i];}
		dx= m_list.AddString(s);
		m_list.SetItemData(dx,i);	
	}

	m_list.SetCurSel(0);
	if(ret2!=0) 
		m_list.SetCurSel(ret2);
	m_list.SetFocus();

	m_list.SetCurSel(0);
	if(ret!=0) m_list.SetCurSel(ret);

	m_list.SetFocus();
	return FALSE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}
