// AudioSelect.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "ogg.h"
#include "AudioSelect.h"

extern CString streamname[20];
// CAudioSelect �_�C�A���O

IMPLEMENT_DYNAMIC(CAudioSelect, CDialog)

CAudioSelect::CAudioSelect(CWnd* pParent /*=NULL*/)
	: CDialog(CAudioSelect::IDD, pParent)
{

}

CAudioSelect::~CAudioSelect()
{
}

void CAudioSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lb);
}


BEGIN_MESSAGE_MAP(CAudioSelect, CDialog)
	ON_LBN_DBLCLK(IDC_LIST1, &CAudioSelect::OnLbnDblclkList1)
	ON_BN_CLICKED(IDOK, &CAudioSelect::OnBnClickedOk)
END_MESSAGE_MAP()


// CAudioSelect ���b�Z�[�W �n���h��

void CAudioSelect::OnLbnDblclkList1()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	select();
}

void CAudioSelect::OnBnClickedOk()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	select();
	OnOK();
}

void CAudioSelect::select()
{
	int cnt=m_lb.GetCurSel();
	no=cnt;
	EndDialog(cnt);
}

BOOL CAudioSelect::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �����ɏ�������ǉ����Ă�������
	m_tooltip.Create(this);
	m_tooltip.Activate(TRUE);
	m_tooltip.AddTool(GetDlgItem(IDOK),_T("�����X�g���[�������肵�܂�"));
	m_tooltip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_tooltip.SendMessage(TTM_SETMAXTIPWIDTH, 0, 512);

	for(int i=0;i<no;i++){
		CString str;
		str.Format(_T("����%d:%s"),i+1, streamname[i]);
		m_lb.AddString(str);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}

BOOL CAudioSelect::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
		m_tooltip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}