// Br4.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "ogg.h"
#include "Br4.h"


// CBr4 �_�C�A���O

IMPLEMENT_DYNAMIC(CBr4, CDialog)

CBr4::CBr4(CWnd* pParent /*=NULL*/)
	: CDialog(CBr4::IDD, pParent)
{

}

CBr4::~CBr4()
{
}

void CBr4::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CBr4, CDialog)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
END_MESSAGE_MAP()


// CBr4 ���b�Z�[�W �n���h��
extern CString fnn;

char tibr4[][128]={
"VT01DA Brandish4 -OP-", 
"VT03DA �Â̋F��-meditation-", 
"VT05DA ���-the prop-", 
"VT13DA �V���b�v-relation-", 
"VT32DA ���{-roar-", 
"VT04DA �X��-division-", 
"VT14DA �J�W�m-eighth wonder-", 
"VT19DA �V�Y-hammer slime-", 
"VT15DA ����-black field-", 
"VT16DA ���̓�-mysterious-", 
"VT27DA ���2-debris-", 
"VT18DA ����-trigger-", 
"VT28DA ���3-deep haze-", 
"VT06DA ����-the abyss-", 
"VT07DA �뉀-bramble-", 
"VT33DA ����-hostile-", 
"VT08DA ���-solid steel-", 
"VT09DA ����-judgement-", 
"VT17DA ���̕���-retribution-", 
"VT10DA �ٓ�-forbidden power-", 
"VT30DA ����-fatal riders-", 
"VT11DA �_�a-heritage-", 
"VT12DA �Y�p�̖��{-another door-", 
"VT34DA �Ւd-altar-", 
"VT20DA �M���A�X-victim-", 
"VT39DA �G�s���[�OI-daybreak-", 
"VT40DA �G�s���[�OII-twilght-", 
"VT41DA �G�s���[�OIV-broken chain-", 
"VT21DA VT21(�G���f�B���O�p)", 
"VT22DA VT22(�G���f�B���O�p)", 
"VT35DA ENDING", 
"VT02DA Staff", 
"VT36DA �x��-slumber-", 
"VT31DA GAME OVER", 
"VT38DA �C���g���_�N�V����", 
"VT43DA �W���O���F���l1", 
"VT44DA �W���O���F���l2", 
"VT45DA �W���O���F���l3", 
"VT46DA �W���O���F���l4", 
"VT47DA �W���O���F���l5", 
"VT48DA �W���O���F���l6", 
"VT49DA �W���O���F���l7"
};

CString CBr4::Gett(int a){
	CString s,ss;
	s=tibr4[a];
	ss=s.Left(6);ss.TrimRight();
	fnn=s.Mid(7);
	return ss;
}

/////////////////////////////////////////////////////////////////////////////
// CZWEIII ���b�Z�[�W �n���h��
void CBr4::OnDblclkList1() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CString s;	s=tibr4[m_list.GetItemData(m_list.GetCurSel())];
	ret=s.Left(6); ret.TrimRight();
	ret2=m_list.GetCurSel();
	if(s.Left(2)=="��"){
		fnn=s.Mid(2);
	}else{
		fnn=s.Mid(7);
	}
	EndDialog(1567);
}

BOOL CBr4::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	int dx;
	for(int i=0;i<(42);i++)
	{
		CString s;
		s=tibr4[i];if(s.Left(2)=="��"){}else{s="ZW2_";s=tibr4[i];}
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
