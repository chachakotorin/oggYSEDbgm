// Kpilist.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ogg.h"
#include "Kpilist.h"


// CKpilist ダイアログ

IMPLEMENT_DYNAMIC(CKpilist, CDialog)

CKpilist::CKpilist(CWnd* pParent /*=NULL*/)
	: CDialog(CKpilist::IDD, pParent)
{

}

CKpilist::~CKpilist()
{
}

void CKpilist::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lc);
}

#include "CImageBase.h"
BEGIN_MESSAGE_MAP(CKpilist, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CKpilist::OnLvnItemchangedList1)
cmn(CKpilist);

// CKpilist メッセージ ハンドラ
extern CString ext[150][30];
extern int kpicnt;
extern CString kpif[200];
extern TCHAR kpifs[200][64];
extern BOOL kpichk[200];
extern TCHAR karento2[1024];

BOOL CKpilist::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ここに初期化を追加してください

	m_tooltip.Create(this);
	m_tooltip.Activate(TRUE);
	m_tooltip.AddTool(GetDlgItem(IDOK),_T("閉じます"));
	m_tooltip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_tooltip.SendMessage(TTM_SETMAXTIPWIDTH, 0, 512);


	Init();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

BOOL kpichks[300];

void CKpilist::Init()
{
	DWORD dwExStyle = m_lc.GetExtendedStyle();
	dwExStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_INFOTIP | LVS_EX_CHECKBOXES;
	m_lc.SetExtendedStyle(dwExStyle);
	m_lc.ModifyStyle(0, LVS_REPORT);
	m_lc.InsertColumn(0, _T("kpi"), LVCFMT_LEFT, 100, 0);
	m_lc.InsertColumn(1, _T("拡張子"), LVCFMT_LEFT, 400, 0);

	//ファイル読み込み kpilist
	CString ss, sss;
	for (int i = 0; i < kpicnt; i++) {
		kpichk[i] = kpichks[i] = 1;
		ss = kpif[i].Right(kpif[i].GetLength() - kpif[i].ReverseFind('\\') - 1);
		_tcscpy(kpifs[i], ss);
	}

	CFile ff;
	int cnt = kpicnt;
	ss = karento2;
	ss += "kpilist.dat";
	if (ff.Open(ss, CFile::modeRead, NULL) == TRUE) {
		ff.Read(&cnt, sizeof(cnt));
		for (int i = 0; i < cnt; i++) {
			ff.Read(&kpichk[i], sizeof(BOOL));
			ff.Read(&kpifs[i], 64*sizeof(TCHAR));
		}
		ff.Close();
	}

	TCHAR *buf;
	buf = (TCHAR*)calloc(10000, 2);
	LV_ITEM LvItem;
	int      idItem;
	m_lc.DeleteAllItems();
	int Lindex = -1;
	for (int j = 0; j<kpicnt; j++) {//選択されているものをピックアップ
		CString s; s = "";
		try {
			if (status == 0) {
			for (int i = 0;; i++) {
				if (ext[j][i] == "") break;
				s += ext[j][i]; s += "/";
			}
			s = s.Left(s.GetLength() - 1);
			int a1, a2, a3;
			a1 = kpif[j].GetLength() * 2;
			a2 = kpif[j].ReverseFind(L'\\');
			a3 = a1 - a2;
			_tcscpy(buf, kpif[j].Right(a3));	LvItem.pszText = buf;
			
			LvItem.iItem = m_lc.GetItemCount();
			LvItem.mask = LVIF_TEXT | LVIF_STATE;
			LvItem.stateMask = LVIS_FOCUSED | LVIS_SELECTED;
			LvItem.state = 0;
			LvItem.iSubItem = 0;
			LvItem.cchTextMax = _tcslen(LvItem.pszText);
			idItem = m_lc.InsertItem(&LvItem);
			// InsertItem() によって item ID (行番号) が返される
			LvItem.iItem = idItem;
			_tcscpy(buf, s);	LvItem.iSubItem = 1;
			LvItem.pszText = buf;
			m_lc.SetItem(&LvItem);
			ss = kpif[j].Right(kpif[j].GetLength() - kpif[j].ReverseFind('\\') - 1);
			m_lc.SetCheck(j, TRUE);
			for (int i = 0; i < cnt; i++) {
				sss = kpifs[i];
				if (ss == sss) {
					if (kpichk[i] == 0) {
						m_lc.SetCheck(j, FALSE);
					}
					else {
						m_lc.SetCheck(j, TRUE);
					}
				}
			}
			}
		}
		catch (...) {
			break;
		}
		try {
			if (status == 1) {
				ss = kpif[j].Right(kpif[j].GetLength() - kpif[j].ReverseFind('\\') - 1);
				for (int i = 0; i < cnt; i++) {
					sss = kpifs[i];
					if (ss == sss) {
						if (kpichk[i] == 0) {
							kpichks[j] = 0;
						}
						else {
							kpichks[j] = 1;
						}
					}
				}
			}
		}
		catch (...) {
				break;
			}

	}
	free(buf);
	RECT r;
	GetWindowRect(&r);
	r.top += 600;
	r.bottom += 600;
	MoveWindow(&r);
}

void CKpilist::Save()
{
	CFile ff;
	TCHAR tc[64];
	CString ss;
	ss = karento2;
	ss += "kpilist.dat";
	if (ff.Open(ss, CFile::modeCreate | CFile::modeWrite, NULL) == TRUE) {
		ff.Write(&kpicnt, sizeof(int));
		for (int i = 0; i < kpicnt; i++) {
			if (status == 1) {
				kpichk[i] = kpichks[i];
			}
			else {
				kpichk[i] = m_lc.GetCheck(i);
			}
			ff.Write(&kpichk[i], sizeof(BOOL));
			_tcscpy(tc, kpif[i].Right(kpif[i].GetLength() - kpif[i].ReverseFind('\\') - 1));
			ff.Write(tc, 64 * sizeof(TCHAR));
		}
		ff.Close();
	}
}

void CKpilist::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	*pResult = 0;
}

BOOL CKpilist::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
		m_tooltip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

