// ZWEIII.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "ogg.h"
#include "ZWEIII.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZWEIII �_�C�A���O

extern CString fnn;

CZWEIII::CZWEIII(CWnd* pParent /*=NULL*/)
	: CDialog(CZWEIII::IDD, pParent)
{
	//{{AFX_DATA_INIT(CZWEIII)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_INIT
}


void CZWEIII::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZWEIII)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CZWEIII, CDialog)
	//{{AFX_MSG_MAP(CZWEIII)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


char tiz2[][128]={
"000 ����Ȃ��`���̐V�V�n",
"001 �O�������@�����̓`��",
"002 �{�N���m���� Opening Version",
"003 ZWEI II End Credit",
"004 �͐s���Ă��c",
"006 ���@���Ăсc",
"007 �������ăA���E�F�� Rushing in Version",
"008 �h���̏I��",
"100 ���V���s�C���o�[�h�t",
"101 �A���b�e�̒�",
"102 �A���b�e��s��",
"103 �u�����f�[���u",
"104 ���A���^��",
"105 ���~��̗�",
"106 �N���X�^���o���[",
"108 �������[���C��",
"109 ���ʒ��l�M�������h�D",
"200 �Z�N���h�D���p�B",
"201 �I���f�B�E���_�a",
"202 ���ł̐X",
"203 �A�E������S��",
"205 �Ŗ�ɗx��",
"206 ���[���u���A��",
"207 ����̘S��",
"208 �G�X�s�i�֕����F��",
"209 ������",
"210 �o������߂�",
"211 ���̐��E�s���i�������h�D�X�t",
"212 �����v�ǃ����Z�f�N",
"300 �܂����냉�O�i",
"301 �X��I�A���J�[�M�A�I�I",
"304 �^�c�̗�",
"305 ��ɂЂꕚ��",
"306 �䂪��̂��߂�",
"307 ���̏u�ԂɑS�Ă�q����",
"308 ��Q��˔j����",
"400 Dog Fight�I�I",
"401 �s���ȋ�C",
"402 �����u�����̃e�[�}",
"403 ���b�c�E�G�N�T�T�@�C�Y�I�I",
"404 ����ɋ����",
"405 �U�n�[���̑�]",
"406 �ň��̎���",
"407 ���������ȑz��",
"408 �ʂ������S�ƐS",
"409 ���H���͑�F�L�O��",
"410 �@�B�d�|���̏���",
"411 �h���̏���",
"412 �������ăA���E�F��",
"413 ���ӂ̃��O�i",
"414 �ۂ���ꂽ�g��",
"415 ���������̂Ȃ�����",
"416 �ĉ�𐾂���",
"417 ���ɘȂ�",
"500 ���y Ys �t�F���K�i�̐���(�������������N)",
"501 ���y Ys �t�F���K�i�̐���(�o���X�^�C����)",
"502 ���y Ys �I���W��(BEYOND THE BEGINNING)",
"503 ���y Ys �I���W��(WATER PRISON)",
"504 ���y Zwei!!(�Ԃƕ��̂��� -arrange-)",
"505 ���y Zwei!!(���̑�n �Z���y���e�B�i)",
"506 ���y ��̋O��FC(����Ȃ���̕��y)",
"507 ���y ��̋O��SC(The Fate of The Fairies)",
"508 ���y ��̋O��The3rd(Overdosing Heavenly Bliss)",
"509 ���y ����݂�(�s�v�c�I�o�P��)",
"510 ���y ����݂�(TO MAKE THE END OF DIGING)",
"���I�[�v�j���O",
"���G���f�B���O"
};

CString CZWEIII::Gett(int a){
	CString s,ss;
	s=tiz2[a];
	ss=s.Left(3);
	fnn=s.Mid(4);
	return ss;
}

/////////////////////////////////////////////////////////////////////////////
// CZWEIII ���b�Z�[�W �n���h��
void CZWEIII::OnDblclkList1() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CString s;	s=tiz2[m_list.GetItemData(m_list.GetCurSel())];
	ret=_tstoi(s.Left(4));
	ret2=m_list.GetCurSel();
	if(ret2>65)
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

BOOL CZWEIII::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	int dx;
	for(int i=0;i<67;i++)
	{
		CString s;
		s=tiz2[i];if(s.Left(2)=="��"){}else{s="ZW2_";s+=tiz2[i];}
		dx= m_list.AddString(s);
		m_list.SetItemData(dx,i);	
	}

	m_list.SetCurSel(0);
	if(ret!=0) 
//		if(ret>65) m_list.SetCurSel(ret);
//		else m_list.SetCurSel(ret-1);
		m_list.SetCurSel(ret);
	m_list.SetFocus();
	return FALSE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}
