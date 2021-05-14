/* Copyright (c) 2010 Xiph.Org Foundation, Skype Limited
Written by Jean-Marc Valin and Koen Vos */
/*
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

- Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.

- Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include "stdafx.h"
#include "opus\opus.h"
#include "opus\opusfile.h"

class IOggOpusDecoder
{
public:
	virtual BOOL  __fastcall Open(TCHAR *cszFileName, SOUNDINFO *pInfo) = 0;
	virtual void  __fastcall Close(void) = 0;
	virtual int   __fastcall SetPosition(DWORD dwPos) = 0;
	virtual DWORD __fastcall Render(BYTE *Buffer, DWORD dwSize) = 0;
	virtual ~IOggOpusDecoder(void) {};
};

class OggOpusDecoder : public IOggOpusDecoder
{
private:
	enum {
		NCH = 2,
		SAMPLE_RATE = 48000,
		BLOCK_ALIGN = sizeof(opus_int16) * NCH,
		OPUS_BLOCKSIZE = 5760
	};
	OggOpusFile   *m_pOpusFile;
	BYTE           m_DecodedBuffer[OUTPUT_BUFFER_SIZE*OUTPUT_BUFFER_NUM * 4];
	DWORD m_dwRemain, m_dwPointer;

public:
	BOOL __fastcall Open(TCHAR *cszFileName, SOUNDINFO *pInfo);
	void __fastcall Close(void);
	int __fastcall SetPosition(DWORD dwPos);
	DWORD __fastcall Render(BYTE *Buffer, DWORD dwSize);
	OggOpusDecoder(void);
	~OggOpusDecoder(void);
};

OggOpusDecoder::OggOpusDecoder(void)
{
	m_pOpusFile = NULL;
	m_dwRemain = m_dwPointer = 0;
}
//////////////////////////////////////////////////////////////////////////////
OggOpusDecoder::~OggOpusDecoder(void)
{
	if (m_pOpusFile) {
		op_free(m_pOpusFile);
	}
}

BOOL __fastcall OggOpusDecoder::Open( TCHAR *cszFileName, SOUNDINFO *pInfo)
{
	ZeroMemory(pInfo, sizeof(SOUNDINFO));
	int buffercount;
	int tagsize;
	DWORD samplerate = 0;
	BYTE  channels = 0;
	DWORD dwRead;
	unsigned long *seek_table = NULL;
	int seek_table_length = 0;
	int op_error = 0;
	int err;
	OpusTags *ot = NULL;
	
	m_pOpusFile = op_open_file(cszFileName, &err);
	

	ogg_int64_t totalSamples = op_pcm_total(m_pOpusFile, -1);

	pInfo->dwSamplesPerSec = 48000;
	pInfo->dwChannels = 2;
	pInfo->dwBitsPerSample = 16;
	pInfo->dwSeekable = 1;
	pInfo->dwUnitRender = 0;//いくつでも OK
	pInfo->dwLength = totalSamples;
	//リプレイゲインの処理は本体が行う
	op_set_gain_offset(m_pOpusFile, OP_ABSOLUTE_GAIN, 0);
	m_dwRemain = m_dwPointer = 0;
	return TRUE;
}

int __fastcall OggOpusDecoder::SetPosition(DWORD dwPos) {
	ogg_int64_t offset = OP_EINVAL;
	int ret = op_pcm_seek(m_pOpusFile, dwPos);
	if (ret == 0) {
		offset = op_pcm_tell(m_pOpusFile);
	}
	if (offset == OP_EINVAL) {
		ret = op_pcm_seek(m_pOpusFile, 0);
		if (ret == 0) {
			offset = op_pcm_tell(m_pOpusFile);
		}
	}
	m_dwRemain = m_dwPointer = 0;
	return offset;
}

DWORD __fastcall OggOpusDecoder::Render(BYTE *pBuffer, DWORD dwSizeSample)
{
	DWORD dwRetSample = 0;
	DWORD dwCopySample = m_dwRemain;
	if (dwCopySample) {
		if (dwCopySample > dwSizeSample) {
			dwCopySample = dwSizeSample;
		}
		memcpy(pBuffer, m_DecodedBuffer + m_dwPointer * BLOCK_ALIGN, dwCopySample * BLOCK_ALIGN);
		m_dwRemain -= dwCopySample;
		m_dwPointer += dwCopySample;
		dwRetSample += dwCopySample;
	}
	while (dwRetSample < dwSizeSample) {
		int ret = op_read_stereo(m_pOpusFile, (opus_int16*)m_DecodedBuffer, OPUS_BLOCKSIZE);
		if (ret <= 0) {//デコード終了
			break;
		}
		dwCopySample = ret;
		if (dwRetSample + dwCopySample > dwSizeSample) {
			dwCopySample = dwSizeSample - dwRetSample;
		}
		memcpy(pBuffer + dwRetSample * BLOCK_ALIGN, m_DecodedBuffer, dwCopySample * BLOCK_ALIGN);
		dwRetSample += dwCopySample;
		m_dwRemain = ret - dwCopySample;
		m_dwPointer = dwCopySample;
	}
	return dwRetSample;
}
void __fastcall OggOpusDecoder::Close()
{
	if (m_pOpusFile) {
		op_free(m_pOpusFile);
	}
}




class opus
{
public:
	static HKMP WINAPI Open(TCHAR *cszFileName, SOUNDINFO *pInfo)
	{
		IOggOpusDecoder *pOpus;
		OggOpusDecoder *pOpusDecoder = new OggOpusDecoder;
		DWORD dwCount = pOpusDecoder->Open(cszFileName, pInfo);
		if (dwCount) {
			pOpus = pOpusDecoder;
			return pOpus;
		}
		else {
			pOpusDecoder->Close();
		}
	}

	static void WINAPI Close(HKMP hKMP)
	{
		if (hKMP) {
			IOggOpusDecoder *pOpus = (IOggOpusDecoder*)pOpus;
			pOpus->Close();
			delete pOpus;
			hKMP = NULL;
		}
	}

	static DWORD WINAPI Render(HKMP hKMP, BYTE* Buffer, DWORD dwSize)
	{
		if (!hKMP)return 0;
		IOggOpusDecoder *pOpus = (IOggOpusDecoder*)hKMP;
		return pOpus->Render(Buffer, dwSize);
	}

	static DWORD WINAPI SetPosition(HKMP hKMP, DWORD dwPos)
	{
		if (!hKMP)return 0;
		IOggOpusDecoder *pOpus = (IOggOpusDecoder*)hKMP;
		return pOpus->SetPosition(dwPos);
	}
};