// itiran_YSO.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "ogg.h"
#include "itiran_YSO.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Citiran_YSO �_�C�A���O

extern CString fnn;

Citiran_YSO::Citiran_YSO(CWnd* pParent /*=NULL*/)
	: CDialog(Citiran_YSO::IDD, pParent)
{
	//{{AFX_DATA_INIT(Citiran_YSO)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_INIT
}


void Citiran_YSO::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Citiran_YSO)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Citiran_YSO, CDialog)
	//{{AFX_MSG_MAP(Citiran_YSO)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


char tiyso[][128]={
"001 �^�C�g��<THE GUIDANCE OF A WHITE TOWER>",
"002 �C�x���g0<BONDS WITH COMPANION>",
"003 �_�[���̓�24-25F<BEYOND THE BEGINNING>",
"004 �_�[���̓�01-05F<TOWER OF THE SHADOW OF DEATH>",
"005 �_�[���̓�06-09F<WATER PRISON>",
"006 �_�[���̓�10-13F<SCARLET TEMPEST>",
"007 �_�[���̓�14-17F<SILENT DESERT>",
"008 �_�[���̓�18-21F<SAMSARA AND PARAMNESIA>",
"009 �_�[���̓�22-24F<PRELUDE TO THE OMEN>",
"010 �_�[���̓��ŏ�K<THE LAST MOMENT OF THE DARK>(�g�[���̂�)",
"011 �{�X��1<TENSION>(�W�F�m�N���X)",
"012 ���h�̓�/���̊�<DREAMING>",
"013 ���̒ʘH <DEVIL'S WIND>",
"014 �{�X��2<SCARS OF THE DIVINE WING>(��׶���ް/Ƹ�èٶް/�����ި/�߸èӽ/�ݽ�װ��)",
"015 �{�X��3<OBORO>(�ާ�ޭص�/���̑�<��>�̈ꑰ)",
"016 �{�X��4<MY LORD, OUR BRAVE>(�U�o/���O���N�X���I�����K��)",
"017 �_���X��<OVER DRIVE>",
"018 �����_�[����<TERMINATION>(�g�[���̂�)",
"019 �C���g��(����p)<PROLOGUE -Ys ORIGIN->",
"020 ���S(����p)",
"021 ���_�̎�<RODA>",
"022 <��>�̈ꑰ�̃e�[�}<THE ROOT OF DARKNESS>",
"023 �C�x���g1<CONFRONTATION>",
"024 �C�x���g2<THE PAIN OF SEPARATION>",
"025 �C�x���g3<MEMORY OF SALMON>",
"026 �C�x���g4<FEENA>",
"027 ��̃n�[���j�J1",
"028 ��̃n�[���j�J2",
"029 ��̃n�[���j�J2'���[Ver",
"030 �C�x���g5<FAIR SKIES>",
"031 �C�x���g6<DETERMINATION>",
"032 �I�[�v�j���O(����p)<GENESIS BEYOND THE BEGINNING OPENING VERSION>",
"033 �G���f�B���O1(����p)<TO THE NEXT GENERATION>���j�J�E���[�S",
"034 �G���f�B���O2(����p)<A NEW LEGENDARY OPENING>�g�[��",
"035 �C�x���g7<BELIEVING>",
"036 �Q�[���I�[�o�[<SO MUCH FOR TODAY>",
"037 �C���X�g���N�V����1<MAGNIFICENCE>",
"038 �C���X�g���N�V����2<MOVEMENT OF WICKED ENERGY>",
"039 �C���X�g���N�V����3<DISAPPEARANCE OF THREAT>",
"040 �_�[���̓��ŏ�K�C�x���g<-Bonus track- GENESIS BEYOND THE BEGINNING>(�g�[���̂�)",
"��FALCOM���S����",
"���v�����[�O����",
"���I�[�v�j���O����",
"���C���X�g���N�V����1",
"���C���X�g���N�V����2",
"���C���X�g���N�V����3",
"���G���f�B���O����1",
"���G���f�B���O����2"
};

CString Citiran_YSO::Gett(int a){
	CString s,ss;
	s=tiyso[a];
	ss=s.Left(3);
	fnn=s.Mid(4);
	return ss;
}

/////////////////////////////////////////////////////////////////////////////
// Citiran_YSO ���b�Z�[�W �n���h��
void Citiran_YSO::OnDblclkList1() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CString s;	s=tiyso[m_list.GetItemData(m_list.GetCurSel())];
	ret=_tstoi(s.Left(3));
	ret2=m_list.GetCurSel();
	if(ret2>39)
		ret=ret2;
#if UNICODE
	if(s.Left(1)=="��"){
		fnn=s.Mid(1);
#else
	if(s.Left(2)=="��"){
		fnn=s.Mid(2);
#endif
	}else{
		fnn=s.Mid(4);
	}
	EndDialog(1567);
}

BOOL Citiran_YSO::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	int dx;
	for(int i=0;i<48;i++)
	{
		CString s;
		s=tiyso[i];if(s.Left(2)=="��"){}else{s="YSO_";s+=tiyso[i];}
		dx= m_list.AddString(s);
		m_list.SetItemData(dx,i);	
	}

	m_list.SetCurSel(0);
	if(ret!=0) 
//		if(ret>39) m_list.SetCurSel(ret);
//		else m_list.SetCurSel(ret-1);
		m_list.SetCurSel(ret);
	m_list.SetFocus();
	return FALSE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}
