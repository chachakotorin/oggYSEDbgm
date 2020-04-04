// ED5.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "ogg.h"
#include "ED5.h"


// CED5 �_�C�A���O

IMPLEMENT_DYNAMIC(CED5, CDialog)

CED5::CED5(CWnd* pParent /*=NULL*/)
	: CDialog(CED5::IDD, pParent)
{

}

CED5::~CED5()
{
}

void CED5::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CED5, CDialog)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
END_MESSAGE_MAP()


// CED5 ���b�Z�[�W �n���h��
extern CString fnn;

char tied5[][128]={
"ED5WV002 Leone Fredrik Richter \"�C�̟B��\"",
"ED5WV065 �Q�V�̃^�b�h(�t�H���g)",
"ED5WV020 �₷�炬�̎�",
"ED5WV030 �z�̂�����u��",
"ED5WV006 �t�̂���(�}�N�׃C��)",
"ED5WV068 ���̃Z���i�[�f(�A���g�X)",
"ED5WV036 ���敗�̉S",
"ED5WV041 �łɏh��Î�",
"ED5WV012 ���b���o�Ă��Ă������!",
"ED5WV011 �y��!...����?",
"ED5WV024 �����ɗU����",
"ED5WV081 �ł��̎g��",
"ED5WV015 �Ȃ񂾂��̖�Y!",
"ED5WV033 �����ɕ�܂��",
"ED5WV052 �V���I�ƃ��C�`�F��",
"ED5WV053 ����тłȂ���SHOW",
"ED5WV031 ��֓o�铹",
"ED5WV034 Deep Forest",
"ED5WV023 ������G��",
"ED5WV061 ���I�[�l�̃G�`���[�h(�V���x�[��)",
"ED5WV107 ���I�[�l�̃G�`���[�h(�}�N�x�C�����)",
"ED5WV084 ���󂢂�����!", 
"ED5WV013 ���Ƃɂ͈����Ȃ�",
"ED5WV089 �����݂��z����",
"ED5WV025 ���v�V�����s�i��",
"ED5WV022 Harvest",
"ED5WV055 �c��̋x��(�o���_�U�[��)",
"ED5WV056 �삢�����E��(�E�F���f�B)",
"ED5WV079 �����̕���(�A�[�K�X���J�`���A)",
"ED5WV067 �s�G���̍s�i(�V���I�����C�`�F��)",
"ED5WV108 �X�ƊC�̃������A(�}�N�x�C�����)",
"ED5WV058 ���[���b�g�܂���",
"ED5WV050 �܂͂��̓��̑z���ƂƂ���",
"ED5WV057 ��̐▽!",
"ED5WV016 �͂̌���",
"ED5WV010 ����Ȃ�E�E",
"ED5WV037 �ő�",
"ED5WV059 ����̎q���(�A���A)",
"ED5WV080 �����c��",
"ED5WV086 ���ׂ����̂̂��߂�",
"ED5WV076 �����Ȃ��̉�(�A���A)", 
"ED5WV077 �����Ȃ��̉�(�t�H���g)", 
"ED5WV021 �i���Ȃ閯�̒�",
"ED5WV083 ���I�[�l�̋O��",
"ED5WV035 Hot and Cool",
"ED5WV045 �g��",
"ED5WV044 �g���ɔR����",
"ED5WV038 �k�����X�̉e",
"ED5WV090 �ł̑��z������",
"ED5WV093 ���C�̑㏞",
"ED5WV042 �����̋�",
"ED5WV073 ����̃����f�B�[��B�ң(�E�[�i)",
"ED5WV088 ����̃����f�B�[��يE�֣",
"ED5WV048 �����𐶂��邽�߂�",
"ED5WV085 �������ɗ�����!", 
"ED5WV032 ���̈ł̌�������",
"ED5WV019 �ז�����҂͗e�͂��Ȃ�",
"ED5WV026 Leone Fredrik Richter \"�����ЂƂ̐��E\"",
"ED5WV071 ����̃����f�B�[��a���(�E�[�i)",
"ED5WV008 ����̃����f�B�[�����(�}�N�x�C��������A���A)",
"ED5WV070 ������(�f���I�[��)", 
"ED5WV047 �ł̑��z���գ",
"ED5WV017 �s������Ղ��",
"ED5WV018 ���ꂼ��̖�����",
"ED5WV007 ����̎q���(�t�H���g)",
"ED5WV110 �C�̟B�̥�g�ȃv�����[�O���������", 
"ED5WV111 �C�̟B�̥�g�ȃZ�O�G�����̃����f�B�[�", 
"ED5WV112 �C�̟B�̥�g�ȃA���A�����̎q��̣", 
"ED5WV113 �C�̟B�̥�g�ȃt�B�i�[���Leone Fredrik Richter�", 
"ED5WV116 ���������Ă�������I���",
"ED5WV069 ����̃����f�B�[��a���(�t�H���g)",
"ED5WV118 ���ꂼ��̖����ց`Leone Fredrik Richter \"End Credits\"", 
"ED5WV119 ���������Ă������u�����āE�E�v",
"ED5WV001 Leone FredrikRichter \"Theme\"",
"ED5WV100 ���ꌩ��䂪���C(�t�H���g)",
"ED5WV101 �ؘR����̎�(�}�N�x�C��)",
"ED5WV102 �䂩���ȏ���(�E�[�i)", 
"ED5WV103 ���l�����̑O�t��(�}�N�x�C�����)",
"ED5WV104 �z�C�ȗ��l(�}�N�x�C�����)",
"ED5WV105 �Ƃ��ɗx���(�}�N�x�C�����)",
"ED5WV106 �S���J����(�}�N�x�C�����)",
"ED5WV062 �����̃J���^�[�^(+���@�C�I����)",
"ED5WV074 ����̃����f�B�[�u�S��v(�t�H���g)",
"ED5WV096 ����̃����f�B�[�u���v(�t�H���g)", 
"ED5WV095 ����̃����f�B�[�u�����v(�}�N�x�C��)", 
"ED5WV066 �s�G���̍s�i������(�V���I�����C�`�F��)",
"ED5WV097 �_���W�����R", 
"ED5WV078 ���I�[�l�̌��J",
"ED5WV003 �t�@���R���̃��S",
"ED5WV060 �����̃J���^�[�^(���X�g)",
"ED5WV063 �����̃J���^�[�^�i���OVER�j",
"ED5WV064 �����̃J���^�[�^(���@�C�I����1)",
"ED5WV087 �����̃J���^�[�^(���@�C�I����2)",
"ED5WV092 ���ꌩ��䂪���C��X�����t��(�t�H���g)",
"ED5WV094 ������(�f���I�[��)", 
"ED5WV098 �Ƃ��ɗx���(�}�N�x�C�����)",
"ED5WV099 �S���J����(�}�N�x�C��������V���I����C�`�F��)",
"ED5WV109 �Ƃ��ɗx���(�}�N�x�C�����)"
};

CString CED5::Gett(int a){
	CString s,ss;
	s=tied5[a];
	ss=s.Left(8);ss.TrimRight();
	fnn=s.Mid(9);
	return ss;
}

/////////////////////////////////////////////////////////////////////////////
// CZWEIII ���b�Z�[�W �n���h��
void CED5::OnDblclkList1() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CString s;	s=tied5[m_list.GetItemData(m_list.GetCurSel())];
	ret=s.Left(8); ret.TrimRight();
	ret2=m_list.GetCurSel();
	if(s.Left(2)=="��"){
		fnn=s.Mid(2);
	}else{
		fnn=s.Mid(9);
	}
	EndDialog(1567);
}

BOOL CED5::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	int dx;
	for(int i=0;i<(98);i++)
	{
		CString s;
		s=tied5[i];if(s.Left(2)=="��"){}else{s="ZW2_";s=tied5[i];}
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


