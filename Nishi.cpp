// Nishi.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "ogg.h"
#include "Nishi.h"


// CNishi �_�C�A���O

IMPLEMENT_DYNAMIC(CNishi, CDialog)

CNishi::CNishi(CWnd* pParent /*=NULL*/)
	: CDialog(CNishi::IDD, pParent)
{

}

CNishi::~CNishi()
{
}

void CNishi::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CNishi, CDialog)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
END_MESSAGE_MAP()


// CNishi ���b�Z�[�W �n���h��
extern CString fnn;

char tinishi[][128]={
"z001 Brieging(�[�t�B�[���t�@���R������c)",
"z002 COOL FIELD(�t�B�[���h�R�x�n��)",
"z003 �f�B�A�u��(�f�B�A�u�����i�K)",
"z004 �Q�C�V���V�e�B(�X)",
"z005 �j��_�̌ۓ�(�f�B�A�u�����i�K)",
"z006 �C���t�F���m(�C���t�F���m�č�(�J�����))",
"z007 �C�I���[��(�A���^���A�n���L�q���C���̃e�[�})",
"z008 Waltz de�c(��z�`�o�[���X�^�C���@)",
"z009 �X Part1(���̃e�[�})",
"z010 ���ʂ�C�x���g�V�[��(�����Z�f�X)",
"z011 �X Part2(���̃e�[�}",
"z012 �]��(�߂����C�x���g)",
"z013 �c�h���C�N�H(�C���̏P��)",
"z014 �퓬(�ʏ�퓬)",
"z015 Zephyr Falcon(����R�[�t�B�[���t�@���R��)",
"z016 The wind of Memory(�V���m�ƃ����Z�f�X�̃s�A�m��)",
"z017 ����(����)",
"z018 Aquamarine(�ŏI�_���W�����`�C����)",
"z019 �������C��(���C���Ƃ̐킢)",
"z020 Decisive Battle(�{�X�o�g��)",
"z021 �A�d(�C�x���g�V�[��(�����p))",
"z022 Force Field(����푈�t�B�[���h)",
"z023 FUZZY(�X�^�b�t���[��)",
"z024 It's time to BATTLE!(�{�X�o�g��2)",
"z025 PEACE(��)",
"z026 Precious Memories(�V���m�̑z���o)",
"z027 Sorrowful�c(�C�x���g(��̂��A�N�������񂾂���))",
"z028 Subway Crisis(�_���W����)",
"z029 �R�s�s(�ٔ��������̃e�[�})",
"z030 �ڊo��(�ŏI�o�g�����O)",
"z031 b-e natural(�_���W����)",
"z032 �`�F�U�� -part1-(�`�F�U���̃e�[�}(�I���K��))",
"z033 �`�F�U�� -part2-(���X�g�o�g��)",
"z034 Fireroad(�_��)",
"z035 Forth step towards plain(�t�B�[���h�E�X�Ȃ�)",
"z036 THE GREAT REPEAT(�Q�[���^�C�g�����)",
"z037 ��(�C���t�F���m�n��)",
"z038 Jungle 2 Jungle(�o�[�X��)",
"z039 Not natural but natural(�������[�v�_���W����)",
"z041 The wind of Memory�i�I�[�P�X�g����~�b�N�X�j(�G���f�B���O�e�[�})",
"z042 ����(���݉��~)",
"z050 The wind of Memory�i�t���[�Y�j(�s�A�m�e��)"
};


CString CNishi::Gett(int a){
	CString s,ss;
	s=tinishi[a];
	ss=s.Left(4);ss.TrimRight();
	fnn=s.Mid(5);
	return ss;
}

/////////////////////////////////////////////////////////////////////////////
// CZWEIII ���b�Z�[�W �n���h��
void CNishi::OnDblclkList1() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CString s;	s=tinishi[m_list.GetItemData(m_list.GetCurSel())];
	ret=s.Left(4); ret.TrimRight();
	ret2=m_list.GetCurSel();
	if(s.Left(2)=="��"){
		fnn=s.Mid(2);
	}else{
		fnn=s.Mid(5);
	}
	EndDialog(1567);
}

BOOL CNishi::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	int dx;
	for(int i=0;i<(42);i++)
	{
		CString s;
		s=tinishi[i];if(s.Left(2)=="��"){}else{s="ZW2_";s=tinishi[i];}
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
