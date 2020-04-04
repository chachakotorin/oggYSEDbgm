//	yaneCriticalSection.h :
//		programmed by yaneurao	'00/03/02

#ifndef __yaneCriticalSection_h__
#define __yaneCriticalSection_h__


class ICriticalSection {
public:
	virtual void	Enter()=0;
	virtual void	Leave()=0;
	virtual bool	IsLockedByThisThread() const =0;
	virtual ~ICriticalSection(){}
};

class CCriticalSection2 : public ICriticalSection {
/**
�@�X���b�h�Ԃ̔r���𐧌䂵�܂��B
�@����X���b�h��Enter�֐����Ăяo�������ƁALeave�֐����Ăяo���܂ł̊Ԃ́A
�@�N���e�B�J���Z�N�V�����ƂȂ�܂��B
�@�N���e�B�J���Z�N�V�������A�����ɂQ�ȏ�̃X���b�h�����s���邱�Ƃ͏o���܂���B
�@����X���b�h����Ȃ�΁A���d��Enter���邱�Ƃ��o���܂��B
�@�i�ڂ����́A�}���`�X���b�h�֌W�̕������Q�Ƃ��邱�Ɓj

  class CMutex �ɔ�r���āA���ɍ����Ȃ̂������ł��B

  ���ӁF
  �@CCriticalSection2�̎��̂́A�O���[�o���X�R�[�v�ɒu�����A
  �@static�ȃ����o�ϐ��ɂ��邩���Ă��������B
*/
public:
	virtual void	Enter();	///	CriticalSection�ɓ���
	virtual void	Leave();	///	CriticalSection����o��

	virtual bool	IsLockedByThisThread() const;
	/**
		���̃X���b�h�ɂ����Lock����Ă����true
	*/

	CCriticalSection2();
	virtual ~CCriticalSection2();
protected:
	CRITICAL_SECTION	m_csCriticalSection;
	DWORD				m_dwLockedThread;	//	Lock���Ă���ThreadId(0:��Lock)
	int					m_nLockCount;		//	Lock����Ă����
			//	(����X���b�h�Ȃ�Ε�����Lock�ł���̂�)
};

class CCriticalLock {
/**
	�N���e�B�J���Z�N�V�����̎g�p�⏕�N���X
		CCriticalSection2��Enter�ɓ������Ƃ��ɗ�O�����������
		���̊֐����甲���Ă��܂��̂ŁALeave����Ȃ��č��邱�Ƃ�����B
	�����ŁA
		{
			CCriticalLock guard(GetCriticalSection());
			//	�����ɂ��̏���������
		}
	�Ƃ����悤�Ɏg���΁A��O�����������Ƃ��Ă��A���̃N���X��
	�f�X�g���N�^�ŁACCriticalSection2::Leave���Ăяo����邱�Ƃ�
	�ۏ؂���܂��B

	�܂��ALeave/Enter�ŁA�����I��Leave/Enter���邱�Ƃ��ł���B

		��P�D
		{
			CCriticalLock guard(GetCriticalSection());
			guard.Leave();	//	CriticalSection���甲����
			//	���̂܂܃X�R�[�v�A�E�g�����ꍇ�ACCriticalSection2::Leave��
			//	�����Ăяo����Ȃ�
		}

		��Q�D
		{
			CCriticalLock guard(GetCriticalSection());
			guard.Enter();	//	CriticalSection�ɓ�d�ɓ���
			//	���̂܂܃X�R�[�v�A�E�g�����ꍇ�ACCriticalSection2::Leave��
			//	�Q�x�Ăяo�����
		}

		���@Enter/Leave�́A����CCriticalLock�̃C���X�^���X�𐶐�����
			�X���b�h�ȊO�̃X���b�h���Ăяo�����Ƃ͑z�肵�Ă��Ȃ��B


			//	synchronized�N���X(��yaneLockObject.h)���Q�Ƃ̂���
*/
public:
	CCriticalLock(ICriticalSection* cs);

	///	�����I��CriticalSection���甲����
	void	Leave();

	///	�����I��CriticalSection�ɓ���
	void	Enter();

	~CCriticalLock();

protected:
	ICriticalSection* m_cs;
	int m_nLockCount;	//	Lock����Ă����
	//	����CCriticalLock�̃f�X�g���N�^�ł́ALock(Enter)���ꂽ�񐔂���Unlock(Leave)���邱�Ƃ�ۏ؂���
};

//	�������Ȃ��_�~�[�̃��b�N�@�\��񋟂���
class SingleThread
{
protected:
	struct Lock {
		Lock(const SingleThread&) {};
	};
};

//	�I�u�W�F�N�g�P�ʂ̃��b�N�@�\��񋟂���
class MultiThread
{
protected:
	struct Lock {
		Lock(const MultiThread& o)
			: lock_object( &(const_cast<MultiThread&>(o).cs) ) {};
	private:
		CCriticalLock lock_object;
	};
private:
	friend struct Lock;
	CCriticalSection2 cs;
};

#endif
