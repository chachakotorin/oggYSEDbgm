// ED3.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "ogg.h"
#include "ED3.h"


// CED3 �_�C�A���O

IMPLEMENT_DYNAMIC(CED3, CDialog)

CED3::CED3(CWnd* pParent /*=NULL*/)
	: CDialog(CED3::IDD, pParent)
{

}

CED3::~CED3()
{
}

void CED3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CED3, CDialog)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
END_MESSAGE_MAP()


// CED3 ���b�Z�[�W �n���h��
extern CString fnn;

char tied3[][128]={
"ED3940DA ���������Q���h",
"ED3940DA �����ЂƂ̉p�Y�����̕���",
"ED3200DA ���͂���߂��̂Ȃ���",
"ED3201DA �����ȉp�Y -�I���S�[��-",
"ED3104DA ���l���C�I������܂�����炤��-Original-",
"ED3106DA WIN!! -Original-",
"ED3111DA �V���[�����O�[�X",
"ED3101DA MOUNTAIN PATH",
"ED3112DA FEEL SO GOOD",
"ED3110DA �֏�",
"ED3103DA ���A",
"ED3119DA �V�����l",
"ED3102DA �l�ӂ̌ߌ�",
"ED3107DA �����킹�Ȉ��",
"ED3203DA �C���̓L���v�e����g�[�}�X",
"ED3120DA �Ɛl�͒N��?!",
"ED3113DA �����Ȓ��Ԃ���",
"ED3108DA ���Ƃ��������",
"ED3121DA �����ȉp�Y -�W�����I�ƃN���X�̑�`��-",
"ED3100DA LET'S START, OK?",
"ED3302DA �Y�B",
"ED3300DA �K���K�̂ߍ�",
"ED3116DA ���[�f�B",
"ED3403DA GAMBLER",
"ED3400DA �ŏ�",
"ED3117DA ���������Q���h -�O��-",
"ED3402DA �_�[�c",
"ED3115DA �����݂̃����f�B",
"ED3401DA ���ꌩ��䂪���C",
"ED3405DA ���̑O",
"ED3404DA �{���g�匈��",
"ED3105DA ���G!!",
"ED3118DA ��������������",
"ED3000DA �s�v�c�Ȃ��b��",
"ED3501DA ���l���C�I������܂�����炤��-Arrange-",
"ED3502DA WIN!! -Arrange-",
"ED3109DA �~����",
"ED3700DA �j�ЂƂ藷",
"ED3506DA �t���_���V���O��I�[���i�C�g",
"ED3500DA �����̐X -Original-",
"ED3601DA �����̐X -Arrange-",
"ED3604DA �I���h�X",
"ED3600DA �I���h�X�吹��",
"ED3602DA �܂낤�ǂ̎^��",
"ED3603DA ���E�A�[��",
"ED3800DA �M�h�i",
"ED3801DA �Ԃ����̗U�f",
"ED3803DA �o�_�b�g",
"ED3802DA �K�K�[�u�̋L��",
"ED3114DA ��",
"ED3900DA INVASION",
"ED3504DA �Q���h�ւ̘H",
"ED3902DA ��z -���N�C�G��-",
"ED3920DA ���[�h��",
"ED3923DA ���b�o��",
"ED3924DA �V�V��",
"ED3503DA ���܃C�U�x�� �퓬�O",
"ED3921DA ���܃C�U�x�� �퓬",
"ED3925DA ���������Q���h -������-",
"ED3926DA �����ȉp�Y -��̂ނ�����-",
"ED3927DA �I��",
"ED3928DA �f�����[���̎莆",
"ED3505DA ���O�s�b�N���G���f�B���OVer.",
"ED3507DA Leone Fredrik Richter",
"ED3930DA HEROES2",
"ED3931DA �����ȉp�Y -�~�̓���-",
"ED3932DA �e�B���X�C�[���̔�������"
};

CString CED3::Gett(int a){
	CString s,ss;
	s=tied3[a];
	ss=s.Left(8);ss.TrimRight();
	fnn=s.Mid(9);
	return ss;
}

/////////////////////////////////////////////////////////////////////////////
// CZWEIII ���b�Z�[�W �n���h��
void CED3::OnDblclkList1() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CString s;	s=tied3[m_list.GetItemData(m_list.GetCurSel())];
	ret=s.Left(8); ret.TrimRight();
	ret2=m_list.GetCurSel();
	if(s.Left(2)=="��"){
		fnn=s.Mid(2);
	}else{
		fnn=s.Mid(9);
	}
	EndDialog(1567);
}

BOOL CED3::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	int dx;
	for(int i=0;i<(67);i++)
	{
		CString s;
		s=tied3[i];if(s.Left(2)=="��"){}else{s="ZW2_";s=tied3[i];}
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
