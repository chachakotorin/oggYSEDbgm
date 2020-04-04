// Br4.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ogg.h"
#include "Br4.h"


// CBr4 ダイアログ

IMPLEMENT_DYNAMIC(CBr4, CDialog)

CBr4::CBr4(CWnd* pParent /*=NULL*/)
	: CDialog(CBr4::IDD, pParent)
{

}

CBr4::~CBr4()
{
}

void CBr4::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CBr4, CDialog)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
END_MESSAGE_MAP()


// CBr4 メッセージ ハンドラ
extern CString fnn;

char tibr4[][128]={
"VT01DA Brandish4 -OP-", 
"VT03DA 古の祈り-meditation-", 
"VT05DA 遺跡-the prop-", 
"VT13DA ショップ-relation-", 
"VT32DA 迷宮-roar-", 
"VT04DA 街区-division-", 
"VT14DA カジノ-eighth wonder-", 
"VT19DA 遊戯-hammer slime-", 
"VT15DA 闘場-black field-", 
"VT16DA 塔の謎-mysterious-", 
"VT27DA 遺跡2-debris-", 
"VT18DA 死闘-trigger-", 
"VT28DA 遺跡3-deep haze-", 
"VT06DA 水域-the abyss-", 
"VT07DA 庭園-bramble-", 
"VT33DA 召喚-hostile-", 
"VT08DA 城塞-solid steel-", 
"VT09DA 聖堂-judgement-", 
"VT17DA 塔の復活-retribution-", 
"VT10DA 胎内-forbidden power-", 
"VT30DA 決闘-fatal riders-", 
"VT11DA 神殿-heritage-", 
"VT12DA 忘却の迷宮-another door-", 
"VT34DA 祭壇-altar-", 
"VT20DA ギリアス-victim-", 
"VT39DA エピローグI-daybreak-", 
"VT40DA エピローグII-twilght-", 
"VT41DA エピローグIV-broken chain-", 
"VT21DA VT21(エンディング用)", 
"VT22DA VT22(エンディング用)", 
"VT35DA ENDING", 
"VT02DA Staff", 
"VT36DA 休息-slumber-", 
"VT31DA GAME OVER", 
"VT38DA イントロダクション", 
"VT43DA ジングル：詩人1", 
"VT44DA ジングル：詩人2", 
"VT45DA ジングル：詩人3", 
"VT46DA ジングル：詩人4", 
"VT47DA ジングル：詩人5", 
"VT48DA ジングル：詩人6", 
"VT49DA ジングル：詩人7"
};

CString CBr4::Gett(int a){
	CString s,ss;
	s=tibr4[a];
	ss=s.Left(6);ss.TrimRight();
	fnn=s.Mid(7);
	return ss;
}

/////////////////////////////////////////////////////////////////////////////
// CZWEIII メッセージ ハンドラ
void CBr4::OnDblclkList1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CString s;	s=tibr4[m_list.GetItemData(m_list.GetCurSel())];
	ret=s.Left(6); ret.TrimRight();
	ret2=m_list.GetCurSel();
	if(s.Left(2)=="★"){
		fnn=s.Mid(2);
	}else{
		fnn=s.Mid(7);
	}
	EndDialog(1567);
}

BOOL CBr4::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	int dx;
	for(int i=0;i<(42);i++)
	{
		CString s;
		s=tibr4[i];if(s.Left(2)=="★"){}else{s="ZW2_";s=tibr4[i];}
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
