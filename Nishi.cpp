// Nishi.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ogg.h"
#include "Nishi.h"


// CNishi ダイアログ

IMPLEMENT_DYNAMIC(CNishi, CDialog)

CNishi::CNishi(CWnd* pParent /*=NULL*/)
	: CDialog(CNishi::IDD, pParent)
{

}

CNishi::~CNishi()
{
}

void CNishi::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CNishi, CDialog)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
END_MESSAGE_MAP()


// CNishi メッセージ ハンドラ
extern CString fnn;

char tinishi[][128]={
"z001 Brieging(ゼフィールファルコン作戦会議)",
"z002 COOL FIELD(フィールド山岳地帯)",
"z003 ディアブロ(ディアブロ第二段階)",
"z004 ゲイシルシティ(街)",
"z005 破壊神の鼓動(ディアブロ第一段階)",
"z006 インフェルノ(インフェルノ監獄(開放作戦))",
"z007 イオリーン(アンタリア創世記ヒロインのテーマ)",
"z008 Waltz de…(回想～バーンスタイン邸)",
"z009 街 Part1(村のテーマ)",
"z010 お別れイベントシーン(メルセデス)",
"z011 街 Part2(町のテーマ",
"z012 犠牲(悲しいイベント)",
"z013 …ドレイク？(海賊の襲撃)",
"z014 戦闘(通常戦闘)",
"z015 Zephyr Falcon(解放軍ゼフィールファルコン)",
"z016 The wind of Memory(シラノとメルセデスのピアノ曲)",
"z017 砂漠(砂漠)",
"z018 Aquamarine(最終ダンジョン～海底遺跡)",
"z019 魔剣阿修羅(阿修羅との戦い)",
"z020 Decisive Battle(ボスバトル)",
"z021 陰謀(イベントシーン(悪役専用))",
"z022 Force Field(解放戦争フィールド)",
"z023 FUZZY(スタッフロール)",
"z024 It's time to BATTLE!(ボスバトル2)",
"z025 PEACE(村)",
"z026 Precious Memories(シラノの想い出)",
"z027 Sorrowful…(イベント(大体が、誰かが死んだあと))",
"z028 Subway Crisis(ダンジョン)",
"z029 軍都市(緊迫した町のテーマ)",
"z030 目覚め(最終バトル直前)",
"z031 b-e natural(ダンジョン)",
"z032 チェザレ -part1-(チェザレのテーマ(オルガン))",
"z033 チェザレ -part2-(ラストバトル)",
"z034 Fireroad(契約)",
"z035 Forth step towards plain(フィールド・森など)",
"z036 THE GREAT REPEAT(ゲームタイトル画面)",
"z037 闇(インフェルノ地下)",
"z038 Jungle 2 Jungle(バース島)",
"z039 Not natural but natural(無限ループダンジョン)",
"z041 The wind of Memory（オーケストラ･ミックス）(エンディングテーマ)",
"z042 迷い(公爵屋敷)",
"z050 The wind of Memory（フレーズ）(ピアノ弾き)"
};


CString CNishi::Gett(int a){
	CString s,ss;
	s=tinishi[a];
	ss=s.Left(4);ss.TrimRight();
	fnn=s.Mid(5);
	return ss;
}

/////////////////////////////////////////////////////////////////////////////
// CZWEIII メッセージ ハンドラ
void CNishi::OnDblclkList1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CString s;	s=tinishi[m_list.GetItemData(m_list.GetCurSel())];
	ret=s.Left(4); ret.TrimRight();
	ret2=m_list.GetCurSel();
	if(s.Left(2)=="★"){
		fnn=s.Mid(2);
	}else{
		fnn=s.Mid(5);
	}
	EndDialog(1567);
}

BOOL CNishi::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	int dx;
	for(int i=0;i<(42);i++)
	{
		CString s;
		s=tinishi[i];if(s.Left(2)=="★"){}else{s="ZW2_";s=tinishi[i];}
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
