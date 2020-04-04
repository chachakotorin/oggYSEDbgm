// San1.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ogg.h"
#include "San1.h"


// CSan1 ダイアログ

IMPLEMENT_DYNAMIC(CSan1, CDialog)

CSan1::CSan1(CWnd* pParent /*=NULL*/)
	: CDialog(CSan1::IDD, pParent)
{

}

CSan1::~CSan1()
{
}

void CSan1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CSan1, CDialog)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
END_MESSAGE_MAP()


// CSan1 メッセージ ハンドラ
extern CString fnn;

char tisan1[][128]={
"42 永遠的旋律",
"01 古松居",
"27 緊迫",
"12 風動",
"48 破軍",
"49 戰闘49",
"39 悲訣",
"38 暗思量",
"47 幽谷潤",
"05 陌上仙郷",
"51 戰闘51",
"08 蜘蛛洞",
"03 臨江雨",
"02 市井榮華",
"35 笑笑",
"36 采飛揚",
"29 征途",
"50 戰闘50",
"07 功名路",
"22 鬼界戰闘",
"45 激戰",
"13 背水一戰",
"53 祭旗",
"14 飲幽恨",
"15 秋瑟涙",
"46 天涯魂夢",
"11 雲中境",
"19 戰場",
"10 江湖行",
"04 朱樓春宴",
"31 衝陣",
"30 戰火",
"21 歩歩為營",
"41 衷情",
"37 回首前塵",
"54 玄機",
"09 幻霧星霜",
"20 水寒淵",
"06 烽火紅顔",
"16 月蒼茫",
"32 登天",
"23 華夜曲",
"34 決戰千里",
"★盡頭",
"40 遙相憶",
"★オープニング",
"★動画",
"★ファルコムロゴ"
};


CString CSan1::Gett(int a){
	CString s,ss;
	s=tisan1[a];
	ss=s.Left(2);ss.TrimRight();
	fnn=s.Mid(3);
	return ss;
}

/////////////////////////////////////////////////////////////////////////////
// CZWEIII メッセージ ハンドラ
void CSan1::OnDblclkList1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CString s;	s=tisan1[m_list.GetItemData(m_list.GetCurSel())];
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

BOOL CSan1::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	int dx;
	for(int i=0;i<(41+3+4);i++)
	{
		CString s;
		s=tisan1[i];if(s.Left(2)=="★"){}else{s="ZW2_";s=tisan1[i];}
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
