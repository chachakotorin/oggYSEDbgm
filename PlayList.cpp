// PlayList.cpp : 実装ファイル
//

#include "stdafx.h"
#include "direct.h"
#include "dshow.h"
#include "ogg.h"
#include "oggDlg.h"
#include "ListCtrlA.h"
#include "PlayList.h"
#include "ListSyosai.h"
#include "Filename.h"
#include "Douga.h"
#include "mp3image.h"

// CPlayList ダイアログ

IMPLEMENT_DYNAMIC(CPlayList, CDialog)

extern 	CString ext[150][30];
extern 	CString kpif[200];
extern  BOOL kpichk[200];
extern 	int kpicnt;
extern COggDlg *og;
extern BOOL plw;


CPlayList::CPlayList(CWnd* pParent /*=NULL*/)
	: CDialog(CPlayList::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_PL);
	pc=NULL;
	plw=0;
//	pc = new playlistdata0[60000];
}

CPlayList::~CPlayList()
{
	if (pc) {
		free(pc);
		pc = NULL;
	}
	m_tooltip.DestroyWindow();
}

void CPlayList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_lsup);
	DDX_Control(pDX, IDC_BUTTON5, m_lup);
	DDX_Control(pDX, IDC_BUTTON10, m_lsdown);
	DDX_Control(pDX, IDC_BUTTON11, m_ldown);
	DDX_Control(pDX, IDC_LIST1, m_lc);
	DDX_Control(pDX, IDC_EDIT1, m_e);
	DDX_Control(pDX, IDC_CHECK1, m_renzoku);
	DDX_Control(pDX, IDC_CHECK4, m_loop);
	DDX_Control(pDX, IDC_CHECK28, m_tool);
	DDX_Control(pDX, IDC_CHECK29, m_saisyo);
	DDX_Control(pDX, IDC_EDIT2, m_find);
	DDX_Control(pDX, IDC_BUTTON16, m_findup);
	DDX_Control(pDX, IDC_BUTTON20, m_finddown);
	DDX_Control(pDX, IDC_CHECK5, m_savecheck);
	DDX_Control(pDX, IDC_CHECK6, m_save_mp3);
	DDX_Control(pDX, IDC_CHECK7, m_save_kpi);
}


BEGIN_MESSAGE_MAP(CPlayList, CDialog)
	ON_WM_NCDESTROY()
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &CPlayList::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CPlayList::OnUP)
	ON_BN_CLICKED(IDC_BUTTON5, &CPlayList::OnSUP)
	ON_BN_CLICKED(IDC_BUTTON10, &CPlayList::OnSDOWN)
	ON_BN_CLICKED(IDC_BUTTON11, &CPlayList::OnDOWN)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST1, &CPlayList::OnLvnKeydownList1)
	ON_WM_DROPFILES()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CPlayList::OnNMDblclkList1)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_CHECK4, &CPlayList::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_CHECK1, &CPlayList::OnBnClickedCheck1)
	ON_NOTIFY(LVN_BEGINDRAG, IDC_LIST1, &CPlayList::OnLvnBegindragList1)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST1, &CPlayList::OnLvnGetdispinfoList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CPlayList::OnNMRclickList1)
	ON_COMMAND(ID_POP_32776, OnList)
	ON_COMMAND(ID_POP_32777,Del)
	ON_WM_ACTIVATE()
	ON_COMMAND(ID_POP_32787, &CPlayList::OnPop32787)
	ON_BN_CLICKED(IDC_BUTTON16, &CPlayList::OnFindUp)
	ON_BN_CLICKED(IDC_BUTTON20, &CPlayList::OnFindDown)
	ON_BN_CLICKED(IDC_CHECK6, &CPlayList::OnBnClickedCheck6mp3)
	ON_BN_CLICKED(IDC_CHECK7, &CPlayList::OnBnClickedCheck7dshow)
END_MESSAGE_MAP()

#include <eh.h>
class SE_Exception1
{
private:
    unsigned int nSE;
public:
    SE_Exception1() {}
    SE_Exception1( unsigned int n ) : nSE( n ) {}
    ~SE_Exception1() {}
    unsigned int getSeNumber() { return nSE; }
};
void trans_func1( unsigned int, EXCEPTION_POINTERS* );
void trans_func1( unsigned int u, EXCEPTION_POINTERS* pExp )
{
    throw SE_Exception1();
}


int playcnt=0;
float hD2;
int syo;
CString syos;
extern TCHAR karento2[1024];
extern int fade1;
extern IMediaPosition *pMediaPosition;
extern int mode,videoonly,playf;
extern int plcnt;
extern save savedata;
BOOL CPlayList::OnInitDialog()
{
	CDialog::OnInitDialog();

	CDC *desktopDc = GetDC();
	// Get native resolution
	int horizontalDPI = GetDeviceCaps(desktopDc->m_hDC, LOGPIXELSX);
	hD2 = (float)(horizontalDPI) / (96.0f);
	ReleaseDC(desktopDc);

	playcnt=0;
	w_flg=TRUE;
	pnt=0;
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定
	// TODO:  ここに初期化を追加してください
	m_lsup.SetIcon(IDR_SUP);
	m_lsup.SetFlat(TRUE);
	m_lup.SetIcon(IDR_UP);
	m_lup.SetFlat(TRUE);
	m_lsdown.SetIcon(IDR_SDOWN);
	m_lsdown.SetFlat(TRUE);
	m_ldown.SetIcon(IDR_DOWN);
	m_ldown.SetFlat(TRUE);

	m_findup.SetIcon(IDR_DOWN);
	m_findup.SetFlat(TRUE);
	m_finddown.SetIcon(IDR_UP);
	m_finddown.SetFlat(TRUE);

	m_tooltip.Create(this,TTS_ALWAYSTIP | TTS_BALLOON);
	m_tooltip.Activate(TRUE);
	m_tooltip.AddTool(GetDlgItem(IDOK), _T("プレイリストを閉じます。"));
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON1), _T("選択項目を一番上に持って行きます。"));
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON5), _T("選択項目を上に持って行きます。"));
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON10), _T("選択項目を一番下に持って行きます。"));
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON11), _T("選択項目を下に持って行きます。"));
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON16), _T("現在の位置から下に検索します。"));
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON20), _T("現在の位置から上に検索します。"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK1), _T("プレイリストの順番に再生を行います。\n再生中にファイルドロップして追加しても演奏中の曲はそのまま鳴り続けます。"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK4), _T("選択した曲をループさせます。\n再生する前にチェックを入れる必要があります。\nそうでないとループはかかりません。\nループポイントが0のもの(mp3やループしない曲)が対象です。"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK28), _T("ツールチップを表示します。"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK29), _T("最小化、最小化からの復帰時、メイン画面とプレイリスト画面も同時に最小化、最小化からの復帰を行います。"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK5), _T("途中で演奏を停止した位置を自動保存します。\nmp3系と動画(avi,mp4など)のみ対応。\n停止ボタンもしくは終了したときのみ保存します。\n再生中に違う曲を選んだ時は位置は保存しません。"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK6), _T("mp3再生時に途中保存を有効にします。"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK7), _T("動画などのDirectShow使用時に途中保存を有効にします。"));
	m_tooltip.SetDelayTime(TTDT_AUTOPOP, 10000);
	m_tooltip.SendMessage(TTM_SETMAXTIPWIDTH, 0, 512);
//	m_lc.SetMaxTipWidth(500)
	DWORD dwExStyle = m_lc.GetExtendedStyle();
	dwExStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;//|LVS_EX_INFOTIP;
	m_lc.SetExtendedStyle(dwExStyle);
	il.Create(16, 16, ILC_COLOR, 0, 1);
	il.Add(::AfxGetApp()->LoadIcon(IDI_ICON1)); 
	il.Add(::AfxGetApp()->LoadIcon(IDI_ICON2)); 
	il.Add(::AfxGetApp()->LoadIcon(IDI_ICON3)); 
	m_lc.SetImageList(&il,LVSIL_SMALL);
	m_lc.ModifyStyle ( 0, LVS_REPORT );
	m_lc.InsertColumn ( 0, _T("名前"), LVCFMT_LEFT, 200, 0 );
	m_lc.InsertColumn ( 1, _T("ゲーム"), LVCFMT_LEFT, 50, 0 );
	m_lc.InsertColumn ( 2, _T("時間"), LVCFMT_RIGHT, 50, 0 );
	m_lc.InsertColumn ( 3, _T("アーティスト"), LVCFMT_LEFT, 200, 0 );
	m_lc.InsertColumn ( 4, _T("アルバム/コメント"), LVCFMT_LEFT, 200, 0 );
	m_lc.InsertColumn ( 5, _T("フォルダ"), LVCFMT_LEFT, 50, 0 );
	m_lc.pc = pc;
//	pc=NULL;
//	pc = (playlistdata0*)malloc(sizeof(playlistdata0)*50000);
//	if(pc==NULL)
//		EndDialog(0);
	m_lc.SetFocus();
	pnt=pnt1=-1;
	nnn=1;
	pc=NULL;

	m_savecheck.SetCheck(savedata.savecheck);
	m_save_mp3.SetCheck(savedata.savecheck_mp3);
	m_save_kpi.SetCheck(savedata.savecheck_dshow);

	Load();
	if(pc==NULL){
		pc = (playlistdata0*)malloc(sizeof(playlistdata0));
	}
	SetTimer(20,20,NULL);
	SetTimer(3000,1200,NULL);
	SetTimer(40,500,NULL);
	SetTimer(5000,100,NULL);
	SIcon(pnt1);
//	CFont pFont;
//	BOOL retfont=pFont.CreateFont(-15,0,0,0,400,0,0,0,128,3,2,1,50,savedata.font2);
//	if(retfont){
//		m_lc.SetFont(&pFont,TRUE);
//		m_find.SetFont(&pFont,TRUE);
//	}
//	pFont.DeleteObject();
//	if(retfont==0)
//		retfont=pFont.CreateFont(0,0,0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,_T("MS UI Gothic"));
//	if(retfont==0)
//		retfont=pFont.CreateFont(0,0,0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,_T("ＭＳ Ｐゴシック"));
//	if(retfont){
//		m_lc.SetFont(&pFont,TRUE);
//		m_find.SetFont(&pFont,TRUE);
//	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}
extern int killw1;
extern CPlayList *pl;
void CPlayList::OnNcDestroy()
{
	CDialog::OnNcDestroy();

	// TODO: ここにメッセージ ハンドラ コードを追加します。
	killw1=1;
}

BOOL CPlayList::DestroyWindow()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	Save();
//	free(pc);
//	pc=NULL;
//	KillTimer(20);
//	KillTimer(30);
	BOOL rr=CDialog::DestroyWindow();
	pl=NULL;
	if(nnn)
		delete this;
	plw=0;
	return rr;
}

int CPlayList::Create(CWnd *pWnd)
{
	 m_pParent = NULL;
	BOOL bret = CDialog::Create( CPlayList::IDD, this);
    if( bret == TRUE)
        ShowWindow( SW_SHOW);
    return bret;
}

void CPlayList::OnClose()
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	nnn=0;
	DestroyWindow();

	CDialog::OnClose();
}

void CPlayList::OnBnClickedOk()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
//	DestroyWindow();
}

BOOL CPlayList::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
		m_tooltip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

int pnt1=-1;

int CPlayList::chk(CString name,int sub,CString art,CString fol,int ret)
{
	int i=m_lc.GetItemCount(),c=0;
	pnt1=-1;
	CString s,s1;
	for(int j=0;j<i;j++){
		c=0;
		if((pc[j].sub==-10)||(pc[j].sub==-2)||(pc[j].sub==-3)){
			if(_tcscmp(pc[j].fol,fol)==0 && pc[j].sub==sub && _tcscmp(pc[j].name,name)==0)
				return j;
		}else{
			if(_tcscmp(pc[j].fol,fol)==0 && pc[j].sub==sub && (pc[j].ret2==ret))
				return j;
		}
	}
	return -1;
}

CString CPlayList::UTF8toSJIS(const char* a)
{
	WCHAR f[1024];
	char ff[1024];
	int rr=MultiByteToWideChar(CP_UTF8,0,a,-1,f,1024);
	int rr2=WideCharToMultiByte(CP_ACP,0,f,rr,ff,0,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,f,rr,ff,rr2,NULL,NULL);
	CString s; s=f;
	return s;
//	return _T("");
}

CString CPlayList::UTF8toUNI(const TCHAR* a)
{
//	WCHAR f[1024];
//	char ff[1024];
//	int rr2=WideCharToMultiByte(CP_ACP, 0, a,1024,ff,1024,NULL,NULL);
//	int rr= MultiByteToWideChar(CP_UTF8,0,ff,-1,f ,1024);
//	WideCharToMultiByte(CP_ACP,0,f,rr,ff,rr2,NULL,NULL);
	CString s; s=a;
	return s;
//	return _T("");
}

int CPlayList::Add(CString name,int sub,int loop1,int loop2,CString art,CString alb,CString fol,int ret,int time,BOOL f,BOOL ff)
{
	int cnt1;
	CString s,ss;
	switch(sub){
		case 1:s="空の軌跡SC";break;
		case 2:s="空の軌跡FC";break;
		case 3:s="イース フェルガナの誓い";break;
		case 4:s="Ys6 ナピシュテムの匣";break;
		case 5:s="イース オリジン";break;
		case 6:s="空の軌跡 The3rd";break;
		case 7:s="ZWEI II";break;
		case 8:s="Ys I&II Chronicles 1";break;
		case 9:s="Ys I&II Chronicles 2";break;
		case 10:s="XANADU NEXT";break;
		case 11:s="Ys I&II 完全版 1";break;
		case 12:s="Ys I&II 完全版 2";break;
		case 13:s="Sorcerian Original";break;
		case 14:s="Zwei!!";break;
		case 15:s="ぐるみん -GURUMIN-";break;
		case 16:s="ダイナソア リザレクション";break;
		case 17:s="Brandish4 眠れる神の塔";break;
		case 18:s="白き魔女";break;
		case 19:s="朱紅い雫";break;
		case 20:s="海の檻歌";break;
		case 21:s = "閃の軌跡I or II"; break;
		case -6:s = "閃の軌跡III or IV"; break;
		case -11:s="月影のラプソディー";break;
		case -12:s="西風の狂詩曲";break;
		case -13:s="アークトゥルス";break;
		case -14:s="幻想三国志1";break;
		case -15:s="幻想三国志2";break;
		case -3:
			ss=fol.Right(fol.GetLength()-fol.ReverseFind('.')-1);
			s.Format(_T("%sファイル"),ss);break;
		case -2:
			ss=fol.Right(fol.GetLength()-fol.ReverseFind('.')-1);
			s.Format(_T("%sファイル"),ss);break;
		case -1:s="oggファイル";break;
		case -7:
			s = fol; s.MakeLower();
			if (s.Right(3) == "dsf") { s = "dsfファイル(DSD)"; break; }
			if (s.Right(3) == "wsd") { s = "wsdファイル(DSD)"; break; }
			if (s.Right(3) == "dff") { s = "dffファイル(DSD)"; break; }
		case -8:
			s = fol; s.MakeLower();
			if (s.Right(4) == "flac") { s = "flacファイル"; break; }
		case -9:
			s = fol; s.MakeLower();
			if (s.Right(3) == "m4a") { s = "m4aファイル"; break; }
			if (s.Right(3) == "aac") { s = "aacファイル"; break; }
		case -10:
			s=fol;s.MakeLower();
			if(s.Right(3)=="mp3"){ s="mp3ファイル";break;}
			if(s.Right(3)=="mp2"){ s="mp2ファイル";break;}
			if(s.Right(3)=="mp1"){ s="mp1ファイル";break;}
			if(s.Right(3)=="rmp"){ s="rmpファイル";break;}
	}

	if(f)
		if((cnt1=chk(name,sub,art,fol,ret))!=-1){
			pc[cnt1].time=time;
			RECT r;
			m_lc.GetItemRect(cnt1,&r,LVIR_BOUNDS);
			m_lc.RedrawWindow(&r);	
			return cnt1;
		}
//	if(playcnt<60000){
		if(ff){
			playlistdata0 *tmp;tmp=pc;
			size_t size=_msize(pc);
			pc=(playlistdata0*)realloc(tmp,size+sizeof(playlistdata0));
			if(pc==NULL){
				return -1;
			}
			m_lc.SetItemCount(playcnt+1);
		}
		_tcscpy(pc[playcnt].name,name);
		_tcscpy(pc[playcnt].art,art);
		_tcscpy(pc[playcnt].alb,alb);
		_tcscpy(pc[playcnt].fol,fol);
		_tcscpy(pc[playcnt].game,s);
		pc[playcnt].loop1=loop1;
		pc[playcnt].loop2=loop2;
		pc[playcnt].sub=sub;
		pc[playcnt].ret2=ret;
		pc[playcnt].icon=1;
		pc[playcnt].time=time;
//		RECT r;
//		m_lc.GetItemRect(playcnt,&r,LVIR_BOUNDS);
//		m_lc.RedrawWindow(&r);	
		playcnt++;
//	}		
		
	return -1;
}

void CPlayList::Del()
{
	int Lindex=-1,j=0;
	for(;;){//選択されているものをピックアップ
		Lindex=m_lc.GetNextItem(Lindex,LVNI_ALL |LVNI_SELECTED);
		if(Lindex==-1) break;
		m_lc.SetItemState(Lindex,m_lc.GetItemState(Lindex,LVIS_SELECTED)&~LVIS_SELECTED,LVIS_SELECTED);
		for(int i=Lindex+1+j;i<playcnt;i++){
			memcpy(&pc[i-1],&pc[i],sizeof(playlistdata0));
		}
		playcnt--;j--;
	}
	playlistdata0 *tmp;tmp=pc;
	pc=(playlistdata0*)realloc(tmp,(size_t)sizeof(playlistdata0)*(playcnt+2));//余裕を持って解放
	m_lc.SetItemCount(playcnt);
	for(j=0;j<playcnt;j++) pc[j].icon=1;
	m_lc.RedrawWindow();
	Save();
}

void CPlayList::OnSUP()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	int i=m_lc.GetItemCount();
	CString s,s1;
	for(int j=0;j<i-1;j++){
		if((m_lc.GetItemState(j+1,LVIS_SELECTED)&LVIS_SELECTED)&&!(m_lc.GetItemState(j,LVIS_SELECTED)&LVIS_SELECTED)){
			playlistdata0 ppp;
			pc[j].icon=pc[j+1].icon=1;
			memcpy(&ppp,&pc[j+1],sizeof(playlistdata0));
			memcpy(&pc[j+1],&pc[j],sizeof(playlistdata0));
			memcpy(&pc[j],&ppp,sizeof(playlistdata0));
			m_lc.RedrawItems(j,j+1);
			m_lc.SetItemState(j  ,m_lc.GetItemState(j  ,LVIS_SELECTED)|LVIS_SELECTED,LVIS_SELECTED);
			m_lc.SetItemState(j+1,m_lc.GetItemState(j+1,LVIS_SELECTED)&~LVIS_SELECTED,LVIS_SELECTED);
		}
	}
//	m_lc.RedrawWindow();
	Save();
}

void CPlayList::OnUP()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	int i=m_lc.GetItemCount(),i2=0;
	CString s,s1;
	for(;;){i2=0;
		for(int j=0;j<i-1;j++){
			if((m_lc.GetItemState(j+1,LVIS_SELECTED)&LVIS_SELECTED)&&!(m_lc.GetItemState(j,LVIS_SELECTED)&LVIS_SELECTED)){
			playlistdata0 ppp;
			pc[j].icon=pc[j+1].icon=1;
			memcpy(&ppp,&pc[j+1],sizeof(playlistdata0));
			memcpy(&pc[j+1],&pc[j],sizeof(playlistdata0));
			memcpy(&pc[j],&ppp,sizeof(playlistdata0));
			m_lc.RedrawItems(j,j+1);
				m_lc.SetItemState(j  ,m_lc.GetItemState(j  ,LVIS_SELECTED)|LVIS_SELECTED,LVIS_SELECTED);
				m_lc.SetItemState(j+1,m_lc.GetItemState(j+1,LVIS_SELECTED)&~LVIS_SELECTED,LVIS_SELECTED);
				i2=1;
			}
		}
		if(i2==0) break;
	}	
//	m_lc.RedrawWindow();
	Save();
}

void CPlayList::OnSDOWN()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	int i=m_lc.GetItemCount(),i2=0;
	CString s,s1;
	for(;;){i2=0;
		for(int j=i-1;j>0;j--){
			if((m_lc.GetItemState(j-1,LVIS_SELECTED)&LVIS_SELECTED)&&!(m_lc.GetItemState(j,LVIS_SELECTED)&LVIS_SELECTED)){
			playlistdata0 ppp;
			pc[j].icon=pc[j+1].icon=1;
			memcpy(&ppp,&pc[j-1],sizeof(playlistdata0));
			memcpy(&pc[j-1],&pc[j],sizeof(playlistdata0));
			memcpy(&pc[j],&ppp,sizeof(playlistdata0));
			m_lc.RedrawItems(j-1,j);
				m_lc.SetItemState(j  ,m_lc.GetItemState(j  ,LVIS_SELECTED)|LVIS_SELECTED,LVIS_SELECTED);
				m_lc.SetItemState(j-1,m_lc.GetItemState(j-1,LVIS_SELECTED)&~LVIS_SELECTED,LVIS_SELECTED);
				i2=1;
			}
		}
		if(i2==0) break;
	}	
//	m_lc.RedrawWindow();
	Save();
}

void CPlayList::OnDOWN()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	int i=m_lc.GetItemCount();
	CString s,s1;
	for(int j=i-1;j>0;j--){
		if((m_lc.GetItemState(j-1,LVIS_SELECTED)&LVIS_SELECTED)&&!(m_lc.GetItemState(j,LVIS_SELECTED)&LVIS_SELECTED)){
			playlistdata0 ppp;
			pc[j].icon=pc[j-1].icon=1;
			memcpy(&ppp,&pc[j-1],sizeof(playlistdata0));
			memcpy(&pc[j-1],&pc[j],sizeof(playlistdata0));
			memcpy(&pc[j],&ppp,sizeof(playlistdata0));
			m_lc.RedrawItems(j-1,j);

			m_lc.SetItemState(j  ,m_lc.GetItemState(j  ,LVIS_SELECTED)|LVIS_SELECTED,LVIS_SELECTED);
			m_lc.SetItemState(j-1,m_lc.GetItemState(j-1,LVIS_SELECTED)&~LVIS_SELECTED,LVIS_SELECTED);
		}
	}
//	m_lc.RedrawWindow();
	Save();
}

void CPlayList::OnXCHG(int i,int j)
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
			playlistdata0 ppp;
			pc[j].icon=pc[j-1].icon=1;
			memcpy(&ppp,&pc[i],sizeof(playlistdata0));
			memcpy(&pc[i],&pc[j],sizeof(playlistdata0));
			memcpy(&pc[j],&ppp,sizeof(playlistdata0));
}

extern COggDlg *og;
extern CString filen,fnn;

extern int modesub,ret2;
extern int loop1, loop2;

void CPlayList::Get(int i)
{
		fnn=pc[i].name; filen=pc[i].fol; modesub=pc[i].sub; loop1=pc[i].loop1; loop2=pc[i].loop2; ret2=pc[i].ret2;
		for(int k=0;k<playcnt;k++){
			m_lc.SetItemState(k,m_lc.GetItemState(k,LVIS_SELECTED)&~LVIS_SELECTED,LVIS_SELECTED);
		}
		m_lc.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);
		SIcon(i);
}

void CPlayList::OnLvnKeydownList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	if(pLVKeyDow->wVKey == VK_DELETE){
		Del();
	}
	*pResult = 0;
}


void CPlayList::OnDropFiles(HDROP hDropInfo)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	TCHAR filen_c[1024];
	syo=0;syos="";
	int ii=m_lc.GetItemCount();
	UINT cnt = DragQueryFile(hDropInfo,(UINT)-1,filen_c,sizeof(filen_c));
	TCHAR tmp[1024];
	_tgetcwd(tmp,1000);
		for(UINT i=0;i<cnt;i++){
			DragQueryFile(hDropInfo,(UINT)i,filen_c,sizeof(filen_c));
			Fol(filen_c);
		}
	_tchdir(tmp);
	if(syo==1 && (fade1==1 || playf==0) && !pMediaPosition){
		plcnt=ii;
		SIcon(ii);
	}
	if(syo==1 && m_renzoku.GetCheck()==FALSE){
		plcnt=ii;
		SIcon(ii);
		if(PathIsDirectory(syos)==FALSE)
			filen = syos;
		else
			filen = syos + L"\\" + fnn;
		og->dp(filen);
	}
	if(syo==1 && pMediaPosition){
		if(mode==-2 || videoonly==TRUE){
			REFTIME aa,bb;
			pMediaPosition->get_CurrentPosition(&aa);
			pMediaPosition->get_Duration(&bb);
			if(aa>=bb){
				if (PathIsDirectory(syos) == FALSE)
					filen = syos;
				else
					filen = syos + L"\\" + fnn;
				og->dp(filen);
			}
		}
	}
	if(syo==1 && (fade1==1 || playf==0) && !pMediaPosition){
		if (PathIsDirectory(syos) == FALSE)
			filen = syos;
		else
			filen = syos + L"\\" + fnn;
		og->dp(filen);
	}
	Save();
	CDialog::OnDropFiles(hDropInfo);
}

#include "Id3tagv1.h"
#include "Id3tagv2.h"

#include "vorbis/codec.h"
#include "vorbis/vorbisfile.h"
OggVorbis_File vf1;
extern BYTE bufimage[0x30000f];

// OggVorbisコールバック関数
extern size_t Callback_Read(
	void* ptr,
	size_t size,
	size_t nmemb,
	void* datasource
);

extern int Callback_Seek(
	void *datasource,
	ogg_int64_t offset,
	int whence
);

extern int Callback_Close(void *datasource);

extern long Callback_Tell(void *datasource);

extern ov_callbacks callbacks;

void CPlayList::Fol(CString fname)
{
	CString ft; 
	ft = "*.*";
	if (PathIsDirectory(fname) == FALSE) {
		CString ft1;
		ft1 = fname;
		ft = ft1.Right(ft1.GetLength()-ft1.ReverseFind(L'\\')-1);
	}
	CString s, ss;
	playlistdata p; ZeroMemory(&p, sizeof(p));
	CFileFind f;
	if (PathIsDirectory(fname) == FALSE) {
		CString ff = fname.Left(fname.ReverseFind('\\'));
		_tchdir(ff);
	}
	else {
		_tchdir(fname);
	}
	CString fname1 = fname;
	if (f.FindFile(ft)) {
		int b = 1;
		for (; b;) {
			b = f.FindNextFile();
			s = f.GetFileName();
			if (f.IsDirectory() == 0) {
				fname = fname1;
				BOOL a1 = PathIsDirectory(fname);
				if (a1) {
					fname = fname1 + L"\\" + s;
				}
				else {
					
				}
				//CString ff = fname.Left(fname.ReverseFind('\\'));
				//_tchdir(ff);
				ft = s;
				ft.MakeLower();
				CFile ff2;
				
				ff2.Open(s, CFile::modeRead | CFile::shareDenyNone, NULL);
				ff2.Read(bufimage, 2);
				ff2.Close();
				if (ft.Right(4) == ".ogg" || ft.Right(4) == ".OGG") {
					p.sub = -1;
					FILE *fp;
					fp = _tfopen(fname, _T("rb"));
					if (fp == NULL) {
						return;
					}

					if (ov_open_callbacks(fp, &vf1, NULL, 0, callbacks) < 0) {
						fclose(fp);
						return;
					}
					CString cc;
					_tcscpy(p.name, ft);
					p.alb[0] = p.art[0] = NULL;
					for (int iii = 0; iii < vf1.vc->comments; iii++) {
#if _UNICODE
						WCHAR f[1024];
						MultiByteToWideChar(CP_UTF8, 0, vf1.vc->user_comments[iii], -1, f, 1024);
						cc = f;
#else
						cc = vf1.vc->user_comments[iii];
#endif
						if (cc.Left(6) == "TITLE=")
						{
#if _UNICODE
							ss = UTF8toUNI(cc.Mid(6));
#else
							ss = UTF8toSJIS(cc.Mid(6));
#endif
							_tcscpy(p.name, ss);
						}
						if (cc.Left(7) == "ARTIST=")
						{
#if _UNICODE
							ss = UTF8toUNI(cc.Mid(7));
#else
							ss = UTF8toSJIS(cc.Mid(7));
#endif
							_tcscpy(p.art, ss);
						}
						if (cc.Left(6) == "ALBUM=")
						{
#if _UNICODE
							ss = UTF8toUNI(cc.Mid(6));
#else
							ss = UTF8toSJIS(cc.Mid(6));
#endif
							_tcscpy(p.alb, ss);
						}
						}
					ov_clear(&vf1);
					fclose(fp);

					//YS8 steam版用　bgmテーブル変換
					CString sss = fname.Left(fname.ReverseFind('\\')); ss = fname.Right(fname.GetLength() - fname.ReverseFind('\\') - 1);
					_tchdir(sss);
					if (ss.Left(3) == "y8_") {
						CFile f, ff;
						f.Open(L"..\\text\\bgmtbl.tbl", CFile::modeRead);
						ff.Open(L"bgmtbl.tbl.txt", CFile::modeWrite | CFile::modeCreate);
						for (int i = 0; i < f.GetLength(); i++) {
							BYTE b;
							f.Read(&b, 1);
							b = b << 4 | b >> 4;
							b ^= 0x0f;
							ff.Write(&b, 1);
						}
						ff.Close();
						f.Close();
					}
					//ys8用
					CStdioFile f;
					char *buff;
					int looping = 0;
					int igg;

					ss = ss.Left(ss.ReverseFind('.'));
					char file[256];
					WCHAR outcm[1024];
					WideCharToMultiByte(CP_ACP, 0, ss, 1024, file, 256, NULL, NULL);
					FILE *fp2;
					fp2 = fopen("bgmtbl.tbl.txt", "r");
					if (fp2) {
						buff = (char*)calloc(256, 1);
						for (;;) {
							if (fgets(buff, 256, fp2) == NULL) {
								free(buff); break;
							}
							char *p1 = strstr(buff, file);
							if (p1 == NULL) continue;
							p1 += strlen(file) + 1;
							for (; *p1 == 0x09; p1++);
							if (*p1 == '1') looping = 1;
							p1++;
							for (; *p1 == 0x09; p1++);
							typedef struct {
								char st[8];
								char a[1];
								char ed[8];
							} aa;
							aa *aa1;
							aa1 = (aa*)p1;
							int i, j;
							j = 0;
							for (i = 0; i < 8; i++) {
								switch (aa1->st[i])
								{
								case '0':
									j *= 10; j += 0;
									break;
								case '1':
									j *= 10; j += 1;
									break;
								case '2':
									j *= 10; j += 2;
									break;
								case '3':
									j *= 10; j += 3;
									break;
								case '4':
									j *= 10; j += 4;
									break;
								case '5':
									j *= 10; j += 5;
									break;
								case '6':
									j *= 10; j += 6;
									break;
								case '7':
									j *= 10; j += 7;
									break;
								case '8':
									j *= 10; j += 8;
									break;
								case '9':
									j *= 10; j += 9;
									break;
								}
							}
							loop1 = j;
							j = 0;
							for (i = 0; i < 8; i++) {
								switch (aa1->ed[i])
								{
								case '0':
									j *= 10; j += 0;
									break;
								case '1':
									j *= 10; j += 1;
									break;
								case '2':
									j *= 10; j += 2;
									break;
								case '3':
									j *= 10; j += 3;
									break;
								case '4':
									j *= 10; j += 4;
									break;
								case '5':
									j *= 10; j += 5;
									break;
								case '6':
									j *= 10; j += 6;
									break;
								case '7':
									j *= 10; j += 7;
									break;
								case '8':
									j *= 10; j += 8;
									break;
								case '9':
									j *= 10; j += 9;
									break;
								}
							}
							loop2 = j - loop1;
							p1 += sizeof(aa) + 1;
							for (; *p1 == 0x09; p1++);
							p1 += 3;
							char* pp = p1;
							for (; *p1 != 0xd; p1++) {
								if (*p1 == 0x9) {
									*p1 = 0x20;
								}
							}
							p1 = pp;
							MultiByteToWideChar(CP_ACP, 0, p1, -1, outcm, 1024);
							ss = outcm;
							_tcscpy(p.name, ss.Trim());
							if (looping == 0) {
								loop1 = loop2 = 0;
							}
							free(buff); break;
						}
						fclose(fp2);
					}

					//YSC
					sss = fname.Left(fname.ReverseFind('\\'));
					_tchdir(sss);
					ss = fname.Right(fname.GetLength() - fname.ReverseFind('\\') - 1);
					if (ss == "yc_b001.ogg") {
						ss = "バトル#58";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_b002.ogg") {
						ss = "灼熱の炎の中で";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_b003.ogg") {
						ss = "最終決戦";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_b004.ogg") {
						ss = "黒き翼";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_b005.ogg") {
						ss = "The False God of Causality";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_d101.ogg") {
						ss = "ダンジョン";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_d201.ogg") {
						ss = "道化師の誘い";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_d301.ogg") {
						ss = "地下遺跡";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_d401.ogg") {
						ss = "導きの塔～エルディールにくちづけを";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_d501.ogg") {
						ss = "失われし仮面を求めて";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_d701.ogg") {
						ss = "イリス";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_d702.ogg") {
						ss = "yc_d702";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_d703.ogg") {
						ss = "聖域";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_e001.ogg") {
						ss = "賢者";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_e002.ogg") {
						ss = "復活の儀式";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_e003.ogg") {
						ss = "レファンス";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_e004.ogg") {
						ss = "涙の少年剣士";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_e005.ogg") {
						ss = "エルディール";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_e006.ogg") {
						ss = "ロムン帝国 -嗚呼レオ団長-";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_e008.ogg") {
						ss = "yc_e008";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_e010.ogg") {
						ss = "冒険家、誕生";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_f101.ogg") {
						ss = "燃ゆる剣";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_f201.ogg") {
						ss = "セルセタの樹海";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_f301.ogg") {
						ss = "クレーター";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_f401.ogg") {
						ss = "THE DAWN OF YS";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_f501.ogg") {
						ss = "暁の森";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_f601.ogg") {
						ss = "一陣の風";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_f701.ogg") {
						ss = "神代の地";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_f801.ogg") {
						ss = "真実への序曲";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_f901.ogg") {
						ss = "雨上がりの朝に";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_over.ogg") {
						ss = "ゲームオーバー";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_t101.ogg") {
						ss = "辺境都市《キャスナン》";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_t201.ogg") {
						ss = "優しくなりたい";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_t301.ogg") {
						ss = "古代の伝承";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_t501.ogg") {
						ss = "RODA";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_title.ogg") {
						ss = "THEME OF ADOL 2012";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_op.ogg") {
						ss = "The Foliage Ocean in CELCETA -Opening size-";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_end.ogg") {
						ss = "新たな時代のステージへ";
						_tcscpy(p.name, ss);
					}

					//zero 
					CString ss;
					ss = fname.Right(fname.GetLength() - fname.ReverseFind(L'\\') - 1);
					sss = fname.Left(fname.ReverseFind('\\'));
					int fg = 0;
					CFile ffff;
					if (ffff.Open(sss + L"\\..\\text\\t_bgm._dt", CFile::modeRead)) { fg = 1; ffff.Close(); }
					CString zero = savedata.zero;
					if(zero != L"") if (ffff.Open(savedata.zero, CFile::modeRead)) { fg = 1; ffff.Close(); }
					if (ss.Mid(0, 3) == L"ed7" && fg == 1) {
						CString a;
						switch (_ttoi(ss.Mid(2, 4))) {
						case 7001:
							a = L"零の軌跡";
							break;
						case 7002:
							a = L"way of live -Opening Version-";
							break;
						case 7003:
							a = L"新しき日々～予兆";
							break;
						case 7005:
							a = L"想い破れて・・・";
							break;
						case 7052:
							a = L"碧い軌跡 -Opening size-";
							break;
						case 7053:
							a = L"それでも僕らは。";
							break;
						case 7100:
							a = L"街角の風景";
							break;
						case 7101:
							a = L"明日は明日の風が吹く";
							break;
						case 7102:
							a = L"クロスベルの午後";
							break;
						case 7103:
							a = L"During Mission Accomplishment";
							break;
						case 7104:
							a = L"創立記念祭";
							break;
						case 7105:
							a = L"降水確率10%";
							break;
						case 7106:
							a = L"風船と紙吹雪";
							break;
						case 7110:
							a = L"特務支援課";
							break;
						case 7111:
							a = L"C.S.P.D. -クロスベル警察";
							break;
						case 7113:
							a = L"Arc-en-ciel";
							break;
						case 7114:
							a = L"黒月貿易公司";
							break;
						case 7116:
							a = L"IGNIS";
							break;
						case 7117:
							a = L"TRINITY";
							break;
						case 7120:
							a = L"アルモリカ村";
							break;
						case 7121:
							a = L"鉱山町マインツ";
							break;
						case 7122:
							a = L"Killing Bear";
							break;
						case 7123:
							a = L"聖ウルスラ医科大学";
							break;
						case 7124:
							a = L"クロスベル大聖堂";
							break;
						case 7125:
							a = L"黒の競売会";
							break;
						case 7126:
							a = L"大国にはさまれて";
							break;
						case 7150:
							a = L"新たなる日常";
							break;
						case 7151:
							a = L"動き始めた事態";
							break;
						case 7160:
							a = L"ミシュラムワンダーランド";
							break;
						case 7161:
							a = L"束の間の休息";
							break;
						case 7162:
							a = L"ささやかな晩餐";
							break;
						case 7200:
							a = L"水と草木と青い空";
							break;
						case 7201:
							a = L"片手にはレモネード";
							break;
						case 7202:
							a = L"木霊の道";
							break;
						case 7203:
							a = L"古の鼓動";
							break;
						case 7204:
							a = L"On The Green Road";
							break;
						case 7205:
							a = L"鉄橋を越えて";
							break;
						case 7250:
							a = L"木洩れ日の中の静寂";
							break;
						case 7251:
							a = L"偽りの楽土を越えて";
							break;
						case 7300:
							a = L"ジオフロント";
							break;
						case 7301:
							a = L"七耀の煌き";
							break;
						case 7302:
							a = L"ルバーチェ商会";
							break;
						case 7303:
							a = L"鳴るはずのない鐘";
							break;
						case 7304:
							a = L"忘れられし幻夢の狭間";
							break;
						case 7305:
							a = L"A Light Illuminating The Depths";
							break;
						case 7350:
							a = L"Dの残影";
							break;
						case 7351:
							a = L"異変の兆し";
							break;
						case 7352:
							a = L"Mystic Core";
							break;
						case 7353:
							a = L"最果ての樹";
							break;
						case 7354:
							a = L"暴魔の呼び声";
							break;
						case 7356:
							a = L"不明";
							break;
						case 7400:
							a = L"Get Over The Barrier!";
							break;
						case 7401:
							a = L"Arrest The Criminal";
							break;
						case 7402:
							a = L"Formidable Enemy";
							break;
						case 7403:
							a = L"Stand Up Battle Formation Again!";
							break;
						case 7404:
							a = L"Inevitable Struggle";
							break;
						case 7405:
							a = L"Demonic Drive";
							break;
						case 7406:
							a = L"Arrival Existence";
							break;
						case 7408:
							a = L"これが俺たちの力だ!";
							break;
						case 7450:
							a = L"Seize The Truth!";
							break;
						case 7451:
							a = L"Concentrate All Firepower!!";
							break;
						case 7452:
							a = L"Conflicting Passions";
							break;
						case 7453:
							a = L"Unexpected Emergency";
							break;
						case 7454:
							a = L"Mythtic Roar";
							break;
						case 7455:
							a = L"Destruction Impulse";
							break;
						case 7458:
							a = L"Unfathomed Force";
							break;
						case 7459:
							a = L"The Azure Arbitrator";
							break;
						case 7460:
							a = L"効果音";
							break;
						case 7500:
							a = L"金の太陽、銀の月　-陽の熱情";
							break;
						case 7501:
							a = L"金の太陽、銀の月　-月の慕情";
							break;
						case 7502:
							a = L"金の太陽、銀の月　-童心";
							break;
						case 7503:
							a = L"金の太陽、銀の月　-運命の刻";
							break;
						case 7504:
							a = L"金の太陽、銀の月　-譲れぬ想い";
							break;
						case 7505:
							a = L"金の太陽、銀の月　-幾千の夜を越えて";
							break;
						case 7506:
							a = L"金の太陽、銀の月　-夜明け～大団円";
							break;
						case 7507:
							a = L"Intense Chase";
							break;
						case 7509:
							a = L"守りぬく意志";
							break;
						case 7510:
							a = L"叡智への誘い";
							break;
						case 7511:
							a = L"危地";
							break;
						case 7512:
							a = L"揺るぎない強さ";
							break;
						case 7513:
							a = L"夜景に霞む星空";
							break;
						case 7514:
							a = L"いつかきっと";
							break;
						case 7515:
							a = L"柔らかな心";
							break;
						case 7516:
							a = L"点と線";
							break;
						case 7517:
							a = L"一触即発";
							break;
						case 7518:
							a = L"Foolish Gig";
							break;
						case 7519:
							a = L"リベールからの風";
							break;
						case 7520:
							a = L"とどいた想い";
							break;
						case 7521:
							a = L"Underground Kids";
							break;
						case 7522:
							a = L"Terminal Room";
							break;
						case 7523:
							a = L"響きあう心";
							break;
						case 7524:
							a = L"Limit Break";
							break;
						case 7525:
							a = L"パラダイスミ☆";
							break;
						case 7526:
							a = L"Gnosis";
							break;
						case 7527:
							a = L"Get Over The Barrier! -Roaring Version-";
							break;
						case 7528:
							a = L"それぞれの明日";
							break;
						case 7529:
							a = L"効果音楽1";
							break;
						case 7530:
							a = L"効果音楽2";
							break;
						case 7531:
							a = L"効果音楽3";
							break;
						case 7532:
							a = L"効果音楽4";
							break;
						case 7533:
							a = L"踏み出す勇気";
							break;
						case 7534:
							a = L"その背中を見つめて";
							break;
						case 7540:
							a = L"不明";
							break;
						case 7541:
							a = L"不明";
							break;
						case 7542:
							a = L"不明";
							break;
						case 7543:
							a = L"不明";
							break;
						case 7544:
							a = L"不明";
							break;
						case 7550:
							a = L"オルキスタワー";
							break;
						case 7551:
							a = L"Catastrophe";
							break;
						case 7552:
							a = L"碧き雫";
							break;
						case 7553:
							a = L"神機降臨";
							break;
						case 7554:
							a = L"ふるわれる奇蹟";
							break;
						case 7555:
							a = L"予定外の奇蹟";
							break;
						case 7556:
							a = L"鋼鉄の咆哮 -脅威-";
							break;
						case 7560:
							a = L"雨の日の真実";
							break;
						case 7561:
							a = L"不穏";
							break;
						case 7562:
							a = L"効果音";
							break;
						case 7563:
							a = L"犠牲の先の希望";
							break;
						case 7564:
							a = L"Strange Feel";
							break;
						case 7565:
							a = L"Exhilarating Ride";
							break;
						case 7566:
							a = L"それぞれの正義";
							break;
						case 7567:
							a = L"乗り越えるべき壁";
							break;
						case 7568:
							a = L"月下の想い";
							break;
						case 7569:
							a = L"Miss You";
							break;
						case 7570:
							a = L"天の車";
							break;
						case 7571:
							a = L"突きつけられた現実";
							break;
						case 7572:
							a = L"効果音";
							break;
						case 7573:
							a = L"全てを識るもの";
							break;
						case 7574:
							a = L"想い、辿り着く場所";
							break;
						case 7575:
							a = L"揺れ動く心";
							break;
						case 7576:
							a = L"星降る夜に";
							break;
						case 7577:
							a = L"効果音";
							break;
						case 7578:
							a = L"効果音";
							break;
						case 7579:
							a = L"効果音";
							break;
						case 7580:
							a = L"効果音";
							break;
						case 7581:
							a = L"本当の絆";
							break;
						case 7582:
							a = L"猛き獣たち";
							break;
						case 7583:
							a = L"西ゼムリア通商会議";
							break;
						case 7584:
							a = L"効果音";
							break;
						case 7585:
							a = L"千年の妄執";
							break;
						case 7586:
							a = L"鋼鉄の咆哮 -死線-";
							break;
						case 7587:
							a = L"ポムっと! -お花見団子の逆襲-";
							break;
						case 7588:
							a = L"Fateful Confrontation -ポムっと! Ver.-";
							break;
						case 7589:
							a = L"ポムりますか";
							break;
						case 7590:
							a = L"エリィ絶叫コースター";
							break;
						case 7591:
							a = L"小さな英雄 -オルゴール-";
							break;
						case 7592:
							a = L"TOWER OF THE SHADOW OF DEATH -Jukebox-";
							break;
						}
						_tcscpy(p.name, a);
					}
					_tcscpy(p.fol, fname1);
					p.loop1 = p.loop2 = 0;
						}
				else if (fname.Right(fname.GetLength() - fname.ReverseFind('\\') - 1).Mid(0,3) == L"ed8" && (ft.Right(4) == ".wav")) {
					p.sub = 21; p.loop1 = p.loop2 = 0;
					CString a = fname.Right(fname.GetLength() - fname.ReverseFind('\\') - 1);
					switch (_ttoi(a.Mid(2, 4))) {
					case 8001:
						a = L"特科クラス《VII組》";
						break;
					case 8002:
						a = L"ただひたすらに、前へ";
						break;
					case 8100:
						a = L"近郊都市トリスタ";
						break;
					case 8101:
						a = L"交易町ケルディック";
						break;
					case 8102:
						a = L"翡翠の公都バリアハート";
						break;
					case 8103:
						a = L"湖畔の街レグラム";
						break;
					case 8104:
						a = L"黒銀の鋼都ルーレ";
						break;
					case 8106:
						a = L"遊牧民の集落";
						break;
					case 8107:
						a = L"緋の帝都ヘイムダル";
						break;
					case 8108:
						a = L"癒しの我が家";
						break;
					case 8109:
						a = L"ダイニングバー《F》";
						break;
					case 8110:
						a = L"常在戦場の気概";
						break;
					case 8111:
						a = L"ガレリアの巨壁";
						break;
					case 8120:
						a = L"足湯の温もり";
						break;
					case 8121:
						a = L"静寂の郷";
						break;
					case 8122:
						a = L"明日への休息";
						break;
					case 8123:
						a = L"春の陽射し";
						break;
					case 8125:
						a = L"カレイジャス発進！";
						break;
					case 8126:
						a = L"目覚める意志";
						break;
					case 8127:
						a = L"白銀の巨船";
						break;
					case 8150:
						a = L"放課後の時間";
						break;
					case 8152:
						a = L"さわやかな朝";
						break;
					case 8153:
						a = L"雨音の学院";
						break;
					case 8154:
						a = L"爽やかな陽射し";
						break;
					case 8156:
						a = L"トールズ士官学院祭";
						break;
					case 8158:
						a = L"青空の開放感";
						break;
					case 8159:
						a = L"自由行動日";
						break;
					case 8200:
						a = L"異郷の空";
						break;
					case 8201:
						a = L"峡谷道を往く";
						break;
					case 8202:
						a = L"精霊の小道";
						break;
					case 8203:
						a = L"蒼穹の大地";
						break;
					case 8210:
						a = L"戦火を越えて";
						break;
					case 8212:
						a = L"Trudge Along";
						break;
					case 8213:
						a = L"冬の訪れ";
						break;
					case 8300:
						a = L"旧校舎の謎";
						break;
					case 8301:
						a = L"探索";
						break;
					case 8302:
						a = L"深淵へ向かう";
						break;
					case 8303:
						a = L"聖女の城";
						break;
					case 8304:
						a = L"明日を掴むために";
						break;
					case 8305:
						a = L"地下に眠る遺構";
						break;
					case 8308:
						a = L"世の礎たるために";
						break;
					case 8310:
						a = L"精霊窟";
						break;
					case 8311:
						a = L"不明";
						break;
					case 8312:
						a = L"Phantasmal Blaze";
						break;
					case 8313:
						a = L"夢幻回廊";
						break;
					case 8315:
						a = L"幻煌";
						break;
					case 8400:
						a = L"The Glint of Cold Steel";
						break;
					case 8401:
						a = L"Tie a Link of ARCUS!";
						break;
					case 8402:
						a = L"Belief";
						break;
					case 8403:
						a = L"Even if Driven to the Wall";
						break;
					case 8404:
						a = L"Eliminate Crisis!";
						break;
					case 8405:
						a = L"Exceed!";
						break;
					case 8406:
						a = L"Don't be Defeated by a Friend!";
						break;
					case 8407:
						a = L"Machinery Attack";
						break;
					case 8408:
						a = L"巨イナルチカラ";
						break;
					case 8409:
						a = L"The Decisive Collision";
						break;
					case 8410:
						a = L"この手で道を切り拓く!";
						break;
					case 8411:
						a = L"赤点です...";
						break;
					case 8412:
						a = L"Unknown Threat";
						break;
					case 8413:
						a = L"不明";
						break;
					case 8420:
						a = L"Heated Mind";
						break;
					case 8421:
						a = L"不明";
						break;
					case 8423:
						a = L"Impatient";
						break;
					case 8424:
						a = L"Severe Blow";
						break;
					case 8426:
						a = L"Transcend Beat";
						break;
					case 8429:
						a = L"Blue Destination";
						break;
					case 8430:
						a = L"Heteromorphy";
						break;
					case 8431:
						a = L"輝ける明日へ";
						break;
					case 8435:
						a = L"迫る巨影";
						break;
					case 8441:
						a = L"E.O.V";
						break;
					case 8442:
						a = L"不明";
						break;
					case 8500:
						a = L"Strain";
						break;
					case 8501:
						a = L"夜のひととき";
						break;
					case 8502:
						a = L"トラブル発生";
						break;
					case 8503:
						a = L"鉄路遥々";
						break;
					case 8504:
						a = L"旅愁";
						break;
					case 8505:
						a = L"皇城にて";
						break;
					case 8506:
						a = L"Let's Study";
						break;
					case 8507:
						a = L"知恵を絞って";
						break;
					case 8508:
						a = L"実技教練";
						break;
					case 8509:
						a = L"寮に帰ろう";
						break;
					case 8510:
						a = L"アーベントタイム";
						break;
					case 8512:
						a = L"鉄の統率";
						break;
					case 8513:
						a = L"暗躍";
						break;
					case 8514:
						a = L"想いの行き先";
						break;
					case 8515:
						a = L"傷心";
						break;
					case 8516:
						a = L"揺らめく炎を見つめて";
						break;
					case 8517:
						a = L"一途な気持ち";
						break;
					case 8520:
						a = L"臨戦態勢";
						break;
					case 8521:
						a = L"Seriousness";
						break;
					case 8522:
						a = L"静かなる昂揚";
						break;
					case 8523:
						a = L"暖かな夕餉";
						break;
					case 8524:
						a = L"Atrocious Raid";
						break;
					case 8525:
						a = L"全てを賭して今、ここに立つ";
						break;
					case 8527:
						a = L"新しい仲間たち";
						break;
					case 8528:
						a = L"不透明な事態";
						break;
					case 8529:
						a = L"鉄血へのレクイエム";
						break;
					case 8530:
						a = L"幻想の唄 -PHANTASMAGORIA-";
						break;
					case 8531:
						a = L"刻ハ至レリ";
						break;
					case 8532:
						a = L"目覚めし伝承";
						break;
					case 8533:
						a = L"唯一の希望";
						break;
					case 8535:
						a = L"不明";
						break;
					case 8537:
						a = L"不明";
						break;
					case 8538:
						a = L"今はまだ...";
						break;
					case 8539:
						a = L"あの日に見た夜空";
						break;
					case 8540:
						a = L"偽りの時間";
						break;
					case 8541:
						a = L"紅き翼 -新たなる風-";
						break;
					case 8550:
						a = L"再会";
						break;
					case 8551:
						a = L"かけがえのない人へ";
						break;
					case 8552:
						a = L"惜しむように、愛おしむように";
						break;
					case 8553:
						a = L"ライノの花が咲く頃";
						break;
					case 8555:
						a = L"戦場の掟";
						break;
					case 8556:
						a = L"Remaining Glow";
						break;
					case 8557:
						a = L"深淵の魔女";
						break;
					case 8558:
						a = L"ALTINA";
						break;
					case 8559:
						a = L"威風";
						break;
					case 8560:
						a = L"一撃に賭ける";
						break;
					case 8561:
						a = L"ユミル渓谷道";
						break;
					case 8562:
						a = L"Awakening";
						break;
					case 8563:
						a = L"Blitzkrieg";
						break;
					case 8564:
						a = L"魔王の凱歌";
						break;
					case 8566:
						a = L"内なる黄昏";
						break;
					case 8567:
						a = L"蘇る記憶";
						break;
					case 8570:
						a = L"静かな決意";
						break;
					case 8571:
						a = L"乾坤一擲";
						break;
					case 8572:
						a = L"交戦";
						break;
					case 8573:
						a = L"効果音";
						break;
					case 8600:
						a = L"大市の賑わい";
						break;
					case 8601:
						a = L"剣の遊戯";
						break;
					case 8602:
						a = L"紙一重の攻防";
						break;
					case 8603:
						a = L"走れマッハ号!";
						break;
					case 8605:
						a = L"効果音";
						break;
					case 8606:
						a = L"効果音";
						break;
					case 8607:
						a = L"星屑のカンタータ";
						break;
					case 8608:
						a = L"効果音";
						break;
					case 8609:
						a = L"Sonata No.45";
						break;
					case 8610:
						a = L"効果音";
						break;
					case 8620:
						a = L"雪ウサギを追いかけて";
						break;
					case 8621:
						a = L"Take The Windward!";
						break;
					case 8622:
						a = L"効果音";
						break;
					case 8623:
						a = L"効果音";
						break;
					case 8624:
						a = L"効果音";
						break;
					case 8625:
						a = L"効果音";
						break;
					case 8627:
						a = L"効果音";
						break;
					case 8628:
						a = L"不明";
						break;
					case 8629:
						a = L"効果音";
						break;
					case 8700:
						a = L"音楽";
						break;
					case 8703:
						a = L"音楽";
						break;
					case 8704:
						a = L"音楽";
						break;
					case 8710:
						a = L"音楽";
						break;
					case 8711:
						a = L"音楽";
						break;
					}
					_tcscpy(p.name, a);
					_tcscpy(p.fol, fname1);
				}
				else if (ft.Right(5) == ".opus") {
					p.sub = -6; p.loop1 = p.loop2 = 0;
					CString a = fname.Right(fname.GetLength() - fname.ReverseFind('\\') - 1);
					CString b = a.Mid(6, 1);
					int err;
					switch (_ttoi(a.Mid(2, 4))) {
					case 8001:
						a = "特科クラス《VII組》";
						break;
					case 8002:
						a = "スタートライン";
						break;
					case 8003:
						a = "不明";
						break;
					case 8004:
						a = "Youthful Victory";
						break;
					case 8006:
						a = "ただひたすらに、前へ";
						break;
					case 8007:
						a = "縁 -つなぐもの-";
						break;
					case 8102:
						a = "翡翠の公都バリアハート";;
						break;
					case 8104:
						a = "黒銀の鋼都ルーレ";
						break;
					case 8150:
						a = "下校途中にパンケーキ";
						break;
					case 8151:
						a = "可能性は無限大";
						break;
					case 8152:
						a = "夜のしじまに";
						break;
					case 8153:
						a = "夕景";
						break;
					case 8154:
						a = "新しい朝";
						break;
					case 8155:
						a = "束の間の里帰り";
						break;
					case 8156:
						a = "白亜の旧都セントアーク";
						break;
					case 8157:
						a = "紡績町パルム";
						break;
					case 8158:
						a = "籠の中のクロスベル";
						break;
					case 8159:
						a = "今、成すべきこと";
						break;
					case 8160:
						a = "歓楽都市ラクウェル";
						break;
					case 8161:
						a = "静かなる駆け引き";
						break;
					case 8162:
						a = "赫奕たるヘイムダル";
						break;
					case 8163:
						a = "紺碧の海都オルディス";
						break;
					case 8164:
						a = "最前線都市";
						break;
					case 8165:
						a = "Base Camp";
						break;
					case 8166:
						a = "精強なる兵たち";
						break;
					case 8168:
						a = "不明";
						break;
					case 8170:
						a = "隠れ里エリン";
						break;
					case 8171:
						a = "潜入調査";
						break;
					case 8172:
						a = "昏冥の中で";
						break;
					case 8173:
						a = "紅き閃影 -光まとう翼-";
						break;
					case 8174:
						a = "聖ウルスラ医科大学 -閃Ver.-";
						break;
					case 8175:
						a = "一抹の不安、一縷の望み";
						break;
					case 8176:
						a = "Lyrical Amber";
						break;
					case 8177:
						a = "水面を渡る風";
						break;
					case 8250:
						a = "流れる雲の彼方に";
						break;
					case 8251:
						a = "静寂の小路";
						break;
					case 8252:
						a = "崖谷の狭間";
						break;
					case 8253:
						a = "Weathering Road";
						break;
					case 8260:
						a = "彼の地へ向かって";
						break;
					case 8261:
						a = "終焉の途へ";
						break;
					case 8262:
						a = "全てを識るもの -閃Ver.-";
						break;
					case 8263:
						a = "たそがれ緑道";
						break;
					case 8311:
						a = "不明";
						break;
					case 8350:
						a = "アインヘル小要塞";
						break;
					case 8351:
						a = "伝承の裏で";
						break;
					case 8352:
						a = "Unplanned Residue";
						break;
					case 8353:
						a = "忘れられし幻夢の狭間 -閃Ver.-";
						break;
					case 8354:
						a = "幽世の気配";
						break;
					case 8355:
						a = "solid as the Rock of JUNO";
						break;
					case 8356:
						a = "地下に巣喰う";
						break;
					case 8359:
						a = "Spiral of Erebos";
						break;
					case 8360:
						a = "鋼の障壁";
						break;
					case 8363:
						a = "Break In";
						break;
					case 8365:
						a = "サングラール迷宮";
						break;
					case 8366:
						a = "静けき森の魔女";
						break;
					case 8367:
						a = "Mystic Core -閃Ver.-";
						break;
					case 8368:
						a = "斉いし舞台";
						break;
					case 8369:
						a = "シンクロニシティ #23";
						break;
					case 8371:
						a = "世界の命運を賭けて";
						break;
					case 8372:
						a = "The End of -SAGA-";
						break;
					case 8429:
						a = "不明";
						break;
					case 8450:
						a = "Brave Steel";
						break;
					case 8451:
						a = "Toughness!!";
						break;
					case 8452:
						a = "剣戟怒涛";
						break;
					case 8453:
						a = "Proud Grudge";
						break;
					case 8454:
						a = "チープ・トラップ";
						break;
					case 8455:
						a = "STEP AHEAD";
						break;
					case 8456:
						a = "劣勢を挽回せよ！";
						break;
					case 8457:
						a = "Abrupt Visitor";
						break;
					case 8458:
						a = "行き着く先 -Opening Size-";
						break;
					case 8460:
						a = "Lift-off!";
						break;
					case 8461:
						a = "Accursed Tycoon";
						break;
					case 8464:
						a = "One-Way to the Netherworld";
						break;
					case 8465:
						a = "不明";
						break;
					case 8466:
						a = "Erosion of Madness";
						break;
					case 8467:
						a = "DOOMSDAY TRANCE";
						break;
					case 8468:
						a = "不明";
						break;
					case 8472:
						a = "Malicious Fiend";
						break;
					case 8473:
						a = "Unlikely Combination";
						break;
					case 8474:
						a = "Robust One";
						break;
					case 8475:
						a = "古の盟約";
						break;
					case 8476:
						a = "七の相克 -EXCELLION KRIEG-";
						break;
					case 8477:
						a = "Burning Throb";
						break;
					case 8478:
						a = "Neck or Nothing";
						break;
					case 8479:
						a = "Majestic Roar";
						break;
					case 8480:
						a = "With Our Own Hands!!";
						break;
					case 8500:
						a = "授業は合同で";
						break;
					case 8501:
						a = "Power or Technique";
						break;
					case 8502:
						a = "Briefing Time";
						break;
					case 8503:
						a = "第II分校の日常";
						break;
					case 8504:
						a = "充実したひととき";
						break;
					case 8505:
						a = "異端の研究者";
						break;
					case 8506:
						a = "君に伝えたいこと";
						break;
					case 8507:
						a = "不明";
						break;
					case 8508:
						a = "不明";
						break;
					case 8509:
						a = "張り詰めた思惑";
						break;
					case 8510:
						a = "混迷の対立";
						break;
					case 8511:
						a = "急転直下";
						break;
					case 8512:
						a = "蠢く陰謀";
						break;
					case 8513:
						a = "託されたもの";
						break;
					case 8514:
						a = "羅刹の薫陶";
						break;
					case 8515:
						a = "ハーメル -遺されたもの-";
						break;
					case 8516:
						a = "Welcome Back! アーベントタイム(ラジオ)";
						break;
					case 8517:
						a = "夏至祭";
						break;
					case 8519:
						a = "夏至祭";
						break;
					case 8520:
						a = "翡翠庭園";
						break;
					case 8521:
						a = "初めての円舞曲";
						break;
					case 8522:
						a = "真打ち登場！";
						break;
					case 8524:
						a = "Tragedy";
						break;
					case 8528:
						a = "僅かな希望の先に";
						break;
					case 8530:
						a = "帰路へ";
						break;
					case 8532:
						a = "Roots of Scar";
						break;
					case 8534:
						a = "想い千里を走り";
						break;
					case 8536:
						a = "光射す空の下で";
						break;
					case 8539:
						a = "不明";
						break;
					case 8541:
						if (b == L"b")
							a = "空を見上げて -Eliot Ver.-";
						else
							a = "空を見上げて -Eliot Ver.-";
						break;
					case 8542:
						a = "不明";
						break;
					case 8543:
						a = "不明";
						break;
					case 8544:
						a = "Little Rain";
						break;
					case 8545:
						a = "暗雲";
						break;
					case 8546:
						a = "鐘、鳴り響く時";
						break;
					case 8547:
						a = "巨イナル黄昏";
						break;
					case 8548:
						a = "あの日の約束";
						break;
					case 8551:
						a = "不明";
						break;
					case 8553:
						a = "Sensitive Talk";
						break;
					case 8554:
						a = "哀花";
						break;
					case 8555:
						a = "Feel at Home";
						break;
					case 8556:
						a = "幾千万の夜を越えて";
						break;
					case 8557:
						a = "不明";
						break;
					case 8558:
						a = "不明";
						break;
					case 8559:
						a = "優しき微睡み";
						break;
					case 8560:
						a = "最悪の最善手";
						break;
					case 8562:
						a = "黒の真実";
						break;
					case 8563:
						a = "いつでもそばに";
						break;
					case 8564:
						a = "その温もりは小さいけれど。";
						break;
					case 8566:
						a = "それでも前へ";
						break;
					case 8570:
						a = "想いひとつに";
						break;
					case 8571:
						a = "千年要塞";
						break;
					case 8572:
						a = "不明";
						break;
					case 8573:
						a = "せめてこの夜に誓って";
						break;
					case 8574:
						a = "Constraint";
						break;
					case 8575:
						a = "過ぎ去りし日々";
						break;
					case 8576:
						a = "不明";
						break;
					case 8577:
						a = "それぞれの覚悟";
						break;
					case 8578:
						a = "無明の闇の中で";
						break;
					case 8579:
						a = "変わる世界 -闇の底から-";
						break;
					case 8600:
						a = "不明";
						break;
					case 8601:
						a = "ゲートイン";
						break;
					case 8602:
						a = "不明(空の軌跡)";
						break;
					case 8603:
						a = "女神はいつも見ています";
						break;
					case 8604:
						a = "不明(空の軌跡)";
						break;
					case 8605:
						a = "不明";
						break;
					case 8606:
						a = "不明";
						break;
					case 8608:
						a = "不明";
						break;
					case 8610:
						a = "不明";
						break;
					case 8611:
						a = "不明";
						break;
					case 8612:
						a = "不明";
						break;
					case 8613:
						a = "不明";
						break;
					case 8614:
						a = "不明";
						break;
					case 8616:
						a = "不明";
						break;
					case 8617:
						a = "不明";
						break;
					case 8618:
						a = "不明";
						break;
					case 8619:
						a = "不明";
						break;
					case 8620:
						a = "不明";
						break;
					case 8621:
						a = "不明";
						break;
					case 8702:
						a = "Master's Vertex";
						break;
					case 8706:
						a = "Endure Grief";
						break;
					case 8707:
						a = "Intuition and Insight";
						break;
					case 8708:
						a = "Bold Assailants";
						break;
					case 8709:
						a = "Seductive Shudder";
						break;
					case 8711:
						a = "Blue Stardust";
						break;
					case 8713:
						a = "Pleasure Smile";
						break;
					case 8714:
						a = "巨竜目覚める";
						break;
					case 8715:
						a = "未来へ。";
						break;
					case 8716:
						a = "明日への軌跡 -Instrumental Ver.-";
						break;
					case 8717:
						a = "Deep Carnival";
						break;
					case 8718:
						a = "不明";
						break;
					case 8719:
						a = "Chain Chain Chain!";
						break;
					case 8720:
						a = "明日への軌跡";
						break;
					case 8721:
						a = "愛の詩(歌)";
						break;
					case 8722:
						a = "Celestial Coalescence";
						break;
					case 8800:
						a = "Vantage Masters";
						break;
					case 8801:
						a = "Concept H.M.I.";
						break;
					case 8802:
						a = "風よりも駿く";
						break;
					case 8803:
						a = "Brilliant Escape";
						break;
					case 8810:
						a = "不明";
						break;
					case 8811:
						a = "不明";
						break;
					case 8812:
						a = "不明";
						break;
					case 8910:
						a = "不明";
						break;
					case 8911:
						a = "不明";
						break;
					case 8912:
						a = "不明";
						break;
					case 8913:
						a = "不明";
						break;
					case 8916:
						a = "不明";
						break;
					case 8917:
						a = "不明";
						break;
					case 8918:
						a = "不明";
						break;
					case 8919:
						a = "不明";
						break;
					case 8920:
						a = "不明";
						break;
					case 8921:
						a = "不明";
						break;

					}
					_tcscpy(p.name, a);
					_tcscpy(p.fol, fname1);
				}
				else if (ft.Right(4) == ".mp3" || ft.Right(4) == ".MP3" || ft.Right(4) == ".mp2" || ft.Right(4) == ".MP2" ||
					ft.Right(4) == ".mp1" || ft.Right(4) == ".MP1" || ft.Right(4) == ".rmp" || ft.Right(4) == ".RMP") {
					p.sub = -10; p.loop1 = p.loop2 = 0;
					_tcscpy(p.fol, fname1);
					CId3tagv1 ta1p;
					CId3tagv2 ta2p;
					int b = ta2p.Load(fname);
					ss = ta2p.GetArtist(); if (b == -1) { ta1p.Load(fname); ss = ta1p.GetArtist(); } _tcscpy(p.art, ss);
					ss = ta2p.GetTitle(); if (b == -1) ss = ta1p.GetTitle(); if (ss == "")ss = ft; _tcscpy(p.name, ss);
					ss = ta2p.GetAlbum(); if (b == -1) ss = ta1p.GetAlbum(); _tcscpy(p.alb, ss);
				}
				else if ((bufimage[0] == 0xff && (bufimage[1] & 0xf0 == 0xf0)) && (ft.Right(4) == ".aac" || ft.Right(4) == ".AAC")) {
					p.sub = -9;
					_tcscpy(p.name, ft);
					_tcscpy(p.fol, fname1);
				}
				else if ((ft.Right(4) == ".dsf" || ft.Right(4) == ".DSF" || ft.Right(4) == ".dff" || ft.Right(4) == ".DFF" || ft.Right(4) == ".wsd" || ft.Right(4) == ".WSD")) {
					CString tagfile, tagname, tagalbum;
					ULONGLONG po;
					og->dsdload(fname,tagfile, tagname, tagalbum,po, 1);
					og->dsdclose();
					_tcscpy(p.name, tagfile);
					_tcscpy(p.alb, tagalbum);
					_tcscpy(p.art, tagname);
					_tcscpy(p.fol, fname1);
					p.sub = -7; p.loop1 = p.loop2 = 0;
				}
				else if ((ft.Right(4) == ".m4a" || ft.Right(4) == ".M4A" || ft.Right(4) == ".aac" || ft.Right(4) == ".AAC")) {
					CFile ff;
					char buf[1024];
					TCHAR kpi[512];
					ff.Open(fname, CFile::modeRead | CFile::shareDenyNone, NULL);
					int flg, read = ff.Read(bufimage, sizeof(bufimage));
					ff.Close();
					kpi[0] = 0;
					plugs(s, &p, kpi);
					if (kpi[0] == 0)
						p.sub = -3;
					else
						p.sub = -2;
					if (savedata.m4a == 1)
						p.sub = -9;
					_tcscpy(p.name, ft);
					_tcscpy(p.fol, fname1);
					flg = 0;
					int i;
					for (i = 0; i < read - 4; i++) {
						if (bufimage[i] == 'u' && bufimage[i + 1] == 'd' && bufimage[i + 2] == 't' && bufimage[i + 3] == 'a') {
							int j;
							for (j = i + 4; j < read - 4; j++) {
								if (bufimage[j] == 'a' && bufimage[j + 1] == 'l' && bufimage[j + 2] == 'b' && bufimage[j + 7] == 'd' && bufimage[j + 8] == 'a' && bufimage[j + 9] == 't' && bufimage[j + 10] == 'a') {
									j += 19;
									for (int k = j; k < read - 4; k++) {
										if (bufimage[k] == 0) {
											flg = 1;
											buf[k - j] = 0;
											buf[k - j + 1] = 0;
											buf[k - j + 2] = 0;
											break;
										}
										buf[k - j] = bufimage[k];
									}
								}
								if (flg == 1) {
									const int wlen = ::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), NULL, 0);
									TCHAR* buff = new TCHAR[wlen + 1];
									if (::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), buff, wlen))
									{
										buff[wlen] = _T('\0');
									}
									wcscpy(p.alb, buff);
									delete[] buff;
									flg = 0;
									break;
								}
							}
							for (j = i + 4; j < read - 4; j++) {
								if (bufimage[j] == 'A' && bufimage[j + 1] == 'R' && bufimage[j + 2] == 'T' && bufimage[j + 7] == 'd' && bufimage[j + 8] == 'a' && bufimage[j + 9] == 't' && bufimage[j + 10] == 'a') {
									j += 19;
									for (int k = j; k < read - 4; k++) {
										if (bufimage[k] == 0) {
											flg = 1;
											buf[k - j] = 0;
											buf[k - j + 1] = 0;
											buf[k - j + 2] = 0;
											break;
										}
										buf[k - j] = bufimage[k];
									}
								}
								if (flg == 1) {
									const int wlen = ::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), NULL, 0);
									TCHAR* buff = new TCHAR[wlen + 1];
									if (::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), buff, wlen))
									{
										buff[wlen] = _T('\0');
									}
									wcscpy(p.art, buff);
									delete[] buff;
									flg = 0;
									break;
								}
							}
							for (j = i + 4; j < read - 4; j++) {
								if (bufimage[j] == 'n' && bufimage[j + 1] == 'a' && bufimage[j + 2] == 'm' && bufimage[j + 7] == 'd' && bufimage[j + 8] == 'a' && bufimage[j + 9] == 't' && bufimage[j + 10] == 'a') {
									j += 19;
									for (int k = j; k < read - 4; k++) {
										if (bufimage[k] == 0) {
											flg = 1;
											buf[k - j] = 0;
											buf[k - j + 1] = 0;
											buf[k - j + 2] = 0;
											break;
									}
										buf[k - j] = bufimage[k];
									}
								}
								if (flg == 1) {
									const int wlen = ::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), NULL, 0);
									TCHAR* buff = new TCHAR[wlen + 1];
									if (::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), buff, wlen))
									{
										buff[wlen] = _T('\0');
								}
									wcscpy(p.name, buff);
									delete[] buff;
									flg = 0;
									break;
							}
						}
					}
				}
						}
				else if ((ft.Right(5) == ".flac" || ft.Right(5) == ".FLAC")) {
					CFile ff;
					char buf[2024];
					TCHAR kpi[512];
					ff.Open(fname, CFile::modeRead | CFile::shareDenyNone, NULL);
					int flg, read = ff.Read(bufimage, sizeof(bufimage));
					ff.Close();
					kpi[0] = 0;
					plugs(s, &p, kpi);
					if (kpi[0] == 0)
						p.sub = -3;
					else
						p.sub = -2;
					//			if (savedata.m4a == 1)
					p.sub = -8;
					_tcscpy(p.name, ft);
					_tcscpy(p.fol, fname1);
					flg = 0;
					int i = 0, j;
					for (j = i; j < read - 6; j++) {
						if (bufimage[j] == 'A' && bufimage[j + 1] == 'L' && bufimage[j + 2] == 'B' && bufimage[j + 3] == 'U' && bufimage[j + 4] == 'M' && bufimage[j + 5] == '=') {
							j += 6;
							for (int k = j; k < read - 4; k++) {
								if (bufimage[k] == 0) {
									flg = 1;
									buf[k - j] = 0;
									buf[k - j + 1] = 0;
									buf[k - j + 2] = 0;
									break;
								}
								buf[k - j] = bufimage[k];
							}
						}
						if (flg == 1) {
							const int wlen = ::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), NULL, 0) - 1;
							TCHAR* buff = new TCHAR[wlen + 1];
							if (::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf) - 1, buff, wlen))
							{
								buff[wlen] = 0;
							}
							wcscpy(p.alb, buff);
							delete[] buff;
							flg = 0;
							break;
						}
					}
					for (j = i; j < read - 6; j++) {
						if ((bufimage[j] == 'A' || bufimage[j] == 'a') && bufimage[j + 1] == 'l' && bufimage[j + 2] == 'b' && bufimage[j + 3] == 'u' && bufimage[j + 4] == 'm' && bufimage[j + 5] == '=') {
							j += 6;
							for (int k = j; k < read - 4; k++) {
								if (bufimage[k] == 0) {
									flg = 1;
									buf[k - j] = 0;
									buf[k - j + 1] = 0;
									buf[k - j + 2] = 0;
									break;
								}
								buf[k - j] = bufimage[k];
							}
						}
						if (flg == 1) {
							const int wlen = ::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), NULL, 0) - 1;
							TCHAR* buff = new TCHAR[wlen + 1];
							if (::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf) - 1, buff, wlen))
							{
								buff[wlen] = 0;
							}
							wcscpy(p.alb, buff);
							delete[] buff;
							flg = 0;
							break;
						}
					}
					for (j = i; j < read - 6; j++) {
						if (bufimage[j] == 'A' && bufimage[j + 1] == 'R' && bufimage[j + 2] == 'T' && bufimage[j + 3] == 'I' && bufimage[j + 4] == 'S' && bufimage[j + 5] == 'T' && bufimage[j + 6] == '=') {
							j += 7;
							for (int k = j; k < read - 4; k++) {
								if (bufimage[k] == 0) {
									flg = 1;
									buf[k - j] = 0;
									buf[k - j + 1] = 0;
									buf[k - j + 2] = 0;
									break;
								}
								buf[k - j] = bufimage[k];
							}
						}
						if (flg == 1) {
							const int wlen = ::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), NULL, 0) - 1;
							TCHAR* buff = new TCHAR[wlen + 1];
							if (::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf) - 1, buff, wlen))
							{
								buff[wlen] = _T('\0');
							}
							wcscpy(p.art, buff);
							delete[] buff;
							flg = 0;
							break;
						}
					}
					for (j = i; j < read - 6; j++) {
						if ((bufimage[j] == 'A' || bufimage[j] == 'a') && bufimage[j + 1] == 'r' && bufimage[j + 2] == 't' && bufimage[j + 3] == 'i' && bufimage[j + 4] == 's' && bufimage[j + 5] == 't' && bufimage[j + 6] == '=') {
							j += 7;
							for (int k = j; k < read - 4; k++) {
								if (bufimage[k] == 0) {
									flg = 1;
									buf[k - j] = 0;
									buf[k - j + 1] = 0;
									buf[k - j + 2] = 0;
									break;
								}
								buf[k - j] = bufimage[k];
							}
							}
						if (flg == 1) {
							const int wlen = ::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), NULL, 0) - 1;
							TCHAR* buff = new TCHAR[wlen + 1];
							if (::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf) - 1, buff, wlen))
							{
								buff[wlen] = _T('\0');
							}
							wcscpy(p.art, buff);
							delete[] buff;
							flg = 0;
							break;
							}
						}
					for (j = i; j < read - 4; j++) {
						if (bufimage[j] == 'T' && bufimage[j + 1] == 'I' && bufimage[j + 2] == 'T' && bufimage[j + 3] == 'L' && bufimage[j + 4] == 'E' && bufimage[j + 5] == '=') {
							j += 6;
							for (int k = j; k < read - 4; k++) {
								if (bufimage[k] == 0) {
									flg = 1;
									buf[k - j] = 0;
									buf[k - j + 1] = 0;
									buf[k - j + 2] = 0;
									break;
								}
								buf[k - j] = bufimage[k];
							}
						}
						if (flg == 1) {
							const int wlen = ::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), NULL, 0) - 1;
							TCHAR* buff = new TCHAR[wlen + 1];
							if (::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf) - 1, buff, wlen))
							{
								buff[wlen] = _T('\0');
							}
							wcscpy(p.name, buff);
							delete[] buff;
							flg = 0;
							break;
						}
					}
					for (j = i; j < read - 4; j++) {
						if ((bufimage[j] == 'T' || bufimage[j] == 't') && bufimage[j + 1] == 'i' && bufimage[j + 2] == 't' && bufimage[j + 3] == 'l' && bufimage[j + 4] == 'e' && bufimage[j + 5] == '=') {
							j += 6;
							for (int k = j; k < read - 4; k++) {
								if (bufimage[k] == 0) {
									flg = 1;
									buf[k - j] = 0;
									buf[k - j + 1] = 0;
									buf[k - j + 2] = 0;
									break;
								}
								buf[k - j] = bufimage[k];
							}
						}
						if (flg == 1) {
							const int wlen = ::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), NULL, 0) - 1;
							TCHAR* buff = new TCHAR[wlen + 1];
							if (::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf) - 1, buff, wlen))
							{
								buff[wlen] = _T('\0');
							}
							wcscpy(p.name, buff);
							delete[] buff;
							flg = 0;
							break;
						}
					}
				}
				else {
					p.sub = -2;
					_tcscpy(p.name, s);
					_tcscpy(p.fol, fname1);
					p.alb[0] = p.art[0] = NULL; p.loop1 = p.loop2 = 0;
					TCHAR kpi[512]; kpi[0] = 0;
					plugs(fname, &p, kpi);
					if (kpi[0]) {
						ft = fname.Left(fname.ReverseFind('.')); ft += ".m3u";
						char ftt[1024];
						WideCharToMultiByte(CP_ACP, 0, ft, -1, ftt, 2000, " ", FALSE);
						ss = fname.Right(4); ss.MakeLower();
						if (ss == ".kss") {
							FILE *f; if (f = fopen(ftt, "r")) {
								char buf[256];  int st, ed, tmp;
								for (;;) {
									if (fgets(buf, sizeof(buf), f) == NULL) break;
									//							if (f.Read(buf1, 250) == FALSE) break;
									if (buf[0] == '#' || buf[0] == '\r' || buf[0] == '\n') continue;
									ss = buf;
									st = ss.Find(',', 0); ed = ss.Find(',', st + 1); s = ss.Mid(st + 1, (ed - 1) - st);
									if (s.Left(1) == _T("$")) {
										int num = 0;
										CString s3 = s.Mid(1, 1);
										if (_T("0") <= s3 && _T("9") >= s3) num = s3.GetAt(0) - _T('0');
										if (_T("a") <= s3 && _T("f") >= s3) num = s3.GetAt(0) - _T('a') + 10;
										if (_T("A") <= s3 && _T("F") >= s3) num = s3.GetAt(0) - _T('A') + 10;
										s3 = s.Mid(2, 1); num *= 16;
										if (_T("0") <= s3 && _T("9") >= s3) num += s3.GetAt(0) - _T('0');
										if (_T("a") <= s3 && _T("f") >= s3) num += s3.GetAt(0) - _T('a') + 10;
										if (_T("A") <= s3 && _T("F") >= s3) num += s3.GetAt(0) - _T('A') + 10;
										ft.Format(_T("%s::%04d"), fname, num + 1);
									}
									else
										ft.Format(_T("%s::%04d"), fname, _tstoi(s) + 1);
									_tcscpy(p.fol, ft);
									//TCHAR ss1[2001];
									//MultiByteToWideChar(CP_ACP, 0, (LPCSTR)buf, -1, ss1, 2000);
									//ss = ss1;
									st = ss.Find(L',', ed); ed = ss.Find(L',', st + 1); s = ss.Mid(st + 1, (ed - 1) - st);
									_tcscpy(p.name, s);
									if (syo == 0) { syo = 1; syos = p.fol; modesub = p.sub;	fnn = p.name; }
									Add(p.name, p.sub, p.loop1, p.loop2, p.art, p.alb, p.fol, 0, 0);
								}
								fclose(f);
								return;
							}
						}
						ft = fname.Left(fname.ReverseFind('.')); ft += ".frm";
						if (ss == ".nsf") {
							CStdioFile f; if (f.Open(ft, CFile::modeRead | CFile::typeText, NULL)) {
								TCHAR buf[256]; int st, ed, tmp;
								f.ReadString(buf, 256);
								f.ReadString(buf, 256);
								_tcscpy(p.alb, buf);
								f.ReadString(buf, 256);
								s = buf; int j = s.Find(_T("songs")); if (j >= 0) {
									int k = s.Find(_T("S.E."));
									int l = s.ReverseFind('('); ss = s.Mid(l + 1, 3); j = _tstoi(ss);
									if (k >= 0) { l = s.ReverseFind('&'); ss = s.Mid(l + 1, 3); j += _tstoi(ss); }
									for (l = 0; l < j; l++) {
										s = fname.Right(fname.GetLength() - fname.ReverseFind('\\') - 1);
										ss.Format(_T("%s::%04d"), s, l + 1);
										_tcscpy(p.name, ss);
										ss.Format(_T("%s::%04d"), fname, l + 1);
										_tcscpy(p.fol, ss);
										if (syo == 0) { syo = 1; syos = p.fol; modesub = p.sub;	fnn = p.name; }
										Add(p.name, p.sub, p.loop1, p.loop2, p.art, p.alb, p.fol, 0, 0);
									}
								}
								f.Close();
								return;
							}
						}
						if (ss == ".gbs") {
							CFile f; if (f.Open(fname, CFile::modeRead, NULL)) {
								char buf[32];
								f.Read(buf, 16); int i = buf[4];
								f.Read(buf, 32);
#if UNICODE
								TCHAR ss1[512];
								MultiByteToWideChar(CP_ACP, 0, (LPCSTR)buf, -1, ss1, 2000);
								_tcscpy(p.name, ss1);
#else
								_tcscpy(p.name, buf);
#endif
								f.Read(buf, 32);
#if UNICODE
								MultiByteToWideChar(CP_ACP, 0, (LPCSTR)buf, -1, ss1, 2000);
								_tcscpy(p.alb, ss1);
#else
								_tcscpy(p.alb, buf);
#endif
								f.Read(buf, 32);
#if UNICODE
								MultiByteToWideChar(CP_ACP, 0, (LPCSTR)buf, -1, ss1, 2000);
								_tcscpy(p.art, ss1);
#else
								_tcscpy(p.art, buf);
#endif
								f.Close();
								for (int j = 0; j < i; j++) {
									ss.Format(_T("%s::%04d"), fname, j + 1); _tcscpy(p.fol, ss);
									if (syo == 0) { syo = 1; syos = p.fol; modesub = p.sub;	fnn = p.name; }
									Add(p.name, p.sub, p.loop1, p.loop2, p.art, p.alb, p.fol, 0, 0);
								}
								return;
							}
						}
						if (ss == ".hes") {
							_tcscpy(p.name, ft);
							_tcscpy(p.fol, fname1);
							_tchdir(fname);
							p.alb[0] = p.art[0] = NULL; p.loop1 = p.loop2 = 0;
							TCHAR kpi[512]; kpi[0] = 0;
							plugs(fname, &p, kpi);
							if (kpi[0]) {
								ft = fname.Left(fname.ReverseFind('.')); ft += ".m3u";
								char ftt[1024];
								WideCharToMultiByte(CP_ACP, 0, ft, -1, ftt, 2000, " ", FALSE);
								ss = fname.Right(4); ss.MakeLower();
								if (ss == ".hes") {
									FILE *f; if (f = fopen(ftt, "r")) {
										char buf[256];  int st, ed;
										for (;;) {
											if (fgets(buf, sizeof(buf), f) == NULL) break;
											if (buf[0] == _T('#') || buf[0] == _T('\r') || buf[0] == _T('\n')) continue;
											ss = buf;
											if (ss.Find(',', 0) == -1) {
												ft = fname.Left(fname.ReverseFind('\\')) + L"\\" + ss.TrimRight();
												if (ft.Right(4) == ".ogg" || ft.Right(4) == ".OGG") {
													p.sub = -1;
													FILE *fp;
													fp = _tfopen(ft, _T("rb"));
													if (fp == NULL) {
														return;
													}
													if (ov_open(fp, &vf1, NULL, 0) < 0) {
														fclose(fp);
														return;
													}
													CString cc;
													_tcscpy(p.name, ft);
													p.alb[0] = p.art[0] = NULL;
													for (int iii = 0; iii < vf1.vc->comments; iii++) {
#if _UNICODE
														WCHAR f[1024];
														MultiByteToWideChar(CP_UTF8, 0, vf1.vc->user_comments[iii], -1, f, 1024);
														cc = f;
#else
														cc = vf1.vc->user_comments[iii];
#endif
														if (cc.Left(6) == "TITLE=")
														{
#if _UNICODE
															ss = UTF8toUNI(cc.Mid(6));
#else
															ss = UTF8toSJIS(cc.Mid(6));
#endif
															_tcscpy(p.name, ss);
														}
														if (cc.Left(7) == "ARTIST=")
														{
#if _UNICODE
															ss = UTF8toUNI(cc.Mid(7));
#else
															ss = UTF8toSJIS(cc.Mid(7));
#endif
															_tcscpy(p.art, ss);
														}
														if (cc.Left(6) == "ALBUM=")
														{
#if _UNICODE
															ss = UTF8toUNI(cc.Mid(6));
#else
															ss = UTF8toSJIS(cc.Mid(6));
#endif
															_tcscpy(p.alb, ss);
														}
													}
													ov_clear(&vf1);
													fclose(fp);
													_tcscpy(p.fol, fname);
													p.loop1 = p.loop2 = 0;
												}
												else if (ft.Right(4) == ".mp3" || ft.Right(4) == ".MP3" || ft.Right(4) == ".mp2" || ft.Right(4) == ".MP2" ||
													ft.Right(4) == ".mp1" || ft.Right(4) == ".MP1" || ft.Right(4) == ".rmp" || ft.Right(4) == ".RMP") {
													p.sub = -10; p.loop1 = p.loop2 = 0;
													_tcscpy(p.fol, fname);
													_tcscpy(p.name, ss.TrimRight());
												}
												else if ((bufimage[0] == 0xff && (bufimage[1] & 0xf0 == 0xf0)) && (ft.Right(4) == ".aac" || ft.Right(4) == ".AAC")) {
													p.sub = -9;
													_tcscpy(p.name, ss.TrimRight());
													_tcscpy(p.fol, fname);
												}
												else if ((ft.Right(4) == ".m4a" || ft.Right(4) == ".M4A" || ft.Right(4) == ".aac" || ft.Right(4) == ".AAC")) {
													CFile ff;
													char buf[1024];
													TCHAR kpi[512];
													ff.Open(fname, CFile::modeRead | CFile::shareDenyNone, NULL);
													int flg, read = ff.Read(bufimage, sizeof(bufimage));
													ff.Close();
													kpi[0] = 0;
													plugs(s, &p, kpi);
													if (kpi[0] == 0)
														p.sub = -3;
													else
														p.sub = -2;
													if (savedata.m4a == 1)
														p.sub = -9;
													_tcscpy(p.name, ft);
													_tcscpy(p.fol, fname);
													flg = 0;
													int i;
													for (i = 0; i < read - 4; i++) {
														if (bufimage[i] == 'u' && bufimage[i + 1] == 'd' && bufimage[i + 2] == 't' && bufimage[i + 3] == 'a') {
															int j;
															for (j = i + 4; j < read - 4; j++) {
																if (bufimage[j] == 'a' && bufimage[j + 1] == 'l' && bufimage[j + 2] == 'b' && bufimage[j + 7] == 'd' && bufimage[j + 8] == 'a' && bufimage[j + 9] == 't' && bufimage[j + 10] == 'a') {
																	j += 19;
																	for (int k = j; k < read - 4; k++) {
																		if (bufimage[k] == 0) {
																			flg = 1;
																			buf[k - j] = 0;
																			buf[k - j + 1] = 0;
																			buf[k - j + 2] = 0;
																			break;
																		}
																		buf[k - j] = bufimage[k];
																	}
																}
																if (flg == 1) {
																	const int wlen = ::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), NULL, 0);
																	TCHAR* buff = new TCHAR[wlen + 1];
																	if (::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), buff, wlen))
																	{
																		buff[wlen] = _T('\0');
																	}
																	wcscpy(p.alb, buff);
																	delete[] buff;
																	flg = 0;
																	break;
																}
															}
															for (j = i + 4; j < read - 4; j++) {
																if (bufimage[j] == 'A' && bufimage[j + 1] == 'R' && bufimage[j + 2] == 'T' && bufimage[j + 7] == 'd' && bufimage[j + 8] == 'a' && bufimage[j + 9] == 't' && bufimage[j + 10] == 'a') {
																	j += 19;
																	for (int k = j; k < read - 4; k++) {
																		if (bufimage[k] == 0) {
																			flg = 1;
																			buf[k - j] = 0;
																			buf[k - j + 1] = 0;
																			buf[k - j + 2] = 0;
																			break;
																		}
																		buf[k - j] = bufimage[k];
																	}
																}
																if (flg == 1) {
																	const int wlen = ::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), NULL, 0);
																	TCHAR* buff = new TCHAR[wlen + 1];
																	if (::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), buff, wlen))
																	{
																		buff[wlen] = _T('\0');
																	}
																	wcscpy(p.art, buff);
																	delete[] buff;
																	flg = 0;
																	break;
																}
															}
															for (j = i + 4; j < read - 4; j++) {
																if (bufimage[j] == 'n' && bufimage[j + 1] == 'a' && bufimage[j + 2] == 'm' && bufimage[j + 7] == 'd' && bufimage[j + 8] == 'a' && bufimage[j + 9] == 't' && bufimage[j + 10] == 'a') {
																	j += 19;
																	for (int k = j; k < read - 4; k++) {
																		if (bufimage[k] == 0) {
																			flg = 1;
																			buf[k - j] = 0;
																			buf[k - j + 1] = 0;
																			buf[k - j + 2] = 0;
																			break;
																		}
																		buf[k - j] = bufimage[k];
																	}
																}
																if (flg == 1) {
																	const int wlen = ::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), NULL, 0);
																	TCHAR* buff = new TCHAR[wlen + 1];
																	if (::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), buff, wlen))
																	{
																		buff[wlen] = _T('\0');
																	}
																	wcscpy(p.name, buff);
																	delete[] buff;
																	flg = 0;
																	break;
																}
															}
														}
													}
												}
												else if ((ft.Right(5) == ".flac" || ft.Right(5) == ".FLAC")) {
													CFile ff;
													char buf[2024];
													TCHAR kpi[512];
													ff.Open(fname, CFile::modeRead | CFile::shareDenyNone, NULL);
													int flg, read = ff.Read(bufimage, sizeof(bufimage));
													ff.Close();
													kpi[0] = 0;
													plugs(s, &p, kpi);
													if (kpi[0] == 0)
														p.sub = -3;
													else
														p.sub = -2;
													//			if (savedata.m4a == 1)
													p.sub = -8;
													_tcscpy(p.name, ft);
													_tcscpy(p.fol, fname);
													flg = 0;
													int i = 0, j;
													for (j = i; j < read - 6; j++) {
														if (bufimage[j] == 'A' && bufimage[j + 1] == 'L' && bufimage[j + 2] == 'B' && bufimage[j + 3] == 'U' && bufimage[j + 4] == 'M' && bufimage[j + 5] == '=') {
															j += 6;
															for (int k = j; k < read - 4; k++) {
																if (bufimage[k] == 0) {
																	flg = 1;
																	buf[k - j] = 0;
																	buf[k - j + 1] = 0;
																	buf[k - j + 2] = 0;
																	break;
																}
																buf[k - j] = bufimage[k];
															}
														}
														if (flg == 1) {
															const int wlen = ::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), NULL, 0) - 1;
															TCHAR* buff = new TCHAR[wlen + 1];
															if (::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf) - 1, buff, wlen))
															{
																buff[wlen] = 0;
															}
															wcscpy(p.alb, buff);
															delete[] buff;
															flg = 0;
															break;
														}
													}
													for (j = i; j < read - 6; j++) {
														if ((bufimage[j] == 'A' || bufimage[j] == 'a') && bufimage[j + 1] == 'l' && bufimage[j + 2] == 'b' && bufimage[j + 3] == 'u' && bufimage[j + 4] == 'm' && bufimage[j + 5] == '=') {
															j += 6;
															for (int k = j; k < read - 4; k++) {
																if (bufimage[k] == 0) {
																	flg = 1;
																	buf[k - j] = 0;
																	buf[k - j + 1] = 0;
																	buf[k - j + 2] = 0;
																	break;
																}
																buf[k - j] = bufimage[k];
															}
														}
														if (flg == 1) {
															const int wlen = ::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), NULL, 0) - 1;
															TCHAR* buff = new TCHAR[wlen + 1];
															if (::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf) - 1, buff, wlen))
															{
																buff[wlen] = 0;
															}
															wcscpy(p.alb, buff);
															delete[] buff;
															flg = 0;
															break;
														}
													}
													for (j = i; j < read - 6; j++) {
														if (bufimage[j] == 'A' && bufimage[j + 1] == 'R' && bufimage[j + 2] == 'T' && bufimage[j + 3] == 'I' && bufimage[j + 4] == 'S' && bufimage[j + 5] == 'T' && bufimage[j + 6] == '=') {
															j += 7;
															for (int k = j; k < read - 4; k++) {
																if (bufimage[k] == 0) {
																	flg = 1;
																	buf[k - j] = 0;
																	buf[k - j + 1] = 0;
																	buf[k - j + 2] = 0;
																	break;
																}
																buf[k - j] = bufimage[k];
															}
														}
														if (flg == 1) {
															const int wlen = ::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), NULL, 0) - 1;
															TCHAR* buff = new TCHAR[wlen + 1];
															if (::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf) - 1, buff, wlen))
															{
																buff[wlen] = _T('\0');
															}
															wcscpy(p.art, buff);
															delete[] buff;
															flg = 0;
															break;
														}
													}
													for (j = i; j < read - 6; j++) {
														if ((bufimage[j] == 'A' || bufimage[j] == 'a') && bufimage[j + 1] == 'r' && bufimage[j + 2] == 't' && bufimage[j + 3] == 'i' && bufimage[j + 4] == 's' && bufimage[j + 5] == 't' && bufimage[j + 6] == '=') {
															j += 7;
															for (int k = j; k < read - 4; k++) {
																if (bufimage[k] == 0) {
																	flg = 1;
																	buf[k - j] = 0;
																	buf[k - j + 1] = 0;
																	buf[k - j + 2] = 0;
																	break;
																}
																buf[k - j] = bufimage[k];
															}
														}
														if (flg == 1) {
															const int wlen = ::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), NULL, 0) - 1;
															TCHAR* buff = new TCHAR[wlen + 1];
															if (::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf) - 1, buff, wlen))
															{
																buff[wlen] = _T('\0');
															}
															wcscpy(p.art, buff);
															delete[] buff;
															flg = 0;
															break;
														}
													}
													for (j = i; j < read - 4; j++) {
														if (bufimage[j] == 'T' && bufimage[j + 1] == 'I' && bufimage[j + 2] == 'T' && bufimage[j + 3] == 'L' && bufimage[j + 4] == 'E' && bufimage[j + 5] == '=') {
															j += 6;
															for (int k = j; k < read - 4; k++) {
																if (bufimage[k] == 0) {
																	flg = 1;
																	buf[k - j] = 0;
																	buf[k - j + 1] = 0;
																	buf[k - j + 2] = 0;
																	break;
																}
																buf[k - j] = bufimage[k];
															}
														}
														if (flg == 1) {
															const int wlen = ::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), NULL, 0) - 1;
															TCHAR* buff = new TCHAR[wlen + 1];
															if (::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf) - 1, buff, wlen))
															{
																buff[wlen] = _T('\0');
															}
															wcscpy(p.name, buff);
															delete[] buff;
															flg = 0;
															break;
														}
													}
													for (j = i; j < read - 4; j++) {
														if ((bufimage[j] == 'T' || bufimage[j] == 't') && bufimage[j + 1] == 'i' && bufimage[j + 2] == 't' && bufimage[j + 3] == 'l' && bufimage[j + 4] == 'e' && bufimage[j + 5] == '=') {
															j += 6;
															for (int k = j; k < read - 4; k++) {
																if (bufimage[k] == 0) {
																	flg = 1;
																	buf[k - j] = 0;
																	buf[k - j + 1] = 0;
																	buf[k - j + 2] = 0;
																	break;
																}
																buf[k - j] = bufimage[k];
															}
														}
														if (flg == 1) {
															const int wlen = ::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), NULL, 0) - 1;
															TCHAR* buff = new TCHAR[wlen + 1];
															if (::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf) - 1, buff, wlen))
															{
																buff[wlen] = _T('\0');
															}
															wcscpy(p.name, buff);
															delete[] buff;
															flg = 0;
															break;
														}
													}
												}
												if (syo == 0) { syo = 1; syos = ft; modesub = p.sub; fnn = p.name; }
												Add(p.name, p.sub, p.loop1, p.loop2, p.art, p.alb, ft, 0, 0);
											}
											else {
												p.sub = -3;
												st = ss.Find(',', 0); ed = ss.Find(',', st + 1); s = ss.Mid(st + 1, (ed - 1) - st);
												if (s.Left(1) == _T("$")) {
													int num = 0;
													CString s3 = s.Mid(1, 1);
													if (_T("0") <= s3 && _T("9") >= s3) num = s3.GetAt(0) - _T('0');
													if (_T("a") <= s3 && _T("f") >= s3) num = s3.GetAt(0) - _T('a') + 10;
													if (_T("A") <= s3 && _T("F") >= s3) num = s3.GetAt(0) - _T('A') + 10;
													s3 = s.Mid(2, 1); num *= 16;
													if (_T("0") <= s3 && _T("9") >= s3) num += s3.GetAt(0) - _T('0');
													if (_T("a") <= s3 && _T("f") >= s3) num += s3.GetAt(0) - _T('a') + 10;
													if (_T("A") <= s3 && _T("F") >= s3) num += s3.GetAt(0) - _T('A') + 10;
													ft.Format(_T("%s::%04d"), fname, num + 1);
												}
												else
													ft.Format(_T("%s::%04d"), fname, _tstoi(s) + 1);
												_tcscpy(p.fol, ft);
												st = ss.Find(L',', ed); ed = ss.Find(L',', st + 1); s = ss.Mid(st + 1, (ed - 1) - st);
												_tcscpy(p.name, s);
												if (syo == 0) { syo = 1; syos = p.fol; modesub = p.sub;	fnn = p.name; }
												Add(p.name, p.sub, p.loop1, p.loop2, p.art, p.alb, p.fol, 0, 0);
											}
										}
									}
									fclose(f);
									return;
								}
								return;
							}
							return;
						}
						if (ss == ".ovi" || ss == ".opi" || ss == ".ozi") {
							CFile f; char buf[512], *buf2;
							f.Open(fname, CFile::modeRead | CFile::shareDenyRead, NULL);
							if (f.GetLength() > 512)
								f.Seek(-512, CFile::end);
							else
								f.SeekToBegin();
							f.Read(buf, 512);
							int i = 0;
							f.Close();
							for (; i < 500; i++) {
								if (buf[i] == 'F'&&buf[i + 1] == 'M'&&buf[i + 2] == 'C') break;
							}
							if (i != 500) {
								buf2 = buf + i + 4; ss = buf2;
								int st = ss.Find(0x0d, 0);
								ft = ss.Left(st); _tcscpy(p.name, ft);
								int ed = ss.Find(0x0d, st + 2);
								ft = ss.Mid(st + 1, ed - st - 1); _tcscpy(p.art, ft);
								st = ss.Find(0x0d, ed + 2);
								ft = ss.Mid(ed + 1, st - ed - 1); _tcscpy(p.alb, ft);
								if (syo == 0) { syo = 1; syos = p.fol; modesub = p.sub; fnn = p.name; }
								Add(p.name, p.sub, p.loop1, p.loop2, p.art, p.alb, p.fol, 0, 0);
								return;
							}
						}
						ss = fname.Right(2); ss.MakeLower();
						ft = fname.Right(3); ft.MakeLower();
						if (ss == ".m" || ft == ".mz") {
							CFile ff; char buf[512], *buf2;
							ff.Open(fname, CFile::modeRead | CFile::shareDenyNone, NULL);
							if (ff.GetLength() > 512)
								ff.Seek(-512, CFile::end);
							else
								ff.SeekToBegin();
							ff.Read(buf, 512);
							int jj = ff.GetLength(); if (jj > 510) jj = 510;
							jj -= 3;
							int i;
							for (i = jj; i > 0; i--) {
								if (buf[i] == 0 && (buf[i + 1] == 0 || (BYTE)buf[i + 1] == 255) && buf[i + 2] == 0)break;
							}
							ff.Close();
							if (i != 0) {
								buf2 = buf + i + 3;
								int j = 0;
								for (;; j++)if (buf2[j] == 0)break;
#if UNICODE
								TCHAR ss1[512];
								MultiByteToWideChar(CP_ACP, 0, (LPCSTR)buf2, -1, ss1, 2000);
								_tcscpy(p.name, ss1); buf2 += j;
#else
								_tcscpy(p.name, buf2); buf2 += j;
#endif
								for (j = 0;; j++)if (buf2[j] != 0)break;
								buf2 += j;
								for (j = 0;; j++)if (buf2[j] == 0)break;
#if UNICODE
								MultiByteToWideChar(CP_ACP, 0, (LPCSTR)buf2, -1, ss1, 2000);
								_tcscpy(p.art, ss1); buf2 += j;
#else
								_tcscpy(p.art, buf2); buf2 += j;
#endif
								for (j = 0;; j++)if (buf2[j] != 0)break;
								buf2 += j;
								for (j = 0;; j++)if (buf2[j] == 0)break;
#if UNICODE
								MultiByteToWideChar(CP_ACP, 0, (LPCSTR)buf2, -1, ss1, 2000);
								_tcscpy(p.alb, ss1); buf2 += j;
#else
								_tcscpy(p.alb, buf2); buf2 += j;
#endif
								if (syo == 0) { syo = 1; syos = p.fol; modesub = p.sub; fnn = p.name; }
								Add(p.name, p.sub, p.loop1, p.loop2, p.art, p.alb, p.fol, 0, 0);
							}
							return;
						}
						ft = fname.Right(4); ft.MakeLower();
						if (ft == ".tta") {
							CFile ff; char buf[512], *buf2;
							ff.Open(fname, CFile::modeRead | CFile::shareDenyNone, NULL);
							if (ff.GetLength() > 0x80)
								ff.Seek(-0x80, CFile::end);
							else
								ff.SeekToBegin();
							ff.Read(buf, 0x80);
							int i = 0;
							for (; i < 0x80; i++) {
								if (buf[i + 0] == 'T'&&buf[i + 1] == 'A'&&buf[i + 2] == 'G')break;
							}
							ff.Close();
							if (i != 0x80) {
								buf2 = buf + i + 3;
#if UNICODE
								TCHAR ss1[512];
								TCHAR buf3 = buf2[30]; buf2[30] = 0;
								MultiByteToWideChar(CP_ACP, 0, (LPCSTR)buf2, -1, ss1, 2000);
								buf2[30] = buf3;
								_tcscpy(p.name, ss1); buf2 += 30;
#else
								_tcscpy(p.name, buf2); buf2 += 30;
#endif
#if UNICODE
								buf3 = buf2[30]; buf2[30] = 0;
								MultiByteToWideChar(CP_ACP, 0, (LPCSTR)buf2, -1, ss1, 2000);
								buf2[30] = buf3;
								_tcscpy(p.art, ss1); buf2 += 30;
#else
								_tcscpy(p.art, buf2); buf2 += 30;
#endif
#if UNICODE
								buf3 = buf2[30]; buf2[30] = 0;
								MultiByteToWideChar(CP_ACP, 0, (LPCSTR)buf2, -1, ss1, 2000);
								buf2[30] = buf3;
								_tcscpy(p.alb, ss1); buf2 += 30;
#else
								_tcscpy(p.alb, buf2); buf2 += 30;
#endif
								if (syo == 0) { syo = 1; syos = p.fol; modesub = p.sub; fnn = s; }
								Add(p.name, p.sub, p.loop1, p.loop2, p.art, p.alb, p.fol, 0, 0);
							}
							return;
						}
					}

				}
				CString sL = s;
				s.MakeLower();
				if (s.Right(4) == ".png" || s.Right(4) == ".url" || s.Right(4) == ".jpg" || s.Right(4) == ".bmp" || s.Right(4) == ".cue" || s.Right(4) == ".iso" || s.Right(4) == ".bin" || s.Right(4) == ".img" || s.Right(4) == ".mds" || s.Right(4) == ".mdf" || s.Right(4) == ".ccd" || s.Right(4) == ".sub" || s.Right(4) == ".pdf" || s.Right(4) == ".com" || s.Right(4) == ".exe" || s.Right(4) == ".dll" || s.Right(4) == ".bat" || s.Right(4) == ".reg" || s.Right(4) == ".msi" || s.Right(4) == ".nfo" || s.Right(4) == ".diz" || s.Right(4) == ".gif" || s.Right(4) == ".ico" ||
					s.Right(4) == ".zip" || s.Right(4) == ".lzh" || s.Right(4) == ".cab" || s.Right(4) == ".rar" || s.Right(4) == ".txt" || s.Right(4) == ".doc" || s.Right(4) == "html" || s.Right(4) == ".htm" || s.Right(4) == ".ini" || s.Right(4) == ".xml" || s.Right(4) == ".kar" || s.Right(4) == ".hed" || s.Right(4) == ".mzi" || s.Right(4) == ".mag" || s.Right(4) == ".mvi" || s.Right(4) == ".lvi" || s.Right(4) == ".mpi" || s.Right(4) == ".pvi" || s.Right(4) == ".pzi" || s.Right(4) == ".p86" || s.Right(4) == ".mml" || s.Right(4) == ".m3u" || s.Right(4) == ".frm" || s.Right(7) == ".psflib" || s.Right(8) == ".psf2lib" || s.Right(7) == ".usflib" || s.Right(7) == ".2sflib" || s.Right(3) == ".gb" || s.Right(7) == ".gsflib" || s.Right(4) == ".pdx") {
				}
				else {
					if (syo == 0) {
						syo = 1; syos = p.fol; modesub = p.sub; fnn = sL;
					}
					CString fol = p.fol;
					if (PathIsDirectory(fol)) {
						fol += L"\\" + sL;
					}
					

					Add(p.name, p.sub, p.loop1, p.loop2, p.art, p.alb, fol, 0, 0);
					fol = p.fol;
					if (PathIsDirectory(fol) == FALSE) {
						return;
					}
				}
			}
		}
	}
	f.Close();
	fname = fname1;
	int cdd=0;
	if(PathIsDirectory(fname)){
		CFileFind cf1;
		if (cf1.FindFile(_T("*.*")) != 0) {
			int r = 1;
			for (; r;) {
				r = cf1.FindNextFile();
				CString ss, sss;
				ss = cf1.GetFileName();
				sss = cf1.GetFilePath();
				if (!(ss == L"." || ss == L"..")) {
					if ((cf1.IsHidden() == 0)) {
						if (cf1.IsDirectory() != 0) { //フォルダ？
							Fol(cf1.GetFilePath());//*/fname+cf1.GetFileName();
						}
					}
				}
			}
		}
		cf1.Close();
	}
	else {

	}
}




void CPlayList::plugs(CString fff, playlistdata *p,TCHAR* kpi)
{
	CString ss,ft;
	int flg=0;
	for(int i=0;i<kpicnt;i++){
		for(int j=0;;j++){
			if(ext[i][j]=="") break;
			ss=fff.Right(fff.GetLength()-fff.ReverseFind('.'));ss.MakeLower();
			if(ext[i][j]==ss){
				ss=kpif[i];
				if (kpichk[i] == 1) {
					flg = 1;
					break;
				}
			}
		}
		if(flg==1)break;
	}
	if(flg==1){
		_tcscpy(p->fol,fff);
		p->sub=-3;
		ft=fff.Right(fff.GetLength()-fff.ReverseFind('\\')-1);
		_tcscpy(p->name,ft);
		p->alb[0]=NULL;p->art[0]=NULL;p->loop1=p->loop2=p->ret2=0;
		_tcscpy(kpi,ss);
	}
}

void CPlayList::Save()
{
	TCHAR tmp[1024];int cnt,j;CString s;
	int cx,cy,x,y;RECT r;
	int c;
	_tgetcwd(tmp,1000);
	_tchdir(karento2);
	if(IsIconic()){
		ShowWindow(SW_RESTORE);
		GetWindowRect(&r);
		ShowWindow(SW_MINIMIZE);
	}else
		GetWindowRect(&r);
	x=r.left;y=r.top;cx=r.right-x;cy=r.bottom-y;
#if _UNICODE
	CFile f;if(f.Open(_T("playlistu.dat"),CFile::modeCreate|CFile::modeWrite,NULL)==TRUE){
#else
	CFile f;if(f.Open(_T("playlist.dat"),CFile::modeCreate|CFile::modeWrite,NULL)==TRUE){
#endif
		cnt=playcnt;
		f.Write(&cnt,4);
		f.Write(&x,4);
		f.Write(&y,4);
		f.Write(&cx,4);
		f.Write(&cy,4);
		c=m_lc.GetColumnWidth(0);f.Write(&c,4);
		c=m_lc.GetColumnWidth(1);f.Write(&c,4);
		c=m_lc.GetColumnWidth(3);f.Write(&c,4);
		c=m_lc.GetColumnWidth(4);f.Write(&c,4);
		c=m_lc.GetColumnWidth(7);f.Write(&c,4);
		playlistdata pld;
		for(int i=0;i<cnt;i++){ZeroMemory(&pld,sizeof(pld));
			_tcscpy(pld.alb,pc[i].alb);
			_tcscpy(pld.art,pc[i].art);
			_tcscpy(pld.fol,pc[i].fol);
			_tcscpy(pld.name,pc[i].name);
			pld.loop1=pc[i].loop1;
			pld.loop2=pc[i].loop2;
			pld.sub=pc[i].sub;
			pld.ret2=pc[i].ret2;
			pld.time=pc[i].time;
			f.Write(&pld,sizeof(pld));
		}
		c=m_loop.GetCheck();f.Write(&c,4);
		c=m_renzoku.GetCheck();f.Write(&c,4);
		c=m_tool.GetCheck();f.Write(&c,4);
		c=m_saisyo.GetCheck();f.Write(&c,4);
		c=m_lc.GetColumnWidth(2);f.Write(&c,4);
		c=m_lc.GetColumnWidth(5);f.Write(&c,4);
		f.Write(&pnt,4);
		f.Close();

	}
	_tchdir(tmp);
}


void CPlayList::Load()
{
	TCHAR tmp[1024];int cnt;
	int cx,cy,x=-10000,y,c;
	_tgetcwd(tmp,1000);
	_tchdir(karento2);
#if _UNICODE
	CFile f;if(f.Open(_T("playlistu.dat"),CFile::modeRead,NULL)==TRUE){
#else
	CFile f;if(f.Open(_T("playlist.dat"),CFile::modeRead,NULL)==TRUE){
#endif
		f.Read(&cnt,4);
		f.Read(&x,4);
		f.Read(&y,4);
		f.Read(&cx,4);
		f.Read(&cy,4);
		f.Read(&c,4);m_lc.SetColumnWidth(0,c);
		f.Read(&c,4);m_lc.SetColumnWidth(1,c);
		f.Read(&c,4);m_lc.SetColumnWidth(3,c);
		f.Read(&c,4);m_lc.SetColumnWidth(4,c);
		f.Read(&c,4);
		playlistdata pld;
		m_lc.SetItemCount(cnt);
		pc = (playlistdata0*)malloc(sizeof(playlistdata0)*(cnt+1));
		for(int i=0;i<cnt;i++){
			f.Read(&pld,sizeof(pld));
			Add(pld.name,pld.sub,pld.loop1,pld.loop2,pld.art,pld.alb,pld.fol,pld.ret2,pld.time,FALSE,FALSE);			
		}
		c=0;f.Read(&c,4);m_loop.SetCheck(c);
		c=0;f.Read(&c,4);m_renzoku.SetCheck(c);
		c=1;f.Read(&c,4);m_tool.SetCheck(c);
		c=1;f.Read(&c,4);m_saisyo.SetCheck(c);
		c=-1;f.Read(&c,4);if(c!=-1)m_lc.SetColumnWidth(2,c);
		c=-1;f.Read(&c,4);if(c!=-1)m_lc.SetColumnWidth(5,c);
		pnt1=-1;f.Read(&pnt1,4);//if(c!=-1)SIcon(pnt);
		f.Close();
	}
	_tchdir(tmp);
	if(GetAsyncKeyState(VK_LCONTROL)&0x8000){
		x=-10000;
	}
	if(x!=-10000){
		MoveWindow(x,y,cx,cy,TRUE);
		RECT r;
		GetClientRect(&r);
	m_lc.SetWindowPos(&wndNoTopMost,0,0,(int)(r.right-20*(hD2)),(int)(r.bottom-65 * (hD2 )),SWP_NOMOVE|SWP_NOOWNERZORDER|SWP_NOZORDER);
	}
}
int SC=0;
void CPlayList::SIcon(int i){
	if(i<0) return;
	if(i>=playcnt) return;
	if(i==pnt) return;
	RECT r;
	pc[i].icon=0; if(pnt>=0&&pnt<playcnt){ pc[pnt].icon=1;
			m_lc.GetItemRect(pnt,&r,LVIR_ICON);
			m_lc.RedrawWindow(&r);
	}
	pnt=i;
	m_lc.GetItemRect(pnt,&r,LVIR_ICON);
	m_lc.RedrawWindow(&r);
	m_lc.EnsureVisible(i,FALSE);
	SC=0;
}

void CPlayList::SIconTimer(int i){
	CString s; s.Format(L"%d", i);
	if(pnt<0) return;
	if(pnt>=playcnt) return;
	if(IsBadReadPtr(&pc[pnt],sizeof(playlistdata0))) return;
	//_try{
	if(i==0)
		pc[pnt].icon=2;
	else
		pc[pnt].icon=0;
	//}__except(EXCEPTION_EXECUTE_HANDLER){}
	RECT r;
	m_lc.GetItemRect(pnt,&r,LVIR_ICON);
	m_lc.RedrawWindow(&r);
}
int pln=0;
extern int ps;
extern void DoEvent();
void CPlayList::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	*pResult = 0;
	CString s;int i,j;
	int Lindex=-1;
	Lindex=m_lc.GetNextItem(Lindex,LVNI_ALL |LVNI_SELECTED);i=Lindex;
	if(Lindex>=playcnt) return;
	if(Lindex==-1) return;
	//SIcon(i);
	fnn=pc[Lindex].name;
	filen=pc[Lindex].fol;
	modesub=pc[Lindex].sub;
	loop1=pc[Lindex].loop1;
	loop2=pc[Lindex].loop2;
	ret2=pc[Lindex].ret2;
	plcnt=i;
	if(pln==0){
		pln=1;
		og->OnRestart();
		for(;ps==1;){
			DoEvent();
			og->OnRestart();
		}
		pln=0;
	}
}
extern CDouga *pMainFrame1;
extern long height, width;
void CPlayList::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: ここにメッセージ ハンドラ コードを追加します。
	RECT r;
	GetClientRect(&r);
	if( ::IsWindow( this->GetSafeHwnd()) == TRUE &&  this->IsWindowVisible() == TRUE)
		m_lc.SetWindowPos(&wndNoTopMost, 0, 0, (int)(r.right - 20 * (hD2 )), (int)(r.bottom - 65 * (hD2 )), SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	if(pl){
		if (nType == SIZE_MINIMIZED){
			if(m_saisyo.GetCheck())
				og->ShowWindow(SW_MINIMIZE);
			if(pMainFrame1){
				pMainFrame1->ShowWindow(SW_HIDE);
			}
		}
		if(nType==SIZE_RESTORED){
			if(m_saisyo.GetCheck())
				og->ShowWindow(SW_RESTORE);
			if(pMainFrame1 && height!=0){
				pMainFrame1->ShowWindow(SW_SHOWNORMAL);
			}
		}
	}
}
int kk=0;
extern int lenl;
int tlg=0;
extern CPlayList*pl;
void timerpl(UINT nIDEvent,CPlayList* pl);
void timerpl1(UINT nIDEvent,CPlayList* pl);
void timerpl1(UINT nIDEvent,CPlayList* pl)
{
	if(nIDEvent==5000){
		pl->KillTimer(5000);
		pl->SIcon(pl->pnt1);
	}
	if(nIDEvent==40){
		pl->KillTimer(40);
		plw=1;
	}

	if(nIDEvent==3000){
		pl->SIconTimer(SC);
		SC++; SC = SC % 2;
	}
	if(nIDEvent==20){
		
		if(pl->w_flg==FALSE) return;
		if(pl->GetFocus()==NULL){return;}
		if(pl->m_find.GetFocus()->m_hWnd==pl->m_find.m_hWnd){return;}
		{
			HWND rtn;
			TCHAR Name[1024];
			long Leng = sizeof(Name);
			rtn = GetActiveWindow();
			GetWindowTextW(rtn, Name, Leng);
			CString sss;
			sss = Name;
			if (sss != _T("プレイリスト")) {
				return;
			}
			if((GetKeyState(VK_RETURN)&0x8000)==0 && kk==1)
				kk=0;
			if(GetKeyState(VK_RETURN)&0x8000 && kk==0){
				kk=1;
				CString s;int i,j;
				int Lindex=-1;
				Lindex=pl->m_lc.GetNextItem(Lindex,LVNI_ALL |LVNI_SELECTED);
				i=Lindex;
				if(Lindex>=playcnt) return;
				if(Lindex==-1) return;
//				pl->SIcon(i);
				fnn=pl->pc[Lindex].name;
				filen=pl->pc[Lindex].fol;
				modesub=pl->pc[Lindex].sub;
				loop1=pl->pc[Lindex].loop1;
				loop2=pl->pc[Lindex].loop2;
				ret2=pl->pc[Lindex].ret2;
				plcnt=i;
				og->OnRestart();
			}
			if((GetKeyState(VK_CONTROL)&0x8000) && (GetKeyState('A')&0x8000)){
				int i=pl->m_lc.GetItemCount();
				for(int j=0;j<i;j++){
					pl->m_lc.SetItemState(j,LVIS_SELECTED,LVIS_SELECTED);
				}
			}
		}
		int tl=pl->m_tool.GetCheck();
		if(tl!=tlg){
			tlg=tl;
			if(tlg){
				pl->m_lc.EnableToolTips(TRUE);
				tl=pl->m_lc.GetExtendedStyle();
				tl = tl & ~LVS_EX_INFOTIP;
				pl->m_lc.SetExtendedStyle(tl);
			}else{
				pl->m_lc.EnableToolTips(FALSE);
				tl=pl->m_lc.GetExtendedStyle();
				tl |=LVS_EX_INFOTIP;
				pl->m_lc.SetExtendedStyle(tl);
			}
		}
	}
}
void timerpl(UINT nIDEvent,CPlayList* pl)
{
	try{
		_set_se_translator( trans_func1 );
		timerpl1(nIDEvent,pl);
//	}__except(EXCEPTION_EXECUTE_HANDLER){}
	}catch(SE_Exception1 e){
	}
	catch(_EXCEPTION_POINTERS *ep){
	}
	catch(...){}
}

extern int stflg;

#if WIN64
void CPlayList::OnTimer(UINT_PTR nIDEvent) 
#else
void CPlayList::OnTimer(UINT nIDEvent) 
#endif
{
	savedata.saveloop = m_loop.GetCheck();
	savedata.saverenzoku = m_renzoku.GetCheck();
	savedata.savecheck=m_savecheck.GetCheck();
	savedata.savecheck_mp3 = m_save_mp3.GetCheck();
	savedata.savecheck_dshow = m_save_kpi.GetCheck();
	CPlayList* pl = (CPlayList*)this;
	if(stflg == FALSE)
		timerpl(nIDEvent,pl);
	CDialog::OnTimer(nIDEvent);
}

void CPlayList::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CPlayList::OnBnClickedCheck4()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	Save();
}

void CPlayList::OnBnClickedCheck1()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	Save();
}

void CPlayList::OnLvnBegindragList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNM = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	POINT ptPos,ptPos2;
    HIMAGELIST hOneImageList;
    HIMAGELIST hTempImageList;
	IMAGEINFO imf;
	long iHeight;
	m_hDragImage = ListView_CreateDragImage(m_lc.m_hWnd,pNM->iItem,&ptPos);
	ImageList_GetImageInfo(m_hDragImage, 0, &imf);
	iHeight = imf.rcImage.bottom;
	for(int Lindex=-1;;){
		Lindex=m_lc.GetNextItem(Lindex,LVNI_ALL |LVNI_SELECTED);//pNM->iItem
		if(Lindex==-1) break;
		if(pNM->iItem==Lindex){
		}else{
            hOneImageList= ListView_CreateDragImage(m_lc.m_hWnd,Lindex,&ptPos2);
            hTempImageList = ImageList_Merge(m_hDragImage, 
                             0, hOneImageList, 0, 0, iHeight);
            ImageList_Destroy(m_hDragImage);
            ImageList_Destroy(hOneImageList);
            m_hDragImage = hTempImageList;
            ImageList_GetImageInfo(m_hDragImage, 0, &imf);
            iHeight = imf.rcImage.bottom;		}
	}
 	// ドラッグ開始
	POINT ptCursor;
	GetCursorPos(&ptCursor);
	m_lc.ScreenToClient(&ptCursor);

	long lX = ptCursor.x- ptPos.x;
	long lY = ptCursor.y- ptPos.y;

	ImageList_BeginDrag(m_hDragImage,0,lX,lY);
	ImageList_DragEnter(m_hWnd,0,0);
	SetCapture();


	*pResult = 0;
}

void CPlayList::OnDrag(int x,int y)
{
	POINT Point={x,y};
	ClientToScreen(&Point);
	RECT Rect;
	GetWindowRect(&Rect);
	ImageList_DragMove(Point.x-Rect.left,Point.y-Rect.top);
	{
		CPoint  point,point2;CRect rect;
		GetCursorPos(&point);
		ScreenToClient(&point);
		m_lc.GetWindowRect(&rect);
		point2.y=rect.top; point2.x=rect.left;
		ScreenToClient(&point2);
		point-=point2;
		int hItem = m_lc.HitTest(point ,NULL);
	}
}

void CPlayList::OnEndDrag()
{
	// ドラッグ終了
	ImageList_DragLeave(m_hWnd);
	ImageList_EndDrag();
	ImageList_Destroy(m_hDragImage);
	m_hDragImage = NULL;

	// カーソル表示
	ShowCursor(TRUE);
}
void CPlayList::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	if(GetCapture()==this){
		OnDrag(point.x,point.y);
	}
	CDialog::OnMouseMove(nFlags, point);
}

void CPlayList::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	if(GetCapture()==this){
		OnEndDrag();
		// キャプチャ解除
		ReleaseCapture();
		//実際の移動のための座標割りだし
		CPoint  point,point2;CRect rect;
		GetCursorPos(&point);
		ScreenToClient(&point);
		m_lc.GetWindowRect(&rect);
		point2.y=rect.top; point2.x=rect.left;
		ScreenToClient(&point2);
		point-=point2;
		int hItem = m_lc.HitTest(point,NULL);
		if( hItem != -1){
			playlistdata *p;int cnt=0,j,cnt2=0,*cn;
			int Lindex = -1, Lindexx;
			for(;;){
				Lindex=m_lc.GetNextItem(Lindex,LVNI_ALL |LVNI_SELECTED);
				if(Lindex==-1) break;
				cnt++;
			}
			//転送データをあらかじめ作っておく
			p = (playlistdata*)malloc(sizeof(playlistdata)*cnt);
			for(Lindexx=-1;;cnt2++){
				Lindexx=m_lc.GetNextItem(Lindexx,LVNI_ALL |LVNI_SELECTED);
				if(Lindexx==-1) break;
			}
			//転送するインテックス番号を獲得する
			int cn1;
			cn =(int*)malloc(sizeof(int)*cnt2);
			for(cn1=0,Lindexx=-1;;cn1++){
				Lindexx=m_lc.GetNextItem(Lindexx,LVNI_ALL |LVNI_SELECTED);
				if(Lindexx==-1) break;
				cn[cn1]=Lindexx;
			}
			CString s;
			for(cnt=0,Lindex=-1;;cnt++){
				Lindex=m_lc.GetNextItem(Lindex,LVNI_ALL |LVNI_SELECTED);
				if(Lindex==-1) break;
				_tcscpy(p[cnt].name,pc[Lindex].name);
				_tcscpy(p[cnt].fol,pc[Lindex].fol);
				p[cnt].sub=pc[Lindex].sub;
				p[cnt].ret2=pc[Lindex].ret2;
			}
			for(Lindex=-1;;){
				playlistdata pp;
				Lindex=m_lc.GetNextItem(Lindex,LVNI_ALL |LVNI_SELECTED);
				if(Lindex==-1) break;
				_tcscpy(pp.name,pc[hItem].name);
				_tcscpy(pp.fol,pc[hItem].fol);
				pp.sub=pc[hItem].sub;
				pp.ret2=pc[hItem].ret2;
				int cnt1 = 0;
				for(;cnt1<cnt;cnt1++){
					if(_tcscmp(p[cnt1].name,pp.name)==0 && _tcscmp(p[cnt1].fol,pp.fol)==0 && p[cnt1].sub==pp.sub && p[cnt1].ret2==pp.ret2){
						break;
					}
				}
				if(cnt1!=cnt) break;
				if(hItem<Lindex){//選択項目が下　ドロップ位置が上
					int k=Lindex-hItem;
					m_lc.SetItemState(Lindex,m_lc.GetItemState(Lindex,LVIS_SELECTED)&~LVIS_SELECTED,LVIS_SELECTED);
					for(int kk=0;kk<k;kk++){
						OnXCHG(Lindex-kk,Lindex-kk-1);
					}
					m_lc.SetItemState(hItem  ,m_lc.GetItemState(hItem,LVIS_SELECTED)|LVIS_SELECTED,LVIS_SELECTED);
				}else{//選択項目が上　ドロップ位置が下
					int Lindexx = -1;
					for(;;){
						Lindexx=m_lc.GetNextItem(Lindexx,LVNI_ALL |LVNI_SELECTED);
						if(Lindexx==-1) break;
						m_lc.SetItemState(Lindexx,m_lc.GetItemState(Lindexx,LVIS_SELECTED)&~LVIS_SELECTED,LVIS_SELECTED);
					}
					int i;
					for(i=0;i<cn1;i++){
						int k=hItem-cn[i];
						for(int kk=0;kk<k;kk++){
								OnXCHG(cn[i]+kk+1,cn[i]+kk);
						}
						for(int j=0;j<cn1;j++) cn[j]--;
					}
					hItem-=cn1;
					for(i=0;i<cn1;i++){
						hItem++;
						m_lc.SetItemState(hItem  ,m_lc.GetItemState(hItem,LVIS_SELECTED)|LVIS_SELECTED,LVIS_SELECTED);
					}
					break;
				}
				hItem++;
			}
			free(cn);
			free(p);
			m_lc.RedrawWindow();
			m_lDragTopItem=0;m_lDragTopItemt=0;
		 }
	}

	CDialog::OnLButtonUp(nFlags, point);
}

void CPlayList::OnLvnGetdispinfoList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *lpDInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	if(lpDInfo==NULL)return;
	try{
	_set_se_translator( trans_func1 );
	if( lpDInfo->item.mask & LVIF_TEXT ){
		 switch( lpDInfo->item.iSubItem ){
			 case 0:
				 _tcscpy( lpDInfo->item.pszText, pc[lpDInfo->item.iItem].name ) ;	 break ;
			 case 1:
				 _tcscpy( lpDInfo->item.pszText, pc[lpDInfo->item.iItem].game ) ;	 break ;
			 case 2:{
				 CString s;
				 if(pc[lpDInfo->item.iItem].time>=3600)
					 s.Format(_T("%d:%02d:%02d"),pc[lpDInfo->item.iItem].time/3600,(pc[lpDInfo->item.iItem].time/60)%60,pc[lpDInfo->item.iItem].time%60);
				 else
					 s.Format(_T("%d:%02d"),pc[lpDInfo->item.iItem].time/60,pc[lpDInfo->item.iItem].time%60);
				 if(pc[lpDInfo->item.iItem].time==0)s="";
				 if(pc[lpDInfo->item.iItem].time==-1)s="取得不能";
				 _tcscpy( lpDInfo->item.pszText,s);
				 }break;
			 case 3:
				 _tcscpy( lpDInfo->item.pszText, pc[lpDInfo->item.iItem].art ) ;	 break ;
			 case 4:
				 _tcscpy( lpDInfo->item.pszText, pc[lpDInfo->item.iItem].alb ) ;	 break ;
			 case 5:
				 _tcscpy( lpDInfo->item.pszText, pc[lpDInfo->item.iItem].fol ) ;	 break ;
			default :
				break ;
		  }
	}
	if( lpDInfo->item.mask & LVIF_IMAGE ){
		lpDInfo->item.iImage=pc[lpDInfo->item.iItem].icon;
	}
	}
	catch(SE_Exception1 e){
	}
	catch(_EXCEPTION_POINTERS *ep){
	}
	catch(...){}
	*pResult = 0;
}

void CPlayList::OnNMRclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	*pResult = 0;

	CPoint point;
	CRect rect;
	GetCursorPos(&point);

	CMenu menu;
	VERIFY(menu.LoadMenu(CG_IDR_POPUP_LIST));

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);
	CWnd* pWndPopupOwner = this;

	while (pWndPopupOwner->GetStyle() & WS_CHILD)
		pWndPopupOwner = pWndPopupOwner->GetParent();

	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
		pWndPopupOwner);

}

void CPlayList::OnList()
{
	int Lindex=-1;
	Lindex=m_lc.GetNextItem(Lindex,LVNI_ALL |LVNI_SELECTED);
	CListSyosai *a = new CListSyosai(CWnd::FromHandle(GetSafeHwnd()));
	w_flg=FALSE;
	CWnd::PostMessage(0x118);
	memcpy(&a->pc,&pc[Lindex],sizeof(playlistdata0));
	a->DoModal();
	w_flg=TRUE;
	delete a;
}

void CPlayList::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);
	if(plw){
		if((nState==WA_ACTIVE || nState==WA_CLICKACTIVE) && bMinimized==0  && m_saisyo.GetCheck()){
			og->ShowWindow(SW_RESTORE);
			og->SetWindowPos(&wndTop,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
			SetWindowPos(&wndTop,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);

		}
	}
	// TODO: ここにメッセージ ハンドラ コードを追加します。
}

void CPlayList::OnPop32787()//ファイル名変更
{
	// TODO: ここにコマンド ハンドラ コードを追加します。
	int Lindex=-1;
	Lindex=m_lc.GetNextItem(Lindex,LVNI_ALL |LVNI_SELECTED);
	CFilename *a = new CFilename(CWnd::FromHandle(GetSafeHwnd()));
	w_flg=FALSE;
	memcpy(&a->pc,&pc[Lindex],sizeof(playlistdata0));
	CWnd::PostMessage(0x118);
	int ret=a->DoModal();
	if(ret==IDOK){
		_tcscpy(pc[Lindex].name,a->pc.name);
		_tcscpy(pc[Lindex].art,a->pc.art);
		_tcscpy(pc[Lindex].alb,a->pc.alb);
		_tcscpy(pc[Lindex].fol,a->pc.fol);
		RECT r;
		m_lc.GetItemRect(Lindex,&r,LVIR_BOUNDS);
		m_lc.RedrawWindow(&r);
	}
	w_flg=TRUE;
	delete a;
}

void CPlayList::OnFindUp()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	CString s;
	m_find.GetWindowText(s);
	s.MakeLower();
	if(s==_T("")) return;
	int pnt2;

	if(pnt<0) pnt=-1;
	if(pnt>=playcnt) pnt=playcnt;

	pnt2=pnt;
	if(pnt1!=-1) pnt2=pnt1;


	int flg=0;
	int i;
	for(i=pnt2;i<playcnt;i++){
		CString ss,ssl;
		ss=pc[i].name;
		ssl=ss;ssl.MakeLower();
		if(ssl.Find(s)!=-1 && pnt2!=i) {flg=1;break;}
		ss=pc[i].alb;
		ssl=ss;ssl.MakeLower();
		if(ssl.Find(s)!=-1 && pnt2!=i) {flg=1;break;}
		ss=pc[i].art;
		ssl=ss;ssl.MakeLower();
		if(ssl.Find(s)!=-1 && pnt2!=i) {flg=1;break;}
	}

	if(flg){
		for(int k=0;k<playcnt;k++){
			m_lc.SetItemState(k,m_lc.GetItemState(k,LVIS_SELECTED)&~LVIS_SELECTED,LVIS_SELECTED);
		}

		pnt1=i;

		m_lc.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
		m_lc.EnsureVisible(i,FALSE);
	}
	m_lc.SetFocus();
}

void CPlayList::OnFindDown()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	CString s;
	m_find.GetWindowText(s);
	s.MakeLower();
	if(s==_T("")) return;
	int pnt2;

	if(pnt<0) pnt=-1;
	if(pnt>=playcnt) pnt=playcnt;

	pnt2=pnt;
	if(pnt1!=-1) pnt2=pnt1;


	int flg=0;
	int i;
	for(i=pnt2;i>=0;i--){
		CString ss,ssl;
		ss=pc[i].name;
		ssl=ss;ssl.MakeLower();
		if(ssl.Find(s)!=-1 && pnt2!=i) {flg=1;break;}
		ss=pc[i].alb;
		ssl=ss;ssl.MakeLower();
		if(ssl.Find(s)!=-1 && pnt2!=i) {flg=1;break;}
		ss=pc[i].art;
		ssl=ss;ssl.MakeLower();
		if(ssl.Find(s)!=-1 && pnt2!=i) {flg=1;break;}
	}

	if(flg){
		for(int k=0;k<playcnt;k++){
			m_lc.SetItemState(k,m_lc.GetItemState(k,LVIS_SELECTED)&~LVIS_SELECTED,LVIS_SELECTED);
		}
		pnt1=i;

		m_lc.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
		m_lc.EnsureVisible(i,FALSE);
	}
	m_lc.SetFocus();
}


void CPlayList::OnBnClickedCheck6mp3()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CPlayList::OnBnClickedCheck7dshow()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}
