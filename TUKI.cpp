// TUKI.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "ogg.h"
#include "TUKI.h"


// CTUKI �_�C�A���O

IMPLEMENT_DYNAMIC(CTUKI, CDialog)

CTUKI::CTUKI(CWnd* pParent /*=NULL*/)
	: CDialog(CTUKI::IDD, pParent)
{

}

CTUKI::~CTUKI()
{
}

void CTUKI::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CTUKI, CDialog)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
END_MESSAGE_MAP()


// CTUKI ���b�Z�[�W �n���h��
extern CString fnn;

char tituki[][128]={
"Mc000 ���I�p��",
"Mc001 �H�",
"Mc003 �c��",
"Mc011 ����",
"Mc002 �k�e",
"Mc013 ����",
"Mc014 �R�J�~��",
"Mc004 �N�H�i�ۗ�j",
"Mc015 ���t",
"Mc005 �������^���m����",
"Mc016 ���",
"Mc006 �ǎv",
"Mc017 ��d",
"Mc007 ����",
"Mc018 ��R",
"Mc008 �H��",
"Mc019 �o�v",
"Mc020 ���E",
"Mc021 ����",
"Mc022 ���D",
"Mc012 ��E",
"Mc023 �Y�J",
"Mc024 �V������",
"Mc025 ���E",
"Mc026 �{�E",
"Mc027 ���D",
"Mc028 �n�G",
"Mc075 (�s��)",
"���t�@���R�����S",
"���I�[�v�j���O",
"���X�^�b�t���[��",
"���G���f�B���O�P",
"���G���f�B���O�Q",
"���G���f�B���O�R",
"������P",
"������Q",
"������R",
"������S",
"������T"
};

CString CTUKI::Gett(int a){
	CString s,ss;
	s=tituki[a];
	ss=s.Left(5);ss.TrimRight();
	fnn=s.Mid(6);
	return ss;
}

/////////////////////////////////////////////////////////////////////////////
// CZWEIII ���b�Z�[�W �n���h��
void CTUKI::OnDblclkList1() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CString s;	s=tituki[m_list.GetItemData(m_list.GetCurSel())];
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

BOOL CTUKI::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	int dx;
	for(int i=0;i<(39);i++)
	{
		CString s;
		s=tituki[i];if(s.Left(2)=="��"){}else{s="ZW2_";s=tituki[i];}
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
