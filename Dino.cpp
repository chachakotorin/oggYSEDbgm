// Dino.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "ogg.h"
#include "Dino.h"


// CDino �_�C�A���O

IMPLEMENT_DYNAMIC(CDino, CDialog)

CDino::CDino(CWnd* pParent /*=NULL*/)
	: CDialog(CDino::IDD, pParent)
{

}

CDino::~CDino()
{
}

void CDino::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CDino, CDialog)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
END_MESSAGE_MAP()


// CDino ���b�Z�[�W �n���h��
extern CString fnn;

char tidi[][128]={
"dinow_01 ����ꂵ���̂���",
"dinow_02 Mark My Words",
"dinow_03 ����̎^��",
"dinow_04 FRONT LINE",
"dinow_05 �˔j�I",
"dinow_06 A TEMPLE",
"dinow_07 GOD�I",
"dinow_08 �y�J",
"dinow_09 EXCITING SHOP",
"dinow_10 INTO THE CASTLE",
"dinow_11 �^���V�X�Ƃ̏o�",
"dinow_12 �킢�͔߂��݂̉ʂĂ�",
"dinow_13 �琂̎�",
"dinow_14 BURNING!",
"dinow_15 ����",
"dinow_16 �_�̌[��",
"dinow_17 �����̓�",
"dinow_18 ����������",
"dinow_19 ���̓�",
"dinow_20 �n���Վ�",
"dinow_21 �����̖��{",
"dinow_22 �_���E�X�̓�",
"dinow_23 ���Ȃ���������",
"dinow_24 �G��",
"dinow_25 ����Ȃ���",
"dinow_26 THE MASCLE MAN",
"dinow_27 �t�H���i",
"dinow_28 ����̓�",
"dinow_29 �R�_",
"dinow_30 DINOSAUR",
"dinow_31 ���ނ�",
"dinow_32 ���̖��",
"dinow_33 �I���S�[��",
"���I�[�v�j���O"
};

double di[34][2]={
	{22.0138095238095,181.765351473923},
	{9.08820861678005,86.2321315192744},
	{10.3009070294785,168.109569160998},
	{9.56086167800454,68.3846258503401},
	{8.93421768707483,156.790839002268},
	{10.2299546485261,178.878843537415},
	{33.8431065759637,144.95537414966},
	{0.0,0.0},
	{7.16244897959183,130.49537414966},
	{9.3097052154195,113.093537414966},
	{11.7062131519274,129.33},
	{7.65356009070295,83.9453741496598},
	{8.9562358276644,97.219433106576},
	{4.27621315192744,138.798526077098},
	{0.0,0.0},
	{4.63199546485261,108.084285714286},
	{21.455283446712,168.808344671202},
	{45.0247392290249,102.797800453515},
	{3.32027210884354,242.057142857143},
	{14.3692743764172,80.6851473922902},
	{15.9714965986395,71.0846031746031},
	{16.7838548752834,87.2922902494331},
	{25.8584126984127,151.348548752834},
	{0.0,0.0},
	{22.0648526077098,88.363514739229},
	{17.430589569161,120.630589569161},
	{22.9173469387755,136.020158730159},
	{6.70092970521542,129.01514739229},
	{18.1054195011338,51.105306122449},
	{21.3657596371882,113.737709750567},
	{13.3610657596372,206.219138321996},
	{82.3797732426304,161.312947845805},
	{0.0,0.0},
	{0.0,0.0}
};

CString CDino::Gett(int a){
	CString s,ss,sss;int aa;
	s=tidi[a];
	ss=s.Left(8);ss.TrimRight();
	sss=ss.Right(2);aa=_tstoi(sss)-1;
	loop1=(int)(di[aa][0]*44100.0);
	loop2=(int)(di[aa][1]*44100.0)-loop1;
	fnn=s.Mid(9);
	return ss;
}

/////////////////////////////////////////////////////////////////////////////
// CZWEIII ���b�Z�[�W �n���h��
void CDino::OnDblclkList1() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CString s,ss,sss;int aa;	s=tidi[m_list.GetItemData(m_list.GetCurSel())];
	ret=s.Left(8); ret.TrimRight();
	ret2=m_list.GetCurSel();ss=ret;
	sss=ss.Right(2);aa=_tstoi(sss)-1;
	loop1=(int)(di[aa][0]*44100.0);
	loop2=(int)(di[aa][1]*44100.0)-loop1;
#if UNICODE
	if(s.Left(1)=="��"){
		fnn=s.Mid(1);
#else
	if(s.Left(2)=="��"){
		fnn=s.Mid(2);
#endif
	}else{
		fnn=s.Mid(9);
	}
	EndDialog(1567);
}

BOOL CDino::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	int dx;
	for(int i=0;i<(34);i++)
	{
		CString s;
		s=tidi[i];if(s.Left(2)=="��"){}else{s="ZW2_";s=tidi[i];}
		dx= m_list.AddString(s);
		m_list.SetItemData(dx,i);	
	}

	m_list.SetCurSel(0);
	if(ret2!=0) 
//		if(ret>65) m_list.SetCurSel(ret);
//		else m_list.SetCurSel(ret-1);
		m_list.SetCurSel(ret2);
	m_list.SetFocus();
	return FALSE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}
