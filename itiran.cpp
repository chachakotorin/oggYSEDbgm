// itiran.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "ogg.h"
#include "itiran.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// itiran �_�C�A���O

extern CString fnn;
itiran::itiran(CWnd* pParent /*=NULL*/)
	: CDialog(itiran::IDD, pParent)
{
	//{{AFX_DATA_INIT(itiran)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_INIT
}


void itiran::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(itiran)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(itiran, CDialog)
	//{{AFX_MSG_MAP(itiran)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// itiran ���b�Z�[�W �n���h��

char ti[][50]={
"001 --/SC �������ɕ����C���� SC Ver",
"010 --/SC Shine of Eidos �`��̋O�Ձ`",
"011 --/SC OP ��̈ӎu ���̗�/�R�e�G�q",
"012 --/SC ED I swear.../������q",
"015 --/SC ���������ꂽ����",
"016 --/SC ���_�̌䋖��",
"017 --/SC �܂�ꂽ��",
"018 --/SC ��]�̍s��",
"100 FC/SC �n���s�s�������g",
"101 FC/SC ���Ɠs�s�{�[�X",
"102 FC/SC �C�`�s�s���[�A��",
"103 FC/SC �H�[�s�s�c�@�C�X",        
"104 FC/SC ���s�O�����Z��",        
"105 FC/SC �z���܂�ɂĘa�ޔL",        
"106 FC/SC �����x�����y����Ȃ�",        
"107 FC/SC ����",        
"108 FC/SC �O�����A���[�i",
"110 --/SC �������b�N���ւ悤����",
"111 --/SC ���΂��������X",
"112 --/SC Heartless Surprise Attack",
"113 --/SC ��s��̓O�����A�X",
"200 FC/-- ���x�[���̕�����",        
"201 FC/SC Secret Green Passage",        
"202 FC/SC Rock on the Road",        
"210 --/SC ������グ��",
"300 FC/SC �ł�f�r��",        
"301 FC/SC �s������͂΂ލ|�̏�",        
"302 FC/SC �Â��肪���ꂽ���炬",        
"303 FC/SC �l�ւ̓�",        
"304 FC/SC ���C�X�g���v��",        
"305 FC/-- ����Ȃ���̕��y",        
"310 --/SC �B���ꂽ�^�̎p",
"311 --/SC ����",
"312 --/SC ���V�s�s���x���A�[�N",
"313 --/SC ���̐��ڎw����",
"314 --/SC �������s�A�N�V�X�s���[�t",
"315 --/SC �����ʉ���",
"316 --/SC ���Ԃ̌���",
"400 FC/-- Sophisticated Fight",        
"402 FC/SC To be Suggestive",        
"403 FC/SC ��̈ӎu",        
"404 FC/SC Challenger Invited",        
"405 FC/-- Ancient Makes",        
"406 FC/-- �������삹�����m",        
"407 FC/SC ���j�I�I",        
"408 FC/SC �����s����",        
"410 FC/SC �s���`�I�I",        
"420 --/SC Strepitoso Fight",
"421 --/SC The Fate Of The Fairies",
"422 --/SC Obstructive Existence",
"423 --/SC Fight with Assailant",
"424 --/SC �傢�Ȃ�ؕ|",
"425 --/SC Fateful confrontation",
"426 --/SC Outskirts of Evolution",
"427 --/SC The Merciless Savior",
"428 --/SC ���̐���W",
"429 --/SC Feeling Danger Nearby",
"500 FC/SC ���݂̍菈 Harmonica short Ver.",        
"501 FC/-- ���߂̈� Hum Ver.",        
"502 FC/-- ���߂̈� Piano Ver.",        
"503 FC/-- ���߂̈� Lute Ver.",        
"504 FC/-- ���݂̍菈 Harmonica long Ver.",        
"505 FC/SC ���₩�ɍs����",        
"510 FC/SC ����s������",        
"511 FC/SC �Ö􂷂�҂���",        
"512 FC/-- �z�𓦂����ȁI",        
"513 FC/SC ���̒���",        
"514 FC/SC ������̉���",        
"516 FC/SC �E�ъ���@",        
"517 FC/-- ���B�J�v�A��ƁI",        
"518 FC/-- �������̏��a",        
"519 FC/SC �D��",        
"520 FC/-- ��������̉���A�����āE�E�E",        
"521 FC/SC ����",        
"522 FC/SC ���̃I�[�u�����g",        
"523 FC/SC ���x�[���̌ւ�",        
"530 FC/-- (��)�P�̔Y��",        
"531 FC/-- (��)�R�m�B�̒Q��",        
"532 FC/-- (��)���ꂼ��̎v�f",        
"533 FC/-- (��)��",        
"534 FC/-- (��)�R���V�A��",        
"535 FC/-- (��)����",        
"536 FC/-- (��)�P�̎�",        
"537 FC/-- (��)��c�~",
"540 --/SC �A�d",
"541 --/SC ���s��",
"542 --/SC �����v��",
"543 --/SC ���肭�鋺��",
"544 --/SC �n�[����",
"546 --/SC �����Ђ������",
"547 --/SC �r��ɐ��މe",
"548 --/SC ���̑���",
"549 --/SC �J�݂̍菈",
"550 --/SC ��̈ӎu Super Arrange Ver",
"551 --/SC ���݂̍菈 Instrumental ver",
"552 --/SC Etude of the Ruin",
"554 --/SC �S���̐^��",
"556 --/SC ����",
"��FALCOM���S����",
"���I�[�v�j���O����",
"���G���f�B���O����",
"������1",
"������2",
"������3",
"������4",
"������5",
"������6",
"������7"
};
/**/

CString itiran::Gett(int a){
	CString s;
	s=ti[a];
	fnn=s.Mid(10);
	return s;
}

void itiran::OnDblclkList1() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CString s;	s=ti[m_list.GetItemData(m_list.GetCurSel())];
	ret=_tstoi(s.Left(3));
	ret2=m_list.GetCurSel();
	if(ret2>97)
		ret=ret2;
#if UNICODE
	if(s.Left(1)=="��"){
		fnn=s.Mid(1);
#else
	if(s.Left(2)=="��"){
		fnn=s.Mid(2);
#endif
	}else{
		fnn=""; if(s.GetLength()>3)
			fnn=s.Mid(10);
	}
	EndDialog(1567);
}

BOOL itiran::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	int dx;
	for(int i=0;i<98;i++)
	{
		CString s;
		s="ED6";
		s+=ti[i];
//		s+="";
/*		switch(ti[i][0])
		{
		case '0':
			s+="��(�^�C�g��)";
			break;
		case '1':
			s+="��(����)";
			break;
		case '2':
			s+="��(�t�B�[���h��)";
			break;
		case '3':
			s+="��(�_���W������)";
			break;
		case '4':
			s+="��(�퓬��)";
			break;
		case '5':
			s+="��(�C�x���g��)";
			break;
		}
*/		dx= m_list.AddString(s);
		m_list.SetItemData(dx,i);	
	}
		dx= m_list.AddString(_T("��FALCOM���S����"));
		m_list.SetItemData(dx,98);	
		dx= m_list.AddString(_T("���I�[�v�j���O����"));
		m_list.SetItemData(dx,99);	
		dx= m_list.AddString(_T("���G���f�B���O����"));
		m_list.SetItemData(dx,100);	
		dx= m_list.AddString(_T("������1"));
		m_list.SetItemData(dx,101);	
		dx= m_list.AddString(_T("������2"));
		m_list.SetItemData(dx,102);	
		dx= m_list.AddString(_T("������3"));
		m_list.SetItemData(dx,103);	
		dx= m_list.AddString(_T("������4"));
		m_list.SetItemData(dx,104);	
		dx= m_list.AddString(_T("������5"));
		m_list.SetItemData(dx,105);	
		dx= m_list.AddString(_T("������6"));
		m_list.SetItemData(dx,106);	
		dx= m_list.AddString(_T("������7"));
		m_list.SetItemData(dx,107);	

		m_list.SetCurSel(0);
	if(ret2!=0) m_list.SetCurSel(ret2);

	m_list.SetFocus();
	return FALSE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

