// Sor.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "ogg.h"
#include "Sor.h"


// CSor �_�C�A���O

IMPLEMENT_DYNAMIC(CSor, CDialog)

CSor::CSor(CWnd* pParent /*=NULL*/)
	: CDialog(CSor::IDD, pParent)
{

}

CSor::~CSor()
{
}

void CSor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CSor, CDialog)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
END_MESSAGE_MAP()


// CSor ���b�Z�[�W �n���h��
extern CString fnn;

char tisor[][128]={
"SSO001 �I�[�v�j���O",
"SSO002 �� (�����ň������)",
"SSO003 ��1",
"SSO004 ��2",
"SSO008 �g���x���[�Y�E�C��",
"SSO059 �V�i���I�N���A",
"SSO005 ���������l�̏� �_���W����",
"SSO006 ���������l�̏� �q�h��",
"SSO007 ���������l�̏� ����",
"SSO009 ����ꂽ�^���X�}�� �X",
"SSO010 ����ꂽ�^���X�}�� �n���_���W����",
"SSO011 ����ꂽ�^���X�}�� �_���e���q�`",
"SSO012 ����ꂽ�^���X�}�� �T���h�E�}���{�[",
"SSO013 ���V�t�F���̐��� �n���_���W����",
"SSO014 ���V�t�F���̐��� �N���[�P��",
"SSO015 ���V�t�F���̐��� �u���f�B�[�E���o�[",
"SSO016 ���ꂽ�I�A�V�X ����",
"SSO017 ���ꂽ�I�A�V�X ���̏�",
"SSO018 ���ꂽ�I�A�V�X �������ƃS�[���h�E�h���S��",
"SSO019 �����B�̓� ��",
"SSO020 �����B�̓� �n��",
"SSO021 �����B�̓� ����",
"SSO022 �����B�̓� ���W���[�E�f�[����",
"SSO023 �����B�̓� �V���h�[�E�h���S��",
"SSO024 �����B�̓� ����",
"SSO025 �Â����̖��@�g�� �Â���",
"SSO026 �Â����̖��@�g�� ���b�h�E�h���S��",
"SSO027 ���}���V�A ���}���V�A����",
"SSO028 ���}���V�A ���}���V�A��",
"SSO029 ���}���V�A �A�]���o����",
"SSO030 ���}���V�A ���@�C�f�X",
"SSO060 ���}���V�A��p�N���A",
"SSO031 �g�ʂ̓� �X",
"SSO032 �g�ʂ̓� ���X�E�W���C�A���g",
"SSO033 �g�ʂ̓� ���a�ȐX",
"SSO034 �Í��̖����m �_���W����",
"SSO035 �Í��̖����m �Q�f�B�X",
"SSO064 �Í��̖����m �Q�f�B�XII",
"SSO036 �Í��̖����m �u���[�E�h���S��",
"SSO037 ���ꂽ�N�C�[���}���[�� �D��",
"SSO038 ���ꂽ�N�C�[���}���[�� �㗤��",
"SSO039 ���ꂽ�N�C�[���}���[�� �A�[�N�E�f�[����",
"SSO040 �V�̐_�X���� ��",
"SSO041 �V�̐_�X���� �R���o�b�g�E�V�[��",
"SSO042 �V�̐_�X���� �V��E",
"SSO043 �V�̐_�X���� �G��",
"SSO044 �V�̐_�X���� �G�r��=�V���[�}��",
"SSO045 �X�̓��A ���A",
"SSO046 �X�̓��A ���AII",
"SSO047 �X�̓��A �G�L��",
"SSO048 ���f���[�T�̎� �X",
"SSO049 ���f���[�T�̎� ��",
"SSO050 ���f���[�T�̎� ���f���[�T",
"SSO051 ����ꂽ���@�g�� �n���v��",
"SSO052 ����ꂽ���@�g�� �t�@�C���[�E�G�������g",
"SSO053 �s�V�����̐� �����Ă��铴�A",
"SSO054 �s�V�����̐� �����S��",
"SSO055 �s�V�����̐� �_�u��=�f�r���X",
"SSO056 �L���O�E�h���S��",
"SSO057 �G���f�B���OI",
"SSO058 �G���f�B���OII",
"SSO066 �V�I�[�v�j���O",
"SSO080 ���閂�p�t�̎��s �z�R�̒n���",
"SSO081 ���閂�p�t�̎��s �A�[�X�G�������^��",
"SSO083 �^�钆�ɏ��͖� �����h����",
"SSO084 �^�钆�ɏ��͖� ����",
"SSO085 �^�钆�ɏ��͖� �U�L�����C�A",
"SSO086 �^�钆�ɏ��͖� ���p�m�Q����",
"SSO087 �h���[�t�̒u���y�Y �h���[�t�̖��{",
"SSO088 �h���[�t�̒u���y�Y ���r�����X�E�h���S��",
"SSO089 �d���̑�����~�� �d�������̑�",
"SSO090 �d���̑�����~�� ������ؓ���",
"SSO091 �d���̑�����~�� �Z���e�B�s�[�h",
"SSO092 �����ꂴ�闈�K�� �������ȓ�",
"SSO093 �����ꂴ�闈�K�� �A�[�N�E�f�[����",
"SSO082 �t�H�[�G�o�[ �V�i���I�P�`�T�N���A"
};

CString CSor::Gett(int a){
	CString s,ss;
	s=tisor[a];
	ss=s.Left(6);ss.TrimRight();
	fnn=s.Mid(7);
	return ss;
}

/////////////////////////////////////////////////////////////////////////////
// CZWEIII ���b�Z�[�W �n���h��
void CSor::OnDblclkList1() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CString s;	s=tisor[m_list.GetItemData(m_list.GetCurSel())];
	ret=s.Left(6); ret.TrimRight();
	ret2=m_list.GetCurSel();
	if(s.Left(2)=="��"){
		fnn=s.Mid(2);
	}else{
		fnn=s.Mid(7);
	}
	EndDialog(1567);
}

BOOL CSor::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	int dx;
	for(int i=0;i<(76);i++)
	{
		CString s;
		s=tisor[i];if(s.Left(2)=="��"){}else{s="ZW2_";s=tisor[i];}
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

