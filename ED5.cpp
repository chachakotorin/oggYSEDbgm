// ED5.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ogg.h"
#include "ED5.h"


// CED5 ダイアログ

IMPLEMENT_DYNAMIC(CED5, CDialog)

CED5::CED5(CWnd* pParent /*=NULL*/)
	: CDialog(CED5::IDD, pParent)
{

}

CED5::~CED5()
{
}

void CED5::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CED5, CDialog)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
END_MESSAGE_MAP()


// CED5 メッセージ ハンドラ
extern CString fnn;

char tied5[][128]={
"ED5WV002 Leone Fredrik Richter \"海の檻歌\"",
"ED5WV065 寝坊のタッド(フォルト)",
"ED5WV020 やすらぎの時",
"ED5WV030 陽のあたる丘で",
"ED5WV006 春のうた(マクべイン)",
"ED5WV068 風のセレナーデ(アルトス)",
"ED5WV036 そよ風の唄",
"ED5WV041 闇に宿る静寂",
"ED5WV012 魔獣が出てきてさぁ大変!",
"ED5WV011 楽勝!...かな?",
"ED5WV024 潮風に誘われて",
"ED5WV081 闇よりの使者",
"ED5WV015 なんだこの野郎!",
"ED5WV033 潮風に包まれて",
"ED5WV052 シャオとレイチェル",
"ED5WV053 およびでないでSHOW",
"ED5WV031 青空へ登る道",
"ED5WV034 Deep Forest",
"ED5WV023 恋する季節",
"ED5WV061 レオーネのエチュード(シュベール)",
"ED5WV107 レオーネのエチュード(マクベイン一座)",
"ED5WV084 お宝いただき!", 
"ED5WV013 あとには引けない",
"ED5WV089 哀しみを越えて",
"ED5WV025 ルプシャ隊行進曲",
"ED5WV022 Harvest",
"ED5WV055 皇帝の休日(バルダザール)",
"ED5WV056 野いちご摘み(ウェンディ)",
"ED5WV079 砂漠の舞い(アーガス＆カチュア)",
"ED5WV067 ピエロの行進(シャオ＆レイチェル)",
"ED5WV108 森と海のメモリア(マクベイン一座)",
"ED5WV058 ルーレットまかせ",
"ED5WV050 涙はあの日の想いとともに",
"ED5WV057 絶体絶命!",
"ED5WV016 力の限り",
"ED5WV010 さよなら・・",
"ED5WV037 焦燥",
"ED5WV059 水底の子守歌(アリア)",
"ED5WV080 黒き皇国",
"ED5WV086 守るべきもののために",
"ED5WV076 いざないの歌(アリア)", 
"ED5WV077 いざないの歌(フォルト)", 
"ED5WV021 永遠なる民の町",
"ED5WV083 レオーネの軌跡",
"ED5WV035 Hot and Cool",
"ED5WV045 波紋",
"ED5WV044 使命に燃えて",
"ED5WV038 ヌメロスの影",
"ED5WV090 闇の太陽｢復活｣",
"ED5WV093 狂気の代償",
"ED5WV042 漆黒の空",
"ED5WV073 水底のメロディー｢隠者｣(ウーナ)",
"ED5WV088 水底のメロディー｢異界へ｣",
"ED5WV048 明日を生きるために",
"ED5WV085 たすけに来たぜ!", 
"ED5WV032 その闇の向こうに",
"ED5WV019 邪魔する者は容赦しない",
"ED5WV026 Leone Fredrik Richter \"もうひとつの世界\"",
"ED5WV071 水底のメロディー｢誕生｣(ウーナ)",
"ED5WV008 水底のメロディー｢浮上｣(マクベイン一座＆アリア)",
"ED5WV070 青き葬送(デュオール)", 
"ED5WV047 闇の太陽｢遺跡｣",
"ED5WV017 行く手を遮る者",
"ED5WV018 それぞれの未来に",
"ED5WV007 水底の子守歌(フォルト)",
"ED5WV110 海の檻歌･組曲プロローグ｢封印解除｣", 
"ED5WV111 海の檻歌･組曲セグエ｢水底のメロディー｣", 
"ED5WV112 海の檻歌･組曲アリア｢水底の子守歌｣", 
"ED5WV113 海の檻歌･組曲フィナーレ｢Leone Fredrik Richter｣", 
"ED5WV116 愛を感じていたい｢終焉｣",
"ED5WV069 水底のメロディー｢誕生｣(フォルト)",
"ED5WV118 それぞれの明日へ～Leone Fredrik Richter \"End Credits\"", 
"ED5WV119 愛を感じていたい「そして・・」",
"ED5WV001 Leone FredrikRichter \"Theme\"",
"ED5WV100 それ見よ我が元気(フォルト)",
"ED5WV101 木漏れ日の詩(マクベイン)",
"ED5WV102 ゆかいな小鳥(ウーナ)", 
"ED5WV103 旅人たちの前奏曲(マクベイン一座)",
"ED5WV104 陽気な旅人(マクベイン一座)",
"ED5WV105 ともに踊らん(マクベイン一座)",
"ED5WV106 心を開いて(マクベイン一座)",
"ED5WV062 星屑のカンタータ(+ヴァイオリン)",
"ED5WV074 水底のメロディー「心眼」(フォルト)",
"ED5WV096 水底のメロディー「愛」(フォルト)", 
"ED5WV095 水底のメロディー「生命」(マクベイン)", 
"ED5WV066 ピエロの行進･下手版(シャオ＆レイチェル)",
"ED5WV097 ダンジョン３", 
"ED5WV078 レオーネの口笛",
"ED5WV003 ファルコムのロゴ",
"ED5WV060 星屑のカンタータ(ラスト)",
"ED5WV063 星屑のカンタータ（会場外VER）",
"ED5WV064 星屑のカンタータ(ヴァイオリン1)",
"ED5WV087 星屑のカンタータ(ヴァイオリン2)",
"ED5WV092 それ見よ我が元気･街頭演奏版(フォルト)",
"ED5WV094 青き葬送(デュオール)", 
"ED5WV098 ともに踊らん(マクベイン一座)",
"ED5WV099 心を開いて(マクベイン一座＆シャオ･レイチェル)",
"ED5WV109 ともに踊らん(マクベイン一座)"
};

CString CED5::Gett(int a){
	CString s,ss;
	s=tied5[a];
	ss=s.Left(8);ss.TrimRight();
	fnn=s.Mid(9);
	return ss;
}

/////////////////////////////////////////////////////////////////////////////
// CZWEIII メッセージ ハンドラ
void CED5::OnDblclkList1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CString s;	s=tied5[m_list.GetItemData(m_list.GetCurSel())];
	ret=s.Left(8); ret.TrimRight();
	ret2=m_list.GetCurSel();
	if(s.Left(2)=="★"){
		fnn=s.Mid(2);
	}else{
		fnn=s.Mid(9);
	}
	EndDialog(1567);
}

BOOL CED5::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	int dx;
	for(int i=0;i<(98);i++)
	{
		CString s;
		s=tied5[i];if(s.Left(2)=="★"){}else{s="ZW2_";s=tied5[i];}
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


