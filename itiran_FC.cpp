// itiran_FC.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "ogg.h"
#include "itiran_FC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Citiran_FC �_�C�A���O

extern CString fnn;

Citiran_FC::Citiran_FC(CWnd* pParent /*=NULL*/)
	: CDialog(Citiran_FC::IDD, pParent)
{
	//{{AFX_DATA_INIT(Citiran_FC)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_INIT
}


void Citiran_FC::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Citiran_FC)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Citiran_FC, CDialog)
	//{{AFX_MSG_MAP(Citiran_FC)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Citiran_FC ���b�Z�[�W �n���h��
char ti1[][40]={
"001 �������ɕ����C����",
"100 �n���s�s�������g",
"101 ���Ɠs�s�{�[�X",
"102 �C�`�s�s���[�A��",
"103 �H�[�s�s�c�@�C�X",        
"104 ���s�O�����Z��",        
"105 �z���܂�ɂĘa�ޔL",        
"106 �����x�����y����Ȃ�",        
"107 ����",        
"108 �O�����A���[�i",        
"200 ���x�[���̕�����",        
"201 Secret Green Passage",        
"202 Rock on the Road",        
"300 �ł�f�r��",        
"301 �s������͂΂ލ|�̏�",        
"302 �Â��肪���ꂽ���炬",        
"303 �l�ւ̓�",        
"304 ���C�X�g���v��",        
"305 ����Ȃ���̕��y",        
"400 Sophisticated Fight",        
"402 To be Suggestive",        
"403 ��̈ӎu",        
"404 Challenger Invited",        
"405 Ancient Makes",        
"406 �������삹�����m",        
"407 ���j�I�I",        
"408 �����s����",        
"410 �s���`�I�I",        
"500 ���݂̍菈 Harmonica short Ver.",        
"501 ���߂̈� Hum Ver.",        
"502 ���߂̈� Piano Ver.",        
"503 ���߂̈� Lute Ver.",        
"504 ���݂̍菈 Harmonica long Ver.",        
"505 ���₩�ɍs����",        
"510 ����s������",        
"511 �Ö􂷂�҂���",        
"512 �z�𓦂����ȁI",        
"513 ���̒���",        
"514 ������̉���",        
"516 �E�ъ���@",        
"517 ���B�J�v�A��ƁI",        
"518 �������̏��a",        
"519 �D��",        
"520 ��������̉���A�����āE�E�E",        
"521 ����",        
"522 ���̃I�[�u�����g",        
"523 ���x�[���̌ւ�",        
"530 (��)�P�̔Y��",        
"531 (��)�R�m�B�̒Q��",        
"532 (��)���ꂼ��̎v�f",        
"533 (��)��",        
"534 (��)�R���V�A��",        
"535 (��)����",        
"536 (��)�P�̎�",        
"537 (��)��c�~",
"��FALCOM���S����",
"���I�[�v�j���O����",
"���G���f�B���O����",
"������\������"
};
/**/

CString Citiran_FC::Gett(int a){
	CString s;
	s=ti1[a];
	fnn=s.Mid(4);
	return s;
}

void Citiran_FC::OnDblclkList1() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CString s;	s=ti1[m_list.GetItemData(m_list.GetCurSel())];
	ret=_tstoi(s.Left(3));
	ret2=m_list.GetCurSel();
	if(ret2>54)
		ret=ret2;
#if UNICODE
	if(s.Left(1)=="��"){
		fnn=s.Mid(1);
#else
	if(s.Left(2)=="��"){
		fnn=s.Mid(2);
#endif
	}else{
		fnn=s.Mid(4);
	}
	EndDialog(1567);
}

BOOL Citiran_FC::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	int dx;
	for(int i=0;i<55;i++)
	{
		CString s;
		s="ED6";
		s+=ti1[i];
//		s+="";
/*		switch(i)
		{
		case 0:
			s+="��(�^�C�g��)";
			break;
		case 1:
			s+="��(����)";
			break;
		case 10:
			s+="��(�t�B�[���h��)";
			break;
		case 13:
			s+="��(�_���W������)";
			break;
		case 19:
			s+="��(�퓬��)";
			break;
		case 28:
			s+="��(�C�x���g��)";
			break;
		}
*/		dx= m_list.AddString(s);
		m_list.SetItemData(dx,i);	
	}
		dx= m_list.AddString(_T("��FALCOM���S����"));
		m_list.SetItemData(dx,55);	
		dx= m_list.AddString(_T("���I�[�v�j���O����"));
		m_list.SetItemData(dx,56);	
		dx= m_list.AddString(_T("���G���f�B���O����"));
		m_list.SetItemData(dx,57);	
		dx= m_list.AddString(_T("������\������"));
		m_list.SetItemData(dx,58);	

		m_list.SetCurSel(0);
	if(ret2!=0) m_list.SetCurSel(ret2);

	m_list.SetFocus();
	return FALSE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}
