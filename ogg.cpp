// ogg.cpp : アプリケーション用クラスの定義を行います。
//

#include "stdafx.h"
#include "Windows.h"
#include "ogg.h"
#include "oggDlg.h"
#include "direct.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COggApp

BEGIN_MESSAGE_MAP(COggApp, CWinApp)
	//{{AFX_MSG_MAP(COggApp)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COggApp クラスの構築

COggApp::COggApp()
{
	// TODO: この位置に構築用のコードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の COggApp オブジェクト

COggApp theApp;
extern COggDlg *og;
/////////////////////////////////////////////////////////////////////////////
// COggApp クラスの初期化
save savedata;
TCHAR karento2[1024];
CString ndd;
void *Mutex;
TCHAR* nd;
BOOL CALLBACK ew(HWND hwnd , LPARAM lp);
BOOL CALLBACK ew(HWND hwnd,LPARAM lParam) {
	TCHAR a[1024];CString s;
	::GetWindowText(hwnd,a,sizeof(a));s=a; 
	if(s.Find(_T("mp3/m4a簡易プレイヤ"))==-1) return TRUE;
	COPYDATASTRUCT cd;
	cd.cbData=ndd.GetLength()*sizeof(TCHAR)+sizeof(TCHAR);
	cd.dwData=0;
	cd.lpData=nd;
	::SendMessage(hwnd,WM_COPYDATA, (WPARAM)NULL, (LPARAM)&cd);
	if(ndd.Left(1)!="*")
		::PostMessage(hwnd,WM_APP +1, (WPARAM)NULL, (LPARAM)NULL);
	return FALSE;
}
#include "OSVersion.h"
BOOL COggApp::InitInstance()
{
//	INITCOMMONCONTROLSEX InitCtrls;
//	InitCtrls.dwSize = sizeof(InitCtrls);
	// アプリケーションで使用するすべてのコモン コントロール クラスを含めるには、
	// これを設定します。
//	InitCtrls.dwICC = ICC_STANDARD_CLASSES;
//	InitCommonControlsEx(&InitCtrls);
	CWinApp::InitInstance();

	AfxEnableControlContainer();
//	_CrtSetBreakAlloc(8408);
	// 標準的な初期化処理
	// もしこれらの機能を使用せず、実行ファイルのサイズを小さくしたけ
	//  れば以下の特定の初期化ルーチンの中から不必要なものを削除して
	//  ください。
	ndd="";
	if(m_lpCmdLine[0] !=NULL){	ndd=m_lpCmdLine; nd=m_lpCmdLine;}
	Mutex = CreateMutex(NULL,FALSE,_T("oggEDYSbgm"));
    DWORD Status = GetLastError(); 
    if(Mutex == NULL){exit(-1);} 
    if(Status == ERROR_ALREADY_EXISTS){ 
        ReleaseMutex(Mutex);
		if(ndd!="")
			EnumWindows( ew, 0);
        exit(0); 
    } 
//	_getcwd(karento2,255);
	if (::GetModuleFileName(NULL, karento2, 1000)){    //実行ファイルのフルパスを取得
		   //取得に成功
			TCHAR* ptmp = _tcsrchr(karento2, _T('\\')); // \の最後の出現位置を取得
			if (ptmp != NULL){   //ファイル名を削除
				ptmp = _tcsinc(ptmp);   //一文字進める
				*ptmp = _T('\0');
			}
	}
	_tchdir(karento2);
	ZeroMemory(&savedata,sizeof(save));
	savedata.supe=1;
	savedata.xx=-10000;
	savedata.yy=-10000;
	savedata.gx=-10000;
	savedata.gy=-10000;
	savedata.dsvol=1;
	savedata.evr=1;
	savedata.con=1;
	savedata.ffd=1;
	savedata.audiost=1;
	_tcscpy(savedata.ysf,_T("C:\\FALCOM\\YSF_WIN"));
	_tcscpy(savedata.ys6,_T("C:\\FALCOM\\YS6_WIN"));
	_tcscpy(savedata.ed6sc,_T("C:\\FALCOM\\ED_SORA2"));
	_tcscpy(savedata.ed6fc,_T("C:\\FALCOM\\ED6_WIN"));
	_tcscpy(savedata.yso,_T("C:\\FALCOM\\YSO_WIN"));
	_tcscpy(savedata.ed6tc,_T("C:\\FALCOM\\ED_SORA3"));
	_tcscpy(savedata.zweiii,_T("C:\\FALCOM\\ZWEI2"));
	_tcscpy(savedata.ysc,_T("C:\\FALCOM\\YSC"));
	_tcscpy(savedata.xa,_T("C:\\FALCOM\\X_NEXT"));
	_tcscpy(savedata.ys12,_T("C:\\FALCOM\\YS12_CMP\\ys1_win"));
	_tcscpy(savedata.ys122,_T("C:\\FALCOM\\YS12_CMP\\ys2_win"));
	_tcscpy(savedata.sor,_T("C:\\FALCOM\\SORO_WIN"));
	_tcscpy(savedata.zwei,_T("C:\\FALCOM\\ZWEI"));
	_tcscpy(savedata.gurumin,_T("C:\\FALCOM\\GURUMIN"));
	_tcscpy(savedata.dino,_T("C:\\FALCOM\\DIN"));
	_tcscpy(savedata.br4,_T("C:\\FALCOM\\BR4_WIN"));
	_tcscpy(savedata.ed3,_T("C:\\FALCOM\\ED3_XP"));
	_tcscpy(savedata.ed4,_T("C:\\FALCOM\\ED4_XP"));
	_tcscpy(savedata.ed5,_T("C:\\FALCOM\\ED5_XP"));
	_tcscpy(savedata.tuki,_T("C:\\FALCOM\\SWORDA"));
	_tcscpy(savedata.nishi,_T("C:\\FALCOM\\ZEP_WIN"));
	_tcscpy(savedata.arc,_T("C:\\FALCOM\\Arcturus"));
	_tcscpy(savedata.san1,_T("C:\\FALCOM\\FS"));
	_tcscpy(savedata.san2,_T("C:\\FALCOM\\FS2"));
	_tcscpy(savedata.zero, _T(""));
	savedata.kaisuu=2;
	savedata.spc=1;
	savedata.mp3=1;
	savedata.savecheck=0;
	savedata.kpivol=1;
	_tcscpy(savedata.font1,_T("Consolas"));
	_tcscpy(savedata.font2,_T("メイリオ"));
	savedata.savecheck_mp3 = 1;
	savedata.savecheck_dshow = 1;
	savedata.bit24 = 1;
	savedata.bit32 = 1;
	savedata.m4a = 1;
	savedata.kakuVol = 100;
	savedata.kakuVal = 100;
	savedata.ms = 30;
	savedata.ms2 = 1;
	savedata.soundguid = { 0,0,0,0 };
	savedata.soundcur=0;
	savedata.samples = 192000;
	savedata.wup = 1.0;
	savedata.aerocheck = 0;

#if _UNICODE
	if(GetKeyState(VK_CONTROL) < 0){
		if(AfxMessageBox(L"ANSI版からのコンバートを行いますか？",MB_YESNO)==IDYES){
			convert();
			AfxMessageBox(L"コンバートが完了しました。");
			ReleaseMutex(Mutex);
			exit(0);
		}
	}
	CFile ab,ac;
	if(ab.Open(L"oggYSEDbgmu.dat",CFile::modeRead,NULL)!=TRUE && ac.Open(L"oggYSEDbgm.dat",CFile::modeRead,NULL)==TRUE){
		ac.Close();
		AfxMessageBox(L"ANSI版からのコンバートを行います。");
		convert();
		AfxMessageBox(L"コンバートが完了しました。");
		ReleaseMutex(Mutex);
		exit(0);
#else
	CFile ab;	if(ab.Open("oggYSEDbgm.dat",CFile::modeRead,NULL)!=TRUE){
#endif
	}else{
		if(ab.m_hFile != CFile::hFileNull){
			ab.Read(&savedata,sizeof(save));
			ab.Close();
		}
	}
#if _UNICODE
	if (ac.m_hFile != CFile::hFileNull)
		ac.Close();
#endif
	if (savedata.ms < 30) savedata.ms = 30;
	if (savedata.ms > 80) savedata.ms = 80;
	COSVersion os;
	os.GetVersionString();
	if(os.in.dwMajorVersion >= 10)
	if (savedata.aerocheck == 0) {
		int abc = AfxMessageBox(L"エアロ(透過処理)がメイン画面等に実装されました。是非試してみて貰えれば。\n有効にしますか？(少し不安定な部分あります)\n(このメッセージは一回しか表示されません)\nもし表示がおかしく強制的にOFFにしたい場合は、SHIFT押しながら実行して下さい\n(設定から変更できますが、設定開けないとき用)", MB_YESNO);
		if (abc == IDYES) {
			savedata.aero = 1;
			savedata.aerocheck = 1;
		}
		else {
			savedata.aero = 0;
			savedata.aerocheck = 1;
		}
	}
	if (GetKeyState(VK_SHIFT) < 0) {
		if (AfxMessageBox(L"設定のエアロ(透過処理)機能をを切りますか？", MB_YESNO) == IDYES) {
			savedata.aero = 0;
		}
	}
		_tchdir(karento2);
#if _UNICODE
	if (ab.Open(L"oggYSEDbgmu.dat", CFile::modeCreate | CFile::modeWrite, NULL) == TRUE) {
#else
	if (ab.Open("oggYSEDbgm.dat", CFile::modeCreate | CFile::modeWrite, NULL) == TRUE) {
#endif
		ab.Write(&savedata, sizeof(save));
		ab.Close();
	}
	COggDlg dlg;
	og=&dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	_tchdir(karento2);
#if _UNICODE
		if(ab.Open(L"oggYSEDbgmu.dat",CFile::modeCreate | CFile::modeWrite,NULL)==TRUE){
#else
		if(ab.Open("oggYSEDbgm.dat",CFile::modeCreate | CFile::modeWrite,NULL)==TRUE){
#endif
		ab.Write(&savedata,sizeof(save));
		ab.Close();
	}
	if (nResponse == IDOK)
	{
		// TODO: ダイアログが <OK> で消された時のコードを
		//       記述してください。
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ダイアログが <ｷｬﾝｾﾙ> で消された時のコードを
		//       記述してください。
	}

	// ダイアログが閉じられてからアプリケーションのメッセージ ポンプを開始するよりは、
	// アプリケーションを終了するために FALSE を返してください。
	ReleaseMutex(Mutex); 
	return FALSE;
}

	struct save1{
		char ysf[1024];
		char ys6[1024];
		char ed6fc[1024];
		char ed6sc[1024];
		int douga;
		int supe;
		int supe2;

		int random;
		int kaisuu;
		int gameflg[4];

		int xx,yy;
		int gx,gy;

		char yso[1024];
		int gameflg2;

		char ed6tc[1024];
		int gameflg3;

		char zweiii[1024];
		int gameflg4;

		int dsvol;
		int render;

		char ysc[1024];
		int gameflg5;
		int gameflg6;

		char xa[1024];
		int gameflg7;

		char ys12[1024];
		int gameflg8;
		int gameflg9;

		char sor[1024];
		int gameflg10;
		char ys122[1024];

		char zwei[1024];
		int gameflg11;

		char gurumin[1024];
		int gameflg12;

		char dino[1024];
		int gameflg13;

		RECT p;

		char br4[1024];
		int gameflg14;

		char ed3[1024];
		int gameflg15;

		char ed4[1024];
		int gameflg16;

		char ed5[1024];
		int gameflg17;

		char tuki[1024];
		char nishi[1024];
		char arc[1024];
		char san1[1024];
		char san2[1024];

		int fs;
		int evr;
		int con;
		int aero;
		int pl;
		int ffd;
	};

struct playlistdataold{
	char name[1024];
	char art[1024];
	char alb[1024];
	char fol[1024];
	int sub;
	int loop1;
	int loop2;
	int ret2;
	int res1;
	int res2;
};

struct playlistdatanew{
	TCHAR name[1024];
	TCHAR art[1024];
	TCHAR alb[1024];
	TCHAR fol[1024];
	int sub;
	int loop1;
	int loop2;
	int ret2;
	int res1;
	int res2;
};
#ifdef _UNICODE
void COggApp::convert()
{
	save1 saveold;
	_tchdir(karento2);
	CFile ab;
	if(ab.Open(_T("oggYSEDbgm.dat"),CFile::modeRead,NULL)!=TRUE){
		return;
	}else{
		ab.Read(&saveold,sizeof(save1));
		ab.Close();
	}
	savedata.aero=saveold.aero;
	WCHAR ss[1024];	LPWSTR ss1; char *s3;
	s3=saveold.arc; ss1=savedata.arc;
	MultiByteToWideChar(CP_ACP,0,s3,-1,ss1,1024);
	s3=saveold.br4; ss1=savedata.br4;
	MultiByteToWideChar(CP_ACP,0,s3,-1,ss1,1024);
	savedata.con=saveold.con;
	s3=saveold.dino; ss1=savedata.dino;
	MultiByteToWideChar(CP_ACP,0,s3,-1,ss1,1024);
	savedata.douga=saveold.douga;
	savedata.dsvol=saveold.dsvol;
	s3=saveold.ed3; ss1=savedata.ed3;
	MultiByteToWideChar(CP_ACP,0,s3,-1,ss1,1024);
	s3=saveold.ed4; ss1=savedata.ed4;
	MultiByteToWideChar(CP_ACP,0,s3,-1,ss1,1024);
	s3=saveold.ed5; ss1=savedata.ed5;
	MultiByteToWideChar(CP_ACP,0,s3,-1,ss1,1024);
	s3=saveold.ed6fc; ss1=savedata.ed6fc;
	MultiByteToWideChar(CP_ACP,0,s3,-1,ss1,1024);
	s3=saveold.ed6sc; ss1=savedata.ed6sc;
	MultiByteToWideChar(CP_ACP,0,s3,-1,ss1,1024);
	s3=saveold.ed6tc; ss1=savedata.ed6tc;
	MultiByteToWideChar(CP_ACP,0,s3,-1,ss1,1024);
	savedata.evr=saveold.evr;
	savedata.ffd=saveold.ffd;
	savedata.fs=saveold.fs;
	savedata.gameflg[0]=saveold.gameflg[0];
	savedata.gameflg[1]=saveold.gameflg[1];
	savedata.gameflg[2]=saveold.gameflg[2];
	savedata.gameflg[3]=saveold.gameflg[3];
	savedata.gameflg10=saveold.gameflg10;
	savedata.gameflg11=saveold.gameflg11;
	savedata.gameflg12=saveold.gameflg12;
	savedata.gameflg13=saveold.gameflg13;
	savedata.gameflg14=saveold.gameflg14;
	savedata.gameflg15=saveold.gameflg15;
	savedata.gameflg16=saveold.gameflg16;
	savedata.gameflg17=saveold.gameflg17;
	savedata.gameflg2=saveold.gameflg2;
	savedata.gameflg3=saveold.gameflg3;
	savedata.gameflg4=saveold.gameflg4;
	savedata.gameflg5=saveold.gameflg5;
	savedata.gameflg6=saveold.gameflg6;
	savedata.gameflg7=saveold.gameflg7;
	savedata.gameflg8=saveold.gameflg8;
	savedata.gameflg9=saveold.gameflg9;
	s3=saveold.gurumin; ss1=savedata.gurumin;
	MultiByteToWideChar(CP_ACP,0,s3,-1,ss1,1024);
	savedata.gx=saveold.gx;
	savedata.gy=saveold.gy;
	savedata.kaisuu=saveold.kaisuu;
	s3=saveold.nishi; ss1=savedata.nishi;
	MultiByteToWideChar(CP_ACP,0,s3,-1,ss1,1024);
	savedata.p.bottom=saveold.p.bottom;
	savedata.p.left=saveold.p.left;
	savedata.p.right=saveold.p.right;
	savedata.p.top=saveold.p.top;
	savedata.pl=saveold.pl;
	savedata.random=saveold.random;
	savedata.render=saveold.render;
	s3=saveold.san1; ss1=savedata.san1;
	MultiByteToWideChar(CP_ACP,0,s3,-1,ss1,1024);
	s3=saveold.san2; ss1=savedata.san2;
	MultiByteToWideChar(CP_ACP,0,s3,-1,ss1,1024);
	s3=saveold.sor; ss1=savedata.sor;
	MultiByteToWideChar(CP_ACP,0,s3,-1,ss1,1024);
	savedata.supe=saveold.supe;
	savedata.supe2=saveold.supe2;
	s3=saveold.tuki; ss1=savedata.tuki;
	MultiByteToWideChar(CP_ACP,0,s3,-1,ss1,1024);
	s3=saveold.xa; ss1=savedata.xa;
	MultiByteToWideChar(CP_ACP,0,s3,-1,ss1,1024);
	s3=saveold.ys12; ss1=savedata.ys12;
	MultiByteToWideChar(CP_ACP,0,s3,-1,ss1,1024);
	s3=saveold.ys122; ss1=savedata.ys122;
	MultiByteToWideChar(CP_ACP,0,s3,-1,ss1,1024);
	s3=saveold.ys6; ss1=savedata.ys6;
	MultiByteToWideChar(CP_ACP,0,s3,-1,ss1,1024);
	s3=saveold.ysc; ss1=savedata.ysc;
	MultiByteToWideChar(CP_ACP,0,s3,-1,ss1,1024);
	s3=saveold.ysf; ss1=savedata.ysf;
	MultiByteToWideChar(CP_ACP,0,s3,-1,ss1,1024);
	s3=saveold.yso; ss1=savedata.yso;
	MultiByteToWideChar(CP_ACP,0,s3,-1,ss1,1024);
	savedata.xx=saveold.xx;
	savedata.yy=saveold.yy;
	s3=saveold.zwei; ss1=savedata.zwei;
	MultiByteToWideChar(CP_ACP,0,s3,-1,ss1,1024);
	s3=saveold.zweiii; ss1=savedata.zweiii;
	MultiByteToWideChar(CP_ACP,0,s3,-1,ss1,1024);

	if(ab.Open(L"oggYSEDbgmu.dat",CFile::modeCreate | CFile::modeWrite,NULL)==TRUE){
		ab.Write(&savedata,sizeof(save));
		ab.Close();
	}

	//プレイリスト移植
	int cnt,x1,y1,cx,cy,x=-10000,y,c[4],c1[5];;
	CFile f;if(f.Open(_T("playlist.dat"),CFile::modeRead,NULL)==TRUE){
		CFile g;g.Open(_T("playlistu.dat"),CFile::modeCreate|CFile::modeWrite,NULL);
		f.Read(&cnt,4);
		f.Read(&x1,4);
		f.Read(&y1,4);
		f.Read(&cx,4);
		f.Read(&cy,4);
		f.Read(&c1[0],4);
		f.Read(&c1[1],4);
		f.Read(&c1[2],4);
		f.Read(&c1[3],4);
		f.Read(&c1[4],4);
		g.Write(&cnt,4);
		g.Write(&x1,4);
		g.Write(&y1,4);
		g.Write(&cx,4);
		g.Write(&cy,4);
		g.Write(&c1[0],4);
		g.Write(&c1[1],4);
		g.Write(&c1[2],4);
		g.Write(&c1[3],4);
		g.Write(&c1[4],4);
		playlistdataold pld;
		playlistdatanew pldn;
		for(int i=0;i<cnt;i++){
			f.Read(&pld,sizeof(pld));
			s3=pld.alb; ss1=pldn.alb;MultiByteToWideChar(CP_ACP,0,s3,-1,ss1,1024);
			s3=pld.art; ss1=pldn.art;MultiByteToWideChar(CP_ACP,0,s3,-1,ss1,1024);
			s3=pld.fol; ss1=pldn.fol;MultiByteToWideChar(CP_ACP,0,s3,-1,ss1,1024);
			s3=pld.name; ss1=pldn.name;MultiByteToWideChar(CP_ACP,0,s3,-1,ss1,1024);
			pldn.loop1=pld.loop1;
			pldn.loop2=pld.loop2;
			pldn.res1=pld.res1;
			pldn.res2=pld.res2;
			pldn.ret2=pld.ret2;
			pldn.sub=pld.sub;
			g.Write(&pldn,sizeof(pldn));
		}
		c[0]=0;f.Read(&c[0],4);
		c[1]=0;f.Read(&c[1],4);
		c[2]=1;f.Read(&c[2],4);
		c[3]=1;f.Read(&c[3],4);
		g.Write(&c[0],4);
		g.Write(&c[1],4);
		g.Write(&c[2],4);
		g.Write(&c[3],4);
		f.Close();
		g.Close();
	}else return;
}
#else
void COggApp::convert()
{
}
#endif
