// itiran.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "ogg.h"
#include "itiran.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// itiran ダイアログ

extern CString fnn;
itiran::itiran(CWnd* pParent /*=NULL*/)
	: CDialog(itiran::IDD, pParent)
{
	//{{AFX_DATA_INIT(itiran)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}


void itiran::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(itiran)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(itiran, CDialog)
	//{{AFX_MSG_MAP(itiran)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// itiran メッセージ ハンドラ

char ti[][50]={
"001 --/SC 風を共に舞う気持ち SC Ver",
"010 --/SC Shine of Eidos ～空の軌跡～",
"011 --/SC OP 銀の意志 金の翼/山脇宏子",
"012 --/SC ED I swear.../小寺可南子",
"015 --/SC 解き放たれた至宝",
"016 --/SC 女神の御許へ",
"017 --/SC 折られた翼",
"018 --/SC 希望の行方",
"100 FC/SC 地方都市ロレント",
"101 FC/SC 商業都市ボース",
"102 FC/SC 海港都市ルーアン",
"103 FC/SC 工房都市ツァイス",        
"104 FC/SC 王都グランセル",        
"105 FC/SC 陽だまりにて和む猫",        
"106 FC/SC 国境警備も楽じゃない",        
"107 FC/SC 王城",        
"108 FC/SC グランアリーナ",
"110 --/SC ル＝ロックルへようこそ",
"111 --/SC 灯火が消えた街",
"112 --/SC Heartless Surprise Attack",
"113 --/SC 飛行戦艦グロリアス",
"200 FC/-- リベールの歩き方",        
"201 FC/SC Secret Green Passage",        
"202 FC/SC Rock on the Road",        
"210 --/SC 空を見上げて",
"300 FC/SC 闇を彷徨う",        
"301 FC/SC 行く手をはばむ鋼の床",        
"302 FC/SC 暗がりがくれた安らぎ",        
"303 FC/SC 四輪の塔",        
"304 FC/SC レイストン要塞",        
"305 FC/-- 虚ろなる光の封土",        
"310 --/SC 隠された真の姿",
"311 --/SC 潜入",
"312 --/SC 浮遊都市リベルアーク",
"313 --/SC その先を目指して",
"314 --/SC 中枢塔《アクシスピラー》",
"315 --/SC ★効果音★",
"316 --/SC 仲間の元へ",
"400 FC/-- Sophisticated Fight",        
"402 FC/SC To be Suggestive",        
"403 FC/SC 銀の意志",        
"404 FC/SC Challenger Invited",        
"405 FC/-- Ancient Makes",        
"406 FC/-- 至宝を守護せしモノ",        
"407 FC/SC 撃破！！",        
"408 FC/SC 消え行く星",        
"410 FC/SC ピンチ！！",        
"420 --/SC Strepitoso Fight",
"421 --/SC The Fate Of The Fairies",
"422 --/SC Obstructive Existence",
"423 --/SC Fight with Assailant",
"424 --/SC 大いなる畏怖",
"425 --/SC Fateful confrontation",
"426 --/SC Outskirts of Evolution",
"427 --/SC The Merciless Savior",
"428 --/SC 雷の穿つ墓標",
"429 --/SC Feeling Danger Nearby",
"500 FC/SC 星の在り処 Harmonica short Ver.",        
"501 FC/-- 琥珀の愛 Hum Ver.",        
"502 FC/-- 琥珀の愛 Piano Ver.",        
"503 FC/-- 琥珀の愛 Lute Ver.",        
"504 FC/-- 星の在り処 Harmonica long Ver.",        
"505 FC/SC 賑やかに行こう",        
"510 FC/SC 去り行く決意",        
"511 FC/SC 暗躍する者たち",        
"512 FC/-- 奴を逃がすな！",        
"513 FC/SC 胸の中に",        
"514 FC/SC 月明りの下で",        
"516 FC/SC 忍び寄る危機",        
"517 FC/-- 俺達カプア一家！",        
"518 FC/-- 旅立ちの小径",        
"519 FC/SC 奪還",        
"520 FC/-- 呪縛からの解放、そして・・・",        
"521 FC/SC 告白",        
"522 FC/SC 黒のオーブメント",        
"523 FC/SC リベールの誇り",        
"530 FC/-- (劇)姫の悩み",        
"531 FC/-- (劇)騎士達の嘆き",        
"532 FC/-- (劇)それぞれの思惑",        
"533 FC/-- (劇)城",        
"534 FC/-- (劇)コロシアム",        
"535 FC/-- (劇)決闘",        
"536 FC/-- (劇)姫の死",        
"537 FC/-- (劇)大団円",
"540 --/SC 陰謀",
"541 --/SC 執行者",
"542 --/SC 福音計画",
"543 --/SC 迫りくる脅威",
"544 --/SC ハーメル",
"546 --/SC うちひしがれて",
"547 --/SC 荒野に潜む影",
"548 --/SC 夢の続き",
"549 --/SC 絆の在り処",
"550 --/SC 銀の意志 Super Arrange Ver",
"551 --/SC 星の在り処 Instrumental ver",
"552 --/SC Etude of the Ruin",
"554 --/SC 惨劇の真相",
"556 --/SC 夢幻",
"★FALCOMロゴ動画",
"★オープニング動画",
"★エンディング動画",
"★動画1",
"★動画2",
"★動画3",
"★動画4",
"★動画5",
"★動画6",
"★動画7"
};
/**/

CString itiran::Gett(int a){
	CString s;
	s=ti[a];
	fnn=s.Mid(10);
	return s;
}

void itiran::OnDblclkList1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CString s;	s=ti[m_list.GetItemData(m_list.GetCurSel())];
	ret=_tstoi(s.Left(3));
	ret2=m_list.GetCurSel();
	if(ret2>97)
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
			fnn=s.Mid(10);
	}
	EndDialog(1567);
}

BOOL itiran::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	int dx;
	for(int i=0;i<98;i++)
	{
		CString s;
		s="ED6";
		s+=ti[i];
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
		dx= m_list.AddString(_T("★FALCOMロゴ動画"));
		m_list.SetItemData(dx,98);	
		dx= m_list.AddString(_T("★オープニング動画"));
		m_list.SetItemData(dx,99);	
		dx= m_list.AddString(_T("★エンディング動画"));
		m_list.SetItemData(dx,100);	
		dx= m_list.AddString(_T("★動画1"));
		m_list.SetItemData(dx,101);	
		dx= m_list.AddString(_T("★動画2"));
		m_list.SetItemData(dx,102);	
		dx= m_list.AddString(_T("★動画3"));
		m_list.SetItemData(dx,103);	
		dx= m_list.AddString(_T("★動画4"));
		m_list.SetItemData(dx,104);	
		dx= m_list.AddString(_T("★動画5"));
		m_list.SetItemData(dx,105);	
		dx= m_list.AddString(_T("★動画6"));
		m_list.SetItemData(dx,106);	
		dx= m_list.AddString(_T("★動画7"));
		m_list.SetItemData(dx,107);	

		m_list.SetCurSel(0);
	if(ret2!=0) m_list.SetCurSel(ret2);

	m_list.SetFocus();
	return FALSE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

