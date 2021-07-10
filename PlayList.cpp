// PlayList.cpp : �����t�@�C��
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

// CPlayList �_�C�A���O

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
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R����ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R����ݒ�
	// TODO:  �����ɏ�������ǉ����Ă�������
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
	m_tooltip.AddTool(GetDlgItem(IDOK), _T("�v���C���X�g����܂��B"));
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON1), _T("�I�����ڂ���ԏ�Ɏ����čs���܂��B"));
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON5), _T("�I�����ڂ���Ɏ����čs���܂��B"));
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON10), _T("�I�����ڂ���ԉ��Ɏ����čs���܂��B"));
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON11), _T("�I�����ڂ����Ɏ����čs���܂��B"));
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON16), _T("���݂̈ʒu���牺�Ɍ������܂��B"));
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON20), _T("���݂̈ʒu�����Ɍ������܂��B"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK1), _T("�v���C���X�g�̏��ԂɍĐ����s���܂��B\n�Đ����Ƀt�@�C���h���b�v���Ēǉ����Ă����t���̋Ȃ͂��̂܂ܖ葱���܂��B"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK4), _T("�I�������Ȃ����[�v�����܂��B\n�Đ�����O�Ƀ`�F�b�N������K�v������܂��B\n�����łȂ��ƃ��[�v�͂�����܂���B\n���[�v�|�C���g��0�̂���(mp3�⃋�[�v���Ȃ���)���Ώۂł��B"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK28), _T("�c�[���`�b�v��\�����܂��B"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK29), _T("�ŏ����A�ŏ�������̕��A���A���C����ʂƃv���C���X�g��ʂ������ɍŏ����A�ŏ�������̕��A���s���܂��B"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK5), _T("�r���ŉ��t���~�����ʒu�������ۑ����܂��B\nmp3�n�Ɠ���(avi,mp4�Ȃ�)�̂ݑΉ��B\n��~�{�^���������͏I�������Ƃ��̂ݕۑ����܂��B\n�Đ����ɈႤ�Ȃ�I�񂾎��͈ʒu�͕ۑ����܂���B"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK6), _T("mp3�Đ����ɓr���ۑ���L���ɂ��܂��B"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK7), _T("����Ȃǂ�DirectShow�g�p���ɓr���ۑ���L���ɂ��܂��B"));
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
	m_lc.InsertColumn ( 0, _T("���O"), LVCFMT_LEFT, 200, 0 );
	m_lc.InsertColumn ( 1, _T("�Q�[��"), LVCFMT_LEFT, 50, 0 );
	m_lc.InsertColumn ( 2, _T("����"), LVCFMT_RIGHT, 50, 0 );
	m_lc.InsertColumn ( 3, _T("�A�[�e�B�X�g"), LVCFMT_LEFT, 200, 0 );
	m_lc.InsertColumn ( 4, _T("�A���o��/�R�����g"), LVCFMT_LEFT, 200, 0 );
	m_lc.InsertColumn ( 5, _T("�t�H���_"), LVCFMT_LEFT, 50, 0 );
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
//		retfont=pFont.CreateFont(0,0,0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,_T("�l�r �o�S�V�b�N"));
//	if(retfont){
//		m_lc.SetFont(&pFont,TRUE);
//		m_find.SetFont(&pFont,TRUE);
//	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}
extern int killw1;
extern CPlayList *pl;
void CPlayList::OnNcDestroy()
{
	CDialog::OnNcDestroy();

	// TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����܂��B
	killw1=1;
}

BOOL CPlayList::DestroyWindow()
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
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
	// TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	nnn=0;
	DestroyWindow();

	CDialog::OnClose();
}

void CPlayList::OnBnClickedOk()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
//	DestroyWindow();
}

BOOL CPlayList::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
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
		case 1:s="��̋O��SC";break;
		case 2:s="��̋O��FC";break;
		case 3:s="�C�[�X �t�F���K�i�̐���";break;
		case 4:s="Ys6 �i�s�V���e���̙�";break;
		case 5:s="�C�[�X �I���W��";break;
		case 6:s="��̋O�� The3rd";break;
		case 7:s="ZWEI II";break;
		case 8:s="Ys I&II Chronicles 1";break;
		case 9:s="Ys I&II Chronicles 2";break;
		case 10:s="XANADU NEXT";break;
		case 11:s="Ys I&II ���S�� 1";break;
		case 12:s="Ys I&II ���S�� 2";break;
		case 13:s="Sorcerian Original";break;
		case 14:s="Zwei!!";break;
		case 15:s="����݂� -GURUMIN-";break;
		case 16:s="�_�C�i�\�A ���U���N�V����";break;
		case 17:s="Brandish4 �����_�̓�";break;
		case 18:s="��������";break;
		case 19:s="��g����";break;
		case 20:s="�C�̟B��";break;
		case 21:s = "�M�̋O��I or II"; break;
		case -6:s = "�M�̋O��III or IV"; break;
		case -11:s="���e�̃��v�\�f�B�[";break;
		case -12:s="�����̋�����";break;
		case -13:s="�A�[�N�g�D���X";break;
		case -14:s="���z�O���u1";break;
		case -15:s="���z�O���u2";break;
		case -3:
			ss=fol.Right(fol.GetLength()-fol.ReverseFind('.')-1);
			s.Format(_T("%s�t�@�C��"),ss);break;
		case -2:
			ss=fol.Right(fol.GetLength()-fol.ReverseFind('.')-1);
			s.Format(_T("%s�t�@�C��"),ss);break;
		case -1:s="ogg�t�@�C��";break;
		case -7:
			s = fol; s.MakeLower();
			if (s.Right(3) == "dsf") { s = "dsf�t�@�C��(DSD)"; break; }
			if (s.Right(3) == "wsd") { s = "wsd�t�@�C��(DSD)"; break; }
			if (s.Right(3) == "dff") { s = "dff�t�@�C��(DSD)"; break; }
		case -8:
			s = fol; s.MakeLower();
			if (s.Right(4) == "flac") { s = "flac�t�@�C��"; break; }
		case -9:
			s = fol; s.MakeLower();
			if (s.Right(3) == "m4a") { s = "m4a�t�@�C��"; break; }
			if (s.Right(3) == "aac") { s = "aac�t�@�C��"; break; }
		case -10:
			s=fol;s.MakeLower();
			if(s.Right(3)=="mp3"){ s="mp3�t�@�C��";break;}
			if(s.Right(3)=="mp2"){ s="mp2�t�@�C��";break;}
			if(s.Right(3)=="mp1"){ s="mp1�t�@�C��";break;}
			if(s.Right(3)=="rmp"){ s="rmp�t�@�C��";break;}
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
	for(;;){//�I������Ă�����̂��s�b�N�A�b�v
		Lindex=m_lc.GetNextItem(Lindex,LVNI_ALL |LVNI_SELECTED);
		if(Lindex==-1) break;
		m_lc.SetItemState(Lindex,m_lc.GetItemState(Lindex,LVIS_SELECTED)&~LVIS_SELECTED,LVIS_SELECTED);
		for(int i=Lindex+1+j;i<playcnt;i++){
			memcpy(&pc[i-1],&pc[i],sizeof(playlistdata0));
		}
		playcnt--;j--;
	}
	playlistdata0 *tmp;tmp=pc;
	pc=(playlistdata0*)realloc(tmp,(size_t)sizeof(playlistdata0)*(playcnt+2));//�]�T�������ĉ��
	m_lc.SetItemCount(playcnt);
	for(j=0;j<playcnt;j++) pc[j].icon=1;
	m_lc.RedrawWindow();
	Save();
}

void CPlayList::OnSUP()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
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
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
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
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
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
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
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
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
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
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	if(pLVKeyDow->wVKey == VK_DELETE){
		Del();
	}
	*pResult = 0;
}


void CPlayList::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
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

// OggVorbis�R�[���o�b�N�֐�
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

					//YS8 steam�ŗp�@bgm�e�[�u���ϊ�
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
					//ys8�p
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
						ss = "�o�g��#58";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_b002.ogg") {
						ss = "�ܔM�̉��̒���";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_b003.ogg") {
						ss = "�ŏI����";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_b004.ogg") {
						ss = "������";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_b005.ogg") {
						ss = "The False God of Causality";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_d101.ogg") {
						ss = "�_���W����";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_d201.ogg") {
						ss = "�����t�̗U��";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_d301.ogg") {
						ss = "�n�����";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_d401.ogg") {
						ss = "�����̓��`�G���f�B�[���ɂ����Â���";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_d501.ogg") {
						ss = "����ꂵ���ʂ����߂�";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_d701.ogg") {
						ss = "�C���X";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_d702.ogg") {
						ss = "yc_d702";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_d703.ogg") {
						ss = "����";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_e001.ogg") {
						ss = "����";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_e002.ogg") {
						ss = "�����̋V��";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_e003.ogg") {
						ss = "���t�@���X";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_e004.ogg") {
						ss = "�܂̏��N���m";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_e005.ogg") {
						ss = "�G���f�B�[��";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_e006.ogg") {
						ss = "�������鍑 -�j�ă��I�c��-";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_e008.ogg") {
						ss = "yc_e008";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_e010.ogg") {
						ss = "�`���ƁA�a��";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_f101.ogg") {
						ss = "�R��錕";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_f201.ogg") {
						ss = "�Z���Z�^�̎��C";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_f301.ogg") {
						ss = "�N���[�^�[";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_f401.ogg") {
						ss = "THE DAWN OF YS";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_f501.ogg") {
						ss = "�ł̐X";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_f601.ogg") {
						ss = "��w�̕�";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_f701.ogg") {
						ss = "�_��̒n";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_f801.ogg") {
						ss = "�^���ւ̏���";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_f901.ogg") {
						ss = "�J�オ��̒���";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_over.ogg") {
						ss = "�Q�[���I�[�o�[";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_t101.ogg") {
						ss = "�Ӌ��s�s�s�L���X�i���t";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_t201.ogg") {
						ss = "�D�����Ȃ肽��";
						_tcscpy(p.name, ss);
					}
					if (ss == "yc_t301.ogg") {
						ss = "�Ñ�̓`��";
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
						ss = "�V���Ȏ���̃X�e�[�W��";
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
							a = L"��̋O��";
							break;
						case 7002:
							a = L"way of live -Opening Version-";
							break;
						case 7003:
							a = L"�V�������X�`�\��";
							break;
						case 7005:
							a = L"�z���j��āE�E�E";
							break;
						case 7052:
							a = L"�ɂ��O�� -Opening size-";
							break;
						case 7053:
							a = L"����ł��l��́B";
							break;
						case 7100:
							a = L"�X�p�̕��i";
							break;
						case 7101:
							a = L"�����͖����̕�������";
							break;
						case 7102:
							a = L"�N���X�x���̌ߌ�";
							break;
						case 7103:
							a = L"During Mission Accomplishment";
							break;
						case 7104:
							a = L"�n���L�O��";
							break;
						case 7105:
							a = L"�~���m��10%";
							break;
						case 7106:
							a = L"���D�Ǝ�����";
							break;
						case 7110:
							a = L"�����x����";
							break;
						case 7111:
							a = L"C.S.P.D. -�N���X�x���x�@";
							break;
						case 7113:
							a = L"Arc-en-ciel";
							break;
						case 7114:
							a = L"�����f�Ռ��i";
							break;
						case 7116:
							a = L"IGNIS";
							break;
						case 7117:
							a = L"TRINITY";
							break;
						case 7120:
							a = L"�A�������J��";
							break;
						case 7121:
							a = L"�z�R���}�C���c";
							break;
						case 7122:
							a = L"Killing Bear";
							break;
						case 7123:
							a = L"���E���X����ȑ�w";
							break;
						case 7124:
							a = L"�N���X�x���吹��";
							break;
						case 7125:
							a = L"���̋�����";
							break;
						case 7126:
							a = L"�卑�ɂ͂��܂��";
							break;
						case 7150:
							a = L"�V���Ȃ����";
							break;
						case 7151:
							a = L"�����n�߂�����";
							break;
						case 7160:
							a = L"�~�V�����������_�[�����h";
							break;
						case 7161:
							a = L"���̊Ԃ̋x��";
							break;
						case 7162:
							a = L"�����₩�Ȕӎ`";
							break;
						case 7200:
							a = L"���Ƒ��؂Ɛ���";
							break;
						case 7201:
							a = L"�Ў�ɂ̓����l�[�h";
							break;
						case 7202:
							a = L"�ؗ�̓�";
							break;
						case 7203:
							a = L"�Â̌ۓ�";
							break;
						case 7204:
							a = L"On The Green Road";
							break;
						case 7205:
							a = L"�S�����z����";
							break;
						case 7250:
							a = L"�؉k����̒��̐Î�";
							break;
						case 7251:
							a = L"�U��̊y�y���z����";
							break;
						case 7300:
							a = L"�W�I�t�����g";
							break;
						case 7301:
							a = L"���s������";
							break;
						case 7302:
							a = L"���o�[�`�F����";
							break;
						case 7303:
							a = L"��͂��̂Ȃ���";
							break;
						case 7304:
							a = L"�Y���ꂵ�����̋���";
							break;
						case 7305:
							a = L"A Light Illuminating The Depths";
							break;
						case 7350:
							a = L"D�̎c�e";
							break;
						case 7351:
							a = L"�ٕς̒���";
							break;
						case 7352:
							a = L"Mystic Core";
							break;
						case 7353:
							a = L"�ŉʂĂ̎�";
							break;
						case 7354:
							a = L"�\���̌Ăѐ�";
							break;
						case 7356:
							a = L"�s��";
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
							a = L"���ꂪ�������̗͂�!";
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
							a = L"���ʉ�";
							break;
						case 7500:
							a = L"���̑��z�A��̌��@-�z�̔M��";
							break;
						case 7501:
							a = L"���̑��z�A��̌��@-���̕��";
							break;
						case 7502:
							a = L"���̑��z�A��̌��@-���S";
							break;
						case 7503:
							a = L"���̑��z�A��̌��@-�^���̍�";
							break;
						case 7504:
							a = L"���̑��z�A��̌��@-����ʑz��";
							break;
						case 7505:
							a = L"���̑��z�A��̌��@-����̖���z����";
							break;
						case 7506:
							a = L"���̑��z�A��̌��@-�閾���`��c�~";
							break;
						case 7507:
							a = L"Intense Chase";
							break;
						case 7509:
							a = L"���ʂ��ӎu";
							break;
						case 7510:
							a = L"�b�q�ւ̗U��";
							break;
						case 7511:
							a = L"��n";
							break;
						case 7512:
							a = L"�h�邬�Ȃ�����";
							break;
						case 7513:
							a = L"��i�ɉ��ސ���";
							break;
						case 7514:
							a = L"����������";
							break;
						case 7515:
							a = L"�_�炩�ȐS";
							break;
						case 7516:
							a = L"�_�Ɛ�";
							break;
						case 7517:
							a = L"��G����";
							break;
						case 7518:
							a = L"Foolish Gig";
							break;
						case 7519:
							a = L"���x�[������̕�";
							break;
						case 7520:
							a = L"�Ƃǂ����z��";
							break;
						case 7521:
							a = L"Underground Kids";
							break;
						case 7522:
							a = L"Terminal Room";
							break;
						case 7523:
							a = L"���������S";
							break;
						case 7524:
							a = L"Limit Break";
							break;
						case 7525:
							a = L"�p���_�C�X�~��";
							break;
						case 7526:
							a = L"Gnosis";
							break;
						case 7527:
							a = L"Get Over The Barrier! -Roaring Version-";
							break;
						case 7528:
							a = L"���ꂼ��̖���";
							break;
						case 7529:
							a = L"���ʉ��y1";
							break;
						case 7530:
							a = L"���ʉ��y2";
							break;
						case 7531:
							a = L"���ʉ��y3";
							break;
						case 7532:
							a = L"���ʉ��y4";
							break;
						case 7533:
							a = L"���ݏo���E�C";
							break;
						case 7534:
							a = L"���̔w�������߂�";
							break;
						case 7540:
							a = L"�s��";
							break;
						case 7541:
							a = L"�s��";
							break;
						case 7542:
							a = L"�s��";
							break;
						case 7543:
							a = L"�s��";
							break;
						case 7544:
							a = L"�s��";
							break;
						case 7550:
							a = L"�I���L�X�^���[";
							break;
						case 7551:
							a = L"Catastrophe";
							break;
						case 7552:
							a = L"�ɂ���";
							break;
						case 7553:
							a = L"�_�@�~��";
							break;
						case 7554:
							a = L"�ӂ������";
							break;
						case 7555:
							a = L"�\��O�̊��";
							break;
						case 7556:
							a = L"�|�S�̙��K -����-";
							break;
						case 7560:
							a = L"�J�̓��̐^��";
							break;
						case 7561:
							a = L"�s��";
							break;
						case 7562:
							a = L"���ʉ�";
							break;
						case 7563:
							a = L"�]���̐�̊�]";
							break;
						case 7564:
							a = L"Strange Feel";
							break;
						case 7565:
							a = L"Exhilarating Ride";
							break;
						case 7566:
							a = L"���ꂼ��̐��`";
							break;
						case 7567:
							a = L"���z����ׂ���";
							break;
						case 7568:
							a = L"�����̑z��";
							break;
						case 7569:
							a = L"Miss You";
							break;
						case 7570:
							a = L"�V�̎�";
							break;
						case 7571:
							a = L"�˂�����ꂽ����";
							break;
						case 7572:
							a = L"���ʉ�";
							break;
						case 7573:
							a = L"�S�Ă��������";
							break;
						case 7574:
							a = L"�z���A�H�蒅���ꏊ";
							break;
						case 7575:
							a = L"�h�ꓮ���S";
							break;
						case 7576:
							a = L"���~����";
							break;
						case 7577:
							a = L"���ʉ�";
							break;
						case 7578:
							a = L"���ʉ�";
							break;
						case 7579:
							a = L"���ʉ�";
							break;
						case 7580:
							a = L"���ʉ�";
							break;
						case 7581:
							a = L"�{�����J";
							break;
						case 7582:
							a = L"�҂��b����";
							break;
						case 7583:
							a = L"���[�����A�ʏ���c";
							break;
						case 7584:
							a = L"���ʉ�";
							break;
						case 7585:
							a = L"��N�̖ώ�";
							break;
						case 7586:
							a = L"�|�S�̙��K -����-";
							break;
						case 7587:
							a = L"�|������! -���Ԍ��c�q�̋t�P-";
							break;
						case 7588:
							a = L"Fateful Confrontation -�|������! Ver.-";
							break;
						case 7589:
							a = L"�|����܂���";
							break;
						case 7590:
							a = L"�G���B�⋩�R�[�X�^�[";
							break;
						case 7591:
							a = L"�����ȉp�Y -�I���S�[��-";
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
						a = L"���ȃN���X�sVII�g�t";
						break;
					case 8002:
						a = L"�����Ђ�����ɁA�O��";
						break;
					case 8100:
						a = L"�ߍx�s�s�g���X�^";
						break;
					case 8101:
						a = L"���Ւ��P���f�B�b�N";
						break;
					case 8102:
						a = L"�Ő��̌��s�o���A�n�[�g";
						break;
					case 8103:
						a = L"�ΔȂ̊X���O����";
						break;
					case 8104:
						a = L"����̍|�s���[��";
						break;
					case 8106:
						a = L"�V�q���̏W��";
						break;
					case 8107:
						a = L"��̒�s�w�C���_��";
						break;
					case 8108:
						a = L"�����̉䂪��";
						break;
					case 8109:
						a = L"�_�C�j���O�o�[�sF�t";
						break;
					case 8110:
						a = L"��ݐ��̋C�T";
						break;
					case 8111:
						a = L"�K�����A�̋���";
						break;
					case 8120:
						a = L"�����̉�����";
						break;
					case 8121:
						a = L"�Î�̋�";
						break;
					case 8122:
						a = L"�����ւ̋x��";
						break;
					case 8123:
						a = L"�t�̗z�˂�";
						break;
					case 8125:
						a = L"�J���C�W���X���i�I";
						break;
					case 8126:
						a = L"�ڊo�߂�ӎu";
						break;
					case 8127:
						a = L"����̋��D";
						break;
					case 8150:
						a = L"���ی�̎���";
						break;
					case 8152:
						a = L"����₩�Ȓ�";
						break;
					case 8153:
						a = L"�J���̊w�@";
						break;
					case 8154:
						a = L"�u�₩�ȗz�˂�";
						break;
					case 8156:
						a = L"�g�[���Y�m���w�@��";
						break;
					case 8158:
						a = L"��̊J����";
						break;
					case 8159:
						a = L"���R�s����";
						break;
					case 8200:
						a = L"�ً��̋�";
						break;
					case 8201:
						a = L"���J��������";
						break;
					case 8202:
						a = L"����̏���";
						break;
					case 8203:
						a = L"���u�̑�n";
						break;
					case 8210:
						a = L"��΂��z����";
						break;
					case 8212:
						a = L"Trudge Along";
						break;
					case 8213:
						a = L"�~�̖K��";
						break;
					case 8300:
						a = L"���Z�ɂ̓�";
						break;
					case 8301:
						a = L"�T��";
						break;
					case 8302:
						a = L"�[���֌�����";
						break;
					case 8303:
						a = L"�����̏�";
						break;
					case 8304:
						a = L"������͂ނ��߂�";
						break;
					case 8305:
						a = L"�n���ɖ����\";
						break;
					case 8308:
						a = L"���̑b���邽�߂�";
						break;
					case 8310:
						a = L"����A";
						break;
					case 8311:
						a = L"�s��";
						break;
					case 8312:
						a = L"Phantasmal Blaze";
						break;
					case 8313:
						a = L"������L";
						break;
					case 8315:
						a = L"����";
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
						a = L"���C�i���`�J��";
						break;
					case 8409:
						a = L"The Decisive Collision";
						break;
					case 8410:
						a = L"���̎�œ���؂��!";
						break;
					case 8411:
						a = L"�ԓ_�ł�...";
						break;
					case 8412:
						a = L"Unknown Threat";
						break;
					case 8413:
						a = L"�s��";
						break;
					case 8420:
						a = L"Heated Mind";
						break;
					case 8421:
						a = L"�s��";
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
						a = L"�P���閾����";
						break;
					case 8435:
						a = L"���鋐�e";
						break;
					case 8441:
						a = L"E.O.V";
						break;
					case 8442:
						a = L"�s��";
						break;
					case 8500:
						a = L"Strain";
						break;
					case 8501:
						a = L"��̂ЂƂƂ�";
						break;
					case 8502:
						a = L"�g���u������";
						break;
					case 8503:
						a = L"�S�H�y�X";
						break;
					case 8504:
						a = L"���D";
						break;
					case 8505:
						a = L"�c��ɂ�";
						break;
					case 8506:
						a = L"Let's Study";
						break;
					case 8507:
						a = L"�m�b���i����";
						break;
					case 8508:
						a = L"���Z����";
						break;
					case 8509:
						a = L"���ɋA�낤";
						break;
					case 8510:
						a = L"�A�[�x���g�^�C��";
						break;
					case 8512:
						a = L"�S�̓���";
						break;
					case 8513:
						a = L"�Ö�";
						break;
					case 8514:
						a = L"�z���̍s����";
						break;
					case 8515:
						a = L"���S";
						break;
					case 8516:
						a = L"�h��߂��������߂�";
						break;
					case 8517:
						a = L"��r�ȋC����";
						break;
					case 8520:
						a = L"�Ր�Ԑ�";
						break;
					case 8521:
						a = L"Seriousness";
						break;
					case 8522:
						a = L"�Â��Ȃ�V�g";
						break;
					case 8523:
						a = L"�g���ȗ[�M";
						break;
					case 8524:
						a = L"Atrocious Raid";
						break;
					case 8525:
						a = L"�S�Ă�q���č��A�����ɗ���";
						break;
					case 8527:
						a = L"�V�������Ԃ���";
						break;
					case 8528:
						a = L"�s�����Ȏ���";
						break;
					case 8529:
						a = L"�S���ւ̃��N�C�G��";
						break;
					case 8530:
						a = L"���z�̉S -PHANTASMAGORIA-";
						break;
					case 8531:
						a = L"���n������";
						break;
					case 8532:
						a = L"�ڊo�߂��`��";
						break;
					case 8533:
						a = L"�B��̊�]";
						break;
					case 8535:
						a = L"�s��";
						break;
					case 8537:
						a = L"�s��";
						break;
					case 8538:
						a = L"���͂܂�...";
						break;
					case 8539:
						a = L"���̓��Ɍ������";
						break;
					case 8540:
						a = L"�U��̎���";
						break;
					case 8541:
						a = L"�g���� -�V���Ȃ镗-";
						break;
					case 8550:
						a = L"�ĉ�";
						break;
					case 8551:
						a = L"���������̂Ȃ��l��";
						break;
					case 8552:
						a = L"�ɂ��ނ悤�ɁA�������ނ悤��";
						break;
					case 8553:
						a = L"���C�m�̉Ԃ��炭��";
						break;
					case 8555:
						a = L"���̝|";
						break;
					case 8556:
						a = L"Remaining Glow";
						break;
					case 8557:
						a = L"�[���̖���";
						break;
					case 8558:
						a = L"ALTINA";
						break;
					case 8559:
						a = L"�Е�";
						break;
					case 8560:
						a = L"�ꌂ�ɓq����";
						break;
					case 8561:
						a = L"���~���k�J��";
						break;
					case 8562:
						a = L"Awakening";
						break;
					case 8563:
						a = L"Blitzkrieg";
						break;
					case 8564:
						a = L"�����̊M��";
						break;
					case 8566:
						a = L"���Ȃ鉩��";
						break;
					case 8567:
						a = L"�h��L��";
						break;
					case 8570:
						a = L"�Â��Ȍ���";
						break;
					case 8571:
						a = L"�����ꝱ";
						break;
					case 8572:
						a = L"���";
						break;
					case 8573:
						a = L"���ʉ�";
						break;
					case 8600:
						a = L"��s�̓��킢";
						break;
					case 8601:
						a = L"���̗V�Y";
						break;
					case 8602:
						a = L"����d�̍U�h";
						break;
					case 8603:
						a = L"����}�b�n��!";
						break;
					case 8605:
						a = L"���ʉ�";
						break;
					case 8606:
						a = L"���ʉ�";
						break;
					case 8607:
						a = L"�����̃J���^�[�^";
						break;
					case 8608:
						a = L"���ʉ�";
						break;
					case 8609:
						a = L"Sonata No.45";
						break;
					case 8610:
						a = L"���ʉ�";
						break;
					case 8620:
						a = L"��E�T�M��ǂ�������";
						break;
					case 8621:
						a = L"Take The Windward!";
						break;
					case 8622:
						a = L"���ʉ�";
						break;
					case 8623:
						a = L"���ʉ�";
						break;
					case 8624:
						a = L"���ʉ�";
						break;
					case 8625:
						a = L"���ʉ�";
						break;
					case 8627:
						a = L"���ʉ�";
						break;
					case 8628:
						a = L"�s��";
						break;
					case 8629:
						a = L"���ʉ�";
						break;
					case 8700:
						a = L"���y";
						break;
					case 8703:
						a = L"���y";
						break;
					case 8704:
						a = L"���y";
						break;
					case 8710:
						a = L"���y";
						break;
					case 8711:
						a = L"���y";
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
						a = "���ȃN���X�sVII�g�t";
						break;
					case 8002:
						a = "�X�^�[�g���C��";
						break;
					case 8003:
						a = "�s��";
						break;
					case 8004:
						a = "Youthful Victory";
						break;
					case 8006:
						a = "�����Ђ�����ɁA�O��";
						break;
					case 8007:
						a = "�� -�Ȃ�����-";
						break;
					case 8102:
						a = "�Ő��̌��s�o���A�n�[�g";;
						break;
					case 8104:
						a = "����̍|�s���[��";
						break;
					case 8150:
						a = "���Z�r���Ƀp���P�[�L";
						break;
					case 8151:
						a = "�\���͖�����";
						break;
					case 8152:
						a = "��̂����܂�";
						break;
					case 8153:
						a = "�[�i";
						break;
					case 8154:
						a = "�V������";
						break;
					case 8155:
						a = "���̊Ԃ̗��A��";
						break;
					case 8156:
						a = "�����̋��s�Z���g�A�[�N";
						break;
					case 8157:
						a = "�a�ђ��p����";
						break;
					case 8158:
						a = "�Ă̒��̃N���X�x��";
						break;
					case 8159:
						a = "���A�����ׂ�����";
						break;
					case 8160:
						a = "���y�s�s���N�E�F��";
						break;
					case 8161:
						a = "�Â��Ȃ�삯����";
						break;
					case 8162:
						a = "�q�󂽂�w�C���_��";
						break;
					case 8163:
						a = "���ɂ̊C�s�I���f�B�X";
						break;
					case 8164:
						a = "�őO���s�s";
						break;
					case 8165:
						a = "Base Camp";
						break;
					case 8166:
						a = "�����Ȃ镺����";
						break;
					case 8168:
						a = "�s��";
						break;
					case 8170:
						a = "�B�ꗢ�G����";
						break;
					case 8171:
						a = "��������";
						break;
					case 8172:
						a = "�����̒���";
						break;
					case 8173:
						a = "�g���M�e -���܂Ƃ���-";
						break;
					case 8174:
						a = "���E���X����ȑ�w -�MVer.-";
						break;
					case 8175:
						a = "�ꖕ�̕s���A���~�̖]��";
						break;
					case 8176:
						a = "Lyrical Amber";
						break;
					case 8177:
						a = "���ʂ�n�镗";
						break;
					case 8250:
						a = "�����_�̔ޕ���";
						break;
					case 8251:
						a = "�Î�̏��H";
						break;
					case 8252:
						a = "�R�J�̋���";
						break;
					case 8253:
						a = "Weathering Road";
						break;
					case 8260:
						a = "�ނ̒n�֌�������";
						break;
					case 8261:
						a = "�I���̓r��";
						break;
					case 8262:
						a = "�S�Ă�������� -�MVer.-";
						break;
					case 8263:
						a = "��������Γ�";
						break;
					case 8311:
						a = "�s��";
						break;
					case 8350:
						a = "�A�C���w�����v��";
						break;
					case 8351:
						a = "�`���̗���";
						break;
					case 8352:
						a = "Unplanned Residue";
						break;
					case 8353:
						a = "�Y���ꂵ�����̋��� -�MVer.-";
						break;
					case 8354:
						a = "�H���̋C�z";
						break;
					case 8355:
						a = "solid as the Rock of JUNO";
						break;
					case 8356:
						a = "�n���ɑ���";
						break;
					case 8359:
						a = "Spiral of Erebos";
						break;
					case 8360:
						a = "�|�̏��";
						break;
					case 8363:
						a = "Break In";
						break;
					case 8365:
						a = "�T���O���[�����{";
						break;
					case 8366:
						a = "�Â����X�̖���";
						break;
					case 8367:
						a = "Mystic Core -�MVer.-";
						break;
					case 8368:
						a = "�Ă�������";
						break;
					case 8369:
						a = "�V���N���j�V�e�B #23";
						break;
					case 8371:
						a = "���E�̖��^��q����";
						break;
					case 8372:
						a = "The End of -SAGA-";
						break;
					case 8429:
						a = "�s��";
						break;
					case 8450:
						a = "Brave Steel";
						break;
					case 8451:
						a = "Toughness!!";
						break;
					case 8452:
						a = "�����{��";
						break;
					case 8453:
						a = "Proud Grudge";
						break;
					case 8454:
						a = "�`�[�v�E�g���b�v";
						break;
					case 8455:
						a = "STEP AHEAD";
						break;
					case 8456:
						a = "�򐨂�҉񂹂�I";
						break;
					case 8457:
						a = "Abrupt Visitor";
						break;
					case 8458:
						a = "�s�������� -Opening Size-";
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
						a = "�s��";
						break;
					case 8466:
						a = "Erosion of Madness";
						break;
					case 8467:
						a = "DOOMSDAY TRANCE";
						break;
					case 8468:
						a = "�s��";
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
						a = "�Â̖���";
						break;
					case 8476:
						a = "���̑��� -EXCELLION KRIEG-";
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
						a = "���Ƃ͍�����";
						break;
					case 8501:
						a = "Power or Technique";
						break;
					case 8502:
						a = "Briefing Time";
						break;
					case 8503:
						a = "��II���Z�̓���";
						break;
					case 8504:
						a = "�[�������ЂƂƂ�";
						break;
					case 8505:
						a = "�ْ[�̌�����";
						break;
					case 8506:
						a = "�N�ɓ`����������";
						break;
					case 8507:
						a = "�s��";
						break;
					case 8508:
						a = "�s��";
						break;
					case 8509:
						a = "����l�߂��v�f";
						break;
					case 8510:
						a = "�����̑Η�";
						break;
					case 8511:
						a = "�}�]����";
						break;
					case 8512:
						a = "忂��A�d";
						break;
					case 8513:
						a = "�����ꂽ����";
						break;
					case 8514:
						a = "�����̌O��";
						break;
					case 8515:
						a = "�n�[���� -�₳�ꂽ����-";
						break;
					case 8516:
						a = "Welcome Back! �A�[�x���g�^�C��(���W�I)";
						break;
					case 8517:
						a = "�Ď���";
						break;
					case 8519:
						a = "�Ď���";
						break;
					case 8520:
						a = "�Ő��뉀";
						break;
					case 8521:
						a = "���߂Ẳ~����";
						break;
					case 8522:
						a = "�^�ł��o��I";
						break;
					case 8524:
						a = "Tragedy";
						break;
					case 8528:
						a = "�͂��Ȋ�]�̐��";
						break;
					case 8530:
						a = "�A�H��";
						break;
					case 8532:
						a = "Roots of Scar";
						break;
					case 8534:
						a = "�z���痢�𑖂�";
						break;
					case 8536:
						a = "���˂���̉���";
						break;
					case 8539:
						a = "�s��";
						break;
					case 8541:
						if (b == L"b")
							a = "������グ�� -Eliot Ver.-";
						else
							a = "������グ�� -Eliot Ver.-";
						break;
					case 8542:
						a = "�s��";
						break;
					case 8543:
						a = "�s��";
						break;
					case 8544:
						a = "Little Rain";
						break;
					case 8545:
						a = "�É_";
						break;
					case 8546:
						a = "���A�苿����";
						break;
					case 8547:
						a = "���C�i������";
						break;
					case 8548:
						a = "���̓��̖�";
						break;
					case 8551:
						a = "�s��";
						break;
					case 8553:
						a = "Sensitive Talk";
						break;
					case 8554:
						a = "����";
						break;
					case 8555:
						a = "Feel at Home";
						break;
					case 8556:
						a = "���疜�̖���z����";
						break;
					case 8557:
						a = "�s��";
						break;
					case 8558:
						a = "�s��";
						break;
					case 8559:
						a = "�D����������";
						break;
					case 8560:
						a = "�ň��̍őP��";
						break;
					case 8562:
						a = "���̐^��";
						break;
					case 8563:
						a = "���ł����΂�";
						break;
					case 8564:
						a = "���̉�����͏���������ǁB";
						break;
					case 8566:
						a = "����ł��O��";
						break;
					case 8570:
						a = "�z���ЂƂ�";
						break;
					case 8571:
						a = "��N�v��";
						break;
					case 8572:
						a = "�s��";
						break;
					case 8573:
						a = "���߂Ă��̖�ɐ�����";
						break;
					case 8574:
						a = "Constraint";
						break;
					case 8575:
						a = "�߂����肵���X";
						break;
					case 8576:
						a = "�s��";
						break;
					case 8577:
						a = "���ꂼ��̊o��";
						break;
					case 8578:
						a = "�����̈ł̒���";
						break;
					case 8579:
						a = "�ς�鐢�E -�ł̒ꂩ��-";
						break;
					case 8600:
						a = "�s��";
						break;
					case 8601:
						a = "�Q�[�g�C��";
						break;
					case 8602:
						a = "�s��(��̋O��)";
						break;
					case 8603:
						a = "���_�͂������Ă��܂�";
						break;
					case 8604:
						a = "�s��(��̋O��)";
						break;
					case 8605:
						a = "�s��";
						break;
					case 8606:
						a = "�s��";
						break;
					case 8608:
						a = "�s��";
						break;
					case 8610:
						a = "�s��";
						break;
					case 8611:
						a = "�s��";
						break;
					case 8612:
						a = "�s��";
						break;
					case 8613:
						a = "�s��";
						break;
					case 8614:
						a = "�s��";
						break;
					case 8616:
						a = "�s��";
						break;
					case 8617:
						a = "�s��";
						break;
					case 8618:
						a = "�s��";
						break;
					case 8619:
						a = "�s��";
						break;
					case 8620:
						a = "�s��";
						break;
					case 8621:
						a = "�s��";
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
						a = "�����ڊo�߂�";
						break;
					case 8715:
						a = "�����ցB";
						break;
					case 8716:
						a = "�����ւ̋O�� -Instrumental Ver.-";
						break;
					case 8717:
						a = "Deep Carnival";
						break;
					case 8718:
						a = "�s��";
						break;
					case 8719:
						a = "Chain Chain Chain!";
						break;
					case 8720:
						a = "�����ւ̋O��";
						break;
					case 8721:
						a = "���̎�(��)";
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
						a = "�������x��";
						break;
					case 8803:
						a = "Brilliant Escape";
						break;
					case 8810:
						a = "�s��";
						break;
					case 8811:
						a = "�s��";
						break;
					case 8812:
						a = "�s��";
						break;
					case 8910:
						a = "�s��";
						break;
					case 8911:
						a = "�s��";
						break;
					case 8912:
						a = "�s��";
						break;
					case 8913:
						a = "�s��";
						break;
					case 8916:
						a = "�s��";
						break;
					case 8917:
						a = "�s��";
						break;
					case 8918:
						a = "�s��";
						break;
					case 8919:
						a = "�s��";
						break;
					case 8920:
						a = "�s��";
						break;
					case 8921:
						a = "�s��";
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
						if (cf1.IsDirectory() != 0) { //�t�H���_�H
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
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
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

	// TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����܂��B
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
			if (sss != _T("�v���C���X�g")) {
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
	// TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CPlayList::OnBnClickedCheck4()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	Save();
}

void CPlayList::OnBnClickedCheck1()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	Save();
}

void CPlayList::OnLvnBegindragList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNM = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
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
 	// �h���b�O�J�n
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
	// �h���b�O�I��
	ImageList_DragLeave(m_hWnd);
	ImageList_EndDrag();
	ImageList_Destroy(m_hDragImage);
	m_hDragImage = NULL;

	// �J�[�\���\��
	ShowCursor(TRUE);
}
void CPlayList::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	if(GetCapture()==this){
		OnDrag(point.x,point.y);
	}
	CDialog::OnMouseMove(nFlags, point);
}

void CPlayList::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	if(GetCapture()==this){
		OnEndDrag();
		// �L���v�`������
		ReleaseCapture();
		//���ۂ̈ړ��̂��߂̍��W���肾��
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
			//�]���f�[�^�����炩���ߍ���Ă���
			p = (playlistdata*)malloc(sizeof(playlistdata)*cnt);
			for(Lindexx=-1;;cnt2++){
				Lindexx=m_lc.GetNextItem(Lindexx,LVNI_ALL |LVNI_SELECTED);
				if(Lindexx==-1) break;
			}
			//�]������C���e�b�N�X�ԍ����l������
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
				if(hItem<Lindex){//�I�����ڂ����@�h���b�v�ʒu����
					int k=Lindex-hItem;
					m_lc.SetItemState(Lindex,m_lc.GetItemState(Lindex,LVIS_SELECTED)&~LVIS_SELECTED,LVIS_SELECTED);
					for(int kk=0;kk<k;kk++){
						OnXCHG(Lindex-kk,Lindex-kk-1);
					}
					m_lc.SetItemState(hItem  ,m_lc.GetItemState(hItem,LVIS_SELECTED)|LVIS_SELECTED,LVIS_SELECTED);
				}else{//�I�����ڂ���@�h���b�v�ʒu����
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
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
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
				 if(pc[lpDInfo->item.iItem].time==-1)s="�擾�s�\";
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
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
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
	// TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����܂��B
}

void CPlayList::OnPop32787()//�t�@�C�����ύX
{
	// TODO: �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
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
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
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
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
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
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
}


void CPlayList::OnBnClickedCheck7dshow()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
}
