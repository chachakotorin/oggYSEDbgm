// Gurumin.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "ogg.h"
#include "Gurumin.h"


// CGurumin �_�C�A���O

IMPLEMENT_DYNAMIC(CGurumin, CDialog)

CGurumin::CGurumin(CWnd* pParent /*=NULL*/)
	: CDialog(CGurumin::IDD, pParent)
{

}

CGurumin::~CGurumin()
{
}

void CGurumin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CGurumin, CDialog)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
END_MESSAGE_MAP()


// CGurumin ���b�Z�[�W �n���h��
extern CString fnn;

char tigu[][128]={
"bgm01 ���邮��Tonight",
"bgm08 �I�o�P�ȓ��X",
"bgm03 ���Ȃ��͂�����H",
"bgm05 �}�C�y�[�X�ȃI�o�P����",
"bgm06 �f�B�[�X���X�X�̃e�[�}",
"bgm04 ���̊�",
"bgm09 ��������ςł���",
"bgm11 EURO BEAT POCO",
"bgm15 �`���̃h����",
"bgm07 �I�o�P���[���h",
"bgm36 �X�e�[�W�N���A",
"bgm12 �ł̖�",
"bgm14 �Ȃ񂾂���ρI�H",
"bgm10 Animal Minimal",
"bgm17 �O���O�����l�Ń|��",
"bgm18 ����������߂�",
"bgm43 ���G�̊Z�͐�Δj��}�Z�`���I",
"bgm21 �}�C�i�X�C�I���̐Î�",
"bgm27 �閧�̖��уT�o�C�o��",
"bgm22 dance in the forest",
"bgm23 ���F�I�o�P�͉j���Ȃ�",
"bgm24 sight of silence",
"bgm25 SAMURAI DRILL�I",
"bgm20 JunJun - Jungle gym",
"bgm26 under the sky",
"bgm28 bomber girl",
"bgm39 �����Ђ�",
"bgm29 �s�v�c�I�o�P��",
"bgm30 Blest of Wind",
"bgm45 Rocky Nebula",
"bgm31 ���K�̎^��",
"bgm46 ���ꂵ��̉�",
"bgm32 �߂������u���Ă���",
"bgm38 ��邵���Ȃ���ˁI",
"bgm35 �킢�I����ē�������",
"bgm40 �����͂����Ƃ݂�ȗF�B",
"bgm42 �����̏ꏊ��",
"bgm02 Friends",
"bgm33 TO MAKE THE END OF DIGING",
"bgm44 �f�B�[�X���X�X�̉�",
"���I�[�v�j���O"
};


CString CGurumin::Gett(int a){
	CString s,ss,sss;int aa;
	s=tigu[a];
	ss=s.Left(5);ss.TrimRight();
	sss=ss.Right(2); aa=_tstoi(sss);
	switch(aa){
		case 1: loop1=0; loop2=0; break;
		case 2: loop1=0; loop2=0; break;
		case 3: loop1=211049; loop2=2479133; break;
		case 4: loop1=875909; loop2=5506409; break;
		case 5: loop1=956443; loop2=4536327; break;
		case 6: loop1=559133; loop2=3320188; break;
		case 7: loop1=717837; loop2=6288363; break;
		case 8: loop1=350186; loop2=4075770; break;
		case 9: loop1=111612; loop2=3083831; break;
		case 10: loop1=454418; loop2=5283368; break;
		case 11: loop1=0; loop2=0; break;
		case 12: loop1=22562; loop2=2656272; break;
		case 14: loop1=138782; loop2=4122910; break;
		case 15: loop1=0; loop2=0; break;
		case 17: loop1=180224; loop2=9620008; break;
		case 18: loop1=532240; loop2=9841064; break;
		case 20: loop1=624308; loop2=6098791; break;
		case 21: loop1=1119619; loop2=6842973; break;
		case 22: loop1=664867; loop2=6712867; break;
		case 23: loop1=1291826; loop2=10041266; break;
		case 24: loop1=1264850; loop2=9167570; break;
		case 25: loop1=460165; loop2=10004014; break;
		case 26: loop1=1346511; loop2=6604369; break;
		case 27: loop1=400130; loop2=6750514; break;
		case 28: loop1=610146; loop2=8254146; break;
		case 29: loop1=1234844; loop2=10537980; break;
		case 30: loop1=203348; loop2=5693798; break;
		case 31: loop1=347847; loop2=6861079; break;
		case 32: loop1=1176658; loop2=11458258; break;
		case 33: loop1=962322; loop2=5580795; break;
		case 35: loop1=22050; loop2=5243486; break;
		case 36: loop1=1004300; loop2=2062700; break;
		case 38: loop1=333547; loop2=4899691; break;
		case 39: loop1=1091098; loop2=5324698; break;
		case 40: loop1=168548; loop2=5191462; break;
		case 42: loop1=239571; loop2=5567931; break;
		case 43: loop1=150544; loop2=4501022; break;
		case 44: loop1=712610; loop2=3473489; break;
		case 45: loop1=419768; loop2=4190318; break;
		case 46: loop1=496280; loop2=3883160; break;
		case 0: loop1=0; loop2=0; break;
	}
	fnn=s.Mid(6);
	return ss;
}

/////////////////////////////////////////////////////////////////////////////
// CZWEIII ���b�Z�[�W �n���h��
void CGurumin::OnDblclkList1() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CString s,ss,sss;int aa;	s=tigu[m_list.GetItemData(m_list.GetCurSel())];
	ret=s.Left(5); ret.TrimRight(); ss=ret;
	ret2=m_list.GetCurSel();
	sss=ss.Right(2); aa=_tstoi(sss);
	switch(aa){
		case 1: loop1=0; loop2=0; break;
		case 2: loop1=0; loop2=0; break;
		case 3: loop1=211049; loop2=2479133; break;
		case 4: loop1=875909; loop2=5506409; break;
		case 5: loop1=956443; loop2=4536327; break;
		case 6: loop1=559133; loop2=3320188; break;
		case 7: loop1=717837; loop2=6288363; break;
		case 8: loop1=350186; loop2=4075770; break;
		case 9: loop1=111612; loop2=3083831; break;
		case 10: loop1=454418; loop2=5283368; break;
		case 11: loop1=0; loop2=0; break;
		case 12: loop1=22562; loop2=2656272; break;
		case 14: loop1=138782; loop2=4122910; break;
		case 15: loop1=0; loop2=0; break;
		case 17: loop1=180224; loop2=9620008; break;
		case 18: loop1=532240; loop2=9841064; break;
		case 20: loop1=624308; loop2=6098791; break;
		case 21: loop1=1119619; loop2=6842973; break;
		case 22: loop1=664867; loop2=6712867; break;
		case 23: loop1=1291826; loop2=10041266; break;
		case 24: loop1=1264850; loop2=9167570; break;
		case 25: loop1=460165; loop2=10004014; break;
		case 26: loop1=1346511; loop2=6604369; break;
		case 27: loop1=400130; loop2=6750514; break;
		case 28: loop1=610146; loop2=8254146; break;
		case 29: loop1=1234844; loop2=10537980; break;
		case 30: loop1=203348; loop2=5693798; break;
		case 31: loop1=347847; loop2=6861079; break;
		case 32: loop1=1176658; loop2=11458258; break;
		case 33: loop1=962322; loop2=5580795; break;
		case 35: loop1=22050; loop2=5243486; break;
		case 36: loop1=1004300; loop2=2062700; break;
		case 38: loop1=333547; loop2=4899691; break;
		case 39: loop1=1091098; loop2=5324698; break;
		case 40: loop1=168548; loop2=5191462; break;
		case 42: loop1=239571; loop2=5567931; break;
		case 43: loop1=150544; loop2=4501022; break;
		case 44: loop1=712610; loop2=3473489; break;
		case 45: loop1=419768; loop2=4190318; break;
		case 46: loop1=496280; loop2=3883160; break;
		case 0: loop1=0; loop2=0; break;
	}
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

BOOL CGurumin::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	int dx;
	for(int i=0;i<(41);i++)
	{
		CString s;
		s=tigu[i];if(s.Left(2)=="��"){}else{s="ZW2_";s=tigu[i];}
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
