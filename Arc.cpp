// Arc.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ogg.h"
#include "Arc.h"


// CArc ダイアログ

IMPLEMENT_DYNAMIC(CArc, CDialog)

CArc::CArc(CWnd* pParent /*=NULL*/)
	: CDialog(CArc::IDD, pParent)
{

}

CArc::~CArc()
{
}

void CArc::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CArc, CDialog)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CArc メッセージ ハンドラ
extern CString fnn;

char tiarc[][128]={
"★OPEN YOUR EYES",
"02 罪の子らの賛美歌",
"03 大陸遠望",
"04 勝利！",
"05 予期せぬ終結",
"06 つかの間の休息",
"07 眠れない夜は",
"08 ENCOUNTER BATTLE",
"09 戦闘＃2",
"10 聖堂",
"11 フィールド＃1",
"12 舞踏会",
"13 トランクォーリー",
"14 緊迫",
"15 ラグニ村",
"16 出発の日",
"17 大海原へ",
"18 港町タイニ",
"19 悪だくみ",
"20 さぁ、特訓だ！",
"21 闇の足音　－予兆－",
"22 国境都市マルテュニ",
"23 共和国首都ドーム",
"24 差し迫る危機",
"25 急げ！",
"26 ふたりで…",
"27 フィールド＃2",
"28 いつもの朝",
"29 港町アンスヴェルス",
"30 サルディス湾",
"31 聖都バアラ",
"32 エリザベス・エンジン",

"33 なつかしい景色",
"34 ダンジョン＃1",
"35 オカリナ",
"36 EVERLASTING NIGHTMARE",
"37 ラグニ村　another version",
"38 BURST INTO THE BATTLE",
"39 フィールド＃3",
"40 荒廃の影",
"41 分かたれた道",
"42 神との決別",
"43 対決",
"44 フィールド＃4",
"45 プリセロナのテーマ",
"46 DESTRUCTION",
"47 エステニュ・チョダル",
"48 不吉",
"49 セテバン研究地区",
"50 DESERTED TOWN",
"51 祈り",
"52 変わりゆく世界",
"53 ラクリモサ渓谷",
"54 ESPIONAGE",
"55 エルハイヴ要塞",
"56 降臨",
"57 戦闘＃4",
"58 フィールド＃5",
"59 ゲルナ高原",

"60 幻夢",
"61 BREAKTHROUGH",
"62 エペソ",
"63 あるマギの記憶",
"64 審判の時",
"65 MBRACE",
"66 戦闘＃5",
"67 FINAL ASSAULT",
"68 フィールド＃5",
"69 凍てついた過去",
"70 FALL OF THE EMPIRE",
"71 コンステルラリウム",
"72 N.O.A.H.",
"73 EDEN",
"74 旅の想い出",
"75 鎮魂歌",
"76 迫りくる脅威",
"77 CASTLE WALKENSWAARD",
"78 礼拝堂　～アケナトン～",
"79 ダンジョン＃2",
"80 ダンジョン＃3",
"81 エピローグ",
"82 Truth In Me",

"84 幻夢"
};


CString CArc::Gett(int a){
	CString s,ss;
	s=tiarc[a];
	ss=s.Left(2);ss.TrimRight();
	fnn=s.Mid(3);
	return ss;
}

/////////////////////////////////////////////////////////////////////////////
// CZWEIII メッセージ ハンドラ
void CArc::OnDblclkList1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CString s;	s=tiarc[m_list.GetItemData(m_list.GetCurSel())];
	ret=s.Left(2); ret.TrimRight();
	ret2=m_list.GetCurSel();
#if UNICODE
	if(s.Left(1)=="★"){
		fnn=s.Mid(1);
#else
	if(s.Left(2)=="★"){
		fnn=s.Mid(2);
#endif
	}else{
		fnn=s.Mid(3);
	}
	EndDialog(1567);
}

BOOL CArc::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	int dx;
	for(int i=0;i<(83);i++)
	{
		CString s;
		s=tiarc[i];if(s.Left(2)=="★"){}else{s="ZW2_";s=tiarc[i];}
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


void CArc::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: ここにメッセージ ハンドラー コードを追加します。
					   // 描画メッセージで CDialog::OnPaint() を呼び出さないでください。
}
