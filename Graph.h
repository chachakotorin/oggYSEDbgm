#pragma once
#include "afxwin.h"
#include "dshow.h"


// CGraph �_�C�A���O

class CGraph : public CDialog
{
	DECLARE_DYNAMIC(CGraph)

public:
	CGraph(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CGraph();
	DWORD CntPin2(IAMStreamSelect *pFilter);
// �_�C�A���O �f�[�^
	enum { IDD = IDD_GRAPH };
	HRESULT EnumFilters (IGraphBuilder *pGraph) ;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
	CButton m_ok;
	virtual BOOL OnInitDialog();
	CListBox m_l;
};
