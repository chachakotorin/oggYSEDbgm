// Zwei.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ogg.h"
#include "Zwei.h"


// CZwei ダイアログ

IMPLEMENT_DYNAMIC(CZwei, CDialog)

CZwei::CZwei(CWnd* pParent /*=NULL*/)
	: CDialog(CZwei::IDD, pParent)
{

}

CZwei::~CZwei()
{
}

void CZwei::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CZwei, CDialog)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
END_MESSAGE_MAP()


// CZwei メッセージ ハンドラ
extern CString fnn;

char tiz1[][128]={
"bgm44 浮遊大陸アルジェス　-Instroduction-",
"bgm35 永劫の夢、大空の記憶 -Zwei!! 2人で大冒険-",
"bgm03 プック村",
"bgm01 浮遊大陸アルジェス -Main Theme-",
"bgm13 パーヴェル庭園",
"bgm12 カヤパの森",
"bgm06 クロップ洞窟",
"bgm07 ケノーピ火山",
"bgm70 浮遊大陸アルジェス -夢見る秘宝-",
"bgm72 コルベットのテーマ　-ネコ言うニャーッ!-",
"bgm27 Fight!! -壊してポックル-",
"bgm60 ひとときの休息を",
"bgm16 ダプネ砂漠",
"bgm18 ヒポリタの丘",
"bgm19 トリポカ湖",
"bgm21 プシュケの屋敷",
"bgm50 おやすみ",
"bgm10 妖精たちの村",
"bgm26 スピリ古代迷宮",
"bgm71 竜の眠る道",
"bgm14 アプリエス神殿",
"bgm15 エスピナ暗黒神殿",
"bgm08 幻の大地 セルペンティナ",
"bgm22 魔王の両腕 -ハンド-",
"bgm09 最後の闘い -魔王ヴェスパー",
"bgm74 安堵のメロディ",
"bgm36 花と風のうた",
"bgm30 ムービー1 -光への誘い-",
"bgm31 ムービー2 -闇への誘い-",
"bgm32 ムービー3 -降臨-",
"bgm33 ムービー4 -大樹-",
"bgm34 ムービー5 -崩壊-",
"bgm77 Zwei!!シューティング -遊んでピピロ-",
"bgm75 Theme of Adol 2001",
"bgm76 モナモ～ナ",
"boss  "
};


CString CZwei::Gett(int a){
	CString s,ss;
	s=tiz1[a];
	ss=s.Left(5);ss.TrimRight();
	fnn=s.Mid(6);
	return ss;
}

/////////////////////////////////////////////////////////////////////////////
// CZWEIII メッセージ ハンドラ
void CZwei::OnDblclkList1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CString s;	s=tiz1[m_list.GetItemData(m_list.GetCurSel())];
	ret=s.Left(5); ret.TrimRight();
	ret2=m_list.GetCurSel();
	if(s.Left(2)=="★"){
		fnn=s.Mid(2);
	}else{
		fnn=s.Mid(6);
	}
	EndDialog(1567);
}

BOOL CZwei::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	int dx;
	for(int i=0;i<(36);i++)
	{
		CString s;
		s=tiz1[i];if(s.Left(2)=="★"){}else{s="ZW2_";s=tiz1[i];}
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
