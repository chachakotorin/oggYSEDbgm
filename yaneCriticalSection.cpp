#include "stdafx.h"

CCriticalSection2::CCriticalSection2(){
	::InitializeCriticalSection(&m_csCriticalSection);
	m_dwLockedThread = (DWORD)-1;
	m_nLockCount	= 0;
}

CCriticalSection2::~CCriticalSection2(){
	::DeleteCriticalSection(&m_csCriticalSection);
	if (m_nLockCount!=0) {
#ifdef USE_EXCEPTION
		throw CRuntimeException("CCriticalSection2をEnterした回数だけLeaveしないまま終了している");
#endif
	}
}

void CCriticalSection2::Enter(){
	::EnterCriticalSection(&m_csCriticalSection);
	m_dwLockedThread = ::GetCurrentThreadId();
	//	↑異なるスレッドからここに入ってくることはできない
	//	(CriticalSectionの定義より)
	m_nLockCount++;
}

void CCriticalSection2::Leave(){
#ifdef USE_EXCEPTION
	if (m_nLockCount==0){
		throw CRuntimeException("CCriticalSection2をEnterしていないのにLeaveしている");
	}
#endif
	if (--m_nLockCount==0) {
		m_dwLockedThread = (DWORD)-1;
	}
	//	↑Leaveした直後に他スレッドがEnterする可能性がある
	::LeaveCriticalSection(&m_csCriticalSection);
}

bool CCriticalSection2::IsLockedByThisThread() const{
	DWORD dw = ::GetCurrentThreadId();
	return m_dwLockedThread == dw;
}

/////////////////////////////////////////////////////////////////////

CCriticalLock::CCriticalLock(ICriticalSection* cs): m_cs(cs),m_nLockCount(0)
{
	Enter();
}

void	CCriticalLock::Leave(){
	if (m_nLockCount-- == 0){
/*
#ifdef USE_EXCEPTION
		throw CRuntimeException("CCriticalLock::Leave(Enterされていない)");
#endif
*/
		//	↑これは実はありうる
		//	例)CriticalLockしているなかで、いったんLeaveして、そのあと
		//		例外が発生してEnterしなおす前に抜けたなど..
		return ;
	}
	m_cs->Leave();
}

void	CCriticalLock::Enter(){
	m_cs->Enter();
	m_nLockCount++;
	//	↑ if (++m_nLockCount==0) { m_cs->Enter(); }
	//	とは書けない。なぜなら、++m_nLockCountがatomicでは無い
}

CCriticalLock::~CCriticalLock()
{
	//	guardされていたときのみ解放
	if (0<m_nLockCount){
		for(int i=0;i<m_nLockCount;i++) m_cs->Leave();
	}
}

