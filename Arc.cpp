// Arc.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "ogg.h"
#include "Arc.h"


// CArc �_�C�A���O

IMPLEMENT_DYNAMIC(CArc, CDialog)

CArc::CArc(CWnd* pParent /*=NULL*/)
	: CDialog(CArc::IDD, pParent)
{

}

CArc::~CArc()
{
}

void CArc::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CArc, CDialog)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CArc ���b�Z�[�W �n���h��
extern CString fnn;

char tiarc[][128]={
"��OPEN YOUR EYES",
"02 �߂̎q��̎^����",
"03 �嗤���]",
"04 �����I",
"05 �\�����ʏI��",
"06 ���̊Ԃ̋x��",
"07 ����Ȃ����",
"08 ENCOUNTER BATTLE",
"09 �퓬��2",
"10 ����",
"11 �t�B�[���h��1",
"12 ������",
"13 �g�����N�H�[���[",
"14 �ٔ�",
"15 ���O�j��",
"16 �o���̓�",
"17 ��C����",
"18 �`���^�C�j",
"19 ��������",
"20 �����A���P���I",
"21 �ł̑����@�|�\���|",
"22 �����s�s�}���e���j",
"23 ���a����s�h�[��",
"24 ���������@",
"25 �}���I",
"26 �ӂ���Łc",
"27 �t�B�[���h��2",
"28 �����̒�",
"29 �`���A���X���F���X",
"30 �T���f�B�X�p",
"31 ���s�o�A��",
"32 �G���U�x�X�E�G���W��",

"33 �Ȃ������i�F",
"34 �_���W������1",
"35 �I�J���i",
"36 EVERLASTING NIGHTMARE",
"37 ���O�j���@another version",
"38 BURST INTO THE BATTLE",
"39 �t�B�[���h��3",
"40 �r�p�̉e",
"41 �������ꂽ��",
"42 �_�Ƃ̌���",
"43 �Ό�",
"44 �t�B�[���h��4",
"45 �v���Z���i�̃e�[�}",
"46 DESTRUCTION",
"47 �G�X�e�j���E�`���_��",
"48 �s�g",
"49 �Z�e�o�������n��",
"50 DESERTED TOWN",
"51 �F��",
"52 �ς��䂭���E",
"53 ���N�����T�k�J",
"54 ESPIONAGE",
"55 �G���n�C���v��",
"56 �~��",
"57 �퓬��4",
"58 �t�B�[���h��5",
"59 �Q���i����",

"60 ����",
"61 BREAKTHROUGH",
"62 �G�y�\",
"63 ����}�M�̋L��",
"64 �R���̎�",
"65 MBRACE",
"66 �퓬��5",
"67 FINAL ASSAULT",
"68 �t�B�[���h��5",
"69 ���Ă����ߋ�",
"70 FALL OF THE EMPIRE",
"71 �R���X�e�������E��",
"72 N.O.A.H.",
"73 EDEN",
"74 ���̑z���o",
"75 ������",
"76 ���肭�鋺��",
"77 CASTLE WALKENSWAARD",
"78 ��q���@�`�A�P�i�g���`",
"79 �_���W������2",
"80 �_���W������3",
"81 �G�s���[�O",
"82 Truth In Me",

"84 ����"
};


CString CArc::Gett(int a){
	CString s,ss;
	s=tiarc[a];
	ss=s.Left(2);ss.TrimRight();
	fnn=s.Mid(3);
	return ss;
}

/////////////////////////////////////////////////////////////////////////////
// CZWEIII ���b�Z�[�W �n���h��
void CArc::OnDblclkList1() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CString s;	s=tiarc[m_list.GetItemData(m_list.GetCurSel())];
	ret=s.Left(2); ret.TrimRight();
	ret2=m_list.GetCurSel();
#if UNICODE
	if(s.Left(1)=="��"){
		fnn=s.Mid(1);
#else
	if(s.Left(2)=="��"){
		fnn=s.Mid(2);
#endif
	}else{
		fnn=s.Mid(3);
	}
	EndDialog(1567);
}

BOOL CArc::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	int dx;
	for(int i=0;i<(83);i++)
	{
		CString s;
		s=tiarc[i];if(s.Left(2)=="��"){}else{s="ZW2_";s=tiarc[i];}
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


void CArc::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����܂��B
					   // �`�惁�b�Z�[�W�� CDialog::OnPaint() ���Ăяo���Ȃ��ł��������B
}
