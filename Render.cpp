// Render.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "ogg.h"
#include "Render.h"
#include "Graph.h"
#include "dsound.h"
#include "ZeroFol.h"
#include "oggDlg.h"
#include "CImageBase.h"

extern IGraphBuilder *pGraphBuilder;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern save savedata;
CImageBase* renderbase;
/////////////////////////////////////////////////////////////////////////////
// CRender �_�C�A���O

IMPLEMENT_DYNAMIC(CRender, CDialogEx)
CRender::CRender(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRender::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRender)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
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
	DDX_Control(pDX, IDC_STATIC12, m_wup);
	DDX_Control(pDX, IDC_SLIDER6, w_wups);
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
	ON_WM_CTLCOLOR()
	ON_WM_CREATE()
	ON_WM_MOVING()
	ON_BN_CLICKED(IDCANCEL, &CRender::OnBnClickedCancel)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRender ���b�Z�[�W �n���h��
CComboBox *sl;
GUID slg[200];
int slgc;
CString sls[200];
DWORD samp[] = { 11025, 12000, 22050, 24000, 44100, 48000, 96000, 192000, 384000, 768000, 1536000, 3072000 };
BOOL CRender::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	OSVERSIONINFO in;ZeroMemory(&in,sizeof(in));in.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);GetVersionEx(&in);
	if(in.dwMajorVersion<=5)
		m_1.AddString(_T("�f�t�H���g"));
	else	
		m_1.AddString(_T("�f�t�H���g(����/EVR)"));
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
	m_tooltip.AddTool(GetDlgItem(IDOK),_T("�ۑ����ĕ��܂�"));
	m_tooltip.AddTool(GetDlgItem(IDCANCEL),_T("�ۑ������ɕ��܂�"));
	m_tooltip.AddTool(GetDlgItem(IDCANCEL2),_T("�Đ����̎g�pDirectShow�t�B���^��\�����܂��B"));
	m_tooltip.AddTool(GetDlgItem(IDCANCEL3),_T("kpi�ꗗ��\�����܂��B"));
	m_tooltip.AddTool(GetDlgItem(IDCANCEL4), _T("�e��t�@�C�����ȈՃv���C���Ɋ֘A�Â����܂��B\n���܂������Ȃ��ꍇ������܂��B"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK1), _T("Windows Vista/7�ȍ~�ŗL���ł��B\nIndeo��p��������̏ꍇOFF�ɂ��Ă��������B\n����ȊO��ON�ł����ł��B"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK2), _T("Windows Vista/7�ȍ~�ŗL���ł��B\n�f�X�N�g�b�v�R���|�W�V����(Aero)���g�p���邩�ǂ�����I�����܂��B\n�g�p���Ȃ��ɂ����EVR����Ȃ��Ă������ʂ͂��ꂢ�ɂȂ�܂��B"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK3), _T("Windows Vista/7�ȍ~�ŗL���ł��B\nAero Grass���g�p���邩�ǂ������߂܂��B\n�����_�ł͎g���ƕ����܂œ��߂����Ⴄ�̂Ō��Â炢�ł��B"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK27), _T("�����ffdshow���g�����ǂ����I�����܂��B\nWindows7�̏ꍇ�A�f�t�H���g��Divx�Ȃǂ��Đ��ł���̂ł�������g�������l��OFF�ɂ��Ă��������B"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK30),_T("vob��dat�t�@�C����Haali��ʂ��Ȃ��悤�ɍ���Ă��܂����A\nvob�ɕ�������������Ƃ��ɂ̓`�F�b�N�����ĉ������B"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK31),_T("�����Haali���g���܂���B\n���悪�d���Ǝv�������╡���������������̓`�F�b�N������ƌy���Ȃ�܂��B"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK32),_T("kpi SPC/NEZplug++����SPC�̉��ʂ�2�{�ɂ��܂��B"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK33),_T("kpi SPC/NEZplug++����SPC�̉��ʂ�3�{�ɂ��܂��B"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK34),_T("kpi SPC/NEZplug++����SPC�̉��ʂ�4�{�ɂ��܂��B"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK35),_T("kpi SPC/NEZplug++����SPC�̉��ʂ𓙔{�ɂ��܂��B"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK36),_T("kpi SPC/NEZplug++����SPC�̉��ʂ�5�{�ɂ��܂��B"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK40),_T("mp3�̉��ʂ𓙔{�ɂ��܂��B"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK37),_T("mp3�̉��ʂ�1.5�{�ɂ��܂��B"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK38),_T("mp3�̉��ʂ�2�{�ɂ��܂��B"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK39),_T("mp3�̉��ʂ�2.5�{�ɂ��܂��B"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK41),_T("mp3�̉��ʂ�3�{�ɂ��܂��B"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK45),_T("kpi�̉��ʂ𓙔{�ɂ��܂��B"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK42),_T("kpi�̉��ʂ�2�{�ɂ��܂��B"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK43),_T("kpi�̉��ʂ�3�{�ɂ��܂��B"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK44),_T("kpi�̉��ʂ�4�{�ɂ��܂��B"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK46),_T("kpi�̉��ʂ�5�{�ɂ��܂��B"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK47),_T("mp3�̃f�R�[�_���I���W�i���̃f�R�[�_���g�킸�ɁA�Ǝ��Ŏg�����f�R�[�_���g���B\n�G���[�Ȃǂŉ��t�ł��Ȃ��Ƃ��Ƀ`�F�b�N����ĉ������B\n�܂��Ǝ��Ő���ɂȂ�Ȃ����͂͂����ĉ������B"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK48),_T("���������̂��铮����Đ����鎞�ɁA�Đ��O��\n�����X�g���[���̑I����ʂ�\�����܂��B\n�ʏ�X�g���[��1�����C���Ƃ��Ďg���A�X�g���[��2�ȍ~�̓R�����^����p�ꉹ���ȂǂɎg���Ă��܂��B"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK49), _T("�Ή����Ă���kpi��24bit(�n�C���])�ōĐ����܂��B\n�ʏ��16bit�ł����A�܂�ɑΉ����Ă�����̂�����܂��B\n������ɂ��Ă͍l������Ă��Ȃ����߁Aspc�Ȃǔ{�����グ�Ȃ��Ƃ����Ȃ����̂͋C�����ĉ������B"));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK50), _T("m4a������G���W���ŉ��t���܂��B"));
	m_tooltip.AddTool(GetDlgItem(IDC_SLIDER3), _T("���t�̃o�b�t�@�����ł̊��荞�ݎ��Ԃ�ݒ肵�܂��B\n���Ȃ�����Ɖ���т���\��������܂��B"));
	m_tooltip.AddTool(GetDlgItem(IDC_SLIDER4), _T("�`��̊��o���Ԃ�ݒ肵�܂��B\nCPU�g�p�������Ƃ��ɏグ�܂��B�B"));
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
	m_ms.SetRange(30, 80);
	if (savedata.ms < 30) savedata.ms = 30;
	m_ms.SetPos(savedata.ms);
	if (savedata.ms > 80) savedata.ms = 80;
	m_hyouji2.SetRange(1, 60);
	m_hyouji2.SetPos(savedata.ms2);
	CString s; s.Format(L"%dms", savedata.ms);
	m_ms2.SetWindowText(s);
	SetTimer(11, 100, NULL);
	w_wups.SetRange(100, 1000);
	w_wups.SetPos(savedata.wup);

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
	// { 11025, 12000, 22050, 24000, 44100, 48000, 96000, 192000, 384000, 768000, 1536000, 3072000 };
	m_Hz.AddString(L"11025");
	m_Hz.AddString(L"12000");
	m_Hz.AddString(L"22050");
	m_Hz.AddString(L"24000");
	m_Hz.AddString(L"44100");
	m_Hz.AddString(L"48000");
	m_Hz.AddString(L"96000");
	m_Hz.AddString(L"192000");
	m_Hz.AddString(L"384000");
	m_Hz.AddString(L"768000");
	m_Hz.AddString(L"1536000");
	m_Hz.AddString(L"3072000 ");
	for (int l = 0; l < 12; l++) {
		if (savedata.samples == samp[l]) {
			m_Hz.SetCurSel(l);
			break;
		}
	}

	renderbase = new CImageBase;
	renderbase->Create(NULL);
	renderbase->oya = this;
	CRect r;
	GetWindowRect(&r);
	renderbase->MoveWindow(&r);
	::SetWindowPos(renderbase->m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	::SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
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
	// TODO: ���̈ʒu�ɂ��̑��̌��ؗp�̃R�[�h��ǉ����Ă�������
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
	delete renderbase;
	CDialog::OnOK();
}

INT_PTR CRender::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B

	return CDialog::OnToolHitTest(point, pTI);
}

BOOL CRender::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
		m_tooltip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

void CRender::OnBnClickedCancel2()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	CGraph *a = new CGraph(CWnd::FromHandle(GetSafeHwnd()));
	::SetWindowPos(m_hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	if (renderbase)::SetWindowPos(renderbase->m_hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	if(pGraphBuilder)
		a->DoModal();
	delete a;
}

void CRender::Onspc2x()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	m_spc2x.SetCheck(TRUE);
	m_spc4x.SetCheck(FALSE);
	m_spc8x.SetCheck(FALSE);
	m_spc16x.SetCheck(FALSE);
	m_spc1x.SetCheck(FALSE);
	savedata.spc=2;
}

void CRender::Onspc4x()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	m_spc2x.SetCheck(FALSE);
	m_spc4x.SetCheck(TRUE);
	m_spc8x.SetCheck(FALSE);
	m_spc16x.SetCheck(FALSE);
	m_spc1x.SetCheck(FALSE);
	savedata.spc=4;
}

void CRender::Onspc8x()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	m_spc2x.SetCheck(FALSE);
	m_spc4x.SetCheck(FALSE);
	m_spc8x.SetCheck(TRUE);
	m_spc16x.SetCheck(FALSE);
	m_spc1x.SetCheck(FALSE);
	savedata.spc=8;
}

void CRender::Onspc1x()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	m_spc2x.SetCheck(FALSE);
	m_spc4x.SetCheck(FALSE);
	m_spc8x.SetCheck(FALSE);
	m_spc16x.SetCheck(FALSE);
	m_spc1x.SetCheck(TRUE);
	savedata.spc=1;
}

void CRender::Onspc16x()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	m_spc2x.SetCheck(FALSE);
	m_spc4x.SetCheck(FALSE);
	m_spc8x.SetCheck(FALSE);
	m_spc16x.SetCheck(TRUE);
	m_spc1x.SetCheck(FALSE);
	savedata.spc=16;
}

void CRender::Onmp31()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	m_mp31.SetCheck(TRUE);
	m_mp315.SetCheck(FALSE);
	m_mp32.SetCheck(FALSE);
	m_mp325.SetCheck(FALSE);
	m_mp33.SetCheck(FALSE);
	savedata.mp3=1;
}

void CRender::Onmp315()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	m_mp31.SetCheck(FALSE);
	m_mp315.SetCheck(TRUE);
	m_mp32.SetCheck(FALSE);
	m_mp325.SetCheck(FALSE);
	m_mp33.SetCheck(FALSE);
	savedata.mp3=2;
}

void CRender::Onmp32()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	m_mp31.SetCheck(FALSE);
	m_mp315.SetCheck(FALSE);
	m_mp32.SetCheck(TRUE);
	m_mp325.SetCheck(FALSE);
	m_mp33.SetCheck(FALSE);
	savedata.mp3=3;
}

void CRender::Onmp325()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	m_mp31.SetCheck(FALSE);
	m_mp315.SetCheck(FALSE);
	m_mp32.SetCheck(FALSE);
	m_mp325.SetCheck(TRUE);
	m_mp33.SetCheck(FALSE);
	savedata.mp3=4;
}

void CRender::Onmp33()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	m_mp31.SetCheck(FALSE);
	m_mp315.SetCheck(FALSE);
	m_mp32.SetCheck(FALSE);
	m_mp325.SetCheck(FALSE);
	m_mp33.SetCheck(TRUE);
	savedata.mp3=5;
}

void CRender::Onkpi10()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	m_kpi10.SetCheck(TRUE);
	m_kpi15.SetCheck(FALSE);
	m_kpi20.SetCheck(FALSE);
	m_kpi25.SetCheck(FALSE);
	m_kpi30.SetCheck(FALSE);
	savedata.kpivol=1;
}

void CRender::Onkpi15()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	m_kpi10.SetCheck(FALSE);
	m_kpi15.SetCheck(TRUE);
	m_kpi20.SetCheck(FALSE);
	m_kpi25.SetCheck(FALSE);
	m_kpi30.SetCheck(FALSE);
	savedata.kpivol=2;
}

void CRender::Onkpi20()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	m_kpi10.SetCheck(FALSE);
	m_kpi15.SetCheck(FALSE);
	m_kpi20.SetCheck(TRUE);
	m_kpi25.SetCheck(FALSE);
	m_kpi30.SetCheck(FALSE);
	savedata.kpivol=3;
}

void CRender::Onkpi25()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	m_kpi10.SetCheck(FALSE);
	m_kpi15.SetCheck(FALSE);
	m_kpi20.SetCheck(FALSE);
	m_kpi25.SetCheck(TRUE);
	m_kpi30.SetCheck(FALSE);
	savedata.kpivol=4;
}

void CRender::Onkpi30()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	m_kpi10.SetCheck(FALSE);
	m_kpi15.SetCheck(FALSE);
	m_kpi20.SetCheck(FALSE);
	m_kpi25.SetCheck(FALSE);
	m_kpi30.SetCheck(TRUE);
	savedata.kpivol=5;
}

void CRender::OnBnClicked24bit()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	savedata.bit24 = m_24.GetCheck();
}

void CRender::OnBnClickedCheck50()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	savedata.m4a = m_m4a.GetCheck();
}



#include "Kpilist.h"
void CRender::Onkpi()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	CKpilist k;
//	::SetWindowPos(m_hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	if (renderbase)::SetWindowPos(renderbase->m_hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	k.status = 0;
	k.DoModal();
	if (renderbase)::SetWindowPos(renderbase->m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	::SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	//delete k;
}

extern HFONT	hFont;
#include "afxdlgs.h"
void CRender::OnFontMain()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
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
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
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
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
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
	delete renderbase;
	CDialog::OnOK();
}




BOOL CRender::MySetFileType(LPCTSTR lpExt, LPCTSTR lpDocName, LPCTSTR lpDocType, LPCTSTR lpPath, LPCTSTR lpPath1)
{
	CRegKey reg;

	// lpExt��lpDocName�Ɋ֘A�t����
	if (reg.SetValue(HKEY_CLASSES_ROOT, lpExt, lpDocName) != ERROR_SUCCESS)
		return FALSE;
	// lpDocName�쐬
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

	// �֘A�t�����ύX���ꂽ�����V�X�e���ɒʒm
	::SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL);
	return TRUE;
}

extern TCHAR karento2[1024];

void CRender::OnBnClickedCancel4()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	CString s,ss;
	s = "\"";
	s += karento2;
	s += "oggYSEDbgm_uni.exe\" \"%1\"";
	ss = karento2;
	ss += "oggYSEDbgm_uni.exe";
	MySetFileType(_T(".mp3"), _T("oggYSEDbgm_uni.exe.mp3"), _T("�ȈՃv���C���ŊJ��"), s, ss);
	MySetFileType(_T(".mp2"), _T("oggYSEDbgm_uni.exe.mp2"), _T("�ȈՃv���C���ŊJ��"), s, ss);
	MySetFileType(_T(".mp1"), _T("oggYSEDbgm_uni.exe.mp1"), _T("�ȈՃv���C���ŊJ��"), s, ss);
	MySetFileType(_T(".rmp"), _T("oggYSEDbgm_uni.exe.rmp"), _T("�ȈՃv���C���ŊJ��"), s, ss);
	MySetFileType(_T(".flac"), _T("oggYSEDbgm_uni.exe.flac"), _T("�ȈՃv���C���ŊJ��"), s, ss);
	MySetFileType(_T(".m4a"), _T("oggYSEDbgm_uni.exe.m4a"), _T("�ȈՃv���C���ŊJ��"), s, ss);
	MySetFileType(_T(".aac"), _T("oggYSEDbgm_uni.exe.aac"), _T("�ȈՃv���C���ŊJ��"), s, ss);
	MySetFileType(_T(".avi"), _T("oggYSEDbgm_uni.exe.avi"), _T("�ȈՃv���C���ŊJ��"), s, ss);
	MySetFileType(_T(".mp4"), _T("oggYSEDbgm_uni.exe.mp4"), _T("�ȈՃv���C���ŊJ��"), s, ss);
	MySetFileType(_T(".mkv"), _T("oggYSEDbgm_uni.exe.mkv"), _T("�ȈՃv���C���ŊJ��"), s, ss);
	MySetFileType(_T(".wmv"), _T("oggYSEDbgm_uni.exe.wmv"), _T("�ȈՃv���C���ŊJ��"), s, ss);
	MySetFileType(_T(".mpg"), _T("oggYSEDbgm_uni.exe.mpg"), _T("�ȈՃv���C���ŊJ��"), s, ss);
	// �֘A�t�����ύX���ꂽ�����V�X�e���ɒʒm
	::SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL);
	MessageBox(_T("�ꉞ�֘A�Â��𑖂点�Ă݂܂����B\nmp1,2,3,rmp,flac,m4a,aac,avi,mp4,mkv,wmv,mpg�Ɋ֘A�����܂����B"));
	// �֘A�t�����ύX���ꂽ�����V�X�e���ɒʒm
	::SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL);
}


void CRender::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	savedata.ms = m_ms.GetPos();
	CString s; s.Format(L"%dms", savedata.ms);
	m_ms2.SetWindowText(s);
	savedata.ms2 = m_hyouji2.GetPos();
	s.Format(L"%dms", savedata.ms2*16);
	m_hyouji3.SetWindowText(s);
	savedata.wup = w_wups.GetPos()/ 100.0;
	s.Format(L"%1.2lf�{",savedata.wup);
	m_wup.SetWindowText(s);
	CDialog::OnTimer(nIDEvent);
}

extern int wavbit, wavch, wavsam, wavbit2, fade1;
#include <MMSystem.h>
#include "dsound.h"
#include <mmdeviceapi.h>
#include <audiopolicy.h>
#include "libmad\decoder.h"
#include "mp3info.h"
#include "mp3.h"
extern void DoEvent();
extern COggDlg *og;
extern int sek;
extern int			logtbl[100 + 1];
extern LPDIRECTSOUND8 m_ds;
extern LPDIRECTSOUNDBUFFER m_dsb1;
extern LPDIRECTSOUNDBUFFER8 m_dsb;
extern CString tagfile,fnn;
void CRender::OnCbnSelchangeCombo2()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	memcpy(&savedata.soundguid, &slg[m_soundlist.GetCurSel()], sizeof(GUID));
	if (m_soundlist.GetCurSel() == 0) {
		savedata.soundguid = { 0,0,0,0 };
	}
	savedata.soundcur= m_soundlist.GetCurSel();
	og->ReleaseDXSound();
	og->init(og->m_hWnd, wavbit);
	sek = 1;
	WAVEFORMATEX wfx1;
	if (wavsam<0)
		wfx1.wFormatTag = WAVE_FORMAT_IEEE_FLOAT;
	else
		wfx1.wFormatTag = WAVE_FORMAT_PCM;
	wfx1.nChannels = wavch;
	wfx1.nSamplesPerSec = wavbit;
	wfx1.wBitsPerSample = abs(wavsam);
	wfx1.nBlockAlign = wfx1.nChannels * wfx1.wBitsPerSample / 8;
	wfx1.nAvgBytesPerSec = wfx1.nSamplesPerSec * wfx1.nBlockAlign;
	wfx1.cbSize = 0;

	static const GUID GUID_SUBTYPE_PCM = { 0x00000001, 0x0000, 0x0010,{ 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71 } };

	DWORD targetSpeakers = 0;
	switch (wavch) {
	case 1:
		targetSpeakers |= SPEAKER_FRONT_CENTER;
		break;
	case 2:
		targetSpeakers |=
			SPEAKER_FRONT_LEFT
			| SPEAKER_FRONT_RIGHT;
		break;
	case 3:
		targetSpeakers |=
			SPEAKER_FRONT_LEFT
			| SPEAKER_FRONT_RIGHT
			| SPEAKER_FRONT_CENTER
			;
	case 4:
		targetSpeakers |=
			SPEAKER_FRONT_LEFT
			| SPEAKER_FRONT_RIGHT
			| SPEAKER_FRONT_CENTER
			| SPEAKER_BACK_CENTER
			;
	case 5:
		targetSpeakers |=
			SPEAKER_FRONT_LEFT
			| SPEAKER_FRONT_RIGHT
			| SPEAKER_FRONT_CENTER
			| SPEAKER_BACK_LEFT
			| SPEAKER_BACK_RIGHT
			;
	case 6:
		targetSpeakers |=
			SPEAKER_FRONT_LEFT
			| SPEAKER_FRONT_RIGHT
			| SPEAKER_FRONT_CENTER
			| SPEAKER_LOW_FREQUENCY
			| SPEAKER_BACK_LEFT
			| SPEAKER_BACK_RIGHT
			;
	}
	int nChannels = __popcnt(targetSpeakers);
	WAVEFORMATEXTENSIBLE wfx = {};
	wfx.Format.wFormatTag = WAVE_FORMAT_EXTENSIBLE;
	wfx.Format.nChannels = nChannels;
	wfx.Format.nSamplesPerSec = wavbit;
	wfx.Format.wBitsPerSample = abs(wavsam);
	wfx.Format.nBlockAlign = (WORD)(wfx.Format.wBitsPerSample / 8 * wfx.Format.nChannels);
	wfx.Format.nAvgBytesPerSec = (DWORD)(wfx.Format.nSamplesPerSec * wfx.Format.nBlockAlign);
	wfx.Format.cbSize = sizeof(WAVEFORMATEXTENSIBLE) - sizeof(WAVEFORMATEX);
	wfx.dwChannelMask = targetSpeakers;
	if (wavsam < 0)
		wfx.SubFormat = KSDATAFORMAT_SUBTYPE_IEEE_FLOAT;
	else
		wfx.SubFormat = GUID_SUBTYPE_PCM;
	wavsam = abs(wavsam);
	wavbit2 = wavbit;
	int i, iii = 0;
	double ik = 32.0;
	double il = 45.71712838;
	for (i = 0; i <= 88; i++, iii++) { // �ቹ��p
		logtbl[i] = (int)(il * pow(2.0, (double)(iii) / ik));// *(double)BUFSZH1 / (double)192000 / 4.0 + 1.0);
		if (i < 20) {
			ik -= 0.12 / ((double)wavbit / 44100.0);
		}
		else {
			ik -= 0.14 / ((double)wavbit / 44100.0);
		}
		if (i != 0) {
			if (iii>240) {
				break;
			}
			if (logtbl[i] <= logtbl[i - 1]) {
				i--; continue;
			}
		}
		//if( logtbl[i] > BUFSZH1 -1 ) logtbl[i] = BUFSZH1 -1;
	}


	//    mmRes = waveOutOpen(&hwo,WAVE_MAPPER,&wfx1,(DWORD)(LPVOID)0,(DWORD)NULL,CALLBACK_NULL);

	fade1 = 0;
	//-------------------------------------------------------------------
	//if (pAudioClient == NULL) {
	DSBUFFERDESC dsbd;
	ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
	dsbd.dwSize = sizeof(DSBUFFERDESC);
	dsbd.dwFlags = DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_LOCSOFTWARE | DSBCAPS_GLOBALFOCUS | DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_CTRLVOLUME;// | DSBCAPS_CTRL3D;
	dsbd.dwBufferBytes = OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM;
	if (wavch > 2)
		dsbd.lpwfxFormat = (LPWAVEFORMATEX)&wfx;
	else
		dsbd.lpwfxFormat = &wfx1;
	//dsbd.guid3DAlgorithm = DS3DALG_HRTF_LIGHT;
	HRESULT r;
	r = m_ds->CreateSoundBuffer(&dsbd, &m_dsb1, NULL);
	if (m_dsb1 == NULL) {
		CString s; s.Format(L"%d", savedata.samples);
		MessageBox(s + L"Hz�̃T���v�����O���[�g�ɃT�E���h�J�[�h���Ή����Ă��܂���", _T("ogg/wav�ȈՃv���C��"));
		return;
	}
	for (i = 0; i < 10; i++) {
		r = m_dsb1->QueryInterface(IID_IDirectSoundBuffer8, (void**)&m_dsb);

		if (m_dsb == NULL) { DoEvent(); Sleep(100); continue; }
		else break;
	}
	if (m_dsb == NULL) {
		AfxMessageBox(_T("DirectSound���J���܂���ł����B"));
		if (r == DSERR_ALLOCATED) {
			AfxMessageBox(_T("�D�惌�x���Ȃǂ̃��\�[�X�����̌Ăяo���ɂ���Ċ��Ɏg�p���ł��邽�߁A�v���͎��s�����B"));
		}
		else if (r == DSERR_CONTROLUNAVAIL) {
			AfxMessageBox(_T("�Ăяo�������v������o�b�t�@ �R���g���[�� (�{�����[���A�p���Ȃ�) �͗��p�ł��Ȃ��B"));
		}
		else if (r == DSERR_BADFORMAT) {
			AfxMessageBox(_T("�w�肵���E�F�[�u �t�H�[�}�b�g�̓T�|�[�g����Ă��Ȃ��B"));
		}
		else if (r == DSERR_INVALIDPARAM) {
			AfxMessageBox(_T("�����ȃp�����[�^���֐��ɓn���ꂽ�B"));
		}
		else if (r == DSERR_NOAGGREGATION) {
			AfxMessageBox(_T("���̃I�u�W�F�N�g�� COM �W�������T�|�[�g���Ȃ��B"));
		}
		else if (r == DSERR_OUTOFMEMORY) {
			AfxMessageBox(_T("DirectSound �T�u�V�X�e���́A�Ăяo�����̗v�����������邽�߂̏\���ȃ����������蓖�Ă��Ȃ������B"));
		}
		else if (r == DSERR_UNINITIALIZED) {
			AfxMessageBox(_T("���̃��\�b�h���Ăяo���O�� IDirectSound::Initialize ���\�b�h���Ăяo���Ȃ��������A�Ăяo�����������Ȃ������B"));
		}
		else if (r == DSERR_UNSUPPORTED) {
			AfxMessageBox(_T("�Ăяo�����֐��͂��̎��_�ł̓T�|�[�g����Ă��Ȃ��B"));
		}
		else {}

		tagfile = fnn;
		og->m_saisai.EnableWindow(TRUE);
		return;
	}
	m_dsb->Play(0, 0, DSBPLAY_LOOPING);
}


void CRender::OnBnClickedButton1()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	CZeroFol z;
	z.DoModal();
}


void CRender::OnCbnSelchangeCombo3()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	savedata.samples = samp[m_Hz.GetCurSel()];
}


HBRUSH CRender::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: ������ DC �̑�����ύX���Ă��������B
	if (savedata.aero == 1) {
		if (nCtlColor == CTLCOLOR_DLG)
		{
			return m_brDlg;
		}
		if (nCtlColor == CTLCOLOR_STATIC)
		{
			SetBkMode(pDC->m_hDC, TRANSPARENT);
			return m_brDlg;
		}
	}
	// TODO: ����l���g�p�������Ȃ��ꍇ�͕ʂ̃u���V��Ԃ��܂��B
	return hbr;
}


int CRender::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: �����ɓ���ȍ쐬�R�[�h��ǉ����Ă��������B
	ModifyStyleEx(0, WS_EX_LAYERED);

	// ���C���[�h�E�B���h�E�̕s�����x�Ɠ����̃J���[�L�[
	SetLayeredWindowAttributes(RGB(255, 0, 0), 0, LWA_COLORKEY);

	// �ԐF�̃u���V���쐬����D
	m_brDlg.CreateSolidBrush(RGB(255, 0, 0));
	return 0;
}


void CRender::OnMoving(UINT fwSide, LPRECT pRect)
{
	CDialogEx::OnMoving(fwSide, pRect);
	CRect r;
	GetWindowRect(&r);
	renderbase->MoveWindow(&r);
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����܂��B
}

int CRender::Create(CWnd* pWnd)
{
	m_pParent = NULL;
	BOOL bret = CDialog::Create(CPlayList::IDD, this);
	if (savedata.aero == 1) {
		ModifyStyleEx(0, WS_EX_LAYERED);

		// ���C���[�h�E�B���h�E�̕s�����x�Ɠ����̃J���[�L�[
		SetLayeredWindowAttributes(RGB(255, 0, 0), 0, LWA_COLORKEY);

		// �ԐF�̃u���V���쐬����D
		m_brDlg.CreateSolidBrush(RGB(255, 0, 0));
	}
	if (bret == TRUE)
		ShowWindow(SW_SHOW);
	return bret;
}

void CRender::OnBnClickedCancel()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	delete renderbase;
	CDialogEx::OnCancel();
}
