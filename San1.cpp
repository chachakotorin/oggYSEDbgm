// San1.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "ogg.h"
#include "San1.h"


// CSan1 �_�C�A���O

IMPLEMENT_DYNAMIC(CSan1, CDialog)

CSan1::CSan1(CWnd* pParent /*=NULL*/)
	: CDialog(CSan1::IDD, pParent)
{

}

CSan1::~CSan1()
{
}

void CSan1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CSan1, CDialog)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
END_MESSAGE_MAP()


// CSan1 ���b�Z�[�W �n���h��
extern CString fnn;

char tisan1[][128]={
"42 �i���I����",
"01 �Ï���",
"27 �ٔ�",
"12 ����",
"48 �j�R",
"49 �D��49",
"39 �ߌ�",
"38 �Îv��",
"47 �H�J��",
"05 虏�勽",
"51 �D��51",
"08 �w偓�",
"03 �Ս]�J",
"02 �s��ĉ�",
"35 �Ώ�",
"36 �є�g",
"29 ���r",
"50 �D��50",
"07 �����H",
"22 �S�E�D��",
"45 ���D",
"13 �w����D",
"53 �Պ�",
"14 ���H��",
"15 �H���",
"46 �V�U����",
"11 �_����",
"19 �D��",
"10 �]�΍s",
"04 ���t��",
"31 �Րw",
"30 �D��",
"21 �����ךz",
"41 ����",
"37 ���O�o",
"54 ���@",
"09 ��������",
"20 ������",
"06 ���΍g��",
"16 �����",
"32 �o�V",
"23 �ؖ��",
"34 ���D�痢",
"��ᶓ�",
"40 ꡑ���",
"���I�[�v�j���O",
"������",
"���t�@���R�����S"
};


CString CSan1::Gett(int a){
	CString s,ss;
	s=tisan1[a];
	ss=s.Left(2);ss.TrimRight();
	fnn=s.Mid(3);
	return ss;
}

/////////////////////////////////////////////////////////////////////////////
// CZWEIII ���b�Z�[�W �n���h��
void CSan1::OnDblclkList1() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CString s;	s=tisan1[m_list.GetItemData(m_list.GetCurSel())];
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

BOOL CSan1::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	int dx;
	for(int i=0;i<(41+3+4);i++)
	{
		CString s;
		s=tisan1[i];if(s.Left(2)=="��"){}else{s="ZW2_";s=tisan1[i];}
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
