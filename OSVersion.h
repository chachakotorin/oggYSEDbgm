#pragma once
#include "afxwin.h"

class COSVersion
{
public:
	static BOOL IsWow64();
	CString GetVersionString();
	void GetVersionInfo(OSVERSIONINFOEX& in, DWORD& edition, BOOL& bit);
	
	OSVERSIONINFOEX in;
	DWORD edition;

};