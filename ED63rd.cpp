// ED63rd.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "ogg.h"
#include "ED63rd.h"

extern CString fnn;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CED63rd ダイアログ


CED63rd::CED63rd(CWnd* pParent /*=NULL*/)
	: CDialog(CED63rd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CED63rd)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}


void CED63rd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CED63rd)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CED63rd, CDialog)
	//{{AFX_MSG_MAP(CED63rd)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CED63rd メッセージ ハンドラ

char ti_3[][50]={
"001◆風を共に舞う気持ち SC Ver",
"020◆仄かに煌く光",
"021◆Cry for me, cry for you Opening version",
"022◆空を見上げて Ending version",
"024◆荒野にそびえし威容",
"100　地方都市ロレント",
"101　商業都市ボース",
"102　海港都市ルーアン",
"103　工房都市ツァイス",        
"104　王都グランセル",        
"105　陽だまりにて和む猫",        
"106　国境警備も楽じゃない",        
"107　王城",        
"108　グランアリーナ",
"110　ル＝ロックルへようこそ",
"111　灯火が消えた街",
"112　Heartless Surprise Attack",
"113　飛行戦艦グロリアス",
"120◆隠者の庭園",
"121◆紫苑の家",
"122◆御心のままに",
"123◆最後の選択",
"200　リベールの歩き方",        
"201　Secret Green Passage",        
"202　Rock on the Road",        
"210　空を見上げて",
"300　闇を彷徨う",        
"301　行く手をはばむ鋼の床",        
"302　暗がりがくれた安らぎ",        
"303　四輪の塔",        
"304　レイストン要塞",        
"305　虚ろなる光の封土",        
"310　隠された真の姿",
"311　潜入",
"312　浮遊都市リベルアーク",
"313　その先を目指して",
"314　中枢塔《アクシスピラー》",
"315　★効果音★",
"316　仲間の元へ",
"320◆翡翠回廊 ",
"321◆異界",
"322◆金の道、銀の道",
"323◆光と影の迷宮",
"324◆深淵",
"325◆幻影城 《Phantasmagoria》",
"330◆宵闇の王城",
"331◆動かぬ世界",
"332◆虎穴に入りて虎児を得よ",
"333◆幻影の蒼い花",
"334◆黒の方舟",
"400　Sophisticated Fight",        
"402　To be Suggestive",        
"403　銀の意志",        
"404　Challenger Invited",        
"405　Ancient Makes",        
"406　至宝を守護せしモノ",        
"407　撃破！！",        
"408　消え行く星",        
"410　ピンチ！！",        
"420　Strepitoso Fight",
"421　The Fate Of The Fairies",
"422　Obstructive Existence",
"423　Fight with Assailant",
"424　大いなる畏怖",
"425A Maybe It Was Fated Instrumental Ver.",
"426　Outskirts of Evolution",
"427　The Merciless Savior",
"428　雷の穿つ墓標",
"429　Feeling Danger Nearby",
"430◆Determination of Fight",
"431◆Fighting Right On",
"432◆Close to the Brink",
"433◆Overdosing Heavenly Bliss",
"434◆Genuine Devil",
"435◆夢と喧騒の聖地",
"436◆Banquet of frenzy",
"437◆Masquerade of Lies",
"438◆これが真の実力や！",
"439◆女神よ、お慈悲を・・・",
"440◆夢と喧騒の聖地(リトライ)",
"500　星の在り処 Harmonica short Ver.",        
"501　琥珀の愛 Hum Ver.",        
"502　琥珀の愛 Piano Ver.",        
"503　琥珀の愛 Lute Ver.",        
"504　星の在り処 Harmonica long Ver.",        
"505　賑やかに行こう",        
"510　去り行く決意",        
"511　暗躍する者たち",        
"512　奴を逃がすな！",        
"513　胸の中に",        
"514　月明りの下で",        
"516　忍び寄る危機",        
"517　俺達カプア一家！",        
"518　旅立ちの小径",        
"519　奪還",        
"520　呪縛からの解放、そして・・・",        
"521　告白",        
"522　黒のオーブメント",        
"523　リベールの誇り",        
"530　(劇)姫の悩み",        
"531　(劇)騎士達の嘆き",        
"532　(劇)それぞれの思惑",        
"533　(劇)城",        
"534　(劇)コロシアム",        
"535　(劇)決闘",        
"536　(劇)姫の死",        
"537　(劇)大団円",
"540　陰謀",
"541　執行者",
"542　福音計画",
"543　迫りくる脅威",
"544　ハーメル",
"546　うちひしがれて",
"547　荒野に潜む影",
"548　夢の続き",
"549　絆の在り処",
"550　銀の意志 Super Arrange Ver",
"551　星の在り処 Instrumental ver",
"552　Etude of the Ruin",
"554　惨劇の真相",
"556　夢幻",
"560◆飛行客船ルシタニア号",
"561◆強襲",
"562◆招かれざる者",
"563◆大切なもの",
"564◆追憶",
"565◆煉獄への階段",
"566◆影の王",
"567◆Cry for your Eternity",
"568◆想いの眠るゆりかご",
"569◆またいつか会うために",
"570◆君を忘れてた",
"571◆The Crimson Stigma",
"572◆星の扉14",
"573◆始まりの地",
"574◆レクルスの方石",
"581◆女神の機嫌は時の運",
"582◆爆釣王よ永遠に",
"583◆空の謎は軌跡でポン！",
"584◆山猫号反攻作戦",
"586◆Till the Night of Glory",
"★FALCOMロゴ動画",
"★オープニング動画",
"★エンディング動画",
"★動画1",
"★動画2",
"★動画3"
};
/**/

CString CED63rd::Gett(int a){
	CString s;
	s=ti_3[a];
	fnn=s.Mid(5);
	return s;
}

void CED63rd::OnDblclkList1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CString s;	s=ti_3[m_list.GetItemData(m_list.GetCurSel())];
	ret=_tstoi(s.Left(3));
	ret2=m_list.GetCurSel();
	if(ret2>141)
		ret=ret2;
#if UNICODE
	if(s.Left(1)=="★"){
		fnn=s.Mid(1);
#else
	if(s.Left(2)=="★"){
		fnn=s.Mid(2);
#endif
	}else{
		fnn=""; if(s.GetLength()>3)
			fnn=s.Mid(5);
	}
	EndDialog(1567);
}

BOOL CED63rd::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	int dx;
	for(int i=0;i<141+6;i++)
	{
		CString s;
		s=ti_3[i];
		if(s.Left(2)=="★"){}else
		{	s="ED6";
		s+=ti_3[i]; }
//		s+="";
/*		switch(ti[i][0])
		{
		case '0':
			s+="▼(タイトル)";
			break;
		case '1':
			s+="▼(町↓)";
			break;
		case '2':
			s+="▼(フィールド↓)";
			break;
		case '3':
			s+="▼(ダンジョン↓)";
			break;
		case '4':
			s+="▼(戦闘↓)";
			break;
		case '5':
			s+="▼(イベント↓)";
			break;
		}
*/		dx= m_list.AddString(s);
		m_list.SetItemData(dx,i);	
	}
//		dx= m_list.AddString("★FALCOMロゴ動画");
//		m_list.SetItemData(dx,98);	
//		dx= m_list.AddString("★オープニング動画");
//		m_list.SetItemData(dx,99);	

		m_list.SetCurSel(0);
	if(ret2!=0) m_list.SetCurSel(ret2);

	m_list.SetFocus();
	return FALSE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

