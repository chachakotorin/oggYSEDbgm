// Zwei.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "ogg.h"
#include "Zwei.h"


// CZwei �_�C�A���O

IMPLEMENT_DYNAMIC(CZwei, CDialog)

CZwei::CZwei(CWnd* pParent /*=NULL*/)
	: CDialog(CZwei::IDD, pParent)
{

}

CZwei::~CZwei()
{
}

void CZwei::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CZwei, CDialog)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
END_MESSAGE_MAP()


// CZwei ���b�Z�[�W �n���h��
extern CString fnn;

char tiz1[][128]={
"bgm44 ���V�嗤�A���W�F�X�@-Instroduction-",
"bgm35 �i���̖��A���̋L�� -Zwei!! 2�l�ő�`��-",
"bgm03 �v�b�N��",
"bgm01 ���V�嗤�A���W�F�X -Main Theme-",
"bgm13 �p�[���F���뉀",
"bgm12 �J���p�̐X",
"bgm06 �N���b�v���A",
"bgm07 �P�m�[�s�ΎR",
"bgm70 ���V�嗤�A���W�F�X -��������-",
"bgm72 �R���x�b�g�̃e�[�}�@-�l�R�����j���[�b!-",
"bgm27 Fight!! -�󂵂ă|�b�N��-",
"bgm60 �ЂƂƂ��̋x����",
"bgm16 �_�v�l����",
"bgm18 �q�|���^�̋u",
"bgm19 �g���|�J��",
"bgm21 �v�V���P�̉��~",
"bgm50 ���₷��",
"bgm10 �d�������̑�",
"bgm26 �X�s���Ñ���{",
"bgm71 ���̖��铹",
"bgm14 �A�v���G�X�_�a",
"bgm15 �G�X�s�i�Í��_�a",
"bgm08 ���̑�n �Z���y���e�B�i",
"bgm22 �����̗��r -�n���h-",
"bgm09 �Ō�̓��� -�������F�X�p�[",
"bgm74 ���g�̃����f�B",
"bgm36 �Ԃƕ��̂���",
"bgm30 ���[�r�[1 -���ւ̗U��-",
"bgm31 ���[�r�[2 -�łւ̗U��-",
"bgm32 ���[�r�[3 -�~��-",
"bgm33 ���[�r�[4 -���-",
"bgm34 ���[�r�[5 -����-",
"bgm77 Zwei!!�V���[�e�B���O -�V��Ńs�s��-",
"bgm75 Theme of Adol 2001",
"bgm76 ���i���`�i",
"boss  "
};


CString CZwei::Gett(int a){
	CString s,ss;
	s=tiz1[a];
	ss=s.Left(5);ss.TrimRight();
	fnn=s.Mid(6);
	return ss;
}

/////////////////////////////////////////////////////////////////////////////
// CZWEIII ���b�Z�[�W �n���h��
void CZwei::OnDblclkList1() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CString s;	s=tiz1[m_list.GetItemData(m_list.GetCurSel())];
	ret=s.Left(5); ret.TrimRight();
	ret2=m_list.GetCurSel();
	if(s.Left(2)=="��"){
		fnn=s.Mid(2);
	}else{
		fnn=s.Mid(6);
	}
	EndDialog(1567);
}

BOOL CZwei::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	int dx;
	for(int i=0;i<(36);i++)
	{
		CString s;
		s=tiz1[i];if(s.Left(2)=="��"){}else{s="ZW2_";s=tiz1[i];}
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
