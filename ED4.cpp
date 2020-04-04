// ED4.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ogg.h"
#include "ED4.h"


// CED4 ダイアログ

IMPLEMENT_DYNAMIC(CED4, CDialog)

CED4::CED4(CWnd* pParent /*=NULL*/)
	: CDialog(CED4::IDD, pParent)
{

}

CED4::~CED4()
{
}

void CED4::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CED4, CDialog)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
END_MESSAGE_MAP()


// CED4 メッセージ ハンドラ
extern CString fnn;

char tied4[][128]={
"E4S00 朱紅い雫　-memoria-",
"★OP1 朱紅い雫　-伝承-（オープニングムービー）",
"★OP2 絆　-熱き想いを胸に（オープニングムービー）",
"E4B01 ぬくもりに抱かれて・・・",
"E4N28 異端者の襲撃　-邪神オクトゥムの陰-",
"E4A00 やすらぎの日々",
"E4S02 いつか来た村", 
"E4S04 足取り軽く", 
"E4N00 そりゃあないでSHOW",
"E4S05 希望へ続く道", 
"E4S13 負けるものか！", 
"E4A01 王都フィルディン",
"E4A02 フィルディン城",
"E4N01 さらに愉快な仲間たち",
"E4S17 走れアヴィン！！", 
"E4C01 怯える人々",
"E4N17 向かうべき路途（みち）へ",
"E4S06 暗闇に巣食う者", 
"E4S14 迷宮乱舞", 
"E4S28 シャムシール団", 
"E4S18 元気なシャノン", 
"E4S07 森を行け", 
"E4N24 朱紅い雫 -神に選ばれし娘-",
"E4S01 にぎやかな街角", 
"E4C00 鉄鋼の町～ギア～",
"E4S15 邪魔をするな！", 
"E4S24 明日があります", 
"E4C03 途方にくれて -ギア・ブルース-",
"E4S03 潮風のリズム", 
"E4S11 海原を風に乗り", 
"E4S25 朱紅い雫　-愛しのアイメル-",
"E4N14 朱紅い雫 -幸せな時間（とき）-",
"E4N20 燃えろアヴィン！！",
"E4N25 たすけに来たぜ！",
"E4N19 朱紅い雫 -待ってろアイメル-",
"E4N99 楽勝！", 
"E4N22 旅立ち",
"E4N12 邪神官ベリアス -襲撃-",
"E4E00 聖都",
"E4E01 礼拝堂 -運命と宿命の中で-",
"E4N10 絆 -哀しみを越えて-",
"E4N11 Blue -取り戻す旅-",
"E4N29 守るべき一線", 
"E4D00 真実を求めて",
"E4N80 我が名はバルドゥス　-真実-",
"E4N15 バルドゥスの眠りし祠",
"E4N33 死闘　-汚された精霊-", 
"E4N23 暗雲たちこめる中で",
"E4S10 太古の遺産", 
"E4S08 泥炭沼", 
"E4N13 神々の犠牲",
"E4N27 異端者の襲撃　-ボルゲイド-",
"E4S19 絆　-凍てつくほどに-", 
"E4N81 我が名はバルドゥス　-集結-",
"E4G06 我が名はバルドゥス -集結-",
"E4N32 避けられぬ戦い", 
"E4G00 封印の地",
"E4G02 時空間迷宮",
"E4G03 邪神官ベリアス -信念-",
"E4G04 我が信念の為に！",
"E4G05 オクトゥムの願い",
"E4N30 かくも強き願い　-代償-", 
"E4N34 かくも強き願い　-冥府-", 
"E4N31 ルティスのこころ", 
"E4N26 絆 -それぞれの場所へ-",
"E4N35 朱紅い雫　-エンドクレジット-"
};

CString CED4::Gett(int a){
	CString s,ss;
	s=tied4[a];
	ss=s.Left(5);ss.TrimRight();
	fnn=s.Mid(6);
	return ss;
}

/////////////////////////////////////////////////////////////////////////////
// CZWEIII メッセージ ハンドラ
void CED4::OnDblclkList1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CString s;	s=tied4[m_list.GetItemData(m_list.GetCurSel())];
	ret=s.Left(5); ret.TrimRight();
	ret2=m_list.GetCurSel();
#if UNICODE
	if(s.Left(1)=="★"){
		fnn=s.Mid(1);
#else
	if(s.Left(2)=="★"){
		fnn=s.Mid(2);
#endif
	}else{
		fnn=s.Mid(6);
	}
	EndDialog(1567);
}

BOOL CED4::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	int dx;
	for(int i=0;i<(66);i++)
	{
		CString s;
		s=tied4[i];if(s.Left(2)=="★"){}else{s="ZW2_";s=tied4[i];}
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


