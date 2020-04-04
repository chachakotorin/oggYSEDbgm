// ZWEIII.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "ogg.h"
#include "ZWEIII.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZWEIII ダイアログ

extern CString fnn;

CZWEIII::CZWEIII(CWnd* pParent /*=NULL*/)
	: CDialog(CZWEIII::IDD, pParent)
{
	//{{AFX_DATA_INIT(CZWEIII)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}


void CZWEIII::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZWEIII)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CZWEIII, CDialog)
	//{{AFX_MSG_MAP(CZWEIII)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


char tiz2[][128]={
"000 限りなき冒険の新天地",
"001 グランヴァレンの伝説",
"002 ボクラノ未来 Opening Version",
"003 ZWEI II End Credit",
"004 力尽きても…",
"006 魔法大戦再び…",
"007 たすけてアルウェン Rushing in Version",
"008 宿縁の終焉",
"100 浮遊島《イルバード》",
"101 アルッテの町",
"102 アルッテ飛行場",
"103 ブランデーヶ丘",
"104 ロアルタ村",
"105 星降りの里",
"106 クリスタルバレー",
"108 魔女ラーライラ",
"109 覆面超人ギャランドゥ",
"200 セクンドゥム廃坑",
"201 オルディウム神殿",
"202 金闇の森",
"203 アウロン大鉄塔",
"205 闇夜に踊れ",
"206 ムーンブリア城",
"207 狂喜の牢獄",
"208 エスピナへ捧ぐ祈り",
"209 星ヶ峰",
"210 覚悟を決めて",
"211 月の世界《ルナ＝ムンドゥス》",
"212 螺旋要塞メルセデク",
"300 まかせろラグナ",
"301 唸れ！アンカーギア！！",
"304 真祖の力",
"305 我にひれ伏せ",
"306 我が主のために",
"307 この瞬間に全てを賭けて",
"308 障害を突破せよ",
"400 Dog Fight！！",
"401 不穏な空気",
"402 モンブランのテーマ",
"403 レッツ・エクササァイズ！！",
"404 激情に駆られて",
"405 ザハールの大望",
"406 最悪の事態",
"407 あたたかな想い",
"408 通い合う心と心",
"409 お食事は大熊猫楼で",
"410 機械仕掛けの少女",
"411 宿縁の少女",
"412 たすけてアルウェン",
"413 失意のラグナ",
"414 課せられた使命",
"415 かけがえのない日常",
"416 再会を誓って",
"417 夜空に佇む",
"500 音楽 Ys フェルガナの誓い(翼を持った少年)",
"501 音楽 Ys フェルガナの誓い(バレスタイン城)",
"502 音楽 Ys オリジン(BEYOND THE BEGINNING)",
"503 音楽 Ys オリジン(WATER PRISON)",
"504 音楽 Zwei!!(花と風のうた -arrange-)",
"505 音楽 Zwei!!(幻の大地 セルペンティナ)",
"506 音楽 空の軌跡FC(虚ろなる光の封土)",
"507 音楽 空の軌跡SC(The Fate of The Fairies)",
"508 音楽 空の軌跡The3rd(Overdosing Heavenly Bliss)",
"509 音楽 ぐるみん(不可思議オバケ卵)",
"510 音楽 ぐるみん(TO MAKE THE END OF DIGING)",
"★オープニング",
"★エンディング"
};

CString CZWEIII::Gett(int a){
	CString s,ss;
	s=tiz2[a];
	ss=s.Left(3);
	fnn=s.Mid(4);
	return ss;
}

/////////////////////////////////////////////////////////////////////////////
// CZWEIII メッセージ ハンドラ
void CZWEIII::OnDblclkList1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CString s;	s=tiz2[m_list.GetItemData(m_list.GetCurSel())];
	ret=_tstoi(s.Left(4));
	ret2=m_list.GetCurSel();
	if(ret2>65)
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

BOOL CZWEIII::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	int dx;
	for(int i=0;i<67;i++)
	{
		CString s;
		s=tiz2[i];if(s.Left(2)=="★"){}else{s="ZW2_";s+=tiz2[i];}
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
