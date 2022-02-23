// stdafx.h : �W���̃V�X�e�� �C���N���[�h �t�@�C���̃C���N���[�h �t�@�C���A�܂���
// �Q�Ɖ񐔂������A�����܂�ύX����Ȃ��A�v���W�F�N�g��p�̃C���N���[�h �t�@�C��
// ���L�q���܂��B
#pragma once
#pragma warning( disable : 4142 4091 )
#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Windows �w�b�_�[����g�p����Ă��Ȃ����������O���܂��B
#endif
#define DIRECT3D_VERSION 0x900
#define DIRECTSOUND_VERSION 0x0900
#ifdef VLD_FORCE_ENABLE
//#include "vld.h"
#endif
#include <SDKDDKVer.h>
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // �ꕔ�� CString �R���X�g���N�^�[�͖����I�ł��B

// ��ʓI�Ŗ������Ă����S�� MFC �̌x�����b�Z�[�W�̈ꕔ�̔�\�����������܂��B
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC �̃R�A����ѕW���R���|�[�l���g
#include <afxext.h>         // MFC �̊g������

//#include <afxdisp.h>        // MFC �I�[�g���[�V���� �N���X



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �R���� �R���g���[�� �T�|�[�g
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �R���� �R���g���[�� �T�|�[�g
#endif // _AFX_NO_AFXCMN_SUPPORT

#pragma warning(disable : 4995)

#define _AFX_DISABLE_DEPRECATED
#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif
typedef double REFTIME;
#include "yaneCriticalSection.h"
/*
typedef PUINT DWORD_PTR
#include	<d3d8.h>
#include	<d3dx8.h>
#include <dxerr8.h>
#include <dmusici.h>    // DirectAudio���g�p�\�ɂ���
*/

#include "kmp_pi.h"
#include "dshow.h"

#include <mmdeviceapi.h>
#include <endpointvolume.h>

struct playlistdata0{
	TCHAR name[1024];
	TCHAR art[1024];
	TCHAR alb[1024];
	TCHAR fol[1024];
	int sub;
	TCHAR game[256];
	int loop1;
	int loop2;
	int ret2;
	int icon;
	int time;
};

struct save{
	TCHAR ysf[1024];
	TCHAR ys6[1024];
	TCHAR ed6fc[1024];
	TCHAR ed6sc[1024];
	int douga;
	int supe;
	int supe2;

	int random;
	int kaisuu;
	int gameflg[4];

	int xx,yy;
	int gx,gy;

	TCHAR yso[1024];
	int gameflg2;

	TCHAR ed6tc[1024];
	int gameflg3;

	TCHAR zweiii[1024];
	int gameflg4;

	int dsvol;
	int render;

	TCHAR ysc[1024];
	int gameflg5;
	int gameflg6;

	TCHAR xa[1024];
	int gameflg7;

	TCHAR ys12[1024];
	int gameflg8;
	int gameflg9;

	TCHAR sor[1024];
	int gameflg10;
	TCHAR ys122[1024];

	TCHAR zwei[1024];
	int gameflg11;

	TCHAR gurumin[1024];
	int gameflg12;

	TCHAR dino[1024];
	int gameflg13;

	RECT p;

	TCHAR br4[1024];
	int gameflg14;

	TCHAR ed3[1024];
	int gameflg15;

	TCHAR ed4[1024];
	int gameflg16;

	TCHAR ed5[1024];
	int gameflg17;

	TCHAR tuki[1024];
	TCHAR nishi[1024];
	TCHAR arc[1024];
	TCHAR san1[1024];
	TCHAR san2[1024];

	int fs;
	int evr;
	int con;
	int aero;
	int pl;
	int ffd;
	int vob;
	int haali;
	int spc;
	int mp3;
	int kpivol;

	TCHAR font1[1024];
	TCHAR font2[1024];

	int mp3orig;

	int audiost;

	int savecheck;
	int savecheck_mp3;
	int savecheck_dshow;

	int bit24;

	int m4a;

	int kakuVol;
	int kakuVal;

	int saveloop;
	int saverenzoku;

	int bit32;

	int ms;
	int ms2;

	GUID soundguid;
	int soundcur;

	TCHAR zero[1024];

	DWORD samples;

	double wup;
};


char *b64_decode(char *s, int size,int &len);

int b64_ctoi(char c);

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B
