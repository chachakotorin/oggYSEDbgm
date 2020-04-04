// Sor.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ogg.h"
#include "Sor.h"


// CSor ダイアログ

IMPLEMENT_DYNAMIC(CSor, CDialog)

CSor::CSor(CWnd* pParent /*=NULL*/)
	: CDialog(CSor::IDD, pParent)
{

}

CSor::~CSor()
{
}

void CSor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CSor, CDialog)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
END_MESSAGE_MAP()


// CSor メッセージ ハンドラ
extern CString fnn;

char tisor[][128]={
"SSO001 オープニング",
"SSO002 城 (ここで逢えるね)",
"SSO003 町1",
"SSO004 町2",
"SSO008 トラベラーズ・イン",
"SSO059 シナリオクリア",
"SSO005 消えた王様の杖 ダンジョン",
"SSO006 消えた王様の杖 ヒドラ",
"SSO007 消えた王様の杖 生還",
"SSO009 失われたタリスマン 森",
"SSO010 失われたタリスマン 地下ダンジョン",
"SSO011 失われたタリスマン 神官テルヒチ",
"SSO012 失われたタリスマン サンド・マリボー",
"SSO013 ルシフェルの水門 地下ダンジョン",
"SSO014 ルシフェルの水門 クラーケン",
"SSO015 ルシフェルの水門 ブラディー・リバー",
"SSO016 呪われたオアシス 砂漠",
"SSO017 呪われたオアシス 砂の城",
"SSO018 呪われたオアシス ルワンとゴールド・ドラゴン",
"SSO019 盗賊達の塔 塔",
"SSO020 盗賊達の塔 地底",
"SSO021 盗賊達の塔 屋上",
"SSO022 盗賊達の塔 メジャー・デーモン",
"SSO023 盗賊達の塔 シャドー・ドラゴン",
"SSO024 盗賊達の塔 封印",
"SSO025 暗き沼の魔法使い 暗き沼",
"SSO026 暗き沼の魔法使い レッド・ドラゴン",
"SSO027 ロマンシア ロマンシア王国",
"SSO028 ロマンシア ロマンシア城",
"SSO029 ロマンシア アゾルバ王国",
"SSO030 ロマンシア ヴァイデス",
"SSO060 ロマンシア専用クリア",
"SSO031 紅玉の謎 森",
"SSO032 紅玉の謎 モス・ジャイアント",
"SSO033 紅玉の謎 平和な森",
"SSO034 暗黒の魔道士 ダンジョン",
"SSO035 暗黒の魔道士 ゲディス",
"SSO064 暗黒の魔道士 ゲディスII",
"SSO036 暗黒の魔道士 ブルー・ドラゴン",
"SSO037 呪われたクイーンマリー号 船内",
"SSO038 呪われたクイーンマリー号 上陸後",
"SSO039 呪われたクイーンマリー号 アーク・デーモン",
"SSO040 天の神々たち 村",
"SSO041 天の神々たち コンバット・シーン",
"SSO042 天の神々たち 天上界",
"SSO043 天の神々たち 竪琴",
"SSO044 天の神々たち エビル=シャーマン",
"SSO045 氷の洞窟 洞窟",
"SSO046 氷の洞窟 洞窟II",
"SSO047 氷の洞窟 エキム",
"SSO048 メデューサの首 森",
"SSO049 メデューサの首 村",
"SSO050 メデューサの首 メデューサ",
"SSO051 囚われた魔法使い 地下要塞",
"SSO052 囚われた魔法使い ファイヤー・エレメント",
"SSO053 不老長寿の水 生きている洞窟",
"SSO054 不老長寿の水 動く心臓",
"SSO055 不老長寿の水 ダブル=デビルス",
"SSO056 キング・ドラゴン",
"SSO057 エンディングI",
"SSO058 エンディングII",
"SSO066 新オープニング",
"SSO080 ある魔術師の失敗 鉱山の地底湖",
"SSO081 ある魔術師の失敗 アースエレメンタル",
"SSO083 真夜中に鐘は鳴る ランドル村",
"SSO084 真夜中に鐘は鳴る 教会",
"SSO085 真夜中に鐘は鳴る ザキュレイア",
"SSO086 真夜中に鐘は鳴る 魔術士ゲラン",
"SSO087 ドワーフの置き土産 ドワーフの迷宮",
"SSO088 ドワーフの置き土産 ラビリンス・ドラゴン",
"SSO089 妖精の大樹を救え 妖精たちの村",
"SSO090 妖精の大樹を救え 巨大樹木内部",
"SSO091 妖精の大樹を救え センティピード",
"SSO092 招かれざる来訪者 怪しげな島",
"SSO093 招かれざる来訪者 アーク・デーモン",
"SSO082 フォーエバー シナリオ１～５クリア"
};

CString CSor::Gett(int a){
	CString s,ss;
	s=tisor[a];
	ss=s.Left(6);ss.TrimRight();
	fnn=s.Mid(7);
	return ss;
}

/////////////////////////////////////////////////////////////////////////////
// CZWEIII メッセージ ハンドラ
void CSor::OnDblclkList1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CString s;	s=tisor[m_list.GetItemData(m_list.GetCurSel())];
	ret=s.Left(6); ret.TrimRight();
	ret2=m_list.GetCurSel();
	if(s.Left(2)=="★"){
		fnn=s.Mid(2);
	}else{
		fnn=s.Mid(7);
	}
	EndDialog(1567);
}

BOOL CSor::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	int dx;
	for(int i=0;i<(76);i++)
	{
		CString s;
		s=tisor[i];if(s.Left(2)=="★"){}else{s="ZW2_";s=tisor[i];}
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

