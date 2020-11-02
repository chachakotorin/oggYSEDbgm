#pragma once
#include "stdafx.h"
#include <math.h>
#include <string.h> 
#include <crtdbg.h>
#include <stdlib.h>
#include "vbrtag.h"
#include "libmad\decoder.h"
#include "ringbuf.h"

#define MPG_MD_STEREO       0
#define MPG_MD_JOINT_STEREO 1
#define MPG_MD_DUAL_CHANNEL 2
#define MPG_MD_MONO         3


static inline DWORD input_read(HANDLE input, void* buffer, DWORD bytes)
{
    if(ReadFile(input, buffer, bytes, &bytes, 0) == FALSE){
        bytes = 0;
    }
    return bytes;
}

static inline DWORD input_seek(HANDLE input, DWORD position, DWORD method)
{
    return SetFilePointer(input, position, 0, method);
}

static const long freqs[9] = { 44100, 48000, 32000,
                         22050, 24000, 16000,
                         11025, 12000 , 8000 };

static const int tabsel_123[2][3][16] = {
   { {0,32,64,96,128,160,192,224,256,288,320,352,384,416,448,},
     {0,32,48,56, 64, 80, 96,112,128,160,192,224,256,320,384,},
     {0,32,40,48, 56, 64, 80, 96,112,128,160,192,224,256,320,} },

   { {0,32,48,56,64,80,96,112,128,144,160,176,192,224,256,},
     {0,8,16,24,32,40,48,56,64,80,96,112,128,144,160,},
     {0,8,16,24,32,40,48,56,64,80,96,112,128,144,160,} }
};

typedef struct id3tag {
    char tag[3];
    char title[30];
    char artist[30];
    char album[30];
    char year[4];
    char comment[30];
    unsigned char genre;
}id3tag;

typedef struct mp3info {
    int nbytes,freq,nch,hpos;
    int hasVbrtag,lsf,bitrate,isStream;
    int total_samples;
    int skip_samples;
    double length;
}mp3info;
struct dither {
  mad_fixed_t error[3];
  mad_fixed_t random;
};

#define BUFSZ			(10240*6/2)
#define OUTPUT_BUFFER_SIZE  BUFSZ
#define OUTPUT_BUFFER_NUM   5
extern BYTE bufwav3[OUTPUT_BUFFER_SIZE*OUTPUT_BUFFER_NUM*4];
extern BOOL wavwait,thend;
extern char *adbuf,*adbuf2;
extern ULONG WAVDALen;
extern BOOL thend1;
extern int loop3;
static const char VBRTag[]={"Xing"};

class CWread : public CWinThread
{
	DECLARE_DYNCREATE(CWread)
private:

	HANDLE m_hHeap;
	DWORD  m_dwReadPos;   //読み取り位置
	DWORD  m_dwWritePos;  //書き込み位置
	DWORD  m_dwWritten;   //書き込んだバッファのサイズ
	DWORD  m_dwBufferSize;//リングバッファのサイズ
	DWORD  m_dwAllocSize; //実際にメモリを割り当てたサイズ
	DWORD  m_dwLockedSize;
	HANDLE        m_hFile;

	mp3info       m_mp3info;
	DWORD         m_dwBufLen;
	DWORD         m_dwBitsPerSample;
	//ギャップレス再生用
	DWORD         m_dwTotalBytes;//曲長（バイト単位）
	DWORD         m_dwSkipBytes; //曲頭のスキップバイト数
	DWORD         m_dwBytesDecoded;//デコード済みバイト数
	DWORD         m_dwSkipRemain;  //スキップバイト数残り
	//
	//DITHER 関係
	HANDLE        m_hNotification;
	BOOL          m_bWatchDither;//INI ファイルの変更を監視するかどうか
	BOOL          m_bEnableDither;
	unsigned long m_clipped;
	mad_fixed_t   m_clipping;
	dither        m_left_dither;
	dither        m_right_dither;
	BYTE          m_tmp[10000];
	KbRingBuffer  m_ringbuf;

public:	
	CWread(); 
    virtual ~CWread();
public:
	virtual BOOL InitInstance();
	void wavread();
	void wavread1(WPARAM a,LPARAM b);

protected:
    DECLARE_MESSAGE_MAP()

/*static int ExtractI4(unsigned char *buf)
{
    int x;
    x = buf[0];
    x <<= 8;
    x |= buf[1];
    x <<= 8;
    x |= buf[2];
    x <<= 8;
    x |= buf[3];
    return x;
}
*/

static int GetVbrTag(VBRTAGDATA *pTagData,  unsigned char *buf)
{
    int  i, head_flags;
    int  h_bitrate, h_id, h_mode, h_sr_index;
    int  enc_delay, enc_padding;
    static const int sr_table[4] = { 44100, 48000, 32000, 99999 };
    static const int br_table[3][16] = {
        { 0,  8, 16, 24, 32, 40, 48, 56,  64,  80,  96, 112, 128, 144, 160, -1 },
        { 0, 32, 40, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320, -1 },
        { 0,  8, 16, 24, 32, 40, 48, 56,  64,  80,  96, 112, 128, 144, 160, -1 },
    };

    pTagData->flags = 0;     

    h_id       = (buf[1] >> 3) & 1;
    h_sr_index = (buf[2] >> 2) & 3;
    h_mode     = (buf[3] >> 6) & 3;

    if( h_id ) 
    {
        if( h_mode != 3 )   buf+=(32+4);
        else                buf+=(17+4);
    }
    else
    {
        if( h_mode != 3 ) buf+=(17+4);
        else              buf+=(9+4);
    }
 	h_bitrate  = ((buf[2]>>4)&0xf);
	h_bitrate  = br_table[h_id][h_bitrate];
   
    if( buf[0] != VBRTag[0] ) return 0;
    if( buf[1] != VBRTag[1] ) return 0;
    if( buf[2] != VBRTag[2] ) return 0;
    if( buf[3] != VBRTag[3] ) return 0;

    buf+=4;

    pTagData->h_id = h_id;

    pTagData->samprate = sr_table[h_sr_index];

    if( h_id == 0 )
        pTagData->samprate >>= 1;

    head_flags = pTagData->flags = ExtractI4(buf); buf+=4;

    if( head_flags & FRAMES_FLAG )
    {
        pTagData->frames   = ExtractI4(buf); buf+=4;
    }

    if( head_flags & BYTES_FLAG )
    {
        pTagData->bytes = ExtractI4(buf); buf+=4;
    }

    if( head_flags & TOC_FLAG )
    {
        if( pTagData->toc != NULL )
        {
            for(i=0;i<NUMTOCENTRIES;i++)
                pTagData->toc[i] = buf[i];
        }
        buf+=NUMTOCENTRIES;
    }

    pTagData->vbr_scale = -1;

    if( head_flags & VBR_SCALE_FLAG )
    {
        pTagData->vbr_scale = ExtractI4(buf); buf+=4;
    }

	pTagData->headersize = 
	  ((h_id+1)*72000*h_bitrate) / pTagData->samprate;

    buf+=21;
    enc_delay = buf[0] << 4;
    enc_delay += buf[1] >> 4;
    enc_padding= (buf[1] & 0x0F)<<8;
    enc_padding += buf[2];
    // check for reasonable values (this may be an old Xing header,
    // not a INFO tag)
    if (enc_delay<0 || enc_delay > 3000) enc_delay=-1;
    if (enc_padding<0 || enc_padding > 3000) enc_padding=-1;
    pTagData->enc_delay=enc_delay;
    pTagData->enc_padding=enc_padding;
    return 1;
}

static int head_check(unsigned long head)
{
    if ((head & 0xffe00000) != 0xffe00000) return FALSE;
    if (!((head>>17)&3)) return FALSE;
    if (((head>>12)&0xf) == 0xf) return FALSE;
    if (((head>>10)&0x3) == 0x3 ) return FALSE;
    if ((4-((head>>17)&3)) == 4) return FALSE;
    return TRUE;
}

static void __fastcall SkipRIFF(HANDLE hFile, DWORD *pSkip, DWORD *pEndPos)
{//呼び出しの前後でファイルポインタの位置が変更されることに注意
    DWORD dwNumRead;
    BYTE  header[16];
    DWORD *hriff = (DWORD*)header;
    DWORD *hdata = (DWORD*)(&header[12]);
    *pSkip = *pEndPos = 0xFFFFFFFF;
    //ファイルポインタが先頭にあるとは限らない
    input_seek(hFile, 0, FILE_BEGIN);
    //ヘッダを調べる
    dwNumRead = input_read(hFile, header, 16);
    if(dwNumRead != 16)
        return;
    if(*hriff != *((const DWORD*)"RIFF")){
        return;//RIFF でない
    }
    while(1){
        //data チャンクを探す
        DWORD dwChunkSize = 0;
        while(*hdata != *((const DWORD*)"data")){
            dwNumRead = input_read(hFile, &dwChunkSize, sizeof(DWORD));
            if(dwNumRead != sizeof(DWORD)){
                return;
            }
            if(dwChunkSize & 0x01)//偶数バイトにする
                dwChunkSize++;
            if((int)dwChunkSize < 0){
                return;
            }
            input_seek(hFile, dwChunkSize, FILE_CURRENT);
            dwNumRead = input_read(hFile, hdata, sizeof(DWORD));
            if(dwNumRead != sizeof(DWORD)){
                return;
            }
            dwChunkSize = 0;
        }
        //data チャンクのサイズ
        dwNumRead = input_read(hFile, &dwChunkSize, sizeof(DWORD));
        if(dwNumRead != sizeof(DWORD)){
            return;
        }
        DWORD dwSkip = input_seek(hFile, 0, FILE_CURRENT);
        if(dwChunkSize&0x01){
            dwChunkSize++;//偶数バイトにする
        }
        if((int)dwChunkSize < 0)return;
        *pSkip = dwSkip;
        *pEndPos = dwSkip+dwChunkSize;
        break;
    }
}

static int getmp3info(HANDLE hFile, mp3info *info,id3tag *id3,VBRTAGDATA *vbr)
{
    unsigned long head;
    int lsf,srate;
    int bitrate_index,mode,nch,lay,extension,mpeg25,padding;
    int hpos,i;
    //char TmpStr[20];
    int lptr;

    DWORD dwUncompressed = 0;
    DWORD dwFileSize = input_seek(hFile, 0, FILE_END);
    info->isStream = 0;
    info->nbytes = dwFileSize;
    int skip_zip = 0;
    input_seek(hFile, skip_zip, FILE_BEGIN);
    bool Riff = false;

    hpos = skip_zip;
    {
        BYTE tmp[4+2+4];
        if(input_read(hFile, tmp, sizeof(tmp)) != sizeof(tmp)){
            return 0;
        }
        if(tmp[0] == 'I' && tmp[1] == 'D' && tmp[2] == '3'){
            //Skip ID3v2 tag
            hpos = tmp[6]*2097152+tmp[7]*16384+tmp[8]*128+tmp[9];
        }
        else if(*(DWORD*)tmp == *(DWORD*)"RIFF"){
            //Skip RIFF chunk
            DWORD dwSkip, dwEndPos;
            SkipRIFF(hFile, &dwSkip, &dwEndPos);
            if(dwSkip != 0xFFFFFFFF && dwEndPos != 0xFFFFFFFF){
                hpos = dwSkip;
                info->nbytes = dwEndPos;
                Riff = true;
            }
        }
    }
    
    lptr=0;
    NEXTSW:;
    for(i=lptr;i<65536;i++)
    {
        BYTE tmp[4];
        input_seek(hFile, hpos+i, FILE_BEGIN);
        if(input_read(hFile, tmp, 4) != 4)
            return 0;
        BYTE *p = (BYTE*)&head;
        p[0] = tmp[3]; p[1] = tmp[2]; p[2] = tmp[1]; p[3] = tmp[0];
        if(head_check(head))break;
    }
    if (i == 65536){
        return 0;
    }
    lptr=i;
    hpos += i;
    info->hpos = hpos;

    if(Riff == false) {
        info->nbytes -= hpos;
        // read ID3 tag
        input_seek(hFile, -128, FILE_END);
        input_read(hFile, id3, 128);
        if (memcmp(id3->tag,"TAG",3) == 0) info->nbytes -= 128;
    }
    if(info->nbytes <= 0){
        return 0;
    }
    input_seek(hFile, hpos, FILE_BEGIN);

    if( head & (1<<20) ) {
      lsf = (head & (1<<19)) ? 0x0 : 0x1;
      mpeg25 = 0;
    } else {
      lsf = 1;
      mpeg25 = 1;
    }

    bitrate_index = ((head>>12)&0xf);
    padding       = ((head>>9)&0x1);
    mode          = ((head>>6)&0x3);
    nch           = (mode == MPG_MD_MONO) ? 1 : 2;
    lay           = 4-((head>>17)&3);
    extension     = ((head>>8)&0x1);

    if(mpeg25) srate = 6 + ((head>>10)&0x3);
    else srate = ((head>>10)&0x3) + (lsf*3);

    //if (lay != 3){
    //    return 0;
    //}
    if (lay == 4){
        return 0;
    }

    //Check frame header//
    if(lay<0 || lay>4  || bitrate_index<1 || bitrate_index>14
		     || srate<0 || srate>8)
     {
         input_seek(hFile, -3, FILE_END);
	 goto NEXTSW; } 
     	
    // read VBR tag
    //pStream->Seek(pvInstance, hpos, NULL, FILE_BEGIN);

    info->lsf  = lsf;
    info->freq = freqs[srate];
    info->nch  = nch;
    
    {
        unsigned char buf[XING_HEADER_SIZE];

        if(input_read(hFile, buf, XING_HEADER_SIZE) != XING_HEADER_SIZE){
            return 1;
        }
        if(GetVbrTag(vbr,buf)) {
            int cur_bitrate = (int)(vbr->bytes*8/(vbr->frames*576.0*(lsf?1:2)/freqs[srate]));
            info->length = vbr->frames*576.0*(lsf?1:2)/freqs[srate];
            info->nbytes = vbr->bytes;
            info->hasVbrtag = 1;
            info->bitrate = cur_bitrate;
            if(dwUncompressed){
                int total_size = dwFileSize-info->hpos;
                int first_mp3_size = dwUncompressed - (info->hpos-skip_zip);
                info->length *= (double)total_size/(double)first_mp3_size;
            }
            else{
                static const int frame_samples_table[3]={384,1152,576};
                int frame_samples = frame_samples_table[lay-1];
                if(lay == 3){
                    if(!info->lsf){
                        frame_samples *= 2;
                    }   
                }
                info->total_samples = vbr->frames * frame_samples;
            }
        } else {
		    //if (bitrate_index==0){bitrate_index=9;lay=3;}
		    int framesize = tabsel_123[lsf][lay-1][bitrate_index]*144000/(freqs[srate]<<lsf)+padding;
            info->length = info->nbytes/framesize*576.0*(lsf?1:2)/freqs[srate];
            info->hasVbrtag = 0;
            info->bitrate = tabsel_123[lsf][lay-1][bitrate_index]*1000;
            info->length = info->nbytes * 8.0 / info->bitrate;
			//info->total_samples = framesize*freqs[srate];
        }
        const int POST_DELAY = 1152;
        const int DECODE_DELAY_LAYER1 = 0;
        const int DECODE_DELAY_LAYER2 = (480 + 1);
        const int DECODE_DELAY_LAYER3 = (528 + 1);
        static const int dec_delay_tbl[] = {0, 480+1, 528+1};
        int dec_delay = dec_delay_tbl[lay-1] + POST_DELAY;
        if(info->hasVbrtag){
            if(vbr->enc_delay > 0){
                dec_delay += vbr->enc_delay;
                info->total_samples -= vbr->enc_delay;
            }
            if(vbr->enc_padding > 0){
                info->total_samples -= vbr->enc_padding;
            }
            if(info->total_samples < 0){
                info->total_samples = 0;
            }
        }
        info->skip_samples = dec_delay;
    }
    return 1; 
}


enum channel {
  CHANNEL_STEREO  = 0,
  CHANNEL_MONO    = 1,
  CHANNEL_LEFT    = 2,
  CHANNEL_RIGHT   = 3,
  CHANNEL_REVERSE = 4
};


static int do_error(struct mad_stream *stream, struct mad_frame *frame,
	     HANDLE input, int *last_error)
{
    int do_continue = 1;
    //signed long tagsize;
    switch (stream->error) {
        case MAD_ERROR_BADCRC:
        if (last_error) {
            if (*last_error) {
	            if (frame)
	                mad_frame_mute(frame);
            }
            else
	            *last_error = 1;
        }
        do_continue = 0;
        break;
        case MAD_ERROR_LOSTSYNC:
            //tagsize = id3_tag_query(stream->this_frame,
			//        stream->bufend - stream->this_frame);
            //if (tagsize > 0)
            //    mad_stream_skip(stream, tagsize);
            //else if (stats)
            //    ++stats->sync_errors;
            break;
        default:
            //if (stats)
            //    ++stats->other_errors;
            break;
    }
    return do_continue;
}
static inline unsigned long prng(unsigned long state)
{
  return (state * 0x0019660dL + 0x3c6ef35fL) & 0xffffffffL;
}

static inline signed long linear_dither(unsigned int bits, mad_fixed_t sample,
			                            struct dither *dither, 
                                        unsigned long *clipped,
			                            mad_fixed_t *clipping,
                                        BOOL bEnableDither)
{
    unsigned int scalebits = MAD_F_FRACBITS + 1 - bits;
    mad_fixed_t output = sample;
    mad_fixed_t mask = (1L << scalebits) - 1;
    mad_fixed_t random = 0;
    enum {
        MIN = -MAD_F_ONE,
        MAX =  MAD_F_ONE - 1
    };
    
    if(bEnableDither){

    /* noise shape */
    sample += dither->error[0] - dither->error[1] + dither->error[2];

    dither->error[2] = dither->error[1];
    dither->error[1] = dither->error[0] / 2;

    /* bias */
    output = sample + (1L << (MAD_F_FRACBITS + 1 - bits - 1));

    scalebits = MAD_F_FRACBITS + 1 - bits;
    mask = (1L << scalebits) - 1;

    /* dither */
    random  = prng(dither->random);
    output += (random & mask) - (dither->random & mask);

    dither->random = random;

    }//if(bEnableDither)

    /* clip */
    if (output > MAX) {
        ++*clipped;
        if (output - MAX > *clipping)
            *clipping = output - MAX;

        output = MAX;

        if (sample > MAX)
            sample = MAX;
    }
    else if (output < MIN) {
        ++*clipped;
        if (MIN - output > *clipping)
            *clipping = MIN - output;

        output = MIN;

        if (sample < MIN)
            sample = MIN;
    }

    /* quantize */
    output &= ~mask;

    /* error feedback */
    dither->error[0] = sample - output;

    /* scale */
    return output >> scalebits;
}


	DWORD GetWritten(void){//書き込んだバッファのサイズ
			return m_dwWritten;
		}

	void mp3init(void)
	{
		m_hFile = INVALID_HANDLE_VALUE;
		m_dwBufLen = 0;
		m_clipped = 0;
		m_clipping = 0;
		m_dwBitsPerSample = 16;
		m_bEnableDither = TRUE;
		m_bWatchDither = TRUE;
		m_hNotification = INVALID_HANDLE_VALUE;
		CloseHandle(m_hFile);
	}



		bool Open(const TCHAR *cszFileName, SOUNDINFO *pInfo)
	{
	//    Close();
		m_dwWritten=m_dwAllocSize =m_dwBufferSize= OUTPUT_BUFFER_SIZE*OUTPUT_BUFFER_NUM;
		if(!pInfo)return false;
		DWORD dwBitsPerSample =pInfo->dwBitsPerSample;
		ZeroMemory(pInfo, sizeof(SOUNDINFO));
		HANDLE hFile =  CreateFile(cszFileName, GENERIC_READ,
							FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
							OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		if (hFile == INVALID_HANDLE_VALUE)
			return false;
		id3tag     id3;
		VBRTAGDATA vbrtag;
		ZeroMemory(&id3, sizeof(id3));
		ZeroMemory(&vbrtag, sizeof(vbrtag));
		if(!getmp3info(hFile, &m_mp3info,&id3,&vbrtag)){
			CloseHandle(hFile);
			return NULL;
		}
		if(dwBitsPerSample == 8 ||
		   dwBitsPerSample == 16 ||
		   dwBitsPerSample == 24 ||
		   dwBitsPerSample == 32){
			m_dwBitsPerSample = dwBitsPerSample;
		}
		else if(dwBitsPerSample > 32){
			m_dwBitsPerSample = 32;
		}
		m_dwTotalBytes = m_mp3info.total_samples*((m_dwBitsPerSample/8)*m_mp3info.nch);
		m_dwSkipBytes = m_mp3info.skip_samples*((m_dwBitsPerSample/8)*m_mp3info.nch);
		pInfo->dwSamplesPerSec = m_mp3info.freq;
		pInfo->dwChannels = m_mp3info.nch;
		pInfo->dwBitsPerSample = m_dwBitsPerSample;
		pInfo->dwUnitRender = 576*m_mp3info.nch*2*2*m_dwBitsPerSample/8;
		pInfo->dwLength = (DWORD)(m_mp3info.length * 1000);
		pInfo->dwSeekable = 1;
		m_hFile = hFile;

		return true;
	}
		void Close(void)
	{
		m_dwBufLen = 0;
		if(m_hFile != INVALID_HANDLE_VALUE){
			CloseHandle(m_hFile);
//			mad_header_finish(&m_header);
//			mad_stream_finish(&m_stream);
//			mad_frame_finish(&m_frame);
//			mad_synth_finish(&m_synth);
			m_hFile = INVALID_HANDLE_VALUE;
//			ZeroMemory(&m_mp3info, sizeof(m_mp3info));
//			ZeroMemory(&m_left_dither, sizeof(m_left_dither));
//			ZeroMemory(&m_right_dither, sizeof(m_right_dither));
			m_clipped = 0;
			m_clipping = 0;
		}
//		if(m_hNotification != INVALID_HANDLE_VALUE){
//			FindCloseChangeNotification(m_hNotification);
//			m_hNotification = INVALID_HANDLE_VALUE;
//		}
	}

	float fade; 



		void Render(int san2=0)
	{
			struct mad_stream    m_stream;
			struct mad_header    m_header;
			struct mad_frame     m_frame;
			struct mad_synth     m_synth;
		mad_header_init(&m_header);
		mad_stream_init(&m_stream);
		mad_frame_init(&m_frame);
		mad_synth_init(&m_synth);
		fade=0.0f;
		CWaitCursor rrr;
		{
		DWORD dl,dwDataLen = (WAVDALen/OUTPUT_BUFFER_NUM)*4; dl=dwDataLen;
		dwDataLen+=dl;
		int cnt=0,cnt2=0;
		input_seek(m_hFile, m_mp3info.hpos, FILE_BEGIN);
		for(;;){
			input_read(m_hFile,m_tmp,4);
			input_seek(m_hFile, -4, FILE_CURRENT);
			BYTE a3=(m_tmp[1]>>3)&0x03;
			BYTE a2=(m_tmp[1]>>1)&0x03;
			BYTE a1=m_tmp[2]>>4;
			int tb=tabsel_123[(a3==3)?0:1][3-a2][a1];
			a1=(m_tmp[2]>>2)&0x03;
			int fr=freqs[a1];
			a1=(m_tmp[2]&0x2)>>1;
			int pb=(int)a1;
			int size=(144*tb*1000)/fr+pb;
	//		ZeroMemory(m_tmp,size*2);
			if(input_read(m_hFile, m_tmp, size+MAD_BUFFER_GUARD)!=size+MAD_BUFFER_GUARD){break;}
			input_seek(m_hFile, -MAD_BUFFER_GUARD, FILE_CURRENT);
			mad_stream_buffer(&m_stream, m_tmp, size+MAD_BUFFER_GUARD);
			if(san2<=cnt){
				mad_frame_decode(&m_frame, &m_stream);
				mad_synth_frame(&m_synth, &m_frame);
				int nch = m_synth.pcm.channels;
				mad_fixed_t *ch1 = m_synth.pcm.samples[0];
				mad_fixed_t *ch2;
				if(nch==2)
					ch2 = m_synth.pcm.samples[1];
				else
					ch2=NULL;
				int pcm_length = m_synth.pcm.length;
				pack_pcm(m_tmp, pcm_length, ch1, ch2,  m_dwBitsPerSample, &m_clipped, &m_clipping);
				memcpy(adbuf2+cnt-san2,m_tmp,pcm_length*2*nch);
				cnt+=pcm_length*2*nch;
				if(loop3*2*nch<cnt-san2 && loop3!=0){break;}
			}else{
				mad_header_decode(&m_header, &m_stream);
				cnt+=(int)((float)mad_timer_count(m_header.duration, MAD_UNITS_MILLISECONDS)*44.1f*4.0f)+22;
	//			cnt+=(int)(m_header.duration.seconds*44.1f*4);

			}
			if((int)dwDataLen+san2<cnt)	wavwait=1;
			if(thend1==TRUE){break;}
		}
		}
			mad_header_finish(&m_header);
			mad_stream_finish(&m_stream);
			mad_frame_finish(&m_frame);
			mad_synth_finish(&m_synth);

		Close();
		wavwait=1;
		thend=1;
	}
	//static
	unsigned int pack_pcm(unsigned char *data, unsigned int nsamples,
				  mad_fixed_t const *left, mad_fixed_t const *right,
				  int resolution, unsigned long *clipped,
				  mad_fixed_t *clipping)
	{
	  dither &left_dither = m_left_dither;
	  dither &right_dither = m_right_dither;
	  unsigned char const *start;
	  register signed long sample0, sample1;
	  int effective, bytes;
	  BOOL bEnableDither = m_bEnableDither;  
	  start     = data;
	  effective = (resolution > 24) ? 24 : resolution;
	  bytes     = resolution / 8;

	  if (right) {  /* stereo */
		while (nsamples--) {
		  sample0 = linear_dither(effective, *left++, &left_dither,
					  clipped, clipping, bEnableDither);
		  sample1 = linear_dither(effective, *right++, &right_dither,
					  clipped, clipping, bEnableDither);
			
		  if(fade<1.0f){
			  sample0=(long)(sample0*fade);
			  sample1=(long)(sample1*fade);
			  fade+=0.01f;
		  }
		  switch (resolution) {
		  case 8:
		data[0] = (char)(sample0 ^ 0x80);
		data[1] = (char)(sample1 ^ 0x80);
		break;

		  case 32:
		sample0 <<= 8;
		sample1 <<= 8;
		data[        3] = (char)(sample0 >> 24);
		data[bytes + 3] = (char)(sample1 >> 24);
		  case 24:
		data[        2] = (char)(sample0 >> 16);
		data[bytes + 2] = (char)(sample1 >> 16);
		  case 16:
		data[        1] = (char)(sample0 >>  8);
		data[bytes + 1] = (char)(sample1 >>  8);
		data[        0] = (char)(sample0 >>  0);
		data[bytes + 0] = (char)(sample1 >>  0);
		  }

		  data += bytes * 2;
		}
	  }
	  else {  /* mono */
		while (nsamples--) {
		  sample0 = linear_dither(effective, *left++, &left_dither,
					  clipped, clipping, bEnableDither);

		  switch (resolution) {
		  case 8:
		data[0] = (char)(sample0 ^ 0x80);
		break;

		  case 32:
		sample0 <<= 8;
		data[3] = (char)(sample0 >> 24);
		  case 24:
		data[2] = (char)(sample0 >> 16);
		  case 16:
		data[1] = (char)(sample0 >>  8);
		data[0] = (char)(sample0 >>  0);
		  }
		  data += bytes;
		}
	  }

	  return data - start;
	}

};

class mp3
{
public:
    HANDLE        m_hFile;
    mad_stream    m_stream;
    mad_header    m_header;
    mad_frame     m_frame;
    mad_synth     m_synth;
    mp3info       m_mp3info;
    BYTE          m_buffer[16384];
    DWORD         m_dwBufLen;
    DWORD         m_dwBitsPerSample;
    //ギャップレス再生用
    DWORD         m_dwTotalBytes;//曲長（バイト単位）
    DWORD         m_dwSkipBytes; //曲頭のスキップバイト数
    DWORD         m_dwBytesDecoded;//デコード済みバイト数
    DWORD         m_dwSkipRemain;  //スキップバイト数残り
    //
    //DITHER 関係
    HANDLE        m_hNotification;
    BOOL          m_bWatchDither;//INI ファイルの変更を監視するかどうか
    BOOL          m_bEnableDither;
    unsigned long m_clipped;
    mad_fixed_t   m_clipping;
    dither        m_left_dither;
    dither        m_right_dither;

    KbRingBuffer  m_ringbuf;
    BYTE          m_tmp[576*2*(32/4)];

static int GetVbrTag(VBRTAGDATA *pTagData,  unsigned char *buf)
{
    int  i, head_flags;
    int  h_bitrate, h_id, h_mode, h_sr_index;
    int  enc_delay, enc_padding;
    static const int sr_table[4] = { 44100, 48000, 32000, 99999 };
    static const int br_table[3][16] = {
        { 0,  8, 16, 24, 32, 40, 48, 56,  64,  80,  96, 112, 128, 144, 160, -1 },
        { 0, 32, 40, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320, -1 },
        { 0,  8, 16, 24, 32, 40, 48, 56,  64,  80,  96, 112, 128, 144, 160, -1 },
    };

    pTagData->flags = 0;     

    h_id       = (buf[1] >> 3) & 1;
    h_sr_index = (buf[2] >> 2) & 3;
    h_mode     = (buf[3] >> 6) & 3;

    if( h_id ) 
    {
        if( h_mode != 3 )   buf+=(32+4);
        else                buf+=(17+4);
    }
    else
    {
        if( h_mode != 3 ) buf+=(17+4);
        else              buf+=(9+4);
    }
 	h_bitrate  = ((buf[2]>>4)&0xf);
	h_bitrate  = br_table[h_id][h_bitrate];
   
    if( buf[0] != VBRTag[0] ) return 0;
    if( buf[1] != VBRTag[1] ) return 0;
    if( buf[2] != VBRTag[2] ) return 0;
    if( buf[3] != VBRTag[3] ) return 0;

    buf+=4;

    pTagData->h_id = h_id;

    pTagData->samprate = sr_table[h_sr_index];

    if( h_id == 0 )
        pTagData->samprate >>= 1;

    head_flags = pTagData->flags = ExtractI4(buf); buf+=4;

    if( head_flags & FRAMES_FLAG )
    {
        pTagData->frames   = ExtractI4(buf); buf+=4;
    }

    if( head_flags & BYTES_FLAG )
    {
        pTagData->bytes = ExtractI4(buf); buf+=4;
    }

    if( head_flags & TOC_FLAG )
    {
        if( pTagData->toc != NULL )
        {
            for(i=0;i<NUMTOCENTRIES;i++)
                pTagData->toc[i] = buf[i];
        }
        buf+=NUMTOCENTRIES;
    }

    pTagData->vbr_scale = -1;

    if( head_flags & VBR_SCALE_FLAG )
    {
        pTagData->vbr_scale = ExtractI4(buf); buf+=4;
    }

	pTagData->headersize = 
	  ((h_id+1)*72000*h_bitrate) / pTagData->samprate;

    buf+=21;
    enc_delay = buf[0] << 4;
    enc_delay += buf[1] >> 4;
    enc_padding= (buf[1] & 0x0F)<<8;
    enc_padding += buf[2];
    // check for reasonable values (this may be an old Xing header,
    // not a INFO tag)
    if (enc_delay<0 || enc_delay > 3000) enc_delay=-1;
    if (enc_padding<0 || enc_padding > 3000) enc_padding=-1;
    pTagData->enc_delay=enc_delay;
    pTagData->enc_padding=enc_padding;
    return 1;
}

static int head_check(unsigned long head)
{
    if ((head & 0xffe00000) != 0xffe00000) return FALSE;
    if (!((head>>17)&3)) return FALSE;
    if (((head>>12)&0xf) == 0xf) return FALSE;
    if (((head>>10)&0x3) == 0x3 ) return FALSE;
    if ((4-((head>>17)&3)) == 4) return FALSE;
    return TRUE;
}

static void __fastcall SkipRIFF(HANDLE hFile, DWORD *pSkip, DWORD *pEndPos)
{//呼び出しの前後でファイルポインタの位置が変更されることに注意
    DWORD dwNumRead;
    BYTE  header[16];
    DWORD *hriff = (DWORD*)header;
    DWORD *hdata = (DWORD*)(&header[12]);
    *pSkip = *pEndPos = 0xFFFFFFFF;
    //ファイルポインタが先頭にあるとは限らない
    input_seek(hFile, 0, FILE_BEGIN);
    //ヘッダを調べる
    dwNumRead = input_read(hFile, header, 16);
    if(dwNumRead != 16)
        return;
    if(*hriff != *((const DWORD*)"RIFF")){
        return;//RIFF でない
    }
    while(1){
        //data チャンクを探す
        DWORD dwChunkSize = 0;
        while(*hdata != *((const DWORD*)"data")){
            dwNumRead = input_read(hFile, &dwChunkSize, sizeof(DWORD));
            if(dwNumRead != sizeof(DWORD)){
                return;
            }
            if(dwChunkSize & 0x01)//偶数バイトにする
                dwChunkSize++;
            if((int)dwChunkSize < 0){
                return;
            }
            input_seek(hFile, dwChunkSize, FILE_CURRENT);
            dwNumRead = input_read(hFile, hdata, sizeof(DWORD));
            if(dwNumRead != sizeof(DWORD)){
                return;
            }
            dwChunkSize = 0;
        }
        //data チャンクのサイズ
        dwNumRead = input_read(hFile, &dwChunkSize, sizeof(DWORD));
        if(dwNumRead != sizeof(DWORD)){
            return;
        }
        DWORD dwSkip = input_seek(hFile, 0, FILE_CURRENT);
        if(dwChunkSize&0x01){
            dwChunkSize++;//偶数バイトにする
        }
        if((int)dwChunkSize < 0)return;
        *pSkip = dwSkip;
        *pEndPos = dwSkip+dwChunkSize;
        break;
    }
}

static DWORD SkipZipHeader(HANDLE hFile, DWORD *pdwUncompressed)
{
    const int SIZEZIPLOCALHEADER = (0x1e);
#pragma pack(push, 1) 
    struct zip_info{
        DWORD magic;                // 0x4034b50 
        WORD  version;              // version made by                 2 bytes
        WORD  flag;                 // general purpose bit flag        2 bytes
        WORD  compression_method;   // compression method              2 bytes
        DWORD dosDate;              // last mod file date in Dos fmt   4 bytes
        DWORD crc;                  // crc-32                          4 bytes
        DWORD compressed_size;      // compressed size                 4 bytes
        DWORD uncompressed_size;    // uncompressed size               4 bytes
        WORD  size_filename;        // filename length                 2 bytes
        WORD  size_file_extra;      // extra field length              2 bytes
        WORD  size_file_comment;    // file comment length             2 bytes
    };
#pragma pack(pop)
    *pdwUncompressed = 0;
    input_seek(hFile, 0, SEEK_SET);
    zip_info zi;
    if(input_read(hFile, &zi, sizeof(zi)) != sizeof(zi)){
        return 0;
    }
    DWORD dwUncompressed = 0;
    int ret = 0;
    int cur = 0;
    int offset = 0;
    while(zi.magic == 0x04034b50){
        dwUncompressed = zi.uncompressed_size;
        offset = zi.size_filename + zi.size_file_extra + SIZEZIPLOCALHEADER;
        cur += offset;
        zi.magic = 0;
        input_seek(hFile, cur, SEEK_SET);
        if(input_read(hFile, &zi, sizeof(zi)) != sizeof(zi)){
            break;
        }
    }
    ret = cur;
    *pdwUncompressed = dwUncompressed;
    return ret;
}

static int getmp3info(HANDLE hFile, mp3info *info,id3tag *id3,VBRTAGDATA *vbr)
{
    unsigned long head;
    int lsf,srate;
    int bitrate_index,mode,nch,lay,extension,mpeg25,padding;
    int hpos,i;
    //char TmpStr[20];
    int lptr;

    DWORD dwUncompressed = 0;
    DWORD dwFileSize = input_seek(hFile, 0, FILE_END);
    info->isStream = 0;
    info->nbytes = dwFileSize;
    int skip_zip = SkipZipHeader(hFile, &dwUncompressed);
    input_seek(hFile, skip_zip, FILE_BEGIN);
    bool Riff = false;

    hpos = skip_zip;
    {
        BYTE tmp[4+2+4];
        if(input_read(hFile, tmp, sizeof(tmp)) != sizeof(tmp)){
            return 0;
        }
        if(tmp[0] == 'I' && tmp[1] == 'D' && tmp[2] == '3'){
            //Skip ID3v2 tag
            hpos = tmp[6]*2097152+tmp[7]*16384+tmp[8]*128+tmp[9]+10;
	        input_seek(hFile, hpos, FILE_BEGIN);
			if(input_read(hFile, tmp, sizeof(tmp)) != sizeof(tmp)){
				return 0;
			}
	        if(tmp[0] == 'I' && tmp[1] == 'D' && tmp[2] == '3'){
				hpos += tmp[6]*2097152+tmp[7]*16384+tmp[8]*128+tmp[9]+10;
				input_seek(hFile, hpos, FILE_BEGIN);
				if(input_read(hFile, tmp, sizeof(tmp)) != sizeof(tmp)){
					return 0;
				}
				if(tmp[0] == 'I' && tmp[1] == 'D' && tmp[2] == '3'){
					hpos += tmp[6]*2097152+tmp[7]*16384+tmp[8]*128+tmp[9]+10;
				}
			}
		}
        else if(*(DWORD*)tmp == *(DWORD*)"RIFF"){
            //Skip RIFF chunk
            DWORD dwSkip, dwEndPos;
            SkipRIFF(hFile, &dwSkip, &dwEndPos);
            if(dwSkip != 0xFFFFFFFF && dwEndPos != 0xFFFFFFFF){
                hpos = dwSkip;
                info->nbytes = dwEndPos;
                Riff = true;
            }
        }
    }
    
    lptr=0;
    NEXTSW:;
    for(i=lptr;i<65536;i++)
    {
        BYTE tmp[4];
        input_seek(hFile, hpos+i, FILE_BEGIN);
        if(input_read(hFile, tmp, 4) != 4)
            return 0;
        BYTE *p = (BYTE*)&head;
        p[0] = tmp[3]; p[1] = tmp[2]; p[2] = tmp[1]; p[3] = tmp[0];
        if(head_check(head))break;
    }
    if (i == 65536){
        return 0;
    }
    lptr=i;
    hpos += i;
    info->hpos = hpos;

    if(Riff == false) {
        info->nbytes -= hpos;
        // read ID3 tag
        input_seek(hFile, -128, FILE_END);
        input_read(hFile, id3, 128);
        if (memcmp(id3->tag,"TAG",3) == 0) info->nbytes -= 128;
    }
    if(info->nbytes <= 0){
        return 0;
    }
    input_seek(hFile, hpos, FILE_BEGIN);

    if( head & (1<<20) ) {
      lsf = (head & (1<<19)) ? 0x0 : 0x1;
      mpeg25 = 0;
    } else {
      lsf = 1;
      mpeg25 = 1;
    }

    bitrate_index = ((head>>12)&0xf);
    padding       = ((head>>9)&0x1);
    mode          = ((head>>6)&0x3);
    nch           = (mode == MPG_MD_MONO) ? 1 : 2;
    lay           = 4-((head>>17)&3);
    extension     = ((head>>8)&0x1);

    if(mpeg25) srate = 6 + ((head>>10)&0x3);
    else srate = ((head>>10)&0x3) + (lsf*3);

    //if (lay != 3){
    //    return 0;
    //}
    if (lay == 4){
        return 0;
    }

    //Check frame header//
    if(lay<0 || lay>4  || bitrate_index<1 || bitrate_index>14
		     || srate<0 || srate>8)
     {
         input_seek(hFile, -3, FILE_END);
	 goto NEXTSW; } 
     	
    // read VBR tag
    //pStream->Seek(pvInstance, hpos, NULL, FILE_BEGIN);

    info->lsf  = lsf;
    info->freq = freqs[srate];
    info->nch  = nch;
    
    {
        unsigned char buf[XING_HEADER_SIZE];

        if(input_read(hFile, buf, XING_HEADER_SIZE) != XING_HEADER_SIZE){
            return 1;
        }
        if(GetVbrTag(vbr,buf)) {
            int cur_bitrate = (int)(vbr->bytes*8/(vbr->frames*576.0*(lsf?1:2)/freqs[srate]));
            info->length = vbr->frames*576.0*(lsf?1:2)/freqs[srate];
            info->nbytes = vbr->bytes;
            info->hasVbrtag = 1;
            info->bitrate = cur_bitrate;
            if(dwUncompressed){
                int total_size = dwFileSize-info->hpos;
                int first_mp3_size = dwUncompressed - (info->hpos-skip_zip);
                info->length *= (double)total_size/(double)first_mp3_size;
            }
            else{
                static const int frame_samples_table[3]={384,1152,576};
                int frame_samples = frame_samples_table[lay-1];
                if(lay == 3){
                    if(!info->lsf){
                        frame_samples *= 2;
                    }   
                }
                info->total_samples = vbr->frames * frame_samples;
            }
        } else {
		    //if (bitrate_index==0){bitrate_index=9;lay=3;}
		    int framesize = tabsel_123[lsf][lay-1][bitrate_index]*144000/(freqs[srate]<<lsf)+padding;
            info->length = info->nbytes/framesize*576.0*(lsf?1:2)/freqs[srate];
            info->hasVbrtag = 0;
            info->bitrate = tabsel_123[lsf][lay-1][bitrate_index]*1000;
            //info->length = info->nbytes * 8 / info->bitrate;
        }
        const int POST_DELAY = 1152;
        const int DECODE_DELAY_LAYER1 = 0;
        const int DECODE_DELAY_LAYER2 = (480 + 1);
        const int DECODE_DELAY_LAYER3 = (528 + 1);
        static const int dec_delay_tbl[] = {0, 480+1, 528+1};
        int dec_delay = dec_delay_tbl[lay-1] + POST_DELAY;
        if(info->hasVbrtag){
            if(vbr->enc_delay > 0){
                dec_delay += vbr->enc_delay;
                info->total_samples -= vbr->enc_delay;
            }
            if(vbr->enc_padding > 0){
                info->total_samples -= vbr->enc_padding;
            }
            if(info->total_samples < 0){
                info->total_samples = 0;
            }
        }
        info->skip_samples = dec_delay;
    }
    return 1; 
}

enum channel {
  CHANNEL_STEREO  = 0,
  CHANNEL_MONO    = 1,
  CHANNEL_LEFT    = 2,
  CHANNEL_RIGHT   = 3,
  CHANNEL_REVERSE = 4
};


static int do_error(struct mad_stream *stream, struct mad_frame *frame,
	     HANDLE input, int *last_error)
{
    int do_continue = 1;
    //signed long tagsize;
    switch (stream->error) {
        case MAD_ERROR_BADCRC:
        if (last_error) {
            if (*last_error) {
	            if (frame)
	                mad_frame_mute(frame);
            }
            else
	            *last_error = 1;
        }
        do_continue = 0;
        break;
        case MAD_ERROR_LOSTSYNC:
            //tagsize = id3_tag_query(stream->this_frame,
			//        stream->bufend - stream->this_frame);
            //if (tagsize > 0)
            //    mad_stream_skip(stream, tagsize);
            //else if (stats)
            //    ++stats->sync_errors;
            break;
        default:
            //if (stats)
            //    ++stats->other_errors;
            break;
    }
    return do_continue;
}
static inline unsigned long prng(unsigned long state)
{
  return (state * 0x0019660dL + 0x3c6ef35fL) & 0xffffffffL;
}

static inline signed long linear_dither(unsigned int bits, mad_fixed_t sample,
			                            struct dither *dither, 
                                        unsigned long *clipped,
			                            mad_fixed_t *clipping,
                                        BOOL bEnableDither)
{
    unsigned int scalebits = MAD_F_FRACBITS + 1 - bits;
    mad_fixed_t output = sample;
    mad_fixed_t mask = (1L << scalebits) - 1;
    mad_fixed_t random = 0;
    enum {
        MIN = -MAD_F_ONE,
        MAX =  MAD_F_ONE - 1
    };
    
    if(bEnableDither){

    /* noise shape */
    sample += dither->error[0] - dither->error[1] + dither->error[2];

    dither->error[2] = dither->error[1];
    dither->error[1] = dither->error[0] / 2;

    /* bias */
    output = sample + (1L << (MAD_F_FRACBITS + 1 - bits - 1));

    scalebits = MAD_F_FRACBITS + 1 - bits;
    mask = (1L << scalebits) - 1;

    /* dither */
    random  = prng(dither->random);
    output += (random & mask) - (dither->random & mask);

    dither->random = random;

    }//if(bEnableDither)

    /* clip */
    if (output > MAX) {
        ++*clipped;
        if (output - MAX > *clipping)
            *clipping = output - MAX;

        output = MAX;

        if (sample > MAX)
            sample = MAX;
    }
    else if (output < MIN) {
        ++*clipped;
        if (MIN - output > *clipping)
            *clipping = MIN - output;

        output = MIN;

        if (sample < MIN)
            sample = MIN;
    }

    /* quantize */
    output &= ~mask;

    /* error feedback */
    dither->error[0] = sample - output;

    /* scale */
    return output >> scalebits;
}


//	DWORD GetWritten(void){//書き込んだバッファのサイズ
//			return m_dwWritten;
//		}

	void mp3init(void)
	{
		m_hFile = INVALID_HANDLE_VALUE;
		m_dwBufLen = 0;
		m_clipped = 0;
		m_clipping = 0;
		m_dwBitsPerSample = 16;
		m_bEnableDither = TRUE;
		m_bWatchDither = TRUE;
		m_hNotification = INVALID_HANDLE_VALUE;
		CloseHandle(m_hFile);
	}



			struct mad_stream    m_stream2;
			struct mad_header    m_header2;
			struct mad_frame     m_frame2;
			struct mad_synth     m_synth2;

	bool Open(const TCHAR *cszFileName, SOUNDINFO *pInfo)
	{
	    Close();
		//m_dwWritten=m_dwAllocSize =m_dwBufferSize= OUTPUT_BUFFER_SIZE*OUTPUT_BUFFER_NUM;
		if(!pInfo)return false;
		DWORD dwBitsPerSample = pInfo->dwBitsPerSample;
		ZeroMemory(pInfo, sizeof(SOUNDINFO));
		HANDLE hFile =  CreateFile(cszFileName, GENERIC_READ,
							FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
							OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		if (hFile == INVALID_HANDLE_VALUE)
			return false;
		id3tag     id3;
		VBRTAGDATA vbrtag;
		ZeroMemory(&id3, sizeof(id3));
		ZeroMemory(&vbrtag, sizeof(vbrtag));
		if(!getmp3info(hFile, &m_mp3info,&id3,&vbrtag)){
			CloseHandle(hFile);
			return NULL;
		}
		if(dwBitsPerSample == 8 ||
		   dwBitsPerSample == 16 ||
		   dwBitsPerSample == 24 ||
		   dwBitsPerSample == 32){
			m_dwBitsPerSample = dwBitsPerSample;
		}
		else if(dwBitsPerSample > 32){
			m_dwBitsPerSample = 32;
		}
		m_dwTotalBytes = m_mp3info.total_samples*((m_dwBitsPerSample/8)*m_mp3info.nch);
		m_dwSkipBytes = m_mp3info.skip_samples*((m_dwBitsPerSample/8)*m_mp3info.nch);
		pInfo->dwSamplesPerSec = m_mp3info.freq;
		pInfo->dwChannels = m_mp3info.nch;
		pInfo->dwBitsPerSample = m_dwBitsPerSample;
		pInfo->dwUnitRender = 576*m_mp3info.nch*2*2*m_dwBitsPerSample/8;
		pInfo->dwLength = (DWORD)(m_mp3info.length * 1000);
		pInfo->dwSeekable = 1;
		m_hFile = hFile;

		mad_header_init(&m_header2);
		mad_stream_init(&m_stream2);
		mad_frame_init(&m_frame2);
		mad_synth_init(&m_synth2);
		input_seek(m_hFile, m_mp3info.hpos, FILE_BEGIN);
		m_dwBytesDecoded=0;
		m_dwSkipRemain=0;
		m_ringbuf.Reset();
		m_clipped = 0;
		m_clipping = 0;
		m_dwBufLen = 0;
    mad_header_finish(&m_header);
    mad_stream_finish(&m_stream);
    mad_frame_finish(&m_frame);
    mad_synth_finish(&m_synth);

    mad_stream_init(&m_stream);
    mad_header_init(&m_header);
    mad_frame_init(&m_frame);
    mad_synth_init(&m_synth);
    ZeroMemory(&m_left_dither, sizeof(m_left_dither));
    ZeroMemory(&m_right_dither, sizeof(m_right_dither));

    input_seek(m_hFile, m_mp3info.hpos, FILE_BEGIN);
    DWORD bytes;
//    bytes = input_read(m_hFile, m_buffer + m_dwBufLen, sizeof(m_buffer) - m_dwBufLen);
		return true;
	}
		void Close(void)
	{
		m_dwBytesDecoded=0;
		m_dwSkipRemain=0;
		m_ringbuf.Reset();
		m_clipped = 0;
		m_clipping = 0;
		m_dwBufLen = 0;
		if(m_hFile != INVALID_HANDLE_VALUE){
			CloseHandle(m_hFile);
			m_hFile = INVALID_HANDLE_VALUE;
			mad_header_finish(&m_header2);
			mad_stream_finish(&m_stream2);
			mad_frame_finish(&m_frame2);
			mad_synth_finish(&m_synth2);
			mad_header_finish(&m_header);
			mad_stream_finish(&m_stream);
			mad_frame_finish(&m_frame);
			mad_synth_finish(&m_synth);
			ZeroMemory(&m_stream2, sizeof(m_stream2));
			ZeroMemory(&m_header2, sizeof(m_header2));
			ZeroMemory(&m_frame2, sizeof(m_frame2));
			ZeroMemory(&m_synth2, sizeof(m_synth2));
			ZeroMemory(&m_mp3info, sizeof(m_mp3info));
			ZeroMemory(&m_left_dither, sizeof(m_left_dither));
			ZeroMemory(&m_right_dither, sizeof(m_right_dither));
			m_clipped = 0;
			m_clipping = 0;
		}
//		if(m_hNotification != INVALID_HANDLE_VALUE){
//			FindCloseChangeNotification(m_hNotification);
//			m_hNotification = INVALID_HANDLE_VALUE;
//		}
	}

	float fade; 


	BOOL seek2(__int64 seek,int ch){
			__int64 seek2=(__int64)seek; //seek2*=100;
			if(m_hFile==INVALID_HANDLE_VALUE) return FALSE;
			input_seek(m_hFile, m_mp3info.hpos, FILE_BEGIN);
			__int64 cnt=0;
			if(seek==0) return TRUE;
			m_ringbuf.Reset();
			for(;;){
				input_read(m_hFile,m_tmp,4);
				input_seek(m_hFile, -4, FILE_CURRENT);
				BYTE a3=(m_tmp[1]>>3)&0x03;
				BYTE a2=(m_tmp[1]>>1)&0x03;
				BYTE a1=m_tmp[2]>>4;
				int tb=tabsel_123[(a3==3)?0:1][3-a2][a1];
				a1=(m_tmp[2]>>2)&0x03;
				int fr=freqs[a1];
				a1=(m_tmp[2]&0x2)>>1;
				int pb=(int)a1;
				int size=(144*tb*1000)/fr+pb;
				if(input_read(m_hFile, m_tmp, size+MAD_BUFFER_GUARD)!=size+MAD_BUFFER_GUARD){return FALSE;}
				input_seek(m_hFile, -MAD_BUFFER_GUARD, FILE_CURRENT);
				mad_stream_buffer(&m_stream2, m_tmp, size+MAD_BUFFER_GUARD);
				mad_header_decode(&m_header2, &m_stream2);
				cnt+=(__int64)((float)mad_timer_count(m_header2.duration, MAD_UNITS_MILLISECONDS)*44.1f*4.0f)+22;
				if(seek2*2*ch<cnt) return TRUE;
			}
		}


DWORD seek(DWORD dwPos,int ch)
{//シーク（戻り値はシーク後の再生位置）
	if (m_mp3info.hasVbrtag == TRUE) {
		return seek2(dwPos,ch);
	}
	DWORD seek2=dwPos;
    m_ringbuf.Reset();
    if(m_hFile == INVALID_HANDLE_VALUE){
        return 0;
    }
    m_clipped = 0;
    m_clipping = 0;
    m_dwBufLen = 0;
    mad_header_finish(&m_header);
    mad_stream_finish(&m_stream);
    mad_frame_finish(&m_frame);
    mad_synth_finish(&m_synth);

    mad_stream_init(&m_stream);
    mad_header_init(&m_header);
    mad_frame_init(&m_frame);
    mad_synth_init(&m_synth);
    ZeroMemory(&m_left_dither, sizeof(m_left_dither));
    ZeroMemory(&m_right_dither, sizeof(m_right_dither));

    input_seek(m_hFile, m_mp3info.hpos, FILE_BEGIN);
    DWORD bytes;
    bytes = input_read(m_hFile, m_buffer + m_dwBufLen, sizeof(m_buffer) - m_dwBufLen);
    if(bytes == 0){
        return 0;
    }
    m_dwBufLen += bytes;
    bytes = (DWORD)-1;
    DWORD dwRet = 0;
	mad_timer_t timer = mad_timer_zero;
    while(dwRet < seek2*2*ch) {
        if (m_stream.error == MAD_ERROR_BUFLEN ||
            m_dwBufLen < sizeof(m_buffer)/4) {
            bytes = input_read(m_hFile, m_buffer + m_dwBufLen, sizeof(m_buffer) - m_dwBufLen);
            m_dwBufLen += bytes;
        }
        mad_stream_buffer(&m_stream, m_buffer, m_dwBufLen);
        while(dwRet < seek2*2*ch) {
            if (mad_header_decode(&m_header2, &m_stream) == -1) {
                if(m_stream.error == MAD_ERROR_BUFLEN){
                    if(bytes == 0){
                        goto END;
                    }
                    break;
                }
                if(!MAD_RECOVERABLE(m_stream.error)){
	                break;
                }
                mad_frame_decode(&m_frame, &m_stream);
    	        //if (do_error(&m_stream, 0, m_hFile, 0))
                //     continue;
            }
            //mad_timer_add(&timer, m_header.duration);
            //dwRet = (DWORD)((float)mad_timer_count(m_header2.duration, MAD_UNITS_MILLISECONDS)*4.0f);
            dwRet += (DWORD)((float)mad_timer_count(m_header2.duration, MAD_UNITS_MILLISECONDS)*44.1f*4.0f)+22;
       }
        memmove(m_buffer, m_stream.next_frame, &m_buffer[m_dwBufLen] - m_stream.next_frame);
        m_dwBufLen -= m_stream.next_frame - &m_buffer[0];
    }
END:
//    m_dwSkipRemain = m_dwSkipBytes;
//    m_dwBytesDecoded = MulDiv(dwRet, m_mp3info.freq, 1000)*(m_mp3info.nch*(abs((int)m_dwBitsPerSample)/8));
//    if(m_dwBytesDecoded > m_dwTotalBytes){
   //     m_dwBytesDecoded = m_dwTotalBytes;
//    }
    return TRUE;   
}




	int Render2(BYTE* buf,int len,int fr)
	{
			if(m_hFile==INVALID_HANDLE_VALUE) return 0;
		{
		int cnt=0;
		for(;;){
			input_read(m_hFile,m_tmp,4);
			input_seek(m_hFile, -4, FILE_CURRENT);
			BYTE a3=(m_tmp[1]>>3)&0x03;
			BYTE a2=(m_tmp[1]>>1)&0x03;
			BYTE a1=m_tmp[2]>>4;
			int tb=tabsel_123[(a3==3)?0:1][3-a2][a1];
			a1=(m_tmp[2]>>2)&0x03;
			int fr=freqs[a1];
			a1=(m_tmp[2]&0x2)>>1;
			int pb=(int)a1;
			int size=(144*tb*1000)/fr+pb;
			BOOL i=input_read(m_hFile, m_tmp, size+MAD_BUFFER_GUARD);
			if(i<ERROR_HANDLE_EOF){return cnt;}
			if(fr<0){
				int a;
				a = 1;
			}

			input_seek(m_hFile, -MAD_BUFFER_GUARD, FILE_CURRENT);
			mad_stream_buffer(&m_stream2, m_tmp, size+MAD_BUFFER_GUARD);
			mad_frame_decode(&m_frame2, &m_stream2);
			mad_synth_frame(&m_synth2, &m_frame2);
			int nch = m_synth2.pcm.channels;
			mad_fixed_t *ch1 = m_synth2.pcm.samples[0];
			mad_fixed_t *ch2;
			if(nch==2)
				ch2 = m_synth2.pcm.samples[1];
			else
				ch2=NULL;
			int pcm_length = m_synth2.pcm.length;
			pack_pcm(m_tmp, pcm_length, ch1, ch2,  m_dwBitsPerSample, &m_clipped, &m_clipping);
			memcpy(buf+cnt,m_tmp,pcm_length*2*nch);
			cnt+=(pcm_length*2*nch);
			if(cnt>=len){return cnt;}
		}
		}

	}

	int Render(BYTE* out, DWORD dwSize)
	{
    DWORD dwRet = 0;
    DWORD bytes = (DWORD)-1;
    int err_count = 0;
    while (dwRet < dwSize) {
        if(m_dwSkipRemain){
            m_dwSkipRemain -= m_ringbuf.Read(m_tmp, m_dwSkipRemain);
        }
        if(m_dwTotalBytes){
            DWORD dwWritten = m_ringbuf.GetWritten();
            if(m_dwBytesDecoded + dwWritten >= m_dwTotalBytes){
                dwWritten = m_dwTotalBytes - m_dwBytesDecoded;
            }
            if(dwWritten > dwSize){
                dwWritten  = dwSize;
            }
            dwWritten = m_ringbuf.Read(out + dwRet, dwWritten);
            dwRet += dwWritten;
            m_dwBytesDecoded += dwWritten;
            if(m_dwBytesDecoded >= m_dwTotalBytes){
                return dwRet;
            }
        }
        else{
            dwRet += m_ringbuf.Read(out + dwRet, dwSize-dwRet);
            if(dwRet == dwSize){
                break;
            }
        }
        if(m_stream.error == MAD_ERROR_BUFLEN ||
           m_dwBufLen < sizeof(m_buffer)/4) {
            bytes = input_read(m_hFile, m_buffer + m_dwBufLen, sizeof(m_buffer) - m_dwBufLen);
            m_dwBufLen += bytes;
        }
        mad_stream_buffer(&m_stream, m_buffer, m_dwBufLen);
        while (1) {
            if(mad_frame_decode(&m_frame, &m_stream) == -1) {
                if(bytes == 0){
                    return dwRet;
                }
                if(m_stream.error == MAD_ERROR_BUFLEN){
                    break;
                }
                if(!MAD_RECOVERABLE(m_stream.error)){
	                return dwRet;
                }
                if(++err_count > 65536){
                    return dwRet;
                }
                continue;
                /*if (do_error(&m_stream, 0, m_hFile, 0)){
                    continue;
                }
                else{
                    return dwRet;
                }*/
            }
            mad_synth_frame(&m_synth, &m_frame);
            int nch = m_synth.pcm.channels;
            mad_fixed_t *ch1 = m_synth.pcm.samples[0];
            mad_fixed_t *ch2 = m_synth.pcm.samples[1];
            if(nch == 1){
                ch2 = NULL;
            }
            int pcm_length = m_synth.pcm.length;
            BYTE *tmp = NULL;
            m_ringbuf.LockBuffer(&tmp, pcm_length*m_synth.pcm.channels * m_dwBitsPerSample/8);
            if(!tmp){
                tmp = m_tmp;
            }
            pack_pcm(tmp, 
                     pcm_length, 
                     ch1, 
                     ch2, 
                     m_dwBitsPerSample, 
                     &m_clipped, &m_clipping);
            if(tmp == m_tmp){
                m_ringbuf.Write(tmp, pcm_length*m_synth.pcm.channels * m_dwBitsPerSample/8);
            }
            else{
                m_ringbuf.UnlockBuffer();
            }
            /*pack_pcm(out+dwRet, 
                     pcm_length, 
                     ch1, 
                     ch2, 
                     m_dwBitsPerSample, 
                     &m_clipped, &m_clipping);
            dwRet += pcm_length * m_synth.pcm.channels * m_dwBitsPerSample/8;
            */
            break;
        }
        memmove(m_buffer, m_stream.next_frame, &m_buffer[sizeof(m_buffer)] - m_stream.next_frame);
        m_dwBufLen -= m_stream.next_frame - m_buffer;
    }
	return dwRet;
}

	//static
	unsigned int pack_pcm(unsigned char *data, unsigned int nsamples,
				  mad_fixed_t const *left, mad_fixed_t const *right,
				  int resolution, unsigned long *clipped,
				  mad_fixed_t *clipping)
	{
	  dither &left_dither = m_left_dither;
	  dither &right_dither = m_right_dither;
	  unsigned char const *start;
	  register signed long sample0, sample1;
	  int effective, bytes;
	  BOOL bEnableDither = m_bEnableDither;  
	  start     = data;
	  effective = (resolution > 24) ? 24 : resolution;
	  bytes     = resolution / 8;

	  if (right) {  /* stereo */
		while (nsamples--) {
		  sample0 = linear_dither(effective, *left++, &left_dither,
					  clipped, clipping, bEnableDither);
		  sample1 = linear_dither(effective, *right++, &right_dither,
					  clipped, clipping, bEnableDither);
			
		  if(fade<1.0f){
			  sample0=(long)(sample0*fade);
			  sample1=(long)(sample1*fade);
			  fade+=0.01f;
		  }
		  switch (resolution) {
		  case 8:
		data[0] = (char)(sample0 ^ 0x80);
		data[1] = (char)(sample1 ^ 0x80);
		break;

		  case 32:
		sample0 <<= 8;
		sample1 <<= 8;
		data[        3] = (char)(sample0 >> 24);
		data[bytes + 3] = (char)(sample1 >> 24);
		  case 24:
		data[        2] = (char)(sample0 >> 16);
		data[bytes + 2] = (char)(sample1 >> 16);
		  case 16:
		data[        1] = (char)(sample0 >>  8);
		data[bytes + 1] = (char)(sample1 >>  8);
		data[        0] = (char)(sample0 >>  0);
		data[bytes + 0] = (char)(sample1 >>  0);
		  }

		  data += bytes * 2;
		}
	  }
	  else {  /* mono */
		while (nsamples--) {
		  sample0 = linear_dither(effective, *left++, &left_dither,
					  clipped, clipping, bEnableDither);

		  switch (resolution) {
		  case 8:
		data[0] = (char)(sample0 ^ 0x80);
		break;

		  case 32:
		sample0 <<= 8;
		data[3] = (char)(sample0 >> 24);
		  case 24:
		data[2] = (char)(sample0 >> 16);
		  case 16:
		data[1] = (char)(sample0 >>  8);
		data[0] = (char)(sample0 >>  0);
		  }
		  data += bytes;
		}
	  }

	  return data - start;
	}

};