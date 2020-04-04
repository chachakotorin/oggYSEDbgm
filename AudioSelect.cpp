// AudioSelect.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ogg.h"
#include "AudioSelect.h"

extern CString streamname[20];
// CAudioSelect ダイアログ

IMPLEMENT_DYNAMIC(CAudioSelect, CDialog)

CAudioSelect::CAudioSelect(CWnd* pParent /*=NULL*/)
	: CDialog(CAudioSelect::IDD, pParent)
{

}

CAudioSelect::~CAudioSelect()
{
}

void CAudioSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lb);
}


BEGIN_MESSAGE_MAP(CAudioSelect, CDialog)
	ON_LBN_DBLCLK(IDC_LIST1, &CAudioSelect::OnLbnDblclkList1)
	ON_BN_CLICKED(IDOK, &CAudioSelect::OnBnClickedOk)
END_MESSAGE_MAP()


// CAudioSelect メッセージ ハンドラ

void CAudioSelect::OnLbnDblclkList1()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	select();
}

void CAudioSelect::OnBnClickedOk()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	select();
	OnOK();
}

void CAudioSelect::select()
{
	int cnt=m_lb.GetCurSel();
	no=cnt;
	EndDialog(cnt);
}

BOOL CAudioSelect::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ここに初期化を追加してください
	m_tooltip.Create(this);
	m_tooltip.Activate(TRUE);
	m_tooltip.AddTool(GetDlgItem(IDOK),_T("音声ストリームを決定します"));
	m_tooltip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_tooltip.SendMessage(TTM_SETMAXTIPWIDTH, 0, 512);

	for(int i=0;i<no;i++){
		CString str;
		str.Format(_T("音声%d:%s"),i+1, streamname[i]);
		m_lb.AddString(str);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

BOOL CAudioSelect::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
		m_tooltip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}