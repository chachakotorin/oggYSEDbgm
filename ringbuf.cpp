#include "stdafx.h"
#include "ringbuf.h"

KbRingBuffer::KbRingBuffer(DWORD dwInitialSize/*=0*/)
{
    m_hHeap = NULL;
    m_pBuffer = NULL;
    if((int)dwInitialSize <= 0){
        dwInitialSize = 4*1024;
    }
    m_dwReadPos = m_dwWritePos = m_dwWritten = 0;
    m_dwBufferSize = dwInitialSize;
    m_dwAllocSize = 0;

    m_dwLockedSize = 0;
}

KbRingBuffer::~KbRingBuffer(void)
{
    if(m_hHeap){
        HeapDestroy(m_hHeap);
    }
}
void __fastcall KbRingBuffer::Expand(DWORD dwNewSize)
{//リングバッファのサイズを拡大・縮小する
 //サイズを縮小する場合は、縮小前のデータはすべて失われる
 //サイズを拡大する場合は、拡大前後でデータは失われない
    //OutputDebugString("Expand\n");
    BYTE *pNewBuf;
    if(dwNewSize < m_dwBufferSize){//縮小する
        m_dwReadPos = m_dwWritePos = m_dwWritten = 0;//縮小前のデータはすべて失われる
    }
#if 1
    //排他処理は呼び出し側で管理するので HEAP_NO_SERIALIZE で問題なし
    if(!m_hHeap){
        m_hHeap = ::HeapCreate(HEAP_NO_SERIALIZE, dwNewSize+4096, 0);
        pNewBuf = (BYTE*)HeapAlloc(m_hHeap, HEAP_NO_SERIALIZE, dwNewSize);
    }
    else{
        pNewBuf = (BYTE*)HeapReAlloc(m_hHeap, HEAP_NO_SERIALIZE, m_pBuffer, dwNewSize);
    }
    if(m_dwReadPos > m_dwWritePos || 
       (m_dwReadPos == m_dwWritePos && m_dwWritten != 0)){
        DWORD dwExpandSize = dwNewSize-m_dwBufferSize;
        //memmove(pNewBuf + m_dwReadPos + dwExpandSize, pNewBuf+m_dwReadPos, 
        //            m_dwBufferSize-m_dwReadPos);
        const DWORD *end4 = (DWORD*)(pNewBuf+m_dwReadPos);
        DWORD *src4 = (DWORD*)(pNewBuf+m_dwBufferSize-4);
        DWORD *dst4 = (DWORD*)((BYTE*)src4+dwExpandSize);
        while(src4 >= end4){
            *dst4-- = *src4--;
        }
        BYTE *src = (BYTE*)src4+3;
        BYTE *dst = (BYTE*)dst4;
        while(src >= (const BYTE*)end4){
            *dst-- = *src--;
        }
        m_dwReadPos += dwExpandSize;
    }
#else
    DWORD dwWritten = m_dwWritten;
    if(!m_hHeap){
        m_hHeap = ::HeapCreate(HEAP_NO_SERIALIZE, dwNewSize+4096, 0);
    }
    pNewBuf = (BYTE*)HeapAlloc(m_hHeap, HEAP_NO_SERIALIZE, dwNewSize);
    Read(pNewBuf, dwWritten);
    HeapFree(m_hHeap, 0, m_pBuffer);
    m_dwReadPos = 0;
    m_dwWritePos = m_dwWritten = dwWritten;
#endif
    m_pBuffer = pNewBuf;
    m_dwBufferSize = dwNewSize;
    m_dwAllocSize = dwNewSize;
}

DWORD __fastcall KbRingBuffer::Read(BYTE* buf, DWORD dwSize)
{//リングバッファの内容を読み取る
 //実際に読み取ったバイト数を返す
    if(dwSize > m_dwWritten){
        dwSize = m_dwWritten;
    }
    DWORD dwCopyFirst;//先頭部分からのコピーサイズ
    DWORD dwCopyTail; //終端部分からのコピーサイズ
    dwCopyTail = m_dwAllocSize-m_dwReadPos;
    if(dwCopyTail > dwSize){
        dwCopyTail = dwSize;
    }
    dwCopyFirst = dwSize-dwCopyTail;

    memcpy(buf,m_pBuffer+m_dwReadPos,dwCopyTail);
	memcpy(buf+dwCopyTail,m_pBuffer,dwCopyFirst);
    m_dwReadPos += dwSize;
    if(m_dwReadPos > m_dwAllocSize){
        m_dwReadPos -= m_dwAllocSize;
    }
    m_dwWritten -= dwSize;
    return dwSize;
}
void __fastcall KbRingBuffer::Write(const BYTE* buf, DWORD dwSize)
{//リングバッファに書き込む
 //バッファサイズが足りない場合は拡大する
    if(m_dwAllocSize-m_dwWritten < dwSize){
        DWORD dwNewSize = m_dwWritten + dwSize;
        if(dwNewSize < m_dwBufferSize){
            //これがないと SetSize でサイズ拡大を指定した意味がなくなる
            dwNewSize = m_dwBufferSize;
        }
        Expand(dwNewSize);
    }
    DWORD dwCopyFirst;//先頭部分へのコピーサイズ
    DWORD dwCopyTail; //終端部分へのコピーサイズ
    dwCopyTail = m_dwAllocSize-m_dwWritePos;
    if(dwCopyTail > dwSize){
        dwCopyTail = dwSize;
    }
    dwCopyFirst = dwSize-dwCopyTail;
    memcpy(m_pBuffer+m_dwWritePos, buf,dwCopyTail);
	memcpy(m_pBuffer,buf+dwCopyTail,dwCopyFirst);
    m_dwWritePos += dwSize;
    if(m_dwWritePos > m_dwAllocSize){
        m_dwWritePos -= m_dwAllocSize;
    }
    m_dwWritten += dwSize;
}
BYTE* __fastcall KbRingBuffer::LockBuffer(BYTE** ppBuf,DWORD dwSize)
{//リングバッファに直接書き込む
 //戻り値への書き込みは呼び出し側で行う
 //バッファサイズが足りない場合は拡大する
    if(m_dwAllocSize-m_dwWritten < dwSize){
        DWORD dwNewSize = m_dwWritten + dwSize;
        if(dwNewSize < m_dwBufferSize){
            //これがないと SetSize でサイズ拡大を指定した意味がなくなる
            dwNewSize = m_dwBufferSize;
        }
        Expand(dwNewSize);
    }
    DWORD dwCopyFirst;//先頭部分へのコピーサイズ
    DWORD dwCopyTail; //終端部分へのコピーサイズ
    dwCopyTail = m_dwAllocSize-m_dwWritePos;
    if(dwCopyTail > dwSize){
        dwCopyTail = dwSize;
    }
    dwCopyFirst = dwSize-dwCopyTail;
    if(dwCopyTail == dwSize){
        *ppBuf = m_pBuffer + m_dwWritePos;
    }
    else if(dwCopyFirst == dwSize){
        *ppBuf = m_pBuffer;
    }
    else{//先頭と終端の両方に書き込まなければならない場合
        *ppBuf = NULL;
    }
    //m_pLocked = *ppBuf;
    m_dwLockedSize = dwSize;
    return *ppBuf;
}
void __fastcall KbRingBuffer::UnlockBuffer(void)
{//リングバッファへの直接書き込み終了
    if(m_dwLockedSize){
        m_dwWritePos += m_dwLockedSize;
        if(m_dwWritePos > m_dwAllocSize){
            m_dwWritePos -= m_dwAllocSize;
        }
        m_dwWritten += m_dwLockedSize;
        m_dwLockedSize = 0;
    }
}
void  __fastcall KbRingBuffer::SetSize(DWORD dwSize)
{//リングバッファのサイズを設定する
    if(dwSize < m_dwAllocSize){
        //現在のバッファサイズよりも小さいサイズを指定した場合は
        //即座にバッファサイズを小さくする
        //サイズ変更前のデータはすべて失われる
        Expand(dwSize);
    }
    else{
        //現在のバッファサイズよりも大きくする場合はサイズ変更前
        //のデータは失われない
        m_dwBufferSize = dwSize;
        Expand(dwSize);
    }
}
