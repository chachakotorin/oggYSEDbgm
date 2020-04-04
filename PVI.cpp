// PVI.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "ogg.h"
#include "PVI.h"


// CPVI �_�C�A���O

IMPLEMENT_DYNAMIC(CPVI, CDialog)

CPVI::CPVI(CWnd* pParent /*=NULL*/)
	: CDialog(CPVI::IDD, pParent)
{

}

CPVI::~CPVI()
{
}

void CPVI::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_pvi);
	DDX_Control(pDX, IDOK, m_ok);
}


BEGIN_MESSAGE_MAP(CPVI, CDialog)
	ON_BN_CLICKED(IDOK, &CPVI::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT1, &CPVI::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CPVI ���b�Z�[�W �n���h��

BOOL CPVI::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �����ɏ�������ǉ����Ă�������
	CString str = regload(_T(""));
	m_pvi.SetWindowText(str);
	return TRUE;  // return TRUE unless you set the focus to a control
	// ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}

void CPVI::OnBnClickedOk()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	OnOK();
	CString str;
	m_pvi.GetWindowText(str);
	regsave(_T(""),str);
}

CString CPVI::regload(CString key)
{
	HKEY  hKey;              // �L�[�̃n���h��
	DWORD dwDisposition;     // ��������
	LONG  lret;              // �֐��̖߂�l
	CString strData;	// �f�[�^���󂯎��o�b�t�@("DataName"�̒l)
	_TCHAR buf[20000];
	DWORD dwType=REG_SZ;		// �l�̎�ނ��󂯎��
	DWORD dwSize;		// �f�[�^�̃T�C�Y���󂯎��


	lret = RegCreateKeyEx(
		 HKEY_CURRENT_USER,		   // ���݃I�[�v�����Ă���L�[�܂��͒�`�ς݃L�[�̃n���h��
		 _T("Software\\Kobarin's Soft\\KbMIDI Player\\SearchPath"),                 // �T�u�L�[�̖��O��������������ւ̃|�C���^
		 0,                        // �\��p�����[�^
		 _T(""),                       // �L�[�̃N���X��������������ւ̃|�C���^
		 REG_OPTION_NON_VOLATILE,  // �I�v�V����
		 KEY_ALL_ACCESS,           // �Z�L�����e�B�̃A�N�Z�X�}�X�N
		 NULL,                     // �n���h���̎q�v���Z�X�ւ̌p���w��
		 &hKey,                    // �쐬���ꂽ�L�[�̃n���h�����󂯎��
		 &dwDisposition            // ��������
	);
	if(lret==ERROR_SUCCESS){
		RegQueryValueEx(hKey, _T("PVI"), NULL, &dwType, NULL, &dwSize);
		RegQueryValueEx(hKey, _T("PVI"), NULL, &dwType, (LPBYTE)buf, &dwSize);
		RegCloseKey(hKey);
		return buf;
	}else{
		return _T("");
	}
}

void CPVI::regsave(CString key, CString value)
{
	HKEY  hKey;              // �L�[�̃n���h��
	DWORD dwDisposition;     // ��������
	LONG  lret;              // �֐��̖߂�l
	CString strData;	// �f�[�^���󂯎��o�b�t�@("DataName"�̒l)
	DWORD dwType=REG_SZ;		// �l�̎�ނ��󂯎��
	DWORD dwSize;		// �f�[�^�̃T�C�Y���󂯎��


	lret = RegCreateKeyEx(
		 HKEY_CURRENT_USER,		   // ���݃I�[�v�����Ă���L�[�܂��͒�`�ς݃L�[�̃n���h��
		 _T("Software\\Kobarin's Soft\\KbMIDI Player\\SearchPath"),                 // �T�u�L�[�̖��O��������������ւ̃|�C���^
		 0,                        // �\��p�����[�^
		 _T(""),                       // �L�[�̃N���X��������������ւ̃|�C���^
		 REG_OPTION_NON_VOLATILE,  // �I�v�V����
		 KEY_ALL_ACCESS,           // �Z�L�����e�B�̃A�N�Z�X�}�X�N
		 NULL,                     // �n���h���̎q�v���Z�X�ւ̌p���w��
		 &hKey,                    // �쐬���ꂽ�L�[�̃n���h�����󂯎��
		 &dwDisposition            // ��������
	);
	if(lret==ERROR_SUCCESS){
		RegSetValueEx(
		  hKey,         // ���݃I�[�v�����Ă���L�[�̃n���h��
		  _T("PVI"),    // �l�́u���O�v��������������ւ̃|�C���^
		  0,            // �\��p�����[�^
		  REG_SZ,       // �l�́u��ށv(NULL�ŏI��镶�����REG_SZ�A32�r�b�g�l��REG_DWORD)
		  (CONST BYTE*)(LPCTSTR)value,  // �l�́u�f�[�^�v���������o�b�t�@�ւ̃|�C���^
#if UNICODE
		  value.GetLength()*2 + 2         // lpData�̃T�C�Y���w�肷��
#else
		  value.GetLength() + 1         // lpData�̃T�C�Y���w�肷��
#endif
		);
		RegCloseKey(hKey);
		return;
	}else{
		return;
	}
}
static int CALLBACK EditWordBreakProc( LPTSTR , int , int , int );

void CPVI::OnEnChangeEdit1()
{
	// TODO:  ���ꂪ RICHEDIT �R���g���[���̏ꍇ�A
	// �܂��ACDialog::OnInitDialog() �֐����I�[�o�[���C�h���āAOR ��Ԃ� ENM_CHANGE
	// �t���O���}�X�N�ɓ���āACRichEditCtrl().SetEventMask() ���Ăяo���Ȃ�����A
	// �R���g���[���́A���̒ʒm�𑗐M���܂���B

	// TODO:  �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����Ă��������B
    //CEdit * pEdit1 = (CEdit *)GetDlgItem(IDC_EDIT1);
    ::SendMessage(m_pvi.m_hWnd, EM_SETWORDBREAKPROC, 0, (LPARAM)EditWordBreakProc);
}

int CALLBACK EditWordBreakProc(LPTSTR lpch, int ichCurrent, int cch, int code)
{
    return (WB_ISDELIMITER == code) ? 0 : ichCurrent;
}
