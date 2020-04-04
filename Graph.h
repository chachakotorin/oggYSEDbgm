#pragma once
#include "afxwin.h"
#include "dshow.h"


// CGraph ダイアログ

class CGraph : public CDialog
{
	DECLARE_DYNAMIC(CGraph)

public:
	CGraph(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CGraph();
	DWORD CntPin2(IAMStreamSelect *pFilter);
// ダイアログ データ
	enum { IDD = IDD_GRAPH };
	HRESULT EnumFilters (IGraphBuilder *pGraph) ;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CButton m_ok;
	virtual BOOL OnInitDialog();
	CListBox m_l;
};
