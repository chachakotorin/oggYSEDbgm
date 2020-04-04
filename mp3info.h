// Mp3Info.h: CMp3Info �N���X�̃C���^�[�t�F�C�X
//
//////////////////////////////////////////////////////////////////////
#ifndef _GLOBALCOMMAND_H
#define _GLOBALCOMMAND_H

#define sizeof_array(a) (sizeof(a)/sizeof(a[0]))

void mbsncpy2(unsigned char *dst,unsigned char *src,int c);
//DLL�̃o�[�W���������擾
BOOL GetDLLVersion(IN LPSTR szDLLFileName,
				   IN DWORD *pdwMajor,
				   IN DWORD *pdwMinor,
				   IN DWORD *pdwBuildNumber1,
				   IN DWORD *pdwBuildNumber2);

  //������Yen�̂Ƃ�TRUE
BOOL IsTailYenSign(char *szStr);

//������'\\'��ǉ�(����'\\'�̂Ƃ��͉������Ȃ�)
void AddTAilYenSigne(char *szStr);
void AddTAilYenSigne(CString &Str);

//LoadString�̃o�O�΍�(MSKB Q140452)
CString LoadResString(HINSTANCE hInstance,UINT uID);

//---------------------------------------------------------------------
//���r�b�O�G���f�B�A��->���g���G���f�B�A���̕ϊ�
DWORD ExtractI4(unsigned char buf[4]);
WORD ExtractI2(unsigned char buf[2]);

CString getFileNameExtName(CString &path);
CString getExtName(CString &path);
CString getPathName(CString &path);
CString getFileName(CString &path);

//////////////////////////////////////////////////////////////////////////////
//getFileName
//�t���p�X������t�@�C�������擾����
//////////////////////////////////////////////////////////////////////////////
/*
�����F	char *szPath	�t�@�C�������܂ރp�X���ւ̃|�C���^

�߂�l�Fchar * �t�@�C�����ւ̃|�C���^
�@�@�@�@�@�@�@�t�@�C�������܂܂Ȃ��Ƃ���""�ւ̃|�C���^
	[\],[/],[:]��������Ȃ������ꍇ�A�������t�@�C�����Ƃ݂Ȃ��Ă��̂܂ܕԂ�
*/
const char *getFileName(const char *szPath);

//////////////////////////////////////////////////////////////////////////////
//getExtName
//�t���p�X������g���q���擾����
//////////////////////////////////////////////////////////////////////////////
/*
�����F	char *szPath	�g���q���܂ރp�X���ւ̃|�C���^

�߂�l�Fchar * �g���q�ւ̃|�C���^
�@�@�@�@�@�@�@�g���q���܂܂Ȃ��Ƃ���""�ւ̃|�C���^
*/
const char *getExtName(const char *szPath);

//�Q�o�C�g������̐؂�̂������������擾
long check2ByteLength(const char *szTag,long lLimit);

//�V�X�e���G���[���b�Z�[�W�{�b�N�X��\��
void sysError(HWND hWnd,char *mes = "Error");
void errMessageBox(HWND hWnd,DWORD dwErrorCode,char *mes = "Error");

//////////////////////////////////////////////////////////////////////////////
//cutFileName
//�p�X������t�@�C��������菜��
//////////////////////////////////////////////////////////////////////////////
/*
�����F	char *szPath	�t�@�C�������܂ރp�X���ւ̃|�C���^
			�i���s��A�p�X������t�@�C�������؂藣�����j
�߂�l�F�Ȃ�
*/
void cutFileName(char *szPath);

//////////////////////////////////////////////////////////////////////////////
//cutExtName
//�t�@�C��������g���q����菜��
//////////////////////////////////////////////////////////////////////////////
/*
�����F	char *szFileName	�t�@�C�����ւ̃|�C���^
			�i���s��A�t�@�C��������g���q���؂藣�����j
�߂�l�F�Ȃ�
*/
void cutExtName(char *szFileName);

//������src���w�蕶��c��n�������Ƃɋ�؂�
CString divString(char *src,char c,int n);



#endif //_GLOBALCOMMAND_H


#if !defined(AFX_MP3INFO_H__0B43E243_8C43_45E9_A96A_F793478F30CC__INCLUDED_)
#define AFX_MP3INFO_H__0B43E243_8C43_45E9_A96A_F793478F30CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable:4786)
#include <list>
using namespace std;

class CMp3Info  
{
private:
#pragma pack(1)
	typedef struct tFRAMEINFO
	{
		DWORD dwPtr;
		DWORD dwSize;
	}FRAMEINFO;

	typedef struct tMPEGINFO
	{
		int lsf;
		int mpeg25;
		int lay;
		int sampling_frequency;
		int error_protection;
		int bitrate_index;
		int padding;
		int extension;
		int mode;
		int mode_ext;
		int copyright;
		int original;
		int emphasis;
		int stereo;
		unsigned long bps;
		int framesize;
		unsigned long msec;
		unsigned long size;
		unsigned long flmnum;
		BOOL bVbr;
	}MPEGINFO;

	typedef struct _VBRI
	{
		char magic[4];
		unsigned short version;
		unsigned short delay;
		unsigned short quality;
		unsigned long streamBytes;
		unsigned long streamFrames;
		unsigned short tableSize;
		unsigned short tableScale; 
		unsigned short entryBytes;
		unsigned short entryFrames;
	}VBRI;
#pragma pack()

public:
	CMp3Info();
	virtual ~CMp3Info();
	BOOL Release();
	BOOL Load(const TCHAR *szFileName,BOOL bVbrScan = FALSE);

	CString GetFormatString(){return m_strFormat;};
	CString GetTimeString(){return m_strTime;};
	const unsigned long GetMSec();
	BYTE toc[100];
	int filesize;

	//list<FRAMEINFO> m_listFrame;
	MPEGINFO m_mpegInfo;

	const BOOL IsVbr();
	const CString GetMpeg();
	const long GetLayers();
	const long GetBps();
	const long GetFreqs();
	const CString GetModes();
	const unsigned long GetFlmNum();
	CString m_strFormat;
	CString m_strTime;

};

#endif // !defined(AFX_MP3INFO_H__0B43E243_8C43_45E9_A96A_F793478F30CC__INCLUDED_)
