#pragma once
#include <afxwin.h>
#include "CImageBase.h"


class CDailog1 :
    public CDialog
{
public:
    CDailog1() {

    };



    DECLARE_MESSAGE_MAP()

    CBrush m_brDlg;
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
};

