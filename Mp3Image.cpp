// Mp3Image.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "ogg.h"
#include "Mp3Image.h"
#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>
#include "oggDlg.h"
extern BOOL miw;
extern CMp3Image *mi;
extern int killw1;
extern OggVorbis_File vf;
extern ULONGLONG po;
void CMp3Image::OnNcDestroy()
{
	CDialog::OnNcDestroy();

	// TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����܂��B
	killw1=1;
}
// CMp3Image �_�C�A���O

IMPLEMENT_DYNAMIC(CMp3Image, CDialog)

CMp3Image::CMp3Image(CWnd* pParent /*=NULL*/)
	: CDialog(CMp3Image::IDD, pParent)
{
m_hIcon = AfxGetApp()->LoadIcon(IDI_PL);
}

CMp3Image::~CMp3Image()
{
}

void CMp3Image::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, m_x);
	DDX_Control(pDX, IDC_STATIC2, m_y);
	DDX_Control(pDX, IDOK, m_close);
}


BEGIN_MESSAGE_MAP(CMp3Image, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_NCDESTROY()
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &CMp3Image::OnBnClickedOk)
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

BYTE bufimage[0x30000f];
// CMp3Image ���b�Z�[�W �n���h��

float hD1;

BOOL CMp3Image::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �����ɏ�������ǉ����Ă�������
	// Get desktop dc

	CDC *desktopDc = GetDC();
	// Get native resolution
	int horizontalDPI = GetDeviceCaps(desktopDc->m_hDC, LOGPIXELSX);
	hD1 = (float)(horizontalDPI) / (96.0f);
	SetStretchBltMode(dc.m_hDC, COLORONCOLOR);
	ReleaseDC(desktopDc);

	ModifyStyleEx(0, WS_EX_LAYERED);
	SetLayeredWindowAttributes(RGB(255, 0, 0), 0, LWA_COLORKEY);
	m_brDlg.CreateSolidBrush(RGB(255, 0, 0));

	nnn=1;
	RECT r;
	GetClientRect(&r);
	rcm.top=0;rcm.left=0;rcm.right=r.right;rcm.bottom=r.bottom;
//	m_close.MoveWindow(r.right-50 * hD1,50 * hD1,50 * hD1,50 * hD1);
	//m_x.MoveWindow(r.right-50* hD1,110 * hD1,50 * hD1,50 * hD1);
	//m_y.MoveWindow(r.right-50* hD1,140 * hD1,50 * hD1,50 * hD1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}
extern COggDlg *og;
CRect grect;
//extern TCHAR karento2[1024];
void CMp3Image::Load(CString s)
{
	CString s1,s2;
	TCHAR env[256];
	GetEnvironmentVariable(_T("temp"),env,sizeof(env));
	s1=env;s1+="\\";
	s2=s1;

	char *cBit;
	HGLOBAL hG=NULL;
	IStream *stream;

	CFile ff;
	if(ff.Open(s,CFile::modeRead|CFile::shareDenyNone,NULL)==FALSE){
		DestroyWindow();
		return;
	}
	UINT size;
	ULONGLONG i, enc;
	s.MakeLower();
	if (s.Right(3) == "mp3"){
		ZeroMemory(bufimage, 2005);
		ff.Read(bufimage, 2005);
		if (bufimage[0x14] == 0 || bufimage[0x14] == 3) enc = 0; else enc = 1;
		for (i = 0; i < 2000; i++){
			if (bufimage[i] == 0x41 && bufimage[i + 1] == 0x50 && bufimage[i + 2] == 0x49 && bufimage[i + 3] == 0x43){
				break;
			}
		}
		if (i == 2000){
			DestroyWindow();
			return;
		}
		size = (UINT)bufimage[i + 4];
		size <<= 8;
		size |= (UINT)bufimage[i + 5];
		size <<= 8;
		size |= (UINT)bufimage[i + 6];
		size <<= 8;
		size |= (UINT)bufimage[i + 7];
		enc = bufimage[i + 10];
		i += (4 + 4 + 3 + 6);
		int flg = 0;
		if (bufimage[i] == 'p'){ s1 += _T("111.png"); }
		else { s1 += _T("111.jpg"); }
		s2 += _T("111.bmp");
		for (; i<2000; i++){
			if (bufimage[i] == 0)
				break;
		}
		i += 2;

		if ((bufimage[i] == 0xff || bufimage[i] == 0xfe)){
			for (; i<2000; i++){
				if (enc == 1){
					if (bufimage[i] == 0 && bufimage[i + 1] == 0){
						if (bufimage[i + 1] == 0 && bufimage[i + 2] == 0)
							flg = 1;
						break;
					}
				}
				else{
					if (bufimage[i] == 0)
						flg = 1;
					break;
				}
			}
			if (i == 2000){
				DestroyWindow();
				return;
			}
			i += flg;
			if (enc == 1)
				i += 2;
		}
		else i++;
	}
	else if (s.Right(3) == "m4a"){
		ZeroMemory(bufimage, sizeof(bufimage));
		ff.Read(bufimage, sizeof(bufimage));
		if (bufimage[0x14] == 0 || bufimage[0x14] == 3) enc = 0; else enc = 1;
		for (i = 0; i < 0x300000; i++){// 00 06 5D 6A 64 61 74 61
			if (bufimage[i] == 0x63 && bufimage[i + 1] == 0x6f && bufimage[i + 2] == 0x76 && bufimage[i + 3] == 0x72 && bufimage[i + 8] == 0x64 && bufimage[i + 9] == 0x61 && bufimage[i + 10] == 0x74 && bufimage[i + 11] == 0x61){
				break;
			}
		}
		if (i == 0x300000){
			DestroyWindow();
			return;
		}
		i += 4;
		size = (UINT)bufimage[i];
		size <<= 8;
		size |= (UINT)bufimage[i + 1];
		size <<= 8;
		size |= (UINT)bufimage[i + 2];
		size <<= 8;
		size |= (UINT)bufimage[i + 3];
		size -= 16;

		i += 16;
		if (bufimage[i + 1] == 0x50 && bufimage[i + 2] == 0x4e && bufimage[i + 3] == 0x47){
			s1 += _T("111.png");
		}else{
			s1 += _T("111.jpg");
		}
		s2 += _T("111.bmp");
	}
	else if (s.Right(3) == "ogg"){
		CString cc;
		int vfiii = FALSE;
		for (int iii = 0; iii < vf.vc->comments; iii++){
#if _UNICODE
			WCHAR *f; f = new WCHAR[0x300000];
			MultiByteToWideChar(CP_UTF8, 0, vf.vc->user_comments[iii], -1, f, 0x300000);
			cc = f;
			delete [] f;
#else
			cc = vf.vc->user_comments[iii];
#endif
			if (cc.Left(23) == "METADATA_BLOCK_PICTURE="){
				vfiii = TRUE;
				char *buf = vf.vc->user_comments[iii];
				buf += 23;//Base64
				int len;
				char *decode = b64_decode(buf, strlen(buf),len);
				if (decode[16 + 16 + 10] == 0x50 && decode[1 + 16 + 16 + 10] == 0x4e && decode[2 + 16 + 16 + 10] == 0x47){
					s1 += _T("111.png");
				}
				else{
					s1 += _T("111.jpg");
					decode += 1;
				}
				s2 += _T("111.bmp");
				for (int j = 0; j < len; j++) {
					if (*(decode + len - j - 1) != 0) {
						len -= j;
						break;
					}
				}
				hG = GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, len);
				memcpy(hG, decode + 16 + 16 + 9, len);
				CreateStreamOnHGlobal(hG, TRUE, &stream);
				//CFile fff; if (fff.Open(s1, CFile::modeCreate | CFile::modeWrite, NULL) == TRUE) {
				//	fff.Write(decode + 16 + 16 + 9, len-16-16-10);
				//	fff.Close();
				//}
				free(decode);
				break;
			}
		}
		if (vfiii == FALSE){
			DestroyWindow();
			return;
		}
	}
	else if (s.Right(4) == "flac") {
		ZeroMemory(bufimage, sizeof(bufimage));
		ff.Read(bufimage, sizeof(bufimage));
		for (i = 0; i < 0x300000; i++) {// 00 06 5D 6A 64 61 74 61
			if (bufimage[i] == 'i' && bufimage[i + 1] == 'm' && bufimage[i + 2] == 'a' && bufimage[i + 3] == 'g' && bufimage[i + 4] == 'e' && bufimage[i + 5] == '/' && bufimage[i + 6] == 'j' && bufimage[i + 7] == 'p' && bufimage[i + 8] == 'e' && bufimage[i + 9] == 'g') {
				s1 += _T("111.jpg");
				i++;
				break;
			}
			if (bufimage[i] == 'i' && bufimage[i + 1] == 'm' && bufimage[i + 2] == 'a' && bufimage[i + 3] == 'g' && bufimage[i + 4] == 'e' && bufimage[i + 5] == '/' && bufimage[i + 6] == 'p' && bufimage[i + 7] == 'n' && bufimage[i + 8] == 'g') {
				s1 += _T("111.png");
				break;
			}
		}
		if (i == 0x300000) {
			DestroyWindow();
			return;
		}
		i += 29;
		size = (UINT)bufimage[i];
		size <<= 8;
		size |= (UINT)bufimage[i + 1];
		size <<= 8;
		size |= (UINT)bufimage[i + 2];
		size <<= 8;
		size |= (UINT)bufimage[i + 3];

		i += 4;
		s2 += _T("111.bmp");
	}
	else if (s.Right(3) == "dsf"|| s.Right(3) == "dff") {
		CString tagfile, tagname, tagalbum;
		CFile f; f.Open(s, CFile::modeRead | CFile::shareDenyNone);
		f.Seek((ULONGLONG)po, CFile::begin);
		int read = f.Read(bufimage, sizeof(bufimage));
		f.Close();
		for (i = 0; i < read; i++) {// 00 06 5D 6A 64 61 74 61
			if (bufimage[i] == 'i' && bufimage[i + 1] == 'm' && bufimage[i + 2] == 'a' && bufimage[i + 3] == 'g' && bufimage[i + 4] == 'e' && bufimage[i + 5] == '/' && bufimage[i + 6] == 'j' && bufimage[i + 7] == 'p' && bufimage[i + 8] == 'e' && bufimage[i + 9] == 'g') {
				s1 += _T("111.jpg");
				i++;
				break;
			}
			if (bufimage[i] == 'i' && bufimage[i + 1] == 'm' && bufimage[i + 2] == 'a' && bufimage[i + 3] == 'g' && bufimage[i + 4] == 'e' && bufimage[i + 5] == '/' && bufimage[i + 6] == 'p' && bufimage[i + 7] == 'n' && bufimage[i + 8] == 'g') {
				s1 += _T("111.png");
				break;
			}
		}
		if (i == read) {
			DestroyWindow();
			return;
		}
		for (i = 0; i < read; i++) {
			if (bufimage[i] == 'A' && bufimage[i + 1] == 'P' && bufimage[i + 2] == 'I' && bufimage[i + 3] == 'C') {
				break;
			}
		}
		i += 4;
		size = (UINT)bufimage[i];
		size <<= 8;
		size |= (UINT)bufimage[i + 1];
		size <<= 8;
		size |= (UINT)bufimage[i + 2];
		size <<= 8;
		size |= (UINT)bufimage[i + 3];

		i += 4+po+16;
		s2 += _T("111.bmp");

	}

	if (s.Right(3) != "ogg"){
		//int ijk = i;
		//CFile fff;
		//if (fff.Open(s1, CFile::modeCreate | CFile::modeWrite, NULL) == FALSE){
		//	int a = 0;
		//}
		//i = ijk;
		//ff.SeekToBegin();
		//ff.Seek(i, CFile::begin);
		//char *b = new char[size];
		//ff.Read(b, size);
		//fff.Write(b, size);
		//delete[] b;
		//ff.Close();
		//fff.Close();
		hG = GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, size);
		ff.SeekToBegin();
		ff.Seek(i, CFile::begin);
		char *cBit = new char[size];
		ff.Read(cBit, size);
		ff.Close();
		memcpy(hG, cBit, size);
		delete[] cBit;
		CreateStreamOnHGlobal(hG, TRUE, &stream);

	}

	cdc0 = GetDC();
	if (img.Load(stream) == E_FAIL) {
		MessageBox(_T("�摜�f�[�^���J���܂���B"));
		GlobalFree(hG);
		DestroyWindow();
		return;
	}
	y=img.GetHeight();
	x=img.GetWidth();
//	if(img.Save(s2)!=S_OK){MessageBox(_T("�v���O�����Ƀo�O�����邩���Ή��`���ł��B"));
//	GlobalFree(hG);
//	DestroyWindow();
//			return;}
	//CFile::Remove(s1);
	//bmpsub = CBitmap::FromHandle(img);
//	HBITMAP hbmp = (HBITMAP)::LoadImage(
//    NULL, s2, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION );
	dc.CreateCompatibleDC(NULL);
//	bmpsub = CBitmap::FromHandle( hbmp );
	CBitmap	bmp1;
	bmp1.CreateCompatibleBitmap(cdc0, img.GetWidth(), img.GetHeight());
	dc.SelectObject(&bmp1);
	img.BitBlt(dc.m_hDC, 0, 0);
//	dc.BitBlt(0, 0, img.GetWidth(), img.GetHeight(), img., 0, 0, SRCCOPY);

	ReleaseDC(cdc0);

	//CFile::Remove(s2);

	CString str;
	str.Format(_T("X: %4d"),x);
	m_x.SetWindowText(str);
	str.Format(_T("Y: %4d"),y);
	m_y.SetWindowText(str);
	// window�g�̑傫���ƈʒu�ݒ�
	RECT rect;
	GetWindowRect(&rect);
	// window�̉��̑傫�����v�Z

	if (x >= y) {
		xy = (double)x / (double)y;
		rect.right = (LONG)(rect.bottom*xy);
	}
	else {
		xy = (double)y / (double)x;
		rect.right = (LONG)(rect.bottom*xy);
	}
	SetWindowPos(NULL, 0, 0, rect.right +100, rect.bottom, SWP_NOMOVE | SWP_NOZORDER);
	// �傫���ύX��̈ʒu���l��
	GetWindowRect(&rect);
	GetWindowRect(&grect);
	rcm.top = 0; rcm.left = 0; rcm.right = grect.right; rcm.bottom = grect.bottom;
	int x2 , y2;
	RECT deskrc;
	int x1, y1;
	// ��ʒ����֔z�u
	x2 = GetSystemMetrics(SM_CXFULLSCREEN);
	y2 = GetSystemMetrics(SM_CYFULLSCREEN);
	x1 = (x2 - (rect.right - rect.left)) / 2;
	y1 = (y2 - (rect.bottom - rect.top)) / 2;
	SetWindowPos(NULL, x1, y1, (rect.right - rect.left) , (rect.bottom - rect.top), SWP_SHOWWINDOW);
	// ����Ax�Ay�̕\���ʒu��ύX
	GetClientRect(&rect);
	rcm.top = 0; rcm.left = 0; rcm.right = rect.right; rcm.bottom = rect.bottom;
	m_close.MoveWindow((int)(rect.right - 50 * hD1), (int)(50 * hD1), (int)(50 * hD1), (int)(50 * hD1));
	m_x.MoveWindow((int)(rect.right - 50 * hD1), (int)(110 * hD1), (int)(50 * hD1), (int)(50 * hD1));
	m_y.MoveWindow((int)(rect.right - 50 * hD1), (int)(140 * hD1), (int)(50 * hD1), (int)(50 * hD1));

	RECT r;
	GetClientRect(&r);
	xy = (double)r.right / (double)grect.right;
	Invalidate(FALSE);
//	InvalidateRect(&rect,FALSE);
	GlobalFree(hG);
}



void CMp3Image::OnPaint()
{
		CPaintDC dcc(this); // �`��p�̃f�o�C�X �R���e�L�X�g
/*	if (IsIconic())
	{

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dcc.GetSafehD1c(), 0);

		// �N���C�A���g�̋�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R����`�悵�܂��B
		dcc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
*/		//if(plf!=0) 
		CRect rc;
		GetClientRect(&rc);
		rc.left = (rc.right + rc.left);
		HBRUSH hbr = CreateSolidBrush(RGB(255, 0, 0));
		FillRect(dc, rc, hbr);

		RECT r;
		GetClientRect(&r);
//			r.right = r.bottom * xy;
		SetStretchBltMode(dcc.m_hDC , HALFTONE); //���掿���[�h
		SetBrushOrgEx(dcc.m_hDC, 0, 0, NULL); //�u���V�̂����h�~
		dcc.StretchBlt(0,0,(r.right-100)*(xy), r.bottom, &dc, 0, 0, x, y, SRCCOPY); //�L�k
		CDialog::OnPaint();
//	}
}

int CMp3Image::Create(CWnd *pWnd)
{
	 m_pParent = NULL;
	BOOL bret = CDialog::Create( CMp3Image::IDD, this);
    if( bret == TRUE)
        ShowWindow( SW_SHOW);
    return bret;
}

void CMp3Image::OnClose()
{
	// TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	nnn=0;
	DestroyWindow();

	CDialog::OnClose();
}

BOOL CMp3Image::DestroyWindow()
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	img.Destroy();
	BOOL rr=CDialog::DestroyWindow();
	mi=NULL;
	if(nnn)
		delete this;
	miw=0;
	return rr;
}
void CMp3Image::OnBnClickedOk()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	DestroyWindow();

}

void CMp3Image::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����܂��B
	Invalidate(FALSE);
}

void CMp3Image::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialog::OnSizing(fwSide, pRect);
	RECT r,rr;
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����Ă�������
	 //���E���ۂ�
	r.bottom=rcm.bottom;r.top=rcm.top;
	r.right=rcm.right;r.left=rcm.left;
    int     width,height;
	int x,y;
	double _x1,_y1;
    width=r.right-r.left;
    height=r.bottom-r.top;
	x=r.bottom-r.top; y=r.right-r.left;xx=(double)y; yy=(double)x;//����̉摜�̑傫�����l��
	r.bottom=pRect->bottom;	r.top=pRect->top;
	r.right=pRect->right;	r.left=pRect->left;
	x1=r.bottom - r.top; y1_=r.right - r.left;xx1=(double)y1_; yy1_=(double)x1;//���݂̃T�C�Y�l��
	_x1=xx1/xx;
	_y1=yy1_/yy;
	switch(fwSide){
		case WMSZ_TOP:
		case WMSZ_BOTTOM:
			pRect->right=pRect->left+(int)(width*_y1)-(GetSystemMetrics(SM_CYSIZEFRAME)+::GetSystemMetrics(SM_CYCAPTION));
			break;
		case WMSZ_LEFT:
        case WMSZ_RIGHT:
			pRect->bottom=pRect->top+(int)(height*_x1)+(GetSystemMetrics(SM_CYSIZEFRAME)+::GetSystemMetrics(SM_CYCAPTION));
			break;
		case WMSZ_BOTTOMRIGHT:
			if(((double)width<(double)height))
				pRect->right=pRect->left+(int)(width*_y1);
			else
				pRect->bottom=pRect->top+(int)(height*_x1);
			break;
		case    WMSZ_TOPLEFT:
			if(((double)width<(double)height))
                pRect->left=pRect->right-(int)(width*_y1);
            else
                pRect->top=pRect->bottom-(int)(height*_x1);
			break;
 		case    WMSZ_TOPRIGHT:
			if(((double)width<(double)height))
				pRect->right=pRect->left+(int)(width*_y1);
            else
                pRect->top=pRect->bottom-(int)(height*_x1);
			break;
		case    WMSZ_BOTTOMLEFT:
			if(((double)width<(double)height))
                pRect->left=pRect->right-(int)(width*_y1);
            else
				pRect->bottom=pRect->top+(int)(height*_x1);
			break;
	}
	RECT rrr;
	GetClientRect(&rrr);
	m_close.MoveWindow((int)(rrr.right - 50.0f * hD1), (int)(50.0f * hD1), (int)(50.0f * hD1), (int)(50.0f * hD1));
	m_x.MoveWindow((int)(rrr.right - 50.0f * hD1), (int)(110.0f * hD1), (int)(50.0f * hD1), (int)(50.0f * hD1));
	m_y.MoveWindow((int)(rrr.right - 50.0f * hD1), (int)(140.0f * hD1), (int)(50.0f * hD1), (int)(50.0f * hD1));
	//SetWindowPos(NULL, 0,0,pRect->right, pRect->bottom,   SWP_NOMOVE|SWP_NOOWNERZORDER);
	Invalidate(FALSE);
}

CPoint m_pointOld1;
BOOL m_bMoving1 = FALSE;


void CMp3Image::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	m_bMoving1 = TRUE;
	SetCapture();
	m_pointOld1 = point;

	CDialog::OnLButtonDown(nFlags, point);
}



void CMp3Image::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	if (m_bMoving1 == TRUE) {
		// �h���b�O���������ꍇ
		m_bMoving1 = FALSE;
		::ReleaseCapture();
	}

	CDialog::OnLButtonUp(nFlags, point);
}


void CMp3Image::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	if (m_bMoving1 == TRUE) {
		CRect rect;
		GetWindowRect(&rect);
		rect.left += (point.x - m_pointOld1.x);
		rect.right += (point.x - m_pointOld1.x);
		rect.top += (point.y - m_pointOld1.y);
		rect.bottom += (point.y - m_pointOld1.y);
		SetWindowPos(NULL, rect.left, rect.top,
			rect.right - rect.left, rect.bottom - rect.top,
			SWP_SHOWWINDOW | SWP_NOOWNERZORDER);
	}
	CDialog::OnMouseMove(nFlags, point);
}


void CMp3Image::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	CMenu menu;
	menu.CreatePopupMenu();
	menu.AppendMenu(MF_STRING | MF_ENABLED, IDOK, _T("����)"));

	ClientToScreen(&point);
	menu.TrackPopupMenu(
		TPM_LEFTALIGN |	//�N���b�N����X���W�����j���[�̍��ӂɂ���
		TPM_RIGHTBUTTON,	//�E�N���b�N�Ń��j���[�I���\�Ƃ���
		point.x, point.y,	//���j���[�̕\���ʒu
		this            	//���̃��j���[�����L����E�B���h�E
		);
	menu.DestroyMenu();

	//CDialog::OnRButtonDown(nFlags, point);
}


HBRUSH CMp3Image::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ������ DC �̑�����ύX���Ă��������B
	switch (nCtlColor) {
	case CTLCOLOR_DLG:
		return (HBRUSH)m_brDlg;
	default:
		break;
	}
	// TODO: ������ DC �̑�����ύX���Ă��������B

	// TODO: ����l���g�p�������Ȃ��ꍇ�͕ʂ̃u���V��Ԃ��܂��B
	return hbr;
}
