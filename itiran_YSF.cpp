// itiran_YSF.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "ogg.h"
#include "itiran_YSF.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Citiran_YSF �_�C�A���O

extern CString fnn;

Citiran_YSF::Citiran_YSF(CWnd* pParent /*=NULL*/)
	: CDialog(Citiran_YSF::IDD, pParent)
{
	//{{AFX_DATA_INIT(Citiran_YSF)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_INIT
}


void Citiran_YSF::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Citiran_YSF)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Citiran_YSF, CDialog)
	//{{AFX_MSG_MAP(Citiran_YSF)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Citiran_YSF ���b�Z�[�W �n���h��

char tiys3[][128]={
"01.Dancing on the road(�s��)",
"02.�\�� ���X�e�B�N�X��(���j���[)",
"03.�f�Ղ̊X���h�����g(���h�����g�̒�)",
"04.�Â��ȍ�(���V�Ȃǂ̉�)",
"05.Welcome!!(���X)",
"06.�`���ւ̏���(�}�b�v)",
"07.�������������N(�t�B�[���h�}�b�v)",
"08.Be careful(�e�B�O���[�̍̐Ώ�)",
"09.�����̖��b(�{�X��)",
"10.�C���o�[���Y�̈��(�C���o�[���Y�̈��)",
"11.�ܔM�̎���(�n��n��)",
"12.�Í����(�e�B�O���[�̍̐Ώꉜ)",
"13.���_�̓d��(�{�X��)",
"14.�����Ƃ��̖�(�Q�[���I�[�o�[)",
"15.���i�Ȃ铬�u(�G���_�[���R��)",
"16.���D�̃g���C���C�g(���h�����g�̒� ��@��)",
"17.�o���X�^�C����(�o���X�^�C�����)",
"18.�����̋F��(�o���X�^�C���鐹��)",
"19.����̌�(�G���f�B���O��)",
"20.���̕���(�o���X�^�C���鎞�v��)",
"21.�j�łւ̌ۓ�(�W�F�m�X��)",
"22.�^���̓�(�W�F�m�X���[��)",
"23.���������I�I(�j�R���X��)",
"24.�ŋ��̓G(�K���o������)",
"25.�������̒�(�N���A��̃��h�����g�̒�)",
"26.Wanderers from Ys(�G���f�B���O(����))",
"27.Dear My Brother(�G���i�A�`�F�X�^�[�Ƃ̃C�x���g)",
"28.�����̃G���i(�G���i�̃e�[�})",
"29.Introduction!!(���h�����g�̒��ł̃C�x���g)",
"30.The Theme of Chester(�`�F�X�^�[�̃e�[�})",
"31.Chop!!(�{�X��)",
"32.Believe in my heart(�N���A���O�̃��h�����g�̒�)",
"33.�\�� ���X�e�B�N�X��(�I�[�v�j���O(����))",
"34.�����̃G���i(�K���o����������(����))"
};

void Citiran_YSF::OnDblclkList1() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CString s,ss;	s=tiys3[m_list.GetItemData(m_list.GetCurSel())];
	ss=s.Left(2);ret=_tstoi(ss)-1;
	fnn=s.Mid(3);
	EndDialog(1567);
}

void Citiran_YSF::Gett(int a){
	CString s,ss;
	s=tiys3[a];
	ss=s.Left(6);ss.TrimRight();
	fnn=s.Mid(3);
}

BOOL Citiran_YSF::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	int dx;
	for(int i=0;i<(34);i++)
	{
		CString s;
		s=tiys3[i];if(s.Left(2)=="��"){}else{s="ZW2_";s=tiys3[i];}
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
