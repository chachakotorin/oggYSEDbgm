#if !defined(AFX_LINKSTATIC_H__8E6FCCDA_144A_4380_9195_02E9428E656D__INCLUDED_)
#define AFX_LINKSTATIC_H__8E6FCCDA_144A_4380_9195_02E9428E656D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LinkStatic.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CLinkStatic �E�B���h�E

class CLinkStatic : public CStatic
{
// �R���X�g���N�V����
public:
	CLinkStatic();

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CLinkStatic)
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CLinkStatic();

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CLinkStatic)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	void ReSetColor();
	BOOL m_bClick;		// �����N��ŃN���b�N���ꂽ���̃t���O
	HICON m_hCursor;	// �w�̃J�[�\����ۑ�
	CFont m_font;		// �������������t�H���g��ݒ肷��
	COLORREF m_text;	// ���I�Ƀ����N�̐F��ς���ׂ̃J���[�l
	CBrush m_brush;		// �F��ݒ肷��ׂ̃u���V
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_LINKSTATIC_H__8E6FCCDA_144A_4380_9195_02E9428E656D__INCLUDED_)
