#pragma once
#include "codec/neaacdec.h"
#include "codec/mp4ff.h"
#include <limits.h>
#include <stdlib.h>
extern "C" {
#include "codec/ALACDecoder.h"
#include "codec/ALACBitUtilities.h"
#include "codec/EndianPortable.h"

}



uint32_t mkps = 0;
// M4a
static const long g_aacFreq[] = {
	96000,88200,64000,48000,44100,32000,
	24000,22050,16000,12000,11025, 8000,
	-1,   -1,   -1,   -1
};

//ADTS_HEADER構造体
typedef struct tagADTS_HEADER {
	int		iProfile;	//音質と圧縮率 0:main,01:LC,2:SSR,3:(予約)
	DWORD	sampleRate;	//周波数
	WORD	nChannel;	//チャンネル数
	DWORD	nFrameSize; //AACフレーム長(バイト、ヘッダ込み）
	DWORD	nFullness;	//ADTSバッファ残量 0x7FF VBR
}ADTS_HEADER;


typedef struct {
	int version;
	int channels;
	int sampling_rate;
	int bitrate;
	int length;
	int object_type;
	int headertype;
} faadAACInfo;

//faad の common/faad/aacinfo.c を改変
//get_AAC_format:   第1引数を char* から FILE* に変更
//read_ADIF_header: 第1引数を FILE_STREAM* から FILE* に変更
//read_ADTS_header: 第1引数を FILE_STREAM* から FILE* に変更
static int get_AAC_format(FILE *file, faadAACInfo *info,
	unsigned long **seek_table, int *seek_table_len,
	int no_seek_table);

static int read_ADIF_header(FILE *file, faadAACInfo *info);
static int read_ADTS_header(FILE *file, faadAACInfo *info,
	unsigned long **seek_table, int *seek_table_len,
	int tagsize, int no_seek_table);
static int StringComp(char const *str1, char const *str2, unsigned long len) { return memcmp(str1, str2, len); }

#define ADIF_MAX_SIZE 30 /* Should be enough */
#define ADTS_MAX_SIZE 10 /* Should be enough */

static int sample_rates[] = { 96000,88200,64000,48000,44100,32000,24000,22050,16000,12000,11025,8000 };

int read_ADIF_header(FILE *file, faadAACInfo *info)
{
	int bitstream;
	unsigned char buffer[ADIF_MAX_SIZE];
	int skip_size = 0;
	int sf_idx;

	/* Get ADIF header data */
	info->headertype = 1;

	if (fread(buffer, 1, ADIF_MAX_SIZE, file) < ADIF_MAX_SIZE)
		return -1;

	/* copyright string */
	if (buffer[0] & 0x80)
		skip_size += 9; /* skip 9 bytes */

	bitstream = buffer[0 + skip_size] & 0x10;
	info->bitrate = ((unsigned int)(buffer[0 + skip_size] & 0x0F) << 19) |
		((unsigned int)buffer[1 + skip_size] << 11) |
		((unsigned int)buffer[2 + skip_size] << 3) |
		((unsigned int)buffer[3 + skip_size] & 0xE0);

	if (bitstream == 0)
	{
		info->object_type = ((buffer[6 + skip_size] & 0x01) << 1) | ((buffer[7 + skip_size] & 0x80) >> 7);
		sf_idx = (buffer[7 + skip_size] & 0x78) >> 3;
	}
	else {
		info->object_type = (buffer[4 + skip_size] & 0x18) >> 3;
		sf_idx = ((buffer[4 + skip_size] & 0x07) << 1) | ((buffer[5 + skip_size] & 0x80) >> 7);
	}
	info->sampling_rate = sample_rates[sf_idx];

	return 0;
}

int read_ADTS_header(FILE *file, faadAACInfo *info,
	unsigned long **seek_table, int *seek_table_len,
	int tagsize, int no_seek_table)
{
	/* Get ADTS header data */
	unsigned char buffer[ADTS_MAX_SIZE];
	int frames, framesinsec = 0, t_framelength = 0, frame_length, sr_idx, ID;
	int second = 0, pos;
	float frames_per_sec = 0;
	unsigned long bytes;
	unsigned long *tmp_seek_table = NULL;

	info->headertype = 2;

	/* Read all frames to ensure correct time and bitrate */
	for (frames = 0; /* */; frames++, framesinsec++)
	{
		pos = ftell(file);

		/* 12 bit SYNCWORD */
		bytes = fread(buffer, 1, ADTS_MAX_SIZE, file);

		if (bytes != ADTS_MAX_SIZE)
		{
			/* Bail out if no syncword found */
			break;
		}

		/* check syncword */
		if (!((buffer[0] == 0xFF) && ((buffer[1] & 0xF6) == 0xF0)))
			break;

		if (!frames)
		{
			/* fixed ADTS header is the same for every frame, so we read it only once */
			/* Syncword found, proceed to read in the fixed ADTS header */
			ID = buffer[1] & 0x08;
			info->object_type = (buffer[2] & 0xC0) >> 6;
			sr_idx = (buffer[2] & 0x3C) >> 2;
			info->channels = ((buffer[2] & 0x01) << 2) | ((buffer[3] & 0xC0) >> 6);

			frames_per_sec = sample_rates[sr_idx] / 1024.f;
		}

		/* ...and the variable ADTS header */
		if (ID == 0) {
			info->version = 4;
		}
		else { /* MPEG-2 */
			info->version = 2;
		}
		frame_length = ((((unsigned int)buffer[3] & 0x3)) << 11)
			| (((unsigned int)buffer[4]) << 3) | (buffer[5] >> 5);

		t_framelength += frame_length;

		//if(!file->http)
		if (1)
		{
			if (framesinsec == 43)
				framesinsec = 0;

			if (framesinsec == 0 && seek_table_len)
			{
				tmp_seek_table = (unsigned long *)realloc(tmp_seek_table, (second + 1) * sizeof(unsigned long));
				tmp_seek_table[second] = pos;
			}
			if (framesinsec == 0)
				second++;
		}

		/* NOTE: While simply skipping ahead by reading may seem to be more work than seeking,
		it is actually much faster, and keeps compatibility with streaming */
		fseek(file, frame_length - ADTS_MAX_SIZE, SEEK_CUR);
		/*for(i=0; i < frame_length - ADTS_MAX_SIZE; i++)
		{
		if(read_byte_filestream(file) < 0)
		break;
		}*/
	}

	if (seek_table_len)
	{
		*seek_table_len = second;
		*seek_table = tmp_seek_table;
	}

	info->sampling_rate = sample_rates[sr_idx];
	info->bitrate = (int)(((t_framelength / frames) * (info->sampling_rate / 1024.0)) + 0.5) * 8;

#if 0
	if (file->http)
	{
		/* Since we only use 5 seconds of aac data to get a rough bitrate, we must use a different
		method of calculating the overall length */
		if (filelength_filestream(file))
		{
			info->length = (int)((filelength_filestream(file) / (((info->bitrate * 8) / 1024) * 16)) * 1000);
		}
		else
		{
			/* Since the server didnt tell us how long the file is,
			we have no way of determining length */
			info->length = 0;
		}
	}
	else
#endif
	{
		//info->length = (int)((float)(frames/frames_per_sec))*1000;
		info->length = MulDiv(frames, 1000, (int)frames_per_sec);
	}

	return 0;
}

int get_AAC_format(FILE *file, faadAACInfo *info,
	unsigned long **seek_table, int *seek_table_len,
	int no_seek_table)
{
	unsigned long tagsize;
	//    FILE *file;
	char buffer[10];
	unsigned long file_len;
	unsigned char adxx_id[5];
	//unsigned long tmp;

	memset(info, 0, sizeof(faadAACInfo));

	//file = open_filestream(filename);

	//file_len = filelength_filestream(file);
	file_len = fseek(file, 0, SEEK_END);
	fseek(file, 0, SEEK_SET);
	/* Skip the tag, if it's there */
	//tmp = read_buffer_filestream(file, buffer, 10);
	if (fread(buffer, 1, 10, file) != 10) {
		return -1;
	}
	if (StringComp(buffer, "ID3", 3) == 0)
	{
		//unsigned int i;

		/* high bit is not used */
		tagsize = (buffer[6] << 21) | (buffer[7] << 14) |
			(buffer[8] << 7) | (buffer[9] << 0);

		/*for(i=0; i < tagsize; i++)
		if(read_byte_filestream(file) < 0)
		return -1;
		*/
		fseek(file, tagsize, SEEK_CUR);
		tagsize += 10;
	}
	else
	{
		tagsize = 0;
		/* Simple hack to reset to the beginning */
		//		file->buffer_offset = 0;
		//		file->file_offset = 0;
		fseek(file, 0, SEEK_SET);
	}

	if (file_len)
		file_len -= tagsize;

	//    tmp = read_buffer_filestream(file, adxx_id, 2);
	fread(adxx_id, 1, 2, file);

	adxx_id[5 - 1] = 0;
	info->length = 0;

	// Determine the header type of the file, check the first two bytes
	if (StringComp((const char*)adxx_id, "AD", 2) == 0)
	{
		// We think its an ADIF header, but check the rest just to make sure
		//tmp = read_buffer_filestream(file, adxx_id + 2, 2);
		fread(adxx_id + 2, 1, 2, file);
		if (StringComp((const char*)adxx_id, "ADIF", 4) == 0)
		{
			read_ADIF_header(file, info);
		}
	}
	else
	{
		/* No ADIF, check for ADTS header */
		if ((adxx_id[0] == 0xFF) && ((adxx_id[1] & 0xF6) == 0xF0))
		{
			/* ADTS  header located */
			/* Since this routine must work for streams, we can't use the seek function to go backwards, thus
			we have to use a quick hack as seen below to go back where we need to. */

			/*if(file->buffer_offset >= 2)
			{
			// simple seeking hack, though not really safe, the probability of it causing a problem is low.
			file->buffer_offset -= 2;
			file->file_offset -= 2;
			}
			*/
			fseek(file, -2, SEEK_CUR);
			read_ADTS_header(file, info, seek_table, seek_table_len, tagsize,
				no_seek_table);
		}
		else
		{
			/* Unknown/headerless AAC file, assume format: */
			info->version = 2;
			info->bitrate = 128000;
			info->sampling_rate = 44100;
			info->channels = 2;
			info->headertype = 0;
			info->object_type = 1;
		}
	}

	//close_filestream(file);
	//fclose(file);//クローズしてはいけない
	return 0;
}



static int id3v2_tag(unsigned char *buffer)
{
	if (memcmp(buffer, "ID3", 3) == 0) {
		unsigned long tagsize;
		tagsize = (buffer[6] << 21) | (buffer[7] << 14) |
			(buffer[8] << 7) | (buffer[9] << 0);
		tagsize += 10;
		return tagsize;
	}
	else {
		return 0;
	}
}

struct KPI_MEDIAINFO
{
	enum {
		SEEK_DISABLE = 0,    //シーク不可
		SEEK_FLAGS_SAMPLE = 0x01, //サンプル単位の高精度なシークに対応
		SEEK_FLAGS_ACCURATE = 0x02, //歌詞との同期に支障がない程度に正確なシーク対応
		SEEK_FLAGS_ROUGH = 0x04, //精度は悪いがシーク対応
		FORMAT_PCM = 0,    //通常の PCM
		FORMAT_DOP = 1,    //最終出力段までデータの加工をしない(リプレイゲインやフェードアウトの処理もしない)
		FORMAT_PLAYER = 2  //演奏専用(IKpiPlayer 用)
	};
	DWORD  cb;             //=sizeof(KPI_MEDIAINFO)
	DWORD  dwNumber;       //曲番号(1ベース)、曲番号0は存在しない(エラーとして扱われる)
						   //Select で選曲した番号にすること
	DWORD  dwCount;        //曲の数、曲数 0 は存在しない(エラーとして扱われる)
	DWORD  dwFormatType;   //FORMAT_PCM or FORMAT_DOP(DOP の場合、最終出力段までデータの加工をしないことが保証される)
	DWORD  dwSampleRate;   //再生周波数(44100, 48000 etc...)
	INT32  nBitsPerSample; //量子化ビット数(8bit, 16bit, 24bit, 32bit, -32bit, -64bit)
						   //float の場合、値を負にする(32bit float => -32, 64bit float => -64)
	DWORD  dwChannels;     //チャネル数(1 or 2)
	DWORD  dwSpeakerConfig;//0(マルチチャンネル対応のために予約)
	UINT64 qwLength;       //１ループ目(イントロ＋ループ１回)の曲の長さ(単位は100ナノ秒)
	UINT64 qwLoop;         //２ループ目以降の１ループの長さ(単位は100ナノ秒)
	UINT64 qwFadeOut;      //フェードアウト時間(単位は100ナノ秒)(フェードアウトしない場合は 0, 本体の設定に従う場合は-1)
						   //(0 でも -1 でもない場合はデータの推奨値)
	DWORD  dwLoopCount;    //ループ回数(ループ曲でない or 本体の設定に従う場合は0、0 以外の場合はデータの推奨値)
	DWORD  dwUnitSample;   //Render の第2引数(dwSizeSample) に渡すべき数(いくつでも良い場合は 0)
						   //なるべく 0 にすること(実装が面倒なら 0 以外でも OK)
						   //16384 より大きな値にしてはいけない(その場合は頑張って実装すること)
	DWORD  dwSeekableFlags;//Seek への対応フラグ
						   //シークに対応していない場合は 0
						   //サンプル単位の正確なシークに対応する場合は SEEK_FLAGS_SAMPLE をセット
						   //歌詞同期可能な精度のシークに対応する場合は SEEK_FLAGS_ACCURATE をセット
						   //精度は悪いがシークに対応する場合は SEEK_FLAGS_ROUGH をセット
						   //シークの精度: SAMPLE > ACCURATE > ROUGH
						   //シークの速度: ROUGH > ACCURATE > SAMPLE
						   //(全部対応する場合は dwSeekableFlag = SEEK_FLAGS_SAMPLE | SEEK_FLAGS_ACCURATE | SEEK_FLAGS_ROUGH となる)
	DWORD  dwVideoWidth;   //映像の横幅(100%時)(映像情報を持たない場合は 0)
	DWORD  dwVideoHeight;  //映像の高さ(100%時)(映像情報を持たない場合は 0)
	DWORD  dwReserved[6];  //予約(0 にすること)
						   /*
						   ・再生周波数、ビット数、チャネル数、ループ回数、フェードアウト時間要求
						   IKpiDecoderModule::Open の cpRequest の各値が 0 以外の場合は、可能なら
						   その形式で、不可能ならそれに最も近い形式でファイルを開くこと。
						   値が 0 の場合はプラグインのデフォルト値で開くこと

						   qwLength, qwLoop, qwFadeOut の時間の単位は 100ナノ秒=(1/10000ミリ秒)
						   例えば qwLength が 1秒 なら 1秒=1000ms=1000*10000 となる

						   ループ１回あたりの演奏時間がわからず、無限ループする場合(Render の戻り値が
						   いつまで経っても dwUnitSample より小さくならない可能性がある場合)は
						   qwLoop == (UINT64)-1

						   演奏時間がわかっていてループしない曲の場合(最も一般的なケース):
						   qwLength == 曲の長さ, qwLoop == 0
						   このとき qwFadeOut と dwLoopCount の値は無視される

						   演奏時間(イントロ+ループ1回)とループ時間がともに分かる曲の場合：
						   実際の演奏時間 = qwLength + (dwLoopCount-1)*qwLoop + qwFadeOut
						   ただし、
						   dwLoopCount == 0 の場合、dwLoopCount は本体の設定値に従う
						   qwFadeOut == -1 の場合、qwFadeOut は本体の設定値に従う

						   演奏時間はわかるが、ループ時間が分からない(無限ループするかもしれない)場合
						   qwLength == 演奏時間(=無音検出を開始する時間),
						   qwLoop == -1
						   qwFadeOut == 0 or -1 or (データから得た値)
						   dwLoopCount == 無視
						   このとき、
						   ・プレイヤーの設定が「単曲リピート」以外の再生モードの場合は
						   qwLength 時間だけ再生後、qwFadeOut だけフェードアウトして演奏を打ち切る
						   実際の演奏時間 = qwLength + qwFadeOut
						   ・演奏モードが「単曲リピート」の場合は qwLength 時間だけ再生後、
						   無音が検出されるまで無限ループ再生する

						   演奏時間はわからないが、いつかは演奏終了する場合
						   (無音検出による演奏の打ち切りが不要な場合):
						   qwLength == -1, qwLoop == 0, qwFadeOut == 0(無視)
						   この場合、プレイヤーが表示する曲の長さは ???? となる

						   演奏時間がわからず、いつ演奏終了するかもわからない場合：
						   (無音検出による演奏打ち切りが必要な場合):
						   qwLength == -1, qwLoop == -1
						   このとき、
						   ・プレイヤーが表示する曲の長さは
						   デフォルトの曲の長さ(DefaultLength) + デフォルトのフェードアウト時間(DefaultFade)になる
						   ・プレイヤーの演奏モードが「単曲リピート」でない場合は DefaultLength だけ
						   再生後、DefaultFade 時間かけてフェードアウトして演奏を打ち切る
						   ・演奏モードが「単曲リピート」の場合は DefaultLength だけ再生後、
						   無音が検出されるまで無限ループ再生する

						   最終的な曲の長さ(qwTotalLength)は
						   1. qwTotalLength = qwLength + (dwLoopCount-1)*qwLoop + qwFadeOut (100ns単位)
						   2. ↑をサンプル単位に変換(小数点以下切り捨て)
						   qwTotalSample = kpi_100nsToSample(qwTotalLength, dwSampleRate);
						   3. ↑を100ns 単位に変換(小数点以下切り捨て)
						   qwTotalLength = kpi_SampleTo100ns(qwTotalSample, dwSampleRate);
						   この時点で 1. とは異なった値になるが、本当の演奏時間と同じになる
						   4. 表示は↑をミリ秒単位に変換(小数点以下四捨五入)
						   qwTotalLengthMs = (qwTotalLength + 5000) / 10000;
						   のような手順で算出する。

						   演奏時間のプレイリストへの保存もこの手順でミリ秒単位で算出した値を記録する。
						   したがって、ライブラリが返す曲の長さがサンプル単位の場合 qwLength の算出時に
						   小数点以下切り捨て/四捨五入のどちらを選んでも曲の長さは同じとなる。

						   ループ曲(qwLoop != 0) の演奏終了の処理は本体が行うため、ループ曲の場合は
						   Render の戻り値を常に第2引数(dwSizeSample)と同じとなるようにすること。
						   デコードライブラリの仕様上それが不可能な場合は、
						   IKpiDecoderModule::Open の第1引数(cpRequest)の dwLoopCount/qwFadeOut
						   の値に従った長さだけ再生後、プラグイン側で演奏終了の処理を行うこと
						   その場合、qwLoop の値は 0 にしなければならない(0以外だと本体がループ曲と
						   判断して演奏終了処理を行おうとするため)
						   */
};


class IKbAacDecoder
{
public:
	virtual BOOL  __fastcall Open(const _TCHAR *cszFileName, SOUNDINFO *pInfo) = 0;
	virtual void  __fastcall Close(void) = 0;
	virtual int   __fastcall SetPosition(DWORD dwPos) = 0;
	virtual DWORD __fastcall Render(BYTE *Buffer, DWORD dwSize) = 0;
	virtual ~IKbAacDecoder(void) {};
};

class KbAacDecoder : public IKbAacDecoder
{
private:
	void  *m_hDecoder;
	FILE  *m_pFile;
	unsigned long *m_seek_table;
	int   m_seek_table_length;
	BYTE  m_buffer[FAAD_MIN_STREAMSIZE * 2];
	int   m_buffercount;
	BOOL  m_bDecodeDone;
	DWORD m_dwRemain;
	BYTE *m_pSample;
public:
	BOOL __fastcall Open(const _TCHAR *cszFileName, SOUNDINFO *pInfo);
	void __fastcall Close(void);
	int __fastcall SetPosition(DWORD dwPos);
	DWORD __fastcall Render(BYTE *Buffer, DWORD dwSize);
	KbAacDecoder(void);
	~KbAacDecoder(void);
};

KbAacDecoder::KbAacDecoder(void)
{
	m_hDecoder = NULL;
	m_pFile = NULL;
	m_seek_table = NULL;
	m_seek_table_length = 0;
	m_buffercount = 0;
	m_bDecodeDone = TRUE;
	m_pSample = NULL;
	m_dwRemain = 0;
}

KbAacDecoder::~KbAacDecoder(void)
{
	Close();
}

BOOL __fastcall KbAacDecoder::Open(const _TCHAR *cszFileName, SOUNDINFO *pInfo)
{
	ZeroMemory(pInfo, sizeof(SOUNDINFO));
	int buffercount;
	int tagsize;
	DWORD samplerate = 0;
	BYTE  channels = 0;
	DWORD dwRead;
	unsigned long *seek_table = NULL;
	int seek_table_length = 0;

#if UNICODE	
	m_pFile = _wfopen(cszFileName, _T("rb"));
#else
	m_pFile = fopen(cszFileName, _T("rb"));
#endif
	if (!m_pFile) {
		return FALSE;
	}
	dwRead = fread(m_buffer, 1, FAAD_MIN_STREAMSIZE * 2, m_pFile);
	if (dwRead != FAAD_MIN_STREAMSIZE * 2) {
		Close();
		return FALSE;
	}
	//id3v2 タグを飛ばす
	tagsize = id3v2_tag(m_buffer);
	if (tagsize) {
		fseek(m_pFile, tagsize, SEEK_SET);
		if (ftell(m_pFile) != tagsize) {
			Close();
			return FALSE;
		}
		dwRead = fread(m_buffer, 1, FAAD_MIN_STREAMSIZE * 2, m_pFile);
		if (dwRead != FAAD_MIN_STREAMSIZE * 2) {
			Close();
			return FALSE;
		}
	}
	m_hDecoder = NeAACDecOpen();
	if ((buffercount = NeAACDecInit(m_hDecoder, m_buffer, sizeof(m_buffer), &samplerate, &channels)) < 0) {
		Close();
		return FALSE;
	}
	if (buffercount > 0) {
		int k;
		for (k = 0; k < (FAAD_MIN_STREAMSIZE * 2 - buffercount); k++) {
			m_buffer[k] = m_buffer[k + buffercount];
		}
		if (fread(m_buffer + (FAAD_MIN_STREAMSIZE * 2) - buffercount, 1, buffercount, m_pFile) != buffercount) {
			Close();
			return FALSE;
		}
		buffercount = 0;
	}
	faadAACInfo file_info = { 0 };

	DWORD dwCurPos = ftell(m_pFile);//ファイルポインタを保存
	if (get_AAC_format(m_pFile, &file_info, &seek_table, &seek_table_length, 0) < 0) {
		Close();
		return FALSE;
	}
	fseek(m_pFile, dwCurPos, SEEK_SET);//元の位置に戻す
								
	pInfo->dwSamplesPerSec = samplerate;
	pInfo->dwChannels = channels;
	pInfo->dwBitsPerSample = 16;
	pInfo->dwSeekable = file_info.headertype == 2;
	pInfo->dwUnitRender = 0;//いくつでも OK
	pInfo->dwLength = file_info.length;
	mkps = 0;
	if (pInfo->dwLength == 0 && file_info.bitrate != 0) {
		//曲の長さがわからない場合はビットレートとファイルサイズを元に
		//近似値を計算する
		dwCurPos = ftell(m_pFile);
		fseek(m_pFile, 0, SEEK_END);
		DWORD dwFileSize = ftell(m_pFile);
		fseek(m_pFile, dwCurPos, SEEK_SET);
		pInfo->dwLength = (DWORD)(1000.0 * ((double)dwFileSize) / (file_info.bitrate / 8));
	}
	pInfo->dwReserved1 = 0;
	pInfo->dwReserved2 = 0;
	m_buffercount = buffercount;
	m_bDecodeDone = FALSE;
	m_seek_table = seek_table;
	m_seek_table_length = seek_table_length;
	return TRUE;
}
void __fastcall KbAacDecoder::Close(void)
{
	if (m_hDecoder) {
		NeAACDecClose(m_hDecoder);
		m_hDecoder = NULL;
	}
	if (m_seek_table) {
		free(m_seek_table);
		m_seek_table = NULL;
	}
	if (m_pFile) {
		fclose(m_pFile);
	}
	m_seek_table_length = 0;
	m_buffercount = 0;
	m_pSample = NULL;
	m_dwRemain = 0;
}

int __fastcall KbAacDecoder::SetPosition(DWORD dwPos)
{
	if (dwPos == 0 && !m_pSample) {//既に先頭位置にいる
		return 0;
	}
	m_bDecodeDone = TRUE;
	if (!m_hDecoder) {
		return 0;
	}
	DWORD dwOffsetSec = 0xFFFFFFFF;
	NeAACDecClose(m_hDecoder);
	m_hDecoder = NeAACDecOpen();

	if (m_seek_table && m_seek_table_length > 0) {//シーク可能
		dwOffsetSec = dwPos / 1000;
		if (dwOffsetSec >= m_seek_table_length) {
			dwOffsetSec = m_seek_table_length - 1;
		}
		fseek(m_pFile, m_seek_table[dwOffsetSec], SEEK_SET);
		if (ftell(m_pFile) != m_seek_table[dwOffsetSec]) {
			return 0;
		}
	}
	else {//シーク不可。先頭位置に戻す
		fseek(m_pFile, 0, SEEK_SET);
		dwPos = 0;
	}
	m_buffercount = 0;
	DWORD dwRead = fread(m_buffer, 1, FAAD_MIN_STREAMSIZE * 2, m_pFile);
	if (dwRead != FAAD_MIN_STREAMSIZE * 2) {
		return 0;
	}
	//id3v2 タグを飛ばす
	int tagsize = id3v2_tag(m_buffer);
	if (tagsize) {
		fseek(m_pFile, tagsize, SEEK_SET);
		if (ftell(m_pFile) != tagsize) {
			Close();
			return FALSE;
		}
		dwRead = fread(m_buffer, 1, FAAD_MIN_STREAMSIZE * 2, m_pFile);
		if (dwRead != FAAD_MIN_STREAMSIZE * 2) {
			return 0;
		}
	}
	DWORD samplerate = 0;
	BYTE  channels = 0;
	int buffercount;
	if ((buffercount = NeAACDecInit(m_hDecoder, m_buffer, FAAD_MIN_STREAMSIZE * 2, &samplerate, &channels)) < 0) {
		return 0;
	}
	if (buffercount > 0) {
		int k;
		for (k = 0; k < (FAAD_MIN_STREAMSIZE * 2 - buffercount); k++) {
			m_buffer[k] = m_buffer[k + buffercount];
		}
		if (fread(m_buffer + (FAAD_MIN_STREAMSIZE * 2) - buffercount, 1, buffercount, m_pFile) != buffercount) {
			return 0;
		}
	}
	m_buffercount = 0;
	m_bDecodeDone = FALSE;
	m_pSample = NULL;
	m_dwRemain = 0;
	if (dwOffsetSec != 0xFFFFFFFF) {
		//足りない分は最大で１秒だけ空読み
		DWORD dwDeltaMS = dwPos - dwOffsetSec * 1000;
		if (dwDeltaMS > 1000) {
			dwDeltaMS = 1000;//seektable が正常なら実行されないはず
		}
		DWORD dwDeltaSample = MulDiv(dwDeltaMS, samplerate, 1000);
		DWORD dwDeltaBytes = dwDeltaSample * 2 * channels;
		BYTE *pBuffer = (BYTE*)malloc(dwDeltaBytes);
		dwDeltaBytes = Render(pBuffer, dwDeltaBytes);
		dwDeltaMS = MulDiv(dwDeltaBytes / 2 / channels, 1000, samplerate);
		dwPos = dwOffsetSec * 1000 + dwDeltaMS;
		free(pBuffer);
	}
	return dwPos;
}
DWORD __fastcall KbAacDecoder::Render(BYTE *Buffer, DWORD dwSize)
{
	if (m_bDecodeDone) {
		return 0;
	}
	DWORD dwRet = 0;
	DWORD dwCopySize = m_dwRemain;
	if (dwCopySize) {
		if (dwCopySize > dwSize) {
			m_dwRemain -= dwSize;
			dwCopySize = dwSize;
		}
		else {
			m_dwRemain -= dwCopySize;
		}
		memcpy(Buffer, m_pSample, dwCopySize);
		m_pSample += dwCopySize;
		dwRet += dwCopySize;
	}
	while (dwRet < dwSize) {
		NeAACDecFrameInfo frameInfo;
		if (m_buffercount > 0) {
			int k;
			for (k = 0; k < (FAAD_MIN_STREAMSIZE * 2 - m_buffercount); k++) {
				m_buffer[k] = m_buffer[k + m_buffercount];
			}
			DWORD dwRead = fread(m_buffer + (FAAD_MIN_STREAMSIZE * 2) - m_buffercount, 1, m_buffercount, m_pFile);
			if (dwRead != m_buffercount) {
				m_bDecodeDone = TRUE;
				return dwRet;
			}
			m_buffercount = 0;
		}
		m_pSample = (BYTE*)NeAACDecDecode(m_hDecoder, &frameInfo, m_buffer, sizeof(m_buffer));
		mkps = (int)((float)(frameInfo.bytesconsumed * 8) /
			(frameInfo.samples /
				frameInfo.num_front_channels)
			* frameInfo.samplerate) / 1000;
		if (frameInfo.error || !m_pSample) {
			m_bDecodeDone = TRUE;
			return dwRet;
		}
		m_buffercount += frameInfo.bytesconsumed;
		m_dwRemain = dwCopySize = frameInfo.samples * 2;
		if (dwRet + dwCopySize > dwSize) {
			dwCopySize = dwSize - dwRet;
		}
		memcpy(Buffer, m_pSample, dwCopySize);
		m_pSample += dwCopySize;
		m_dwRemain -= dwCopySize;
		//dwRet += dwCopySize;
	}
	return dwRet;
}


class KbMp4AacDecoder : public IKbAacDecoder
{
private:
	NeAACDecHandle   m_hDecoder;
	mp4ff_callback_t m_callback;
	mp4ff_t *m_pMp4ff;
	BYTE    *m_pSample;
	DWORD    m_dwLastSample;
	DWORD    m_dwCurrentSample;
	DWORD    m_dwRemain;
	DWORD    m_dwSampleRate;
	DWORD    m_dwChannels;
	int      m_nNumSampleId;
	int      m_nCurrentSampleId;
	int      m_nTrack;
public:
	BOOL  __fastcall Open(const _TCHAR *cszFileName, SOUNDINFO *pInfo);
	void  __fastcall Close(void);
	int   __fastcall SetPosition(DWORD dwPos);
	DWORD __fastcall Render(BYTE *Buffer, DWORD dwSize);
	KbMp4AacDecoder(void);
	~KbMp4AacDecoder(void);
};

uint32_t read_callback(void *user_data, void *buffer, uint32_t length) {
	return fread(buffer, 1, length, (FILE*)user_data);
}

uint32_t seek_callback(void *user_data, uint64_t position) {
	return fseek((FILE*)user_data, position, SEEK_SET);
}

//faad の aacDECdrop/decode.c から引用
int GetAACTrack(mp4ff_t *infile)
{
	/* find AAC track */
	int i, rc;
	int numTracks = mp4ff_total_tracks(infile);

	for (i = 0; i < numTracks; i++)
	{
		unsigned char *buff = NULL;
		unsigned int buff_size = 0;
		mp4AudioSpecificConfig mp4ASC;

		mp4ff_get_decoder_config(infile, i, &buff, &buff_size);

		if (buff)
		{
			rc = NeAACDecAudioSpecificConfig(buff, buff_size, &mp4ASC);
			free(buff);

			if (rc < 0)
				continue;
			return i;
		}
	}

	/* can't decode this */
	return -1;
}
KbMp4AacDecoder::KbMp4AacDecoder(void)
{
	m_hDecoder = NULL;
	m_callback.read = read_callback;
	m_callback.seek = seek_callback;
	m_callback.truncate = NULL;
	m_callback.write = NULL;
	m_callback.user_data = NULL;
	m_pMp4ff = NULL;
	m_pSample = NULL;
	m_dwLastSample = 0;
	m_dwCurrentSample = 0;
	m_dwRemain = 0;
	m_dwSampleRate = 0;
	m_dwChannels = 0;
	m_nNumSampleId = 0;
	m_nCurrentSampleId = 0;
	m_nTrack = 0;
}

KbMp4AacDecoder::~KbMp4AacDecoder(void)
{
	Close();
}


BOOL __fastcall KbMp4AacDecoder::Open(const _TCHAR *cszFileName, SOUNDINFO *pInfo)
{
	ZeroMemory(pInfo, sizeof(SOUNDINFO));
	FILE *fp;
#if UNICODE	
	fp = _wfopen(cszFileName, _T("rb"));
#else
	fp = fopen(cszFileName, _T("rb"));
#endif	
	if (!fp) {
		return FALSE;
	}

	int track;
	unsigned long samplerate;
	unsigned char channels;
	mp4ff_t *infile;
	NeAACDecHandle hDecoder;

	unsigned char *buffer;
	unsigned int buffer_size;
	m_callback.user_data = fp;
	infile = mp4ff_open_read(&m_callback);
	if (!infile) {
		fclose(fp);
		m_callback.user_data = NULL;
		return FALSE;
	}
	if ((track = GetAACTrack(infile)) < 0) {
		mp4ff_close(infile);
		fclose(fp);
		m_callback.user_data = NULL;
		return FALSE;
	}

	buffer = NULL;
	buffer_size = 0;
	mp4ff_get_decoder_config(infile, track, &buffer, &buffer_size);

	hDecoder = NeAACDecOpen();

	if (NeAACDecInit2(hDecoder, buffer, buffer_size, &samplerate, &channels) < 0) {
		// If some error initializing occured, skip the file
		NeAACDecClose(hDecoder);
		mp4ff_close(infile);
		fclose(fp);
		m_callback.user_data = NULL;
		if (buffer) {
			free(buffer);
		}
		return FALSE;
	}
	if (buffer) {
		free(buffer);
	}
	m_nNumSampleId = mp4ff_num_samples(infile, track);
	m_dwLastSample = mp4ff_get_track_duration(infile, track);
	pInfo->dwSamplesPerSec = m_dwSampleRate = samplerate;
	pInfo->dwChannels = m_dwChannels = channels;
	pInfo->dwBitsPerSample = 16;
	pInfo->dwLength = MulDiv(m_dwLastSample, 1000, samplerate);
	pInfo->dwSeekable = 1;
	int iAveBitRate = ::mp4ff_get_avg_bitrate(infile, track);
	mkps = iAveBitRate/1000;
	int m_nFrames = ::mp4ff_num_samples(infile, track);
	pInfo->vbr = 1;
	//平均ビットレートを取得します。
		int iMaxBitrate = ::mp4ff_get_max_bitrate(infile, track);
	pInfo->iAveBitRate = iAveBitRate / 1000;

	//平均ビットレートと最大ビットレートが等しい場合は、CBRにします。
	if (iAveBitRate == iMaxBitrate) pInfo->vbr = 0;

	//演奏時間を算出します。
	//	（NeAACDecInit2関数で得たサンプルレートは44100Hz未満の場合、何故か
	//	mp4ff_get_sample_rate関数で得たサンプルレートと異なる場合があるため、
	//	演奏時間はこちらの関数で得た値を元に算出します。）
	int sampleRate = ::mp4ff_get_sample_rate(infile, track);
	float framePerSec = (float)sampleRate / 1024.0f;
	float totalTime = (float)m_nFrames / framePerSec;
	//演奏時間からデコード済み総データサイズを取得します。
	int m_nDataSize = (int)(totalTime*(float)(channels*2* samplerate) + 0.5);
	//1フレーム当りデコード済みデータサイズの平均値を算出します。
	int m_sizeAveFrameDecoded = (int)round((double)m_nDataSize / (double)m_nFrames);
	pInfo->dwLength = m_nDataSize;
	m_pMp4ff = infile;
	m_hDecoder = hDecoder;
	m_nTrack = track;
	return TRUE;
}
void __fastcall KbMp4AacDecoder::Close(void)
{
	if (m_hDecoder) {
		NeAACDecClose(m_hDecoder);
		m_hDecoder = NULL;
	}
	if (m_pMp4ff) {
		mp4ff_close(m_pMp4ff);
		m_pMp4ff = NULL;
	}
	if (m_callback.user_data) {
		FILE *fp = (FILE*)m_callback.user_data;
		fclose(fp);
		m_callback.user_data = NULL;
	}
	m_pSample = NULL;
	m_dwLastSample = 0;
	m_dwCurrentSample = 0;
	m_dwRemain = 0;
	m_dwSampleRate = 0;
	m_dwChannels = 0;
	m_nNumSampleId = 0;
	m_nCurrentSampleId = 0;
	m_nTrack = 0;
}
//////////////////////////////////////////////////////////////////////////
int __fastcall KbMp4AacDecoder::SetPosition(DWORD dwPos)
{
	if (dwPos == 0 && m_nCurrentSampleId == 0) {//既に先頭位置にある
												//なくても問題ないが、無駄なので
		return 0;
	}
	int64_t i64PosSample = MulDiv(dwPos, m_dwSampleRate, 1000);
	//↑目的の位置をサンプル単位にしたもの

	int nStartId = 0;
	int nEndId = m_nNumSampleId;
	int64_t i64CurPos;
	while (1) {
		//2分探索で目的の位置を探す（一発で見つける方法が分からないので）
		//mp4ff_find_sample を使えば一発で行けそうだけど使い方が分からない
		int nId = nStartId + (nEndId - nStartId) / 2;
		i64CurPos = mp4ff_get_sample_position(m_pMp4ff, m_nTrack, nId);
		if (i64CurPos == i64PosSample) {//滅多に成立しない
			nStartId = nEndId = nId;
		}
		else if (i64CurPos > i64PosSample) {
			nEndId = nId - 1;
		}
		else {
			nStartId = nId + 1;
		}
		if (nEndId <= nStartId) {
			break;
		}
	}
	m_nCurrentSampleId = nEndId - 1;//1つ手前にシークする
	if (m_nCurrentSampleId >= m_nNumSampleId) {
		m_nCurrentSampleId = m_nNumSampleId - 1;
	}
	if (m_nCurrentSampleId < 0) {
		m_nCurrentSampleId = 0;
	}
	m_pSample = NULL;
	m_dwRemain = 0;
	//足りない分を最大1秒だけ空読み
	//KbMedia Player 本体が必要に応じてやるので実際は不要
	m_dwCurrentSample = mp4ff_get_sample_position(m_pMp4ff, m_nTrack, m_nCurrentSampleId);
	DWORD dwCurPosMS = MulDiv(m_dwCurrentSample, 1000, m_dwSampleRate);
	DWORD dwDeltaMS = dwPos - dwCurPosMS;
	if (dwDeltaMS > 1000) {
		dwDeltaMS = 1000;
	}
	DWORD dwDeltaSample = MulDiv(dwDeltaMS, m_dwSampleRate, 1000);
	DWORD dwDeltaBytes = dwDeltaSample * 2 * m_dwChannels;
	if (dwDeltaBytes) {
		BYTE *pBuffer = (BYTE*)malloc(dwDeltaBytes);
		dwDeltaBytes = Render(pBuffer, dwDeltaBytes);
		dwDeltaMS = MulDiv(dwDeltaBytes / 2 / m_dwChannels, 1000, m_dwSampleRate);
		dwPos = dwCurPosMS + dwDeltaMS;
		free(pBuffer);
	}
	return dwPos;
}
//////////////////////////////////////////////////////////////////////////
DWORD __fastcall KbMp4AacDecoder::Render(BYTE *Buffer, DWORD dwSize)
{
	if (m_pMp4ff == NULL) {
		return dwSize;
	}
	DWORD dwRet = 0;
	DWORD dwCopySize = m_dwRemain;
	if (dwCopySize) {
		if (dwCopySize > dwSize) {
			m_dwRemain -= dwSize;
			dwCopySize = dwSize;
		}
		else {
			m_dwRemain -= dwCopySize;
		}
		memcpy(Buffer, m_pSample, dwCopySize);
		m_pSample += dwCopySize;
		dwRet += dwCopySize;
	}
	while (dwRet < dwSize && m_nCurrentSampleId < m_nNumSampleId) {
		BYTE *buffer = NULL;
		UINT buffer_size = 0;
		int rc = mp4ff_read_sample(m_pMp4ff, m_nTrack, m_nCurrentSampleId, &buffer, &buffer_size);
		if (rc == 0) {
			break;
		}

		NeAACDecFrameInfo frameInfo;
		void *sample_buffer;
		sample_buffer = NeAACDecDecode(m_hDecoder, &frameInfo, buffer, buffer_size);
		if (buffer) {
			free(buffer);
		}
		if (frameInfo.error > 0) {
			break;
		}
		dwCopySize = frameInfo.samples * 2;//2==bps/8==16/8
		if (dwRet + dwCopySize > dwSize) {
			dwCopySize = dwSize - dwRet;
			m_dwRemain = frameInfo.samples * 2 - dwCopySize;
		}
		else {
			m_dwRemain = 0;
		}
		memcpy(Buffer + dwRet, sample_buffer, dwCopySize);
		m_nCurrentSampleId++;
		m_pSample = ((BYTE*)sample_buffer) + dwCopySize;
		dwRet += dwCopySize;
	}
	//ギャップレス再生用
	//m_dwLastSample が正しい値でないので機能しない
	m_dwCurrentSample += (dwRet / 2 / m_dwChannels);
	if (m_dwCurrentSample > m_dwLastSample) {
		dwRet -= (m_dwCurrentSample - m_dwLastSample) / 2 / m_dwChannels;
		m_dwCurrentSample = m_dwLastSample;
	}
	//ここまで

	return dwRet;
}



class KbAlacDecoder : public IKbAacDecoder {
private:
	mp4ff_callback_t m_callback;
	BitBuffer        m_BitBuffer;
	mp4ff_t         *m_pMp4ff;
	ALACDecoder     *m_pAlacDecoder;

	DWORD    m_dwLastSample;   //デコード最終サンプル位置
	DWORD    m_dwCurrentSample;//現在のサンプル位置
	DWORD    m_dwSampleRate;
	DWORD    m_dwChannels;
	DWORD    m_dwBitsPerSample;
	int      m_nNumSampleId;
	int      m_nCurrentSampleId;
	int      m_nTrack;
public:
	BOOL  __fastcall Open(const _TCHAR *cszFileName, SOUNDINFO *pInfo);
	void  __fastcall Close(void);
	int   __fastcall SetPosition(DWORD dwPos);
	DWORD __fastcall Render(BYTE *Buffer, DWORD dwSize);
	KbAlacDecoder(void);
	~KbAlacDecoder(void);
};


//////////////////////////////////////////////////////////////////////////////


KbAlacDecoder::KbAlacDecoder(void)
{
	m_pAlacDecoder = NULL;
	m_callback.read = read_callback;
	m_callback.seek = seek_callback;
	m_callback.truncate = NULL;
	m_callback.write = NULL;
	m_callback.user_data = NULL;
	m_pMp4ff = NULL;
	m_dwLastSample = 0;
	m_dwCurrentSample = 0;
	m_dwSampleRate = 0;
	m_dwChannels = 0;
	m_nNumSampleId = 0;
	m_nCurrentSampleId = 0;
	m_nTrack = 0;
	m_dwBitsPerSample = 0;
}

KbAlacDecoder::~KbAlacDecoder(void)
{
	Close();
}

BOOL __fastcall KbAlacDecoder::Open(const _TCHAR *cszFileName, SOUNDINFO *pInfo)
{
	FILE *fp = _tfopen(cszFileName, _T("rb"));
	if (!fp) {
		return FALSE;
	}
	mp4ff_t *infile;

	unsigned char *buffer;
	unsigned int buffer_size;
	m_callback.user_data = fp;
	infile = mp4ff_open_read(&m_callback);
	if (!infile) {
		fclose(fp);
		m_callback.user_data = NULL;
		return FALSE;
	}

	int track = 0;
	buffer = NULL;
	buffer_size = 0;
	if (mp4ff_get_decoder_config(infile, track, &buffer, &buffer_size) != 0) {
		mp4ff_close(infile);
		fclose(fp);
		m_callback.user_data = NULL;
		return FALSE;
	}
	ALACDecoder *pAlacDecoder = new ALACDecoder;
	if (pAlacDecoder->Init(buffer, buffer_size) != 0) {
		mp4ff_close(infile);
		fclose(fp);
		m_callback.user_data = NULL;
		delete pAlacDecoder;
		return FALSE;
	}
	m_dwLastSample = mp4ff_get_track_duration(infile, 0);
	pInfo->dwSamplesPerSec = m_dwSampleRate = pAlacDecoder->mConfig.sampleRate;
	pInfo->dwChannels = m_dwChannels = pAlacDecoder->mConfig.numChannels;
	pInfo->dwBitsPerSample = m_dwBitsPerSample = pAlacDecoder->mConfig.bitDepth;
	pInfo->dwLength = MulDiv(m_dwLastSample, 1000, pAlacDecoder->mConfig.sampleRate);
//	pInfo->dwLength = (int)((float)(m_dwLastSample) / (float)pAlacDecoder->mConfig.sampleRate * 1000.0f);
	pInfo->dwSeekable = 1;
	pInfo->dwUnitRender = m_dwChannels * (m_dwBitsPerSample / 8) * pAlacDecoder->mConfig.frameLength;
	m_pMp4ff = infile;
	m_nTrack = track;
	m_nNumSampleId = mp4ff_num_samples(infile, track);
	m_pAlacDecoder = pAlacDecoder;
	return TRUE;
}
void __fastcall KbAlacDecoder::Close(void)
{
	delete m_pAlacDecoder; m_pAlacDecoder = NULL;
	if (m_pMp4ff) {
		mp4ff_close(m_pMp4ff);
		m_pMp4ff = NULL;
	}
	if (m_callback.user_data) {
		FILE *fp = (FILE*)m_callback.user_data;
		fclose(fp);
		m_callback.user_data = NULL;
	}
	m_dwLastSample = 0;
	m_dwCurrentSample = 0;
	m_dwSampleRate = 0;
	m_dwChannels = 0;
	m_nNumSampleId = 0;
	m_nCurrentSampleId = 0;
	m_nTrack = 0;
}
//////////////////////////////////////////////////////////////////////////
int __fastcall KbAlacDecoder::SetPosition(DWORD dwPos)
{
	if (dwPos == 0 && m_nCurrentSampleId == 0) {//既に先頭位置にある
												//なくても問題ないが、無駄なので
		return 0;
	}
	int64_t i64PosSample = MulDiv(dwPos, m_dwSampleRate, 1000);
	//↑目的の位置をサンプル単位にしたもの

	int nStartId = 0;
	int nEndId = m_nNumSampleId;
	int64_t i64CurPos;
	while (1) {
		//2分探索で目的の位置を探す（一発で見つける方法が分からないので）
		//mp4ff_find_sample を使えば一発で行けそうだけど使い方が分からない
		int nId = nStartId + (nEndId - nStartId) / 2;
		i64CurPos = mp4ff_get_sample_position(m_pMp4ff, m_nTrack, nId);
		if (i64CurPos == i64PosSample) {//滅多に成立しない
			nStartId = nEndId = nId;
		}
		else if (i64CurPos > i64PosSample) {
			nEndId = nId - 1;
		}
		else {
			nStartId = nId + 1;
		}
		if (nEndId <= nStartId) {
			break;
		}
	}
	m_nCurrentSampleId = nEndId - 1;//1つ手前にシークする
	if (m_nCurrentSampleId >= m_nNumSampleId) {
		m_nCurrentSampleId = m_nNumSampleId - 1;
	}
	if (m_nCurrentSampleId < 0) {
		m_nCurrentSampleId = 0;
	}
	m_dwCurrentSample = mp4ff_get_sample_position(m_pMp4ff, m_nTrack, m_nCurrentSampleId);
	DWORD dwRetMS = MulDiv(m_dwCurrentSample, 1000, m_dwSampleRate);
	return dwRetMS;
}
//////////////////////////////////////////////////////////////////////////
DWORD __fastcall KbAlacDecoder::Render(BYTE *Buffer, DWORD dwSize)
{
	const DWORD cdwBlockAlign = (m_dwBitsPerSample / 8) * m_dwChannels;
	DWORD dwRet = 0;
	if (m_nCurrentSampleId < m_nNumSampleId) {
		BYTE *buffer = NULL;
		UINT buffer_size = 0;
		int rc = mp4ff_read_sample(m_pMp4ff, m_nTrack, m_nCurrentSampleId, &buffer, &buffer_size);
		m_nCurrentSampleId++;
		if (rc == 0) {
			return 0;
		}
		BitBufferInit(&m_BitBuffer, buffer, buffer_size);
		uint32_t dwSample = 0;
		int ret = m_pAlacDecoder->Decode(&m_BitBuffer, Buffer, dwSize / cdwBlockAlign, m_dwChannels, &dwSample);
		if (ret != 0) {
			free(buffer);
			return 0;
		}
		BitBufferReset(&m_BitBuffer);
		free(buffer);
		dwRet += dwSample * cdwBlockAlign;
	}
	m_dwCurrentSample += (dwRet / cdwBlockAlign);
	if (m_dwCurrentSample > m_dwLastSample) {
		dwRet -= (m_dwCurrentSample - m_dwLastSample)*cdwBlockAlign;
		m_dwCurrentSample = m_dwLastSample;
	}
	return dwRet;
}


class m4a
{
public:
	static HKMP WINAPI Open(const _TCHAR *cszFileName, SOUNDINFO *pInfo)
	{//MP4 コンテナに格納されていれば KbMp4AacDecoder
	 //MP4 コンテナに格納されなければ KbAacDecoder
	 //を作成し、そのポインタを返す
		FILE *fp;
#if UNICODE	
		fp = _wfopen(cszFileName, _T("rb"));
#else
		fp = fopen(cszFileName, _T("rb"));
#endif	
		if (!fp) {
			return FALSE;
		}

		IKbAacDecoder *pAAC;
		mp4ff_callback_t callback = { 0 };
		callback.read = read_callback;
		callback.seek = seek_callback;
		callback.user_data = fp;
		mp4ff_t *pMp4ff = mp4ff_open_read(&callback);
		if (!pMp4ff) {
			KbAacDecoder *pAacDecoder = new KbAacDecoder;
			DWORD dwCount = pAacDecoder->Open(cszFileName, pInfo);
			if (dwCount) {
				pAAC = pAacDecoder;
				return pAAC;
			}
			else {
				pAacDecoder->Close();
			}
		}
		else
		 {
			if (mp4ff_total_tracks(pMp4ff) > 0) {
				fseek(fp,0, SEEK_SET);
				char a[0x400];
				char b;
				CString str;
				int flag = 0;
				fread(a,0x400,1,fp);
				//if (strstr(a,"alac")==0) {
				//	flag = 1;
				//}
				//if (flag == 0){ //TRACK_AUDIO){
				//	pAAC = new KbMp4AacDecoder;
				//}
				//else if (flag == 1) {//TRACK_AUDIO_ALAC
				//	pAAC = new KbAlacDecoder;
				//}
				if (mp4ff_total_tracks(pMp4ff) > 0) {
					int type = mp4ff_get_track_type(pMp4ff, 0);
					if (type == 1) {//TRACK_AUDIO)
						pAAC = new KbMp4AacDecoder;
					}
					else if (type == 4) {//TRACK_AUDIO_ALAC
						pAAC = new KbAlacDecoder;
					}
				}
			}
		}
		fclose(fp);

		if (pAAC->Open(cszFileName, pInfo)) {
			return pAAC;
		}
		delete pAAC;
		return NULL;
	}

	static void WINAPI Close(HKMP hKMP)
	{
		if (hKMP) {
			IKbAacDecoder *pAAC = (IKbAacDecoder*)hKMP;
			delete pAAC;
			hKMP = NULL;
		}
	}

	static DWORD WINAPI Render(HKMP hKMP, BYTE* Buffer, DWORD dwSize)
	{
		if (!hKMP)return 0;
		IKbAacDecoder *pAAC = (IKbAacDecoder*)hKMP;
		return pAAC->Render(Buffer, dwSize);
	}

	static DWORD WINAPI SetPosition(HKMP hKMP, DWORD dwPos)
	{
		if (!hKMP)return 0;
		IKbAacDecoder *pAAC = (IKbAacDecoder*)hKMP;
		return pAAC->SetPosition(dwPos);
	}
};