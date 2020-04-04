#pragma once
#include "afxwin.h"


// CListSyosai ダイアログ

class CListSyosai : public CDialog
{
	DECLARE_DYNAMIC(CListSyosai)

public:
	CListSyosai(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CListSyosai();

// ダイアログ データ
	enum { IDD = IDD_SYOSAI };


	playlistdata0 pc;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_name;
	CEdit m_id;
	CEdit m_game;
	CEdit m_art;
	CEdit m_alb;
	CEdit m_fol;
	afx_msg
		void OnClose();
	void OnBnClickedOk2();
	virtual BOOL OnInitDialog();
	CButton m_ok2;
	CEdit m_cmt;
	CEdit m_year;
	CEdit m_track;
	CEdit m_j;
};
