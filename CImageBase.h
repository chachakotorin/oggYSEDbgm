﻿#pragma once
#include "afxdialogex.h"

// CImageBase ダイアログ

class CImageBase : public CDialogEx
{
	DECLARE_DYNAMIC(CImageBase)

public:
	CImageBase(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~CImageBase();


	afx_msg int Create(CWnd* pWnd);
	 CWnd* m_pParent;
	 void move();

	 
	 CWnd* oya;

	 int m_bMoving_;
	 CPoint m_pointOld_;
// ダイアログ データ

	enum { IDD = IDD_IMAGEBASE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
