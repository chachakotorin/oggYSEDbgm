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
		throw CRuntimeException("CCriticalSection2��Enter�����񐔂���Leave���Ȃ��܂܏I�����Ă���");
#endif
	}
}

void CCriticalSection2::Enter(){
	::EnterCriticalSection(&m_csCriticalSection);
	m_dwLockedThread = ::GetCurrentThreadId();
	//	���قȂ�X���b�h���炱���ɓ����Ă��邱�Ƃ͂ł��Ȃ�
	//	(CriticalSection�̒�`���)
	m_nLockCount++;
}

void CCriticalSection2::Leave(){
#ifdef USE_EXCEPTION
	if (m_nLockCount==0){
		throw CRuntimeException("CCriticalSection2��Enter���Ă��Ȃ��̂�Leave���Ă���");
	}
#endif
	if (--m_nLockCount==0) {
		m_dwLockedThread = (DWORD)-1;
	}
	//	��Leave��������ɑ��X���b�h��Enter����\��������
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
		throw CRuntimeException("CCriticalLock::Leave(Enter����Ă��Ȃ�)");
#endif
*/
		//	������͎��͂��肤��
		//	��)CriticalLock���Ă���Ȃ��ŁA��������Leave���āA���̂���
		//		��O����������Enter���Ȃ����O�ɔ������Ȃ�..
		return ;
	}
	m_cs->Leave();
}

void	CCriticalLock::Enter(){
	m_cs->Enter();
	m_nLockCount++;
	//	�� if (++m_nLockCount==0) { m_cs->Enter(); }
	//	�Ƃ͏����Ȃ��B�Ȃ��Ȃ�A++m_nLockCount��atomic�ł͖���
}

CCriticalLock::~CCriticalLock()
{
	//	guard����Ă����Ƃ��̂݉��
	if (0<m_nLockCount){
		for(int i=0;i<m_nLockCount;i++) m_cs->Leave();
	}
}

