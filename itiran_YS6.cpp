// itiran_YS6.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "ogg.h"
#include "itiran_YS6.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Citiran_YS6 �_�C�A���O

extern CString fnn;

Citiran_YS6::Citiran_YS6(CWnd* pParent /*=NULL*/)
	: CDialog(Citiran_YS6::IDD, pParent)
{
	//{{AFX_DATA_INIT(Citiran_YS6)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_INIT
}


void Citiran_YS6::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Citiran_YS6)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Citiran_YS6, CDialog)
	//{{AFX_MSG_MAP(Citiran_YS6)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Citiran_YS6 ���b�Z�[�W �n���h��

char tiys6[][128]={
"01.�^�C�g��/���[�h",
"02.�I�[�v�j���O(���悠��)",
"03.�e����",
"04.���_�̏W��",
"05.�V���b�v",
"06.�N�A�e�����C",
"07.���{�X���",
"08.�C��Q��",
"09.�����[�W���̍`��",
"10.�J�i������",
"11.�O���i���@���X",
"12.�Y�p�̈��",
"13.�[���X�̐��n",
"14.�ߓ����E�n����",
"15.�P��",
"16.�苒��",
"17.�������R�́i�ʏ�j",
"18.�������R�́i�E�o�j",
"19.�A���}�̕���",
"20.�K�����@�����A��",
"21.�G�����X�g��",
"22.�i�s�V���e���̙�,������L",
"23.�i�s�j��<��P�i�K>�i���X�{�X�j",
"24.�i�s�j��<��Q�i�K>�i���X�{�X�j",
"25.�X�^�b�t���[��",
"26.���[�r�[1�i�Q���Ł`�������P���j(���悠��)",
"27.���[�r�[2�i�i�s�����j(���悠��)",
"28.���[�r�[3�i�i�s����j(���悠��)",
"29.���[�r�[4�i�G���f�B���O1�j(���悠��)",
"30.�Q�[���I�[�o�[",
"30.�Q�[���I�[�o�["
};

void Citiran_YS6::OnDblclkList1() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CString s,ss;	s=tiys6[m_list.GetItemData(m_list.GetCurSel())];
	ss=s.Left(2);ret=_tstoi(ss)-1;
	fnn=s.Mid(3);
	EndDialog(1567);
}

void Citiran_YS6::Gett(int a){
	CString s,ss;
	s=tiys6[a];
	ss=s.Left(6);ss.TrimRight();
	fnn=s.Mid(3);
}

BOOL Citiran_YS6::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	int dx;
	for(int i=0;i<(30);i++)
	{
		CString s;
		s=tiys6[i];if(s.Left(2)=="��"){}else{s="ZW2_";s=tiys6[i];}
		dx= m_list.AddString(s);
		m_list.SetItemData(dx,i);	
	}

	m_list.SetCurSel(0);
	if(ret2!=0) 
		m_list.SetCurSel(ret2);
	m_list.SetFocus();

	m_list.SetCurSel(0);
	if(ret!=0) m_list.SetCurSel(ret);

	m_list.SetFocus();
	return FALSE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}
