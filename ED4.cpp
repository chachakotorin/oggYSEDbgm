// ED4.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "ogg.h"
#include "ED4.h"


// CED4 �_�C�A���O

IMPLEMENT_DYNAMIC(CED4, CDialog)

CED4::CED4(CWnd* pParent /*=NULL*/)
	: CDialog(CED4::IDD, pParent)
{

}

CED4::~CED4()
{
}

void CED4::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CED4, CDialog)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
END_MESSAGE_MAP()


// CED4 ���b�Z�[�W �n���h��
extern CString fnn;

char tied4[][128]={
"E4S00 ��g�����@-memoria-",
"��OP1 ��g�����@-�`��-�i�I�[�v�j���O���[�r�[�j",
"��OP2 �J�@-�M���z�������Ɂi�I�[�v�j���O���[�r�[�j",
"E4B01 �ʂ�����ɕ�����āE�E�E",
"E4N28 �ْ[�҂̏P���@-�א_�I�N�g�D���̉A-",
"E4A00 �₷�炬�̓��X",
"E4S02 ����������", 
"E4S04 �����y��", 
"E4N00 ����Ⴀ�Ȃ���SHOW",
"E4S05 ��]�֑�����", 
"E4S13 ��������̂��I", 
"E4A01 ���s�t�B���f�B��",
"E4A02 �t�B���f�B����",
"E4N01 ����ɖ����Ȓ��Ԃ���",
"E4S17 ����A���B���I�I", 
"E4C01 ������l�X",
"E4N17 �������ׂ��H�r�i�݂��j��",
"E4S06 �Èłɑ��H����", 
"E4S14 ���{����", 
"E4S28 �V�����V�[���c", 
"E4S18 ���C�ȃV���m��", 
"E4S07 �X���s��", 
"E4N24 ��g���� -�_�ɑI�΂ꂵ��-",
"E4S01 �ɂ��₩�ȊX�p", 
"E4C00 �S�|�̒��`�M�A�`",
"E4S15 �ז�������ȁI", 
"E4S24 ����������܂�", 
"E4C03 �r���ɂ���� -�M�A�E�u���[�X-",
"E4S03 �����̃��Y��", 
"E4S11 �C���𕗂ɏ��", 
"E4S25 ��g�����@-�����̃A�C����-",
"E4N14 ��g���� -�K���Ȏ��ԁi�Ƃ��j-",
"E4N20 �R����A���B���I�I",
"E4N25 �������ɗ������I",
"E4N19 ��g���� -�҂��Ă�A�C����-",
"E4N99 �y���I", 
"E4N22 ������",
"E4N12 �א_���x���A�X -�P��-",
"E4E00 ���s",
"E4E01 ��q�� -�^���Əh���̒���-",
"E4N10 �J -�����݂��z����-",
"E4N11 Blue -���߂���-",
"E4N29 ���ׂ����", 
"E4D00 �^�������߂�",
"E4N80 �䂪���̓o���h�D�X�@-�^��-",
"E4N15 �o���h�D�X�̖��肵�K",
"E4N33 �����@-�����ꂽ����-", 
"E4N23 �É_�������߂钆��",
"E4S10 ���Â̈�Y", 
"E4S08 �D�Y��", 
"E4N13 �_�X�̋]��",
"E4N27 �ْ[�҂̏P���@-�{���Q�C�h-",
"E4S19 �J�@-���Ă��قǂ�-", 
"E4N81 �䂪���̓o���h�D�X�@-�W��-",
"E4G06 �䂪���̓o���h�D�X -�W��-",
"E4N32 �������ʐ킢", 
"E4G00 ����̒n",
"E4G02 ����Ԗ��{",
"E4G03 �א_���x���A�X -�M�O-",
"E4G04 �䂪�M�O�ׂ̈ɁI",
"E4G05 �I�N�g�D���̊肢",
"E4N30 �����������肢�@-�㏞-", 
"E4N34 �����������肢�@-���{-", 
"E4N31 ���e�B�X�̂�����", 
"E4N26 �J -���ꂼ��̏ꏊ��-",
"E4N35 ��g�����@-�G���h�N���W�b�g-"
};

CString CED4::Gett(int a){
	CString s,ss;
	s=tied4[a];
	ss=s.Left(5);ss.TrimRight();
	fnn=s.Mid(6);
	return ss;
}

/////////////////////////////////////////////////////////////////////////////
// CZWEIII ���b�Z�[�W �n���h��
void CED4::OnDblclkList1() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CString s;	s=tied4[m_list.GetItemData(m_list.GetCurSel())];
	ret=s.Left(5); ret.TrimRight();
	ret2=m_list.GetCurSel();
#if UNICODE
	if(s.Left(1)=="��"){
		fnn=s.Mid(1);
#else
	if(s.Left(2)=="��"){
		fnn=s.Mid(2);
#endif
	}else{
		fnn=s.Mid(6);
	}
	EndDialog(1567);
}

BOOL CED4::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	int dx;
	for(int i=0;i<(66);i++)
	{
		CString s;
		s=tied4[i];if(s.Left(2)=="��"){}else{s="ZW2_";s=tied4[i];}
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


