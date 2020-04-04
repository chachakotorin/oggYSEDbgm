// ED63rd.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "ogg.h"
#include "ED63rd.h"

extern CString fnn;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CED63rd �_�C�A���O


CED63rd::CED63rd(CWnd* pParent /*=NULL*/)
	: CDialog(CED63rd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CED63rd)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_INIT
}


void CED63rd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CED63rd)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CED63rd, CDialog)
	//{{AFX_MSG_MAP(CED63rd)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CED63rd ���b�Z�[�W �n���h��

char ti_3[][50]={
"001���������ɕ����C���� SC Ver",
"020��������������",
"021��Cry for me, cry for you Opening version",
"022��������グ�� Ending version",
"024���r��ɂ��т����Зe",
"100�@�n���s�s�������g",
"101�@���Ɠs�s�{�[�X",
"102�@�C�`�s�s���[�A��",
"103�@�H�[�s�s�c�@�C�X",        
"104�@���s�O�����Z��",        
"105�@�z���܂�ɂĘa�ޔL",        
"106�@�����x�����y����Ȃ�",        
"107�@����",        
"108�@�O�����A���[�i",
"110�@�������b�N���ւ悤����",
"111�@���΂��������X",
"112�@Heartless Surprise Attack",
"113�@��s��̓O�����A�X",
"120���B�҂̒뉀",
"121�������̉�",
"122����S�̂܂܂�",
"123���Ō�̑I��",
"200�@���x�[���̕�����",        
"201�@Secret Green Passage",        
"202�@Rock on the Road",        
"210�@������グ��",
"300�@�ł�f�r��",        
"301�@�s������͂΂ލ|�̏�",        
"302�@�Â��肪���ꂽ���炬",        
"303�@�l�ւ̓�",        
"304�@���C�X�g���v��",        
"305�@����Ȃ���̕��y",        
"310�@�B���ꂽ�^�̎p",
"311�@����",
"312�@���V�s�s���x���A�[�N",
"313�@���̐��ڎw����",
"314�@�������s�A�N�V�X�s���[�t",
"315�@�����ʉ���",
"316�@���Ԃ̌���",
"320���Ő���L ",
"321���يE",
"322�����̓��A��̓�",
"323�����Ɖe�̖��{",
"324���[��",
"325�����e�� �sPhantasmagoria�t",
"330�����ł̉���",
"331�������ʐ��E",
"332���Ռ��ɓ���ČՎ��𓾂�",
"333�����e�̑�����",
"334�����̕��M",
"400�@Sophisticated Fight",        
"402�@To be Suggestive",        
"403�@��̈ӎu",        
"404�@Challenger Invited",        
"405�@Ancient Makes",        
"406�@�������삹�����m",        
"407�@���j�I�I",        
"408�@�����s����",        
"410�@�s���`�I�I",        
"420�@Strepitoso Fight",
"421�@The Fate Of The Fairies",
"422�@Obstructive Existence",
"423�@Fight with Assailant",
"424�@�傢�Ȃ�ؕ|",
"425A Maybe It Was Fated Instrumental Ver.",
"426�@Outskirts of Evolution",
"427�@The Merciless Savior",
"428�@���̐���W",
"429�@Feeling Danger Nearby",
"430��Determination of Fight",
"431��Fighting Right On",
"432��Close to the Brink",
"433��Overdosing Heavenly Bliss",
"434��Genuine Devil",
"435�����ƌ����̐��n",
"436��Banquet of frenzy",
"437��Masquerade of Lies",
"438�����ꂪ�^�̎��͂�I",
"439�����_��A�����߂��E�E�E",
"440�����ƌ����̐��n(���g���C)",
"500�@���݂̍菈 Harmonica short Ver.",        
"501�@���߂̈� Hum Ver.",        
"502�@���߂̈� Piano Ver.",        
"503�@���߂̈� Lute Ver.",        
"504�@���݂̍菈 Harmonica long Ver.",        
"505�@���₩�ɍs����",        
"510�@����s������",        
"511�@�Ö􂷂�҂���",        
"512�@�z�𓦂����ȁI",        
"513�@���̒���",        
"514�@������̉���",        
"516�@�E�ъ���@",        
"517�@���B�J�v�A��ƁI",        
"518�@�������̏��a",        
"519�@�D��",        
"520�@��������̉���A�����āE�E�E",        
"521�@����",        
"522�@���̃I�[�u�����g",        
"523�@���x�[���̌ւ�",        
"530�@(��)�P�̔Y��",        
"531�@(��)�R�m�B�̒Q��",        
"532�@(��)���ꂼ��̎v�f",        
"533�@(��)��",        
"534�@(��)�R���V�A��",        
"535�@(��)����",        
"536�@(��)�P�̎�",        
"537�@(��)��c�~",
"540�@�A�d",
"541�@���s��",
"542�@�����v��",
"543�@���肭�鋺��",
"544�@�n�[����",
"546�@�����Ђ������",
"547�@�r��ɐ��މe",
"548�@���̑���",
"549�@�J�݂̍菈",
"550�@��̈ӎu Super Arrange Ver",
"551�@���݂̍菈 Instrumental ver",
"552�@Etude of the Ruin",
"554�@�S���̐^��",
"556�@����",
"560����s�q�D���V�^�j�A��",
"561�����P",
"562�������ꂴ���",
"563����؂Ȃ���",
"564���ǉ�",
"565�������ւ̊K�i",
"566���e�̉�",
"567��Cry for your Eternity",
"568���z���̖����肩��",
"569���܂���������߂�",
"570���N��Y��Ă�",
"571��The Crimson Stigma",
"572�����̔�14",
"573���n�܂�̒n",
"574�����N���X�̕���",
"581�����_�̋@���͎��̉^",
"582�����މ���i����",
"583����̓�͋O�ՂŃ|���I",
"584���R�L�����U���",
"586��Till the Night of Glory",
"��FALCOM���S����",
"���I�[�v�j���O����",
"���G���f�B���O����",
"������1",
"������2",
"������3"
};
/**/

CString CED63rd::Gett(int a){
	CString s;
	s=ti_3[a];
	fnn=s.Mid(5);
	return s;
}

void CED63rd::OnDblclkList1() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CString s;	s=ti_3[m_list.GetItemData(m_list.GetCurSel())];
	ret=_tstoi(s.Left(3));
	ret2=m_list.GetCurSel();
	if(ret2>141)
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
			fnn=s.Mid(5);
	}
	EndDialog(1567);
}

BOOL CED63rd::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	int dx;
	for(int i=0;i<141+6;i++)
	{
		CString s;
		s=ti_3[i];
		if(s.Left(2)=="��"){}else
		{	s="ED6";
		s+=ti_3[i]; }
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
//		dx= m_list.AddString("��FALCOM���S����");
//		m_list.SetItemData(dx,98);	
//		dx= m_list.AddString("���I�[�v�j���O����");
//		m_list.SetItemData(dx,99);	

		m_list.SetCurSel(0);
	if(ret2!=0) m_list.SetCurSel(ret2);

	m_list.SetFocus();
	return FALSE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

