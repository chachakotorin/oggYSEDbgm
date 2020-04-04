// Render.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "ogg.h"
#include "Render.h"
#include "Graph.h"
#include "dsound.h"
#include "ZeroFol.h"
extern IGraphBuilder *pGraphBuilder;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern save savedata;
/////////////////////////////////////////////////////////////////////////////
// CRender ダイアログ

IMPLEMENT_DYNAMIC(CRender, CDialogEx)
CRender::CRender(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRender::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRender)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}


void CRender::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRender)
	DDX_Control(pDX, IDC_COMBO1, m_1);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_CHECK1, m_evr);
	DDX_Control(pDX, IDC_CHECK2, m_con);
	DDX_Control(pDX, IDC_CHECK3, m_a);
	DDX_Control(pDX, IDC_CHECK27, m_ffd);
	DDX_Control(pDX, IDCANCEL2, m_l);
	DDX_Control(pDX, IDC_CHECK30, m_vob);
	DDX_Control(pDX, IDC_CHECK31, m_haali);
	DDX_Control(pDX, IDC_CHECK32, m_spc2x);
	DDX_Control(pDX, IDC_CHECK33, m_spc4x);
	DDX_Control(pDX, IDC_CHECK34, m_spc8x);
	DDX_Control(pDX, IDC_CHECK35, m_spc1x);
	DDX_Control(pDX, IDC_CHECK36, m_spc16x);
	DDX_Control(pDX, IDC_CHECK40, m_mp31);
	DDX_Control(pDX, IDC_CHECK37, m_mp315);
	DDX_Control(pDX, IDC_CHECK38, m_mp32);
	DDX_Control(pDX, IDC_CHECK39, m_mp325);
	DDX_Control(pDX, IDC_CHECK41, m_mp33);
	DDX_Control(pDX, IDC_CHECK45, m_kpi10);
	DDX_Control(pDX, IDC_CHECK42, m_kpi15);
	DDX_Control(pDX, IDC_CHECK43, m_kpi20);
	DDX_Control(pDX, IDC_CHECK44, m_kpi25);
	DDX_Control(pDX, IDC_CHECK46, m_kpi30);
	DDX_Control(pDX, IDCANCEL3, m_kpi);
	DDX_Control(pDX, IDC_CHECK47, m_mp3orig);
	DDX_Control(pDX, IDC_CHECK48, m_audiost);
	DDX_Control(pDX, IDC_CHECK49, m_24);
	DDX_Control(pDX, IDC_CHECK50, m_m4a);
	DDX_Control(pDX, IDC_CHECK51, m_32bit);
	DDX_Control(pDX, IDC_SLIDER3, m_ms);
	DDX_Control(pDX, IDC_STATIC9, m_ms2);
	DDX_Control(pDX, IDC_SLIDER5, m_hyouji2);
	DDX_Control(pDX, IDC_STATIC10, m_hyouji3);
	DDX_Control(pDX, IDC_COMBO2, m_soundlist);
	DDX_Control(pDX, IDC_BUTTON1, m_ao);
	DDX_Control(pDX, IDC_COMBO3, m_Hz);
}


BEGIN_MESSAGE_MAP(CRender, CDialog)
	//{{AFX_MSG_MAP(CRender)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDCANCEL2, &CRender::OnBnClickedCancel2)
	ON_BN_CLICKED(IDC_CHECK32, &CRender::Onspc2x)
	ON_BN_CLICKED(IDC_CHECK33, &CRender::Onspc4x)
	ON_BN_CLICKED(IDC_CHECK34, &CRender::Onspc8x)
	ON_BN_CLICKED(IDC_CHECK35, &CRender::Onspc1x)
	ON_BN_CLICKED(IDC_CHECK36, &CRender::Onspc16x)
	ON_BN_CLICKED(IDC_CHECK40, &CRender::Onmp31)
	ON_BN_CLICKED(IDC_CHECK37, &CRender::Onmp315)
	ON_BN_CLICKED(IDC_CHECK38, &CRender::Onmp32)
	ON_BN_CLICKED(IDC_CHECK39, &CRender::Onmp325)
	ON_BN_CLICKED(IDC_CHECK41, &CRender::Onmp33)
	ON_BN_CLICKED(IDC_CHECK45, &CRender::Onkpi10)
	ON_BN_CLICKED(IDC_CHECK42, &CRender::Onkpi15)
	ON_BN_CLICKED(IDC_CHECK43, &CRender::Onkpi20)
	ON_BN_CLICKED(IDC_CHECK44, &CRender::Onkpi25)
	ON_BN_CLICKED(IDC_CHECK46, &CRender::Onkpi30)
	ON_BN_CLICKED(IDCANCEL3, &CRender::Onkpi)
	ON_BN_CLICKED(IDC_FONT, &CRender::OnFontMain)
	ON_BN_CLICKED(IDC_FONT2, &CRender::OnFontList)
	ON_BN_CLICKED(IDOK, &CRender::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK49, &CRender::OnBnClicked24bit)
	ON_BN_CLICKED(IDC_CHECK50, &CRender::OnBnClickedCheck50)
	ON_BN_CLICKED(IDCANCEL4, &CRender::OnBnClickedCancel4)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBO2, &CRender::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON1, &CRender::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CRender::OnCbnSelchangeCombo3)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRender メッセージ ハンドラ
CComboBox *sl;
GUID slg[200];
int slgc;
CString sls[200];
DWORD samp[] = { 11025, 12000, 22050, 24000, 44100, 48000, 96000, 192000, 382000, 768000, 1536000, 3072000 };
BOOL CRender::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	OSVERSIONINFO in;ZeroMemory(&in,sizeof(in));in.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);GetVersionEx(&in);
	if(in.dwMajorVersion<=5)
		m_1.AddString(_T("デフォルト"));
	else	
		m_1.AddString(_T("デフォルト(普通/EVR)"));
	m_1.AddString(_T("VMR7"));
	m_1.AddString(_T("VMR9"));
	m_1.SetCurSel(savedata.render);
	switch(savedata.spc){
		case 1:m_spc1x.SetCheck(TRUE); break;
		case 2:m_spc2x.SetCheck(TRUE); break;
		case 4:m_spc4x.SetCheck(TRUE); break;
		case 8:m_spc8x.SetCheck(TRUE); break;
		case 16:m_spc16x.SetCheck(TRUE); break;
	}
	switch(savedata.mp3){
		case 1:m_mp31.SetCheck(TRUE); break;
		case 2:m_mp315.SetCheck(TRUE); break;
		case 3:m_mp32.SetCheck(TRUE); break;
		case 4:m_mp325.SetCheck(TRUE); break;
		case 5:m_mp33.SetCheck(TRUE); break;
	}
	switch(savedata.kpivol){
		case 1:m_kpi10.SetCheck(TRUE); break;
		case 2:m_kpi15.SetCheck(TRUE); break;
		case 3:m_kpi20.SetCheck(TRUE); break;
		case 4:m_kpi25.SetCheck(TRUE); break;
		case 5:m_kpi30.SetCheck(TRUE); break;
	}
	if(in.dwMajorVersion<=5){
		m_evr.EnableWindow(FALSE);
		m_con.EnableWindow(FALSE);
		m_a.EnableWindow(FALSE);
	}
	m_mp3orig.SetCheck(savedata.mp3orig);
	m_audiost.SetCheck(savedata.audiost);
	m_24.SetCheck(savedata.bit24);
	m_32bit.SetCheck(savedata.bit32);
	m_m4a.SetCheck(savedata.m4a);

	m_tooltip.Create(this);
	m_tooltip.Activate(TRUE);
	m_tooltip.AddTool(GetDlgItem(IDOK),_T("保存して閉じます"));
	m_tooltip.AddTool(GetDlgItem(IDCANCEL),_T("保存せずに閉じます"));
	m_tooltip.AddTool(GetDlgItem(IDCANCEL2),_T("再生中の使用DirectShowフィルタを表示します。"));
	m_tooltip.AddTool(GetDlgItem(IDCANCEL3),_T("kpi一覧を表示します。"));
	m_tooltip.AddTool(GetDlgItem(IDCANCEL4), _T("各種ファイルを簡易プレイヤに関連づけします。\nうまくいかない場合もあります。"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK1), _T("Windows Vista/7以降で有効です。\nIndeoを用いた動画の場合OFFにしてください。\nそれ以外はONでいいです。"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK2), _T("Windows Vista/7以降で有効です。\nデスクトップコンポジション(Aero)を使用するかどうかを選択します。\n使用しないにするとEVRじゃなくても動画画面はきれいになります。"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK3), _T("Windows Vista/7以降で有効です。\nAero Grassを使用するかどうか決めます。\n現時点では使うと文字まで透過しちゃうので見づらいです。"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK27), _T("動画にffdshowを使うかどうか選択します。\nWindows7の場合、デフォルトでDivxなどを再生できるのでそちらを使いたい人はOFFにしてください。"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK30),_T("vobとdatファイルはHaaliを通さないように作られていますが、\nvobに複数音声があるときにはチェックを入れて下さい。"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK31),_T("動画にHaaliを使いません。\n動画が重いと思った時や複数音声が無い時はチェックを入れると軽くなります。"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK32),_T("kpi SPC/NEZplug++等のSPCの音量を2倍にします。"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK33),_T("kpi SPC/NEZplug++等のSPCの音量を3倍にします。"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK34),_T("kpi SPC/NEZplug++等のSPCの音量を4倍にします。"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK35),_T("kpi SPC/NEZplug++等のSPCの音量を等倍にします。"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK36),_T("kpi SPC/NEZplug++等のSPCの音量を5倍にします。"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK40),_T("mp3の音量を等倍にします。"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK37),_T("mp3の音量を1.5倍にします。"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK38),_T("mp3の音量を2倍にします。"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK39),_T("mp3の音量を2.5倍にします。"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK41),_T("mp3の音量を3倍にします。"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK45),_T("kpiの音量を等倍にします。"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK42),_T("kpiの音量を2倍にします。"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK43),_T("kpiの音量を3倍にします。"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK44),_T("kpiの音量を4倍にします。"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK46),_T("kpiの音量を5倍にします。"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK47),_T("mp3のデコーダをオリジナルのデコーダを使わずに、独自で使ったデコーダを使う。\nエラーなどで演奏できないときにチェック入れて下さい。\nまた独自で正常にならない時ははずして下さい。"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK48),_T("複数音声のある動画を再生する時に、再生前に\n音声ストリームの選択画面を表示します。\n通常ストリーム1がメインとして使われ、ストリーム2以降はコメンタリや英語音声などに使われています。"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK49), _T("対応しているkpiを24bit(ハイレゾ)で再生します。\n通常は16bitですが、まれに対応しているものがあります。\n音割れについては考慮されていないため、spcなど倍率を上げないといけないものは気をつけて下さい。"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK50), _T("m4aを内蔵エンジンで演奏します。"));
	m_tooltip.AddTool(GetDlgItem(IDC_SLIDER3), _T("演奏のバッファ処理での割り込み時間を設定します。\n少なすぎると音飛びする可能性があります。"));
	m_tooltip.AddTool(GetDlgItem(IDC_SLIDER4), _T("描画の感覚時間を設定します。\nCPU使用が高いときに上げます。。"));
	m_tooltip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_tooltip.SendMessage(TTM_SETMAXTIPWIDTH, 0, 512);

	m_evr.SetCheck(savedata.evr);
	m_con.SetCheck(savedata.con);
	m_a.SetCheck(savedata.aero);
	m_ffd.SetCheck(savedata.ffd);
	m_vob.SetCheck(savedata.vob);
	m_haali.SetCheck(savedata.haali);


#if WIN64
	m_kpi.EnableWindow(FALSE);
#else
#endif
	m_ms.SetRange(30, 100);
	m_ms.SetPos(savedata.ms);
	if (savedata.ms > 100) savedata.ms = 100;
	m_hyouji2.SetRange(1, 60);
	m_hyouji2.SetPos(savedata.ms2);
	CString s; s.Format(L"%dms", savedata.ms);
	m_ms2.SetWindowText(s);
	SetTimer(11, 100, NULL);

	sl = &m_soundlist;
	slgc = 0;
	DirectSoundEnumerate(DSEnumCallback, NULL);
	m_soundlist.SetCurSel(savedata.soundcur);
	if(!pGraphBuilder)
		m_l.EnableWindow(FALSE);
	CString abc = savedata.zero;
	if (abc == L"") {
		m_ao.ShowWindow(FALSE);
	}

	m_Hz.AddString(L"11025");
	m_Hz.AddString(L"12000");
	m_Hz.AddString(L"22050");
	m_Hz.AddString(L"24000");
	m_Hz.AddString(L"44100");
	m_Hz.AddString(L"48000");
	m_Hz.AddString(L"96000");
	m_Hz.AddString(L"192000");
	m_Hz.AddString(L"382000");
	m_Hz.AddString(L"768000");
	m_Hz.AddString(L"1536000");
	m_Hz.AddString(L"3072000 ");
	for (int l = 0; l < 12; l++) {
		if (savedata.samples == samp[l]) {
			m_Hz.SetCurSel(l);
			break;
		}
	}
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

BOOL CALLBACK CRender::DSEnumCallback(LPGUID pGUID, LPCWSTR strDesc,LPCWSTR strDrvName, LPVOID pContext)
{
	if (pGUID)
	{
		sl->AddString(strDesc);
		sls[slgc] = strDesc;
		CopyMemory(&slg[slgc], pGUID, sizeof(GUID));
		slgc++;
	}

	return TRUE;
}

void CRender::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	savedata.render=m_1.GetCurSel();
	savedata.evr=m_evr.GetCheck();
	savedata.con=m_con.GetCheck();
	savedata.aero=m_a.GetCheck();
	savedata.ffd=m_ffd.GetCheck();
	savedata.vob=m_vob.GetCheck();
	savedata.haali=m_haali.GetCheck();
	savedata.audiost=m_audiost.GetCheck();
	savedata.bit24 = m_24.GetCheck();
	savedata.bit32 = m_32bit.GetCheck();
	savedata.m4a = m_m4a.GetCheck();
	savedata.ms = m_ms.GetPos();
	savedata.samples = samp[m_Hz.GetCurSel()];
	//	savedata.mp3orig=m_mp3orig.GetCheck();
	CDialog::OnOK();
}

INT_PTR CRender::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。

	return CDialog::OnToolHitTest(point, pTI);
}

BOOL CRender::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
		m_tooltip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

void CRender::OnBnClickedCancel2()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	CGraph *a = new CGraph(CWnd::FromHandle(GetSafeHwnd()));
	if(pGraphBuilder)
		a->DoModal();
	delete a;
}

void CRender::Onspc2x()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	m_spc2x.SetCheck(TRUE);
	m_spc4x.SetCheck(FALSE);
	m_spc8x.SetCheck(FALSE);
	m_spc16x.SetCheck(FALSE);
	m_spc1x.SetCheck(FALSE);
	savedata.spc=2;
}

void CRender::Onspc4x()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	m_spc2x.SetCheck(FALSE);
	m_spc4x.SetCheck(TRUE);
	m_spc8x.SetCheck(FALSE);
	m_spc16x.SetCheck(FALSE);
	m_spc1x.SetCheck(FALSE);
	savedata.spc=4;
}

void CRender::Onspc8x()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	m_spc2x.SetCheck(FALSE);
	m_spc4x.SetCheck(FALSE);
	m_spc8x.SetCheck(TRUE);
	m_spc16x.SetCheck(FALSE);
	m_spc1x.SetCheck(FALSE);
	savedata.spc=8;
}

void CRender::Onspc1x()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	m_spc2x.SetCheck(FALSE);
	m_spc4x.SetCheck(FALSE);
	m_spc8x.SetCheck(FALSE);
	m_spc16x.SetCheck(FALSE);
	m_spc1x.SetCheck(TRUE);
	savedata.spc=1;
}

void CRender::Onspc16x()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	m_spc2x.SetCheck(FALSE);
	m_spc4x.SetCheck(FALSE);
	m_spc8x.SetCheck(FALSE);
	m_spc16x.SetCheck(TRUE);
	m_spc1x.SetCheck(FALSE);
	savedata.spc=16;
}

void CRender::Onmp31()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	m_mp31.SetCheck(TRUE);
	m_mp315.SetCheck(FALSE);
	m_mp32.SetCheck(FALSE);
	m_mp325.SetCheck(FALSE);
	m_mp33.SetCheck(FALSE);
	savedata.mp3=1;
}

void CRender::Onmp315()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	m_mp31.SetCheck(FALSE);
	m_mp315.SetCheck(TRUE);
	m_mp32.SetCheck(FALSE);
	m_mp325.SetCheck(FALSE);
	m_mp33.SetCheck(FALSE);
	savedata.mp3=2;
}

void CRender::Onmp32()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	m_mp31.SetCheck(FALSE);
	m_mp315.SetCheck(FALSE);
	m_mp32.SetCheck(TRUE);
	m_mp325.SetCheck(FALSE);
	m_mp33.SetCheck(FALSE);
	savedata.mp3=3;
}

void CRender::Onmp325()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	m_mp31.SetCheck(FALSE);
	m_mp315.SetCheck(FALSE);
	m_mp32.SetCheck(FALSE);
	m_mp325.SetCheck(TRUE);
	m_mp33.SetCheck(FALSE);
	savedata.mp3=4;
}

void CRender::Onmp33()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	m_mp31.SetCheck(FALSE);
	m_mp315.SetCheck(FALSE);
	m_mp32.SetCheck(FALSE);
	m_mp325.SetCheck(FALSE);
	m_mp33.SetCheck(TRUE);
	savedata.mp3=5;
}

void CRender::Onkpi10()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	m_kpi10.SetCheck(TRUE);
	m_kpi15.SetCheck(FALSE);
	m_kpi20.SetCheck(FALSE);
	m_kpi25.SetCheck(FALSE);
	m_kpi30.SetCheck(FALSE);
	savedata.kpivol=1;
}

void CRender::Onkpi15()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	m_kpi10.SetCheck(FALSE);
	m_kpi15.SetCheck(TRUE);
	m_kpi20.SetCheck(FALSE);
	m_kpi25.SetCheck(FALSE);
	m_kpi30.SetCheck(FALSE);
	savedata.kpivol=2;
}

void CRender::Onkpi20()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	m_kpi10.SetCheck(FALSE);
	m_kpi15.SetCheck(FALSE);
	m_kpi20.SetCheck(TRUE);
	m_kpi25.SetCheck(FALSE);
	m_kpi30.SetCheck(FALSE);
	savedata.kpivol=3;
}

void CRender::Onkpi25()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	m_kpi10.SetCheck(FALSE);
	m_kpi15.SetCheck(FALSE);
	m_kpi20.SetCheck(FALSE);
	m_kpi25.SetCheck(TRUE);
	m_kpi30.SetCheck(FALSE);
	savedata.kpivol=4;
}

void CRender::Onkpi30()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	m_kpi10.SetCheck(FALSE);
	m_kpi15.SetCheck(FALSE);
	m_kpi20.SetCheck(FALSE);
	m_kpi25.SetCheck(FALSE);
	m_kpi30.SetCheck(TRUE);
	savedata.kpivol=5;
}

void CRender::OnBnClicked24bit()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	savedata.bit24 = m_24.GetCheck();
}

void CRender::OnBnClickedCheck50()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	savedata.m4a = m_m4a.GetCheck();
}



#include "Kpilist.h"
void CRender::Onkpi()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	CKpilist k;
	k.status = 0;
	k.DoModal();
	//delete k;
}

extern HFONT	hFont;
#include "afxdlgs.h"
void CRender::OnFontMain()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	LOGFONT      logFont;
	CFont* f=CFont::FromHandle(hFont);
	f->GetLogFont(&logFont);
	CFontDialog fontDlg(&logFont);
	if (fontDlg.DoModal() == IDOK){
		DeleteObject(hFont);
		hFont=CreateFontIndirect(fontDlg.m_cf.lpLogFont);
	}

}
#include "PlayList.h"
extern CPlayList *pl;
void CRender::OnFontList()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	LOGFONT      logFont;
	CFont* f=pl->m_lc.GetFont();
	f->GetLogFont(&logFont);
	CFontDialog fontDlg(&logFont,CF_SCREENFONTS);
	if (fontDlg.DoModal() == IDOK && pl){
		pl->m_lc.SetFont(fontDlg.GetFont());
	}
}


void CRender::OnBnClickedOk()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	savedata.render = m_1.GetCurSel();
	savedata.evr = m_evr.GetCheck();
	savedata.con = m_con.GetCheck();
	savedata.aero = m_a.GetCheck();
	savedata.ffd = m_ffd.GetCheck();
	savedata.vob = m_vob.GetCheck();
	savedata.haali = m_haali.GetCheck();
	savedata.audiost = m_audiost.GetCheck();
	savedata.bit24 = m_24.GetCheck();
	savedata.bit32 = m_32bit.GetCheck();
	savedata.m4a = m_m4a.GetCheck();
	savedata.ms = m_ms.GetPos();
	CDialog::OnOK();
}




BOOL CRender::MySetFileType(LPCTSTR lpExt, LPCTSTR lpDocName, LPCTSTR lpDocType, LPCTSTR lpPath, LPCTSTR lpPath1)
{
	CRegKey reg;

	// lpExtをlpDocNameに関連付ける
	if (reg.SetValue(HKEY_CLASSES_ROOT, lpExt, lpDocName) != ERROR_SUCCESS)
		return FALSE;
	// lpDocName作成
	CString strDocNameTmp = lpDocName;
	CString strIcon = lpPath1; strIcon += ",0";
	if (reg.SetValue(HKEY_CLASSES_ROOT, strDocNameTmp, lpDocType) != ERROR_SUCCESS)
		return FALSE;
	if (reg.SetValue(HKEY_CLASSES_ROOT, strDocNameTmp + _T("\\shell"), _T("open"))
		!= ERROR_SUCCESS)
		return FALSE;
	if (reg.SetValue(HKEY_CLASSES_ROOT, strDocNameTmp + _T("\\shell\\open\\command"),
		lpPath) != ERROR_SUCCESS)
		return FALSE;
	if (reg.SetValue(HKEY_CLASSES_ROOT, strDocNameTmp + _T("\\DefaultIcon"),
		strIcon) != ERROR_SUCCESS)
		return FALSE;

	if (reg.SetValue(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\RegisteredApplications"),
		_T("SOFTWARE\\PrePrayerPowerSoft\\oggYSEDbgm_uni\\Capabilities"),_T("oggYSEDbgm_uni")) != ERROR_SUCCESS)
		return FALSE;
	if (reg.Create(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\PrePrayerPowerSoft\\oggYSEDbgm_uni\\Capabilities")) != ERROR_SUCCESS)
		return FALSE;
	if (reg.SetValue(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\PrePrayerPowerSoft\\oggYSEDbgm_uni\\Capabilities"),
		strDocNameTmp, lpExt) != ERROR_SUCCESS)
		return FALSE;
	strIcon = _T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\");
	strIcon += lpExt;
	strIcon += _T("\\UserChoice");
	reg.Open(HKEY_CURRENT_USER, _T(""));
	if(reg.DeleteSubKey(strIcon) != ERROR_SUCCESS)
		return FALSE;
	reg.Close();
	if (reg.SetValue(HKEY_CURRENT_USER, strIcon,
		lpDocName, _T("Progid")) != ERROR_SUCCESS)
		return FALSE;

	// 関連付けが変更された事をシステムに通知
	::SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL);
	return TRUE;
}

extern TCHAR karento2[1024];

void CRender::OnBnClickedCancel4()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CString s,ss;
	s = "\"";
	s += karento2;
	s += "oggYSEDbgm_uni.exe\" \"%1\"";
	ss = karento2;
	ss += "oggYSEDbgm_uni.exe";
	MySetFileType(_T(".mp3"), _T("oggYSEDbgm_uni.exe.mp3"), _T("簡易プレイヤで開く"), s, ss);
	MySetFileType(_T(".mp2"), _T("oggYSEDbgm_uni.exe.mp2"), _T("簡易プレイヤで開く"), s, ss);
	MySetFileType(_T(".mp1"), _T("oggYSEDbgm_uni.exe.mp1"), _T("簡易プレイヤで開く"), s, ss);
	MySetFileType(_T(".rmp"), _T("oggYSEDbgm_uni.exe.rmp"), _T("簡易プレイヤで開く"), s, ss);
	MySetFileType(_T(".flac"), _T("oggYSEDbgm_uni.exe.flac"), _T("簡易プレイヤで開く"), s, ss);
	MySetFileType(_T(".m4a"), _T("oggYSEDbgm_uni.exe.m4a"), _T("簡易プレイヤで開く"), s, ss);
	MySetFileType(_T(".aac"), _T("oggYSEDbgm_uni.exe.aac"), _T("簡易プレイヤで開く"), s, ss);
	MySetFileType(_T(".avi"), _T("oggYSEDbgm_uni.exe.avi"), _T("簡易プレイヤで開く"), s, ss);
	MySetFileType(_T(".mp4"), _T("oggYSEDbgm_uni.exe.mp4"), _T("簡易プレイヤで開く"), s, ss);
	MySetFileType(_T(".mkv"), _T("oggYSEDbgm_uni.exe.mkv"), _T("簡易プレイヤで開く"), s, ss);
	MySetFileType(_T(".wmv"), _T("oggYSEDbgm_uni.exe.wmv"), _T("簡易プレイヤで開く"), s, ss);
	MySetFileType(_T(".mpg"), _T("oggYSEDbgm_uni.exe.mpg"), _T("簡易プレイヤで開く"), s, ss);
	// 関連付けが変更された事をシステムに通知
	::SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL);
	MessageBox(_T("一応関連づけを走らせてみました。\nmp1,2,3,rmp,flac,m4a,aac,avi,mp4,mkv,wmv,mpgに関連をつけました。"));
	// 関連付けが変更された事をシステムに通知
	::SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL);
}


void CRender::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	savedata.ms = m_ms.GetPos();
	CString s; s.Format(L"%dms", savedata.ms);
	m_ms2.SetWindowText(s);
	savedata.ms2 = m_hyouji2.GetPos();
	s.Format(L"%dms", savedata.ms2*16);
	m_hyouji3.SetWindowText(s);
	CDialog::OnTimer(nIDEvent);
}


void CRender::OnCbnSelchangeCombo2()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	memcpy(&savedata.soundguid, &slg[m_soundlist.GetCurSel()], sizeof(GUID));
	if (m_soundlist.GetCurSel() == 0) {
		savedata.soundguid = { 0,0,0,0 };
	}
	savedata.soundcur= m_soundlist.GetCurSel();
}


void CRender::OnBnClickedButton1()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CZeroFol z;
	z.DoModal();
}


void CRender::OnCbnSelchangeCombo3()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	savedata.samples = samp[m_Hz.GetCurSel()];
}
