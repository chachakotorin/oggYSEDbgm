// Douga.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "d3d9.h"
//#include "d3dtypes.h"
#include "ogg.h"
#include "oggDlg.h"
#include "Douga.h"
//#include "vfw.h"
//#include <digitalv.h>
//#include "resource.h"
//#include "objbase.h"
#include "dshow.h"
#include "evr9.h"
//#include "qedit.h"
#include "Dwmapi.h"
#include <Mtype.h>

static const GUID MR_VIDEO_RENDER_SERVICE = { 0x1092a86c, 0xab1a, 0x459a,{ 0xa3, 0x36, 0x83, 0x1f, 0xbc, 0x4d, 0x11, 0xff } };
static const GUID MR_VIDEO_MIXER_SERVICE = { 0x73cd2fc, 0x6cf4, 0x40b7,{ 0x88, 0x59, 0xe8, 0x95, 0x52, 0xc8, 0x41, 0xf8 } };
static const IID IID_IMFVideoDisplayControl = { 0xa490b1e4, 0xab84, 0x4d31,{ 0xa1, 0xb2, 0x18, 0x1e, 0x03, 0xb1, 0x07, 0x7a } };
static const IID IID_IMFVideoMixerControl = { 0xA5C6C53F, 0xC202, 0x4aa5,{ 0x96, 0x95, 0x17, 0x5B, 0xA8, 0xC5, 0x08, 0xA5 } };
static const IID IID_IMFVideoProcessor = { 0x6AB0000C, 0xFECE, 0x4d1f,{ 0xA2, 0xAC, 0xA9, 0x57, 0x35, 0x30, 0x65, 0x6E } };
static const IID IID_IMFGetService = { 0xFA993888, 0x4383, 0x415A,{ 0xA9, 0x30, 0xDD, 0x47, 0x2A, 0x8C, 0xF6, 0xF7 } };
static const GUID CLSID_EnhancedVideoRenderer = { 0xfa10746c, 0x9b63, 0x4b6c,{ 0xbc, 0x49, 0xfc, 0x30,  0xe, 0xa5, 0xf2, 0x56 } };

typedef interface ISampleGrabberCB ISampleGrabberCB;
EXTERN_C const IID IID_ISampleGrabberCB;
MIDL_INTERFACE("0579154A-2B53-4994-B0D0-E773148EFF85")
ISampleGrabberCB : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE SampleCB(
		double SampleTime,
		IMediaSample *pSample) = 0;

	virtual HRESULT STDMETHODCALLTYPE BufferCB(
		double SampleTime,
		BYTE *pBuffer,
		long BufferLen) = 0;

};

EXTERN_C const IID IID_ISampleGrabber;
MIDL_INTERFACE("6B652FFF-11FE-4fce-92AD-0266B5D7C78F")
ISampleGrabber : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE SetOneShot(
		BOOL OneShot) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetMediaType(
		const AM_MEDIA_TYPE *pType) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetConnectedMediaType(
		AM_MEDIA_TYPE *pType) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetBufferSamples(
		BOOL BufferThem) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetCurrentBuffer(
		/* [out][in] */ long *pBufferSize,
		/* [out] */ long *pBuffer) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetCurrentSample(
		/* [retval][out] */ IMediaSample **ppSample) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetCallback(
		ISampleGrabberCB *pCallback,
		long WhichMethodToCallback) = 0;

};
typedef interface IMediaDet IMediaDet;
EXTERN_C const IID IID_IMediaDet;
EXTERN_C const CLSID CLSID_MediaDet;
MIDL_INTERFACE("65BD0710-24D2-4ff7-9324-ED2E5D3ABAFA")
IMediaDet : public IUnknown
{
public:
	virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Filter(
		/* [retval][out] */ IUnknown **pVal) = 0;

	virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Filter(
		/* [in] */ IUnknown *newVal) = 0;

	virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OutputStreams(
		/* [retval][out] */ long *pVal) = 0;

	virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentStream(
		/* [retval][out] */ long *pVal) = 0;

	virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CurrentStream(
		/* [in] */ long newVal) = 0;

	virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StreamType(
		/* [retval][out] */ GUID *pVal) = 0;

	virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StreamTypeB(
		/* [retval][out] */ BSTR *pVal) = 0;

	virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StreamLength(
		/* [retval][out] */ double *pVal) = 0;

	virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Filename(
		/* [retval][out] */ BSTR *pVal) = 0;

	virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Filename(
		/* [in] */ BSTR newVal) = 0;

	virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetBitmapBits(
		double StreamTime,
		long *pBufferSize,
		char *pBuffer,
		long Width,
		long Height) = 0;

	virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WriteBitmapBits(
		double StreamTime,
		long Width,
		long Height,
		BSTR Filename) = 0;

	virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StreamMediaType(
		/* [retval][out] */ AM_MEDIA_TYPE *pVal) = 0;

	virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSampleGrabber(
		/* [out] */ ISampleGrabber **ppVal) = 0;

	virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FrameRate(
		/* [retval][out] */ double *pVal) = 0;

	virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnterBitmapGrabMode(
		double SeekTime) = 0;

};





#define		RELEASE1(x)			{ if(x){ULONG r;for(r=1;;){r=x->Release();if(r==0)break;} x=NULL;} }
#define		RELEASE(x)			{ if (x != NULL) {x->Release(); x = NULL;} }
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern save savedata;
/////////////////////////////////////////////////////////////////////////////
// CDouga

IMPLEMENT_DYNCREATE(CDouga, CFrameWnd)

CDouga::CDouga()
{
}

CDouga::~CDouga()
{
//	delete this;

}


BEGIN_MESSAGE_MAP(CDouga, CFrameWnd)
	ON_WM_TIMER()
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CDouga)
	ON_WM_SIZING()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_WM_SHOWWINDOW()
	ON_COMMAND(ID_MENUITEM32771, OnMenuitem32771)
	ON_COMMAND(ID_MENUITEM32772, OnMenuitem32772)
	ON_COMMAND(ID_MENUITEM32773, OnMenuitem32773)
	ON_COMMAND(ID_ST1, OnST1)
	ON_COMMAND(ID_ST2, OnST2)
	ON_COMMAND(ID_ST3, OnST3)
	ON_COMMAND(ID_ST4, OnST4)
	ON_COMMAND(ID_ST5, OnST5)
	ON_COMMAND(ID_ST6, OnST6)
	ON_COMMAND(ID_ST7, OnST7)
	ON_COMMAND(ID_ST8, OnST8)
	ON_COMMAND(ID_ST9, OnST9)
	ON_COMMAND(ID_ST10, OnST10)
	ON_COMMAND(ID_MV1, OnMV1)
	ON_COMMAND(ID_MV2, OnMV2)
	ON_COMMAND(ID_MV3, OnMV3)
	ON_COMMAND(ID_MV4, OnMV4)
	ON_COMMAND(ID_MV5, OnMV5)
	ON_COMMAND(ID_MV6, OnMV6)
	ON_COMMAND(ID_MV7, OnMV7)
	ON_COMMAND(ID_MV8, OnMV8)
	ON_COMMAND(ID_MV9, OnMV9)
	ON_COMMAND(ID_MV10, OnMV10)
	ON_COMMAND(ID_ETC1, OnETC1)
	ON_COMMAND(ID_ETC2, OnETC2)
	ON_COMMAND(ID_ETC3, OnETC3)
	ON_COMMAND(ID_ETC4, OnETC4)
	ON_COMMAND(ID_ETC5, OnETC5)
	ON_COMMAND(ID_ETC6, OnETC6)
	ON_COMMAND(ID_ETC7, OnETC7)
	ON_COMMAND(ID_ETC8, OnETC8)
	ON_COMMAND(ID_ETC9, OnETC9)
	ON_COMMAND(ID_ETC10, OnETC10)
	ON_WM_PAINT()
	ON_WM_NCHITTEST()
	ON_WM_GETMINMAXINFO()
	ON_WM_MOUSEACTIVATE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
//	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_KEYDOWN()
	ON_WM_RBUTTONDOWN()
//	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCRBUTTONDOWN()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_NCLBUTTONDBLCLK()
	ON_COMMAND(32775, &CDouga::On32775)
	ON_WM_DROPFILES()
	ON_WM_NCMOUSEMOVE()
	ON_WM_NCDESTROY()
	ON_WM_NCRBUTTONUP()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDouga メッセージ ハンドラ
BOOL st12=FALSE;

HWND hMCIWnd;
RECT rc,rcm;
int si=0;
IGraphBuilder *pGraphBuilder = NULL;
IMediaControl *pMediaControl = NULL;
IVideoWindow *pVideoWindow = NULL;
IBasicVideo *pBasicVideo = NULL;
IMediaSeeking *pMediaSeeking = NULL;
ICaptureGraphBuilder2 *pCaptureGraphBuilder2 = NULL;
IBaseFilter *pVmr9 = NULL;
IBaseFilter *pSource=NULL;
IBaseFilter *pSource1=NULL;
IBaseFilter *pSource2=NULL;

IBaseFilter   *pSourceFilter=NULL;
IBaseFilter   *pSplitter=NULL;
IBaseFilter   *pAviDecomp=NULL;
IBaseFilter   *pColour=NULL;
IBaseFilter   *pRenderer=NULL;
IBaseFilter   *pRenderer0=NULL;
IBaseFilter   *pRenderer0_=NULL;
IBaseFilter   *pRenderer1=NULL;
IBaseFilter   *pRenderer2=NULL;
IBaseFilter   *pACM=NULL;
IBaseFilter   *pDSRenderer=NULL;
IBaseFilter   *pDSRenderer2=NULL;
IBaseFilter   *pDSRenderer3=NULL;
IBaseFilter   *pDSRenderer4=NULL;
IBaseFilter   *pDSRenderer5=NULL;
IBaseFilter   *pDSRenderer6=NULL;
IBaseFilter   *pDSRenderer7=NULL;
IBaseFilter   *pDSRenderer8=NULL;
IBaseFilter   *pDSRenderer9=NULL;
IBaseFilter   *pDSRenderer10=NULL;
IBaseFilter   *prend=NULL;
IBaseFilter   *prenda=NULL;
IBaseFilter   *prenda2=NULL;
IBaseFilter   *prenda3=NULL;
IBaseFilter   *prenda4=NULL;
IBaseFilter   *prenda5=NULL;
IBaseFilter   *prenda6=NULL;
IBaseFilter   *prenda7=NULL;
IBaseFilter   *prenda8=NULL;
IBaseFilter   *prenda9=NULL;
IBaseFilter   *prenda10=NULL;
IFileSourceFilter *Haali=NULL;

IBasicAudio *pBasicAudio=NULL;
IMediaPosition *pMediaPosition=NULL;

IMFGetService *service=NULL;
IMFVideoDisplayControl *Vdc=NULL;
IQualProp *pop=NULL;
IMediaDet *vr=NULL;

IAMStreamSelect *iam = NULL;

BOOL ev=FALSE;

CString streamname[20];
CString streamname1[20];
CString streamname2[20];


extern WCHAR douga[2050];
extern save savedata;
extern int mode;

extern COggDlg *og;

BOOL CDouga::Create(HWND h)
{
	CString sClassName;
	sClassName = AfxRegisterWndClass(NULL ,
    LoadCursor(NULL, IDC_ARROW),
    (HBRUSH)::GetStockObject(BLACK_BRUSH),
    LoadIcon(AfxGetInstanceHandle(),
    MAKEINTRESOURCE(IDR_DOUGA)));

    int ret=CreateEx(WS_EX_OVERLAPPEDWINDOW|WS_EX_ACCEPTFILES,sClassName, _T("mp3/m4a簡易プレイヤ(動画画面)"),
	  ((WS_OVERLAPPEDWINDOW)& ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX & ~WS_SYSMENU),
	0,0,640,360,NULL,NULL,NULL);
	if(ret==0) MessageBox(_T("作成"));
	ev=FALSE;
 
    ::GetWindowRect(this->GetSafeHwnd(), &rc);
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, TRUE);
//	savedata.gx=10;savedata.gy=10;savedata.p.top=0;savedata.p.left=0;
	if(savedata.gx==-10000){
			MoveWindow(10, 10,100,100,TRUE);
		}else{
			MoveWindow(savedata.gx,savedata.gy,100,100);
//			MoveWindow(10,10,100,100);
//			SetWindowPos(NULL, savedata.gx,savedata.gy,100, 100,   SWP_NOOWNERZORDER);
	}
	si=0;

	cdc0 = GetDC(); //new CClientDC(this);
	savedata.fs=0;
	dc.CreateCompatibleDC(NULL);
	bmp.CreateCompatibleBitmap(cdc0,GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN));
	dc.SelectObject(&bmp);
	dc.FillSolidRect(0,0,GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN),RGB(0,0,0));
	ReleaseDC(cdc0);

	HMODULE hDLL;
	typedef DWORD (WINAPI *PFUNC)(UINT);
	PFUNC pFunc;
	hDLL=::LoadLibrary(_T("Dwmapi"));
	pFunc=(PFUNC)::GetProcAddress(hDLL,"DwmEnableComposition");

	if(pFunc){
		if(savedata.con){
			pFunc(DWM_EC_ENABLECOMPOSITION  );
		}else{
			pFunc(DWM_EC_DISABLECOMPOSITION );
		}
	}
	::FreeLibrary(hDLL);

	st12=0;
	return TRUE;
}
long DeviceID=-1;
int u1=0;
extern save savedata;
extern int spc;
int audionum;
HRESULT GetPin(IBaseFilter *pFilter,PIN_DIRECTION dir,IPin *&pPin,GUID majorType,WCHAR *name);
HRESULT CntPin(IBaseFilter *pFilter);
DWORD CntPin2(IAMStreamSelect *pFilter);
HRESULT ConnectFilter(IBaseFilter *pSrc,IBaseFilter *pDest,GUID majorType,WCHAR *name);

// ピンを取得する
HRESULT CntPin(IBaseFilter *pFilter){
	audionum=0;
	HRESULT retCode=E_FAIL;
	HRESULT hr=NOERROR;
	IEnumPins *e=NULL;
	IPin *pResult=NULL;
	if(pFilter)
		hr=pFilter->EnumPins(&e);
	if(FAILED(hr) || pFilter==NULL)
		return hr;
	FILTER_INFO filinfo;
	pFilter->QueryFilterInfo(&filinfo);
	while(e->Next(1, &pResult, NULL) == S_OK){
		PIN_DIRECTION PinDirThis;
		hr=pResult->QueryDirection(&PinDirThis);
		if (pResult!=NULL && SUCCEEDED(hr) && PinDirThis==PINDIR_OUTPUT){
			PIN_INFO info;
			pResult->QueryPinInfo(&info);
			{
				IEnumMediaTypes *em=NULL;
				AM_MEDIA_TYPE *amt;
				hr=pResult->EnumMediaTypes(&em);
				if(SUCCEEDED(hr)){
					while(em->Next(1,&amt,NULL)==S_OK){
						GUID mj=amt->majortype;
						// amt を解放
						if (amt->cbFormat != 0){
							CoTaskMemFree((PVOID)amt->pbFormat);
						}
						RELEASE(amt->pUnk);
						CoTaskMemFree(amt);
						if(_wcsnicmp(info.achName,L"Audio 1",14)==0){ audionum++;break;}
						if(_wcsnicmp(info.achName,L"Audio 2",14)==0){ audionum++;break;}
						if(_wcsnicmp(info.achName,L"Audio 3",14)==0){ audionum++;break;}
						if(_wcsnicmp(info.achName,L"Audio 4",14)==0){ audionum++;break;}
						if(_wcsnicmp(info.achName,L"Audio 5",14)==0){ audionum++;break;}
						if(_wcsnicmp(info.achName,L"Audio 6",14)==0){ audionum++;break;}
						if(_wcsnicmp(info.achName,L"Audio 7",14)==0){ audionum++;break;}
						if(_wcsnicmp(info.achName,L"Audio 8",14)==0){ audionum++;break;}
						if(_wcsnicmp(info.achName,L"Audio 9",14)==0){ audionum++;break;}
						if(_wcsnicmp(info.achName,L"Audio 10",14)==0){audionum++;break;}
					}
				}
				RELEASE(em);
			}
			if(retCode==S_OK)
				break;
		}
		RELEASE(pResult);
	}
	RELEASE(e);
	return retCode;
}

int au, etc;

DWORD CntPin2(IAMStreamSelect *pFilter) {
	DWORD i,j,k,k1,k2,l;
	k =k1=k2= 0;
	l = 0;
	au = etc = 0;
	AM_MEDIA_TYPE *am;
	for (j = 0; j < 10; j++) {
		streamname[k] = "";
		streamname1[k] = "";
		streamname2[k] = "";
	}
	LPWSTR p;
	pFilter->Count(&i);
	l = i;
	for (j = 0; j < i; j++) {
		pFilter->Info(j, &am, NULL, NULL, NULL, &p, NULL, NULL);
		if (am->majortype == MEDIATYPE_Audio) {
			streamname[k] = p;
			k++;
		}
		else {
			l--;
			if (am->majortype == MEDIATYPE_Video) {
				streamname1[k1] = p;
				au++;
				k1++;
			}
			else {
				if (etc == 0)etc = j;
				streamname2[k2] = p;
				k2++;
			}
		}
		CoTaskMemFree(p);
		DeleteMediaType(am);
		FreeMediaType(*am);
	}
	return l;
}

HRESULT GetPin(IBaseFilter *pFilter,PIN_DIRECTION dir,IPin *&pPin,GUID majorType,WCHAR *name){
	HRESULT retCode=E_FAIL;
	HRESULT hr=NOERROR;
	IEnumPins *e=NULL;
	IPin *pResult=NULL;
	if(pFilter)
		hr=pFilter->EnumPins(&e);
	if(FAILED(hr) || pFilter==NULL)
		return hr;
	FILTER_INFO filinfo;
	pFilter->QueryFilterInfo(&filinfo);
	while(e->Next(1, &pResult, NULL) == S_OK){
		PIN_DIRECTION PinDirThis;
		hr=pResult->QueryDirection(&PinDirThis);
		if (pResult!=NULL && SUCCEEDED(hr) && PinDirThis==dir){
			PIN_INFO info;
			pResult->QueryPinInfo(&info);
			if(dir==PINDIR_INPUT){
				pPin=pResult;
				retCode=S_OK;
			}else{
				IEnumMediaTypes *em=NULL;
				AM_MEDIA_TYPE *amt=NULL;
				hr=pResult->EnumMediaTypes(&em);
//				if(_wcsnicmp(info.achName,L"Video",5*2+2)>=0){
//					pPin=pResult;
//					retCode=S_OK;
//					break;
//				}
				if(SUCCEEDED(hr)){
					while(em->Next(1,&amt,NULL)==S_OK){
						GUID mj=amt->majortype;
						// amt を解放
						if (amt->cbFormat != 0){
							CoTaskMemFree((PVOID)amt->pbFormat);
						}
						RELEASE(amt->pUnk);
						CoTaskMemFree(amt);
						if(Haali==NULL || name==NULL){
							if(mj==majorType){
								pPin=pResult;
								retCode=S_OK;
								break;
							}
						}else{
							if(mj==majorType && _wcsnicmp(info.achName,name,14)==0){
								pPin=pResult;
								retCode=S_OK;
								break;
							}
						}
					}
				}
				RELEASE(em);
			}
			if(retCode==S_OK)
				break;
		}
		RELEASE(pResult);
	}
	RELEASE(e);
	return retCode;
}
// フィルタの同士を接続する
HRESULT ConnectFilter(IBaseFilter *pSrc,IBaseFilter *pDest,GUID majorType,WCHAR *name){
	HRESULT hr=-1;
	IPin *pPinOut=NULL;
	IPin *pPinIn=NULL;
	if(pSrc==NULL || pDest==NULL) return hr;
	hr=GetPin(pSrc,PINDIR_OUTPUT,pPinOut,majorType,name);
	if(FAILED(hr)){
		printf("Output pin is not found. : from %p to %p\n",pSrc,pDest);
		return hr;
	}
	hr=GetPin(pDest,PINDIR_INPUT,pPinIn,GUID_NULL,name);
	if(SUCCEEDED(hr)){
//		hr=pGraphBuilder->Connect(pPinIn,pPinOut);
		hr=pPinOut->Connect(pPinIn,NULL);
	}
	if(FAILED(hr)){
		printf("Failed Connecting. : from %p to %p\n",pSrc,pDest);
	}
	// 取得したピン インターフェイスを解放
	RELEASE(pPinIn);
	RELEASE(pPinOut);
	return hr;
}
	long p;
#include "AudioSelect.h"
int bit=0;
double rate;
int rateflg = 0;
extern DWORD videocnt3;
extern int wavch,wavbit;
CString s2;
#if WIN64
#else
//static const GUID MR_VIDEO_RENDER_SERVICE =     {0x1092a86c, 0xab1a, 0x459a, {0xa3, 0x36, 0x83, 0x1f, 0xbc, 0x4d, 0x11, 0xff} };
//static const IID IID_IMFVideoDisplayControl =   {0xa490b1e4, 0xab84, 0x4d31, {0xa1, 0xb2, 0x18, 0x1e, 0x03, 0xb1, 0x07, 0x7a} };
#endif
void CDouga::plays(TCHAR* s)
{
	WCHAR ss[2050];HRESULT hr;
	int cflg=0;
	LPWSTR ss1; ss1=ss;
	TCHAR *s3; s2=s; s3=s;
#if _UNICODE
	_tcscpy(ss,s);
#else
	MultiByteToWideChar(CP_ACP,0,s3,-1,ss1,2000);
#endif
	CoInitialize(NULL);
	
	int len = ::WideCharToMultiByte(CP_THREAD_ACP,0, ss, -1, NULL, 0, NULL, NULL);
	memcpy((TCHAR*)douga,(TCHAR*)ss,len*2+2);
	vr=NULL;
	rate=30.0;
	hr=CoCreateInstance(CLSID_MediaDet,NULL,CLSCTX_INPROC,IID_IMediaDet,(LPVOID *)&vr);
	double rate1=0.0;rate=0.0;
	if(vr){
		vr->put_Filename(ss);
		vr->get_OutputStreams(&p);
		for(int i=0;i<p+1;i++){
			vr->put_CurrentStream(i);
				vr->get_FrameRate(&rate1);
			if(rate1!=0.0){
				rate=rate1;
			}
			AM_MEDIA_TYPE am;
			s2.MakeLower();
			if(rate1==0.0 && s2.Right(4)==".vob" || s2.Right(4)==".mpg" || s2.Right(3)==".ts"){
				rate=29.97;
			}
			if(rate==0.0){
				wavbit=0;wavch=0;
				vr->get_StreamMediaType(&am);
				if(am.formattype==FORMAT_WaveFormatEx){
					WAVEFORMATEX *w;
					w=(WAVEFORMATEX*)am.pbFormat;
					wavbit=w->nSamplesPerSec;
					wavch=w->nChannels;
				}
			}
		}
		vr->Release(); vr=NULL;
	}

	rateflg=0;
	if(rate==0.0){
		rateflg=1;
	}
	Haali=NULL;pSplitter=NULL;
	CoCreateInstance(CLSID_FilterGraph,NULL,CLSCTX_INPROC_SERVER,IID_IGraphBuilder,(LPVOID *)&pGraphBuilder);
	if(pGraphBuilder){
		pGraphBuilder->QueryInterface(IID_IMediaControl,(LPVOID *)&pMediaControl);
		pGraphBuilder->QueryInterface(IID_IVideoWindow,(LPVOID *)&pVideoWindow);
		pGraphBuilder->QueryInterface(IID_IMediaPosition,(LPVOID *)&pMediaPosition);
		pGraphBuilder->QueryInterface(IID_IBasicAudio, (LPVOID *)&pBasicAudio);
	}
		IFilterMapper2 *pMapper = NULL;
		ICreateDevEnum *pDevEnum = NULL;
		IEnumMoniker *pEnum = NULL;
		hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC,
			IID_ICreateDevEnum, (void**)&pDevEnum);
		hr = pDevEnum->CreateClassEnumerator(CLSID_LegacyAmFilterCategory, &pEnum, 0);
	    pDevEnum->Release();
		OSVERSIONINFO in;ZeroMemory(&in,sizeof(in));in.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);GetVersionEx(&in);
///		CString s_;s_.Format("%d",in.dwMajorVersion);
//		::MessageBox(m_hWnd,s_,"",NULL);
		if(in.dwMajorVersion>=5){

			// モニカを列挙する。
			IMoniker *pMoniker;
			ULONG cFetched;
			while (pEnum->Next(1, &pMoniker, &cFetched) == S_OK){
				IPropertyBag *pPropBag = NULL;
				hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag, 
				   (void **)&pPropBag);
				if (SUCCEEDED(hr)){
					// フィルタのフレンドリ名を取得するには、次の処理を行う。
					VARIANT varName;
					VariantInit(&varName);
					hr = pPropBag->Read(L"FriendlyName", &varName, 0);
					int len = ::WideCharToMultiByte(CP_THREAD_ACP,0, varName.bstrVal, -1, NULL, 0, NULL, NULL);

					if(_wcsnicmp(varName.bstrVal,L"Enhanced Video Renderer",len*2-2)==0 && savedata.evr && savedata.render==0
						&& !(mode==11 || mode==12 || mode==16 || mode==19)){ev=TRUE;
//						CoCreateInstance(CLSID_EnhancedVideoRenderer, NULL, CLSCTX_INPROC_SERVER,IID_IBaseFilter, reinterpret_cast<void **>(&prend));
						hr = pMoniker->BindToObject(NULL, NULL, IID_IBaseFilter, (void**)&prend);
						prend->QueryInterface(IID_IMFGetService,(LPVOID *)&service);
						hr=service->GetService(MR_VIDEO_RENDER_SERVICE, IID_IMFVideoDisplayControl, (void**)&Vdc);
						hr=Vdc->SetVideoWindow(m_hWnd);
					}
					VariantClear(&varName);
					RELEASE(pPropBag);
				}
				RELEASE(pMoniker);
			}
		}
		RELEASE(pMapper);
		RELEASE(pEnum);
		BOOL renderr=0;
		CString ssss;
#if UNICODE
		ssss=ss;
#else
		char sss[1024];
		WideCharToMultiByte(CP_ACP,0, ss, 1024, sss, 1024, NULL, NULL);
		ssss=sss;
#endif
	ssss.MakeLower();
	int flg=0;
	if(prend)
		pGraphBuilder->AddFilter(prend, L"Enhanced Video Renderer");
	pGraphBuilder->RenderFile(ss,NULL);
	//Filtervideooff(pGraphBuilder);
	//pGraphBuilder->RenderFile(ss, NULL);
	if (prend)
		Filtervideooff2(pGraphBuilder);
	//Filtervideooff3(pGraphBuilder);
	if(pGraphBuilder)pGraphBuilder->QueryInterface(IID_IMediaSeeking,(LPVOID *)&pMediaSeeking);

	Filtersdown(pGraphBuilder, NULL);
	Filtersdown(pGraphBuilder, NULL);
	Filtersdown(pGraphBuilder, NULL);
	Filtersdown(pGraphBuilder, NULL);
	Filtersdown(pGraphBuilder, NULL);
	Filtersdown(pGraphBuilder, NULL);
	Filtersdown(pGraphBuilder, NULL);
	Filtersdown(pGraphBuilder, NULL);
	Filtersdown(pGraphBuilder, NULL);

	audionum = 1;
	if (iam) {
		audionum = CntPin2(iam);
	}

	if(savedata.audiost==1)
		if (audionum > 1) {
			CAudioSelect as;
			as.no = audionum;
			int rett = as.DoModal();
			if (as.no < 0)as.no = 0;
			st12 = as.no + 1;
			if (pGraphBuilder && iam) {
				iam->Enable(as.no+1, AMSTREAMSELECTENABLE_ENABLE);
			}
		}
}

void CDouga::Filtersdown(IGraphBuilder *pGraph,WCHAR *filter) 
{
    IEnumFilters *pEnum = NULL;
    IBaseFilter *pFilter;
    ULONG cFetched;
	CString s;
    HRESULT hr = pGraph->EnumFilters(&pEnum);
    if (FAILED(hr)) return ;

    while(pEnum->Next(1, &pFilter, &cFetched) == S_OK)
    {
		IEnumPins *p;
		IPin *pPin;
		PIN_INFO pp, pp1;
		FILTER_INFO FilterInfo,FilterInfo1,FilterInfo2;
        pFilter->QueryFilterInfo(&FilterInfo);
		pFilter->EnumPins(&p);
		pFilter->QueryFilterInfo(&FilterInfo1);
		s = FilterInfo1.achName;
		if (s.Find(L"\\") != -1) {
			if (iam == NULL)pFilter->QueryInterface(IID_IAMStreamSelect, (void**)&iam);
			RELEASE(pFilter);
		}
		if (s.Find(L"Splitter") != -1) {
			if (iam == NULL)pFilter->QueryInterface(IID_IAMStreamSelect, (void**)&iam);
			RELEASE(pFilter);
		}
		while(p->Next(1, &pPin, 0) == S_OK)
		{
			PIN_DIRECTION PinDirThis;
			pPin->QueryDirection(&PinDirThis);
			//if (PinDirThis == PINDIR_OUTPUT){
				PIN_INFO pp,pp1;
				IPin *pn;
				if (pPin->ConnectedTo(&pn) == S_OK) {
					pn->QueryPinInfo(&pp);
					pp.pFilter->QueryFilterInfo(&FilterInfo1);
					pPin->QueryPinInfo(&pp1);
					pp1.pFilter->QueryFilterInfo(&FilterInfo2);
					s = FilterInfo1.achName;
					if (s.Find(L"Splitter") != -1) {
						if (iam == NULL)pp.pFilter->QueryInterface(IID_IAMStreamSelect, (void**)&iam);
						RELEASE(pp.pFilter);
						RELEASE(pp1.pFilter);
					}
					if (_wcsnicmp(FilterInfo1.achName, L"Default DirectSound Device", 27 * 2 + 4) == 0) {
						//pGraph->RemoveFilter(pp.pFilter);
						//pGraph->RemoveFilter(pp1.pFilter);
						RELEASE(pp.pFilter);
						RELEASE(pp1.pFilter);
					}
					RELEASE(pp.pFilter);
					RELEASE(pp1.pFilter);
				}
				//}
		}
		p->Release();
        // FILTER_INFO 構造体はフィルタ グラフ マネージャへのポインタを保持する。
        // その参照カウントは解放しなければならない。
        if (FilterInfo.pGraph != NULL)
            FilterInfo.pGraph->Release();
		if(pFilter)
	        pFilter->Release();
    }

    pEnum->Release();
    return ;
}

void CDouga::Filtervideooff(IGraphBuilder *pGraph,WCHAR *filter) 
{
    IEnumFilters *pEnum = NULL;
    IBaseFilter *pFilter;
    ULONG cFetched;
	CString s;

    HRESULT hr = pGraph->EnumFilters(&pEnum);
    if (FAILED(hr)) return ;

    while(pEnum->Next(1, &pFilter, &cFetched) == S_OK)
    {
		IEnumPins *p;
		IPin *pPin;
        FILTER_INFO FilterInfo,FilterInfo1;
        pFilter->QueryFilterInfo(&FilterInfo);
		pFilter->EnumPins(&p);
		PIN_INFO pp;
		pFilter->QueryFilterInfo(&FilterInfo1);
		s = FilterInfo1.achName;
		if (s.Find(L"Video Decoder") != -1) {
			pGraph->AddFilter(prend, L"Enhanced Video Renderer");
			ConnectFilter(pFilter, prend, MEDIATYPE_Video, NULL);
			RELEASE(pFilter);
		}
		RELEASE(pFilter);
		while(p->Next(1, &pPin, 0) == S_OK)
		{
			PIN_DIRECTION PinDirThis;
			pPin->QueryDirection(&PinDirThis);
			if (PinDirThis == PINDIR_OUTPUT){
				PIN_INFO pp;
				IPin *pn;
				if(pPin->ConnectedTo(&pn)==S_OK){
					pn->QueryPinInfo(&pp);
					pp.pFilter->QueryFilterInfo(&FilterInfo1);
					s = FilterInfo1.achName;
					if (s.Find(L"Video Decoder") != -1) {
						pGraph->AddFilter(prend, L"Enhanced Video Renderer");
						ConnectFilter(pp.pFilter, prend, MEDIATYPE_Video, NULL);
						RELEASE(pp.pFilter);
					}
				}
			}
		}
		p->Release();
        // FILTER_INFO 構造体はフィルタ グラフ マネージャへのポインタを保持する。
        // その参照カウントは解放しなければならない。
        if (FilterInfo.pGraph != NULL)
            FilterInfo.pGraph->Release();
		if(pFilter)
	        pFilter->Release();
    }

    pEnum->Release();
    return ;
}

void CDouga::Filtervideooff2(IGraphBuilder *pGraph, WCHAR *filter)
{
	IEnumFilters *pEnum = NULL;
	IBaseFilter *pFilter;
	ULONG cFetched;
	CString s;

	HRESULT hr = pGraph->EnumFilters(&pEnum);
	if (FAILED(hr)) return;

	while (pEnum->Next(1, &pFilter, &cFetched) == S_OK)
	{
		IEnumPins *p;
		IPin *pPin;
		FILTER_INFO FilterInfo, FilterInfo1;
		pFilter->QueryFilterInfo(&FilterInfo);
		pFilter->EnumPins(&p);
		PIN_INFO pp;
		pFilter->QueryFilterInfo(&FilterInfo1);
		s = FilterInfo1.achName;
		if (s.Find(L"Video Renderer") == 0) {
			pGraph->RemoveFilter(pFilter);
			RELEASE(pFilter);
		}
		RELEASE(pFilter);
		while (p->Next(1, &pPin, 0) == S_OK)
		{
			PIN_DIRECTION PinDirThis;
			pPin->QueryDirection(&PinDirThis);
			if (PinDirThis == PINDIR_OUTPUT) {
				PIN_INFO pp;
				IPin *pn;
				if (pPin->ConnectedTo(&pn) == S_OK) {
					pn->QueryPinInfo(&pp);
					pp.pFilter->QueryFilterInfo(&FilterInfo1);
					s = FilterInfo1.achName;
					if (s.Find(L"Video Renderer") == 0) {
						pGraph->RemoveFilter(pp.pFilter);
						RELEASE(pp.pFilter);
					}
				}
			}
		}
		p->Release();
		// FILTER_INFO 構造体はフィルタ グラフ マネージャへのポインタを保持する。
		// その参照カウントは解放しなければならない。
		if (FilterInfo.pGraph != NULL)
			FilterInfo.pGraph->Release();
		if (pFilter)
			pFilter->Release();
	}

	pEnum->Release();
	return;
}

void CDouga::Filtervideooff3(IGraphBuilder *pGraph, WCHAR *filter)
{
	IEnumFilters *pEnum = NULL;
	IBaseFilter *pFilter;
	ULONG cFetched;
	CString s;
	int cnt;
	cnt = 0;

	HRESULT hr = pGraph->EnumFilters(&pEnum);
	if (FAILED(hr)) return;

	while (pEnum->Next(1, &pFilter, &cFetched) == S_OK)
	{
		IEnumPins *p;
		IPin *pPin;
		FILTER_INFO FilterInfo, FilterInfo1;
		pFilter->QueryFilterInfo(&FilterInfo);
		pFilter->EnumPins(&p);
		pFilter->QueryFilterInfo(&FilterInfo1);
		s = FilterInfo1.achName;
		if (s.Find(L"ffdshow Video Decoder") == 0) {
			cnt++;
			RELEASE(pFilter);
		}
		if (s.Find(L"LAV Video Decoder") == 0) {
			cnt++;
			RELEASE(pFilter);
		}
		RELEASE(pFilter);
		while (p->Next(1, &pPin, 0) == S_OK)
		{
			PIN_DIRECTION PinDirThis;
			pPin->QueryDirection(&PinDirThis);
			if (PinDirThis == PINDIR_OUTPUT) {
				PIN_INFO pp;
				IPin *pn;
				if (pPin->ConnectedTo(&pn) == S_OK) {
					pn->QueryPinInfo(&pp);
				}
			}
		}
		p->Release();
		// FILTER_INFO 構造体はフィルタ グラフ マネージャへのポインタを保持する。
		// その参照カウントは解放しなければならない。
		if (FilterInfo.pGraph != NULL)
			FilterInfo.pGraph->Release();
		if (pFilter)
			pFilter->Release();
	}

	pEnum->Release();
	if(cnt==2)Filtervideooff4(pGraph);
	return;
}

void CDouga::Filtervideooff4(IGraphBuilder *pGraph)
{
	IEnumFilters *pEnum = NULL;
	IBaseFilter *pFilter;
	ULONG cFetched;
	CString s;
	int cnt;
	cnt = 0;

	HRESULT hr = pGraph->EnumFilters(&pEnum);
	if (FAILED(hr)) return;

	while (pEnum->Next(1, &pFilter, &cFetched) == S_OK)
	{
		IEnumPins *p;
		IPin *pPin;
		FILTER_INFO FilterInfo, FilterInfo1;
		pFilter->QueryFilterInfo(&FilterInfo);
		pFilter->EnumPins(&p);
		pFilter->QueryFilterInfo(&FilterInfo1);
		s = FilterInfo1.achName;
		if (s.Find(L"LAV Video Decoder") == 0) {
			pGraph->RemoveFilter(pFilter);
			RELEASE(pFilter);
		}
		RELEASE(pFilter);
		while (p->Next(1, &pPin, 0) == S_OK)
		{
			PIN_DIRECTION PinDirThis;
			pPin->QueryDirection(&PinDirThis);
			if (PinDirThis == PINDIR_OUTPUT) {
				PIN_INFO pp;
				IPin *pn;
				if (pPin->ConnectedTo(&pn) == S_OK) {
					pn->QueryPinInfo(&pp);
					pp.pFilter->QueryFilterInfo(&FilterInfo1);
					s = FilterInfo1.achName;
					if (s.Find(L"LAV Video Decoder") == 0) {
						pGraph->RemoveFilter(pp.pFilter);
						RELEASE(pp.pFilter);
					}
				}
			}
		}
		p->Release();
		// FILTER_INFO 構造体はフィルタ グラフ マネージャへのポインタを保持する。
		// その参照カウントは解放しなければならない。
		if (FilterInfo.pGraph != NULL)
			FilterInfo.pGraph->Release();
		if (pFilter)
			pFilter->Release();
	}

	pEnum->Release();
	return;
}

extern CString filen;
void CDouga::play(int u, CString str)
{
	u1=u;
	CString s0;
	if(mode==-2){
		TCHAR *s;
//		s = new TCHAR [filen.GetLength()+1];
		s=filen.GetBuffer();
		plays(s);
		filen.ReleaseBuffer();
//		delete [] s;
	}
	if (mode == -1) {//ogg ys8
		CString str2 = str;
		str += L"\\";
		switch (u)
		{
		case 1:
			{
				TCHAR *s;
				str += _T("movie\\logo.wmv");
				s = str.GetBuffer();
				plays(s);
				str.ReleaseBuffer();
				break;
			}
		case 2:
		{
			TCHAR *s;
			str += _T("movie\\op.wmv");
			s = str.GetBuffer();
			plays(s);
			str.ReleaseBuffer();
			break;
		}
		case 3:
		{
			TCHAR *s;
			str += _T("movie\\ed2.wmv");
			s = str.GetBuffer();
			plays(s);
			str.ReleaseBuffer();
			break;
		}
		case 4:
		{
			TCHAR *s;
			str += _T("movie\\logo.wmv");
			s = str.GetBuffer();
			plays(s);
			str.ReleaseBuffer();
			break;
		}
		}
}

	if(mode==1){//ED6SC
		switch(u)
		{
		case 98:
				{
				TCHAR s[]=_T("..\\ED6_2_LOGO.avi");
				;
				plays(s);
			break;
				}
		case 99:
				{
				TCHAR s[]=_T("..\\ED6_2_OP.avi");
				plays(s);
			break;
				}
		case 100:
				{
			TCHAR s[]=_T("..\\ED6_DT47.dat");
			plays(s);
			break;
				}
		case 101:
				{
			TCHAR s[]=_T("..\\ED6_DT40.dat");
			plays(s);
			break;
				}
		case 102:
				{
			TCHAR s[]=_T("..\\ED6_DT41.dat");
			plays(s);
			break;
				}
		case 103:
				{
			TCHAR s[]=_T("..\\ED6_DT42.dat");
			plays(s);
			break;
				}
		case 104:
				{
			TCHAR s[]=_T("..\\ED6_DT43.dat");
			plays(s);
			break;
				}
		case 105:
				{
			TCHAR s[]=_T("..\\ED6_DT44.dat");
			plays(s);
			break;
				}
		case 106:
				{
			TCHAR s[]=_T("..\\ED6_DT45.dat");
			plays(s);
			break;
				}
		case 107:
				{
			TCHAR s[]=_T("..\\ED6_DT46.dat");
			plays(s);
			break;
				}
		}
	}
	if(mode==2){//ED6FC
	switch(u)
	{
		case 55:
				{
			TCHAR s[]=_T("..\\ED6_LOGO.avi");
			plays(s);
			break;
				}
		case 56:
				{
			TCHAR s[]=_T("..\\ED6_OP.avi");
			plays(s);
			break;
				}
		case 57:
				{
			TCHAR s[]=_T("..\\ED6_DT17.dat");
			plays(s);
			break;
				}
		case 58:
				{
			TCHAR s[]=_T("..\\ED6_DT18.dat");
			plays(s);
			break;
				}
		}
	}
	if(mode==3){//YSF
		switch(u)
		{
		case 32:
				{
			TCHAR s[]=_T("..\\opening.avi");
			plays(s);
			break;
				}
		case 33:
				{
			TCHAR s[]=_T("..\\im01.dt");
			plays(s);
			break;
				}
		case 25:
				{
			TCHAR s[]=_T("..\\im03a.dt");
			plays(s);
			break;
				}
		}
	}
	if(mode==4){//YS6
		switch(u)
		{
		case 1:
				{
			TCHAR s[]=_T("..\\opening.avi");
			plays(s);
			break;
				}
		case 25:
				{
			TCHAR s[]=_T("..\\im01.dt");
			plays(s);
			break;
				}
		case 26:
				{
			TCHAR s[]=_T("..\\im02.dt");
			plays(s);
			break;
				}
		case 27:
				{
			TCHAR s[]=_T("..\\im03a.dt");
			plays(s);
			break;
				}
		case 28:
				{
			TCHAR s[]=_T("..\\im03b.dt");
			plays(s);
			break;
				}
		}
	}
	if(mode==5){//YSO
		switch(u+1)
		{
		case 41:
				{
			TCHAR s[]=_T("..\\yso_logo.avi");
			plays(s);
			break;
				}
		case 42:
				{
			TCHAR s[]=_T("..\\yso_pro.avi");
			plays(s);
			break;
				}
		case 43:
				{
			TCHAR s[]=_T("..\\yso_op.avi");
			plays(s);
			break;
				}
		case 44:
				{
			TCHAR s[]=_T("..\\yso_ins01.dat");
			plays(s);
			break;
				}
		case 45:
				{
			TCHAR s[]=_T("..\\yso_ins02.dat");
			plays(s);
			break;
				}
		case 46:
				{
			TCHAR s[]=_T("..\\yso_ins03.dat");
			plays(s);
			break;
				}
		case 47:
				{
			TCHAR s[]=_T("..\\yso_ed01.dat");
			plays(s);
			break;
				}
		case 48:
				{
			TCHAR s[]=_T("..\\yso_ed02.dat");
			plays(s);
			break;
				}
		}
	}
	if(mode==6){//YSO
		switch(u)
		{
		case 141:
				{
			TCHAR s[]=_T("..\\ED6_3_LOGO.avi");
			plays(s);
			break;
				}
		case 142:
				{
			TCHAR s[]=_T("..\\ED6_3_OP.avi");
			plays(s);
			break;
				}
		case 143:
				{
			TCHAR s[]=_T("..\\ED6_DT51.dat");
			plays(s);
			break;
				}
		case 144:
				{
			TCHAR s[]=_T("..\\ED6_DT48.dat");
			plays(s);
			break;
				}
		case 145:
				{
			TCHAR s[]=_T("..\\ED6_DT49.dat");
			plays(s);
			break;
				}
		case 146:
				{
			TCHAR s[]=_T("..\\ED6_DT50.dat");
			plays(s);
			break;
				}
		}
	}
	if(mode==7){//YSO
		switch(u)
		{
		case 65:
			{
			TCHAR s[]=_T("..\\data\\sys\\op.mpg");
			plays(s);
			break;
			}
		case 66:
			{
			TCHAR s[]=_T("..\\data\\sys\\ed.mpg");
			plays(s);
			break;
			}
		}
	}
	if(mode==8){//YSC1
		switch(u)
		{
		case 72:
			{
			TCHAR s[]=_T("..\\..\\data\\ys1_opwp.dat");
			plays(s);
			break;
			}
		case 73:
			{
			TCHAR s[]=_T("..\\..\\data\\ys1_opwo.dat");
			plays(s);
			break;
			}
		case 74:
			{
			TCHAR s[]=_T("..\\..\\data\\ys1_opwn.dat");
			plays(s);
			break;
			}
		}
	}
	if(mode==9){//YSC1
		switch(u)
		{
		case 93:
			{
			TCHAR s[]=_T("..\\..\\data2\\ys2op2op.dat");
			plays(s);
			break;
			}
		case 94:
			{
			TCHAR s[]=_T("..\\..\\data2\\ys2op2oo.dat");
			plays(s);
			break;
			}
		case 95:
			{
			TCHAR s[]=_T("..\\..\\data2\\ys2op2on.dat");
			plays(s);
			break;
			}
		case 96:
			{
			TCHAR s[]=_T("..\\..\\data2\\ys2ed1op.dat");
			plays(s);
			break;
			}
		case 97:
			{
			TCHAR s[]=_T("..\\..\\data2\\ys2ed1oo.dat");
			plays(s);
			break;
			}
		case 98:
			{
			TCHAR s[]=_T("..\\..\\data2\\ys2ed1on.dat");
			plays(s);
			break;
			}
		case 99:
			{
			TCHAR s[]=_T("..\\..\\data2\\ys2ed1np.dat");
			plays(s);
			break;
			}
		case 100:
			{
			TCHAR s[]=_T("..\\..\\data2\\ys2ed1no.dat");
			plays(s);
			break;
			}
		case 101:
			{
			TCHAR s[]=_T("..\\..\\data2\\ys2ed1nn.dat");
			plays(s);
			break;
			}
		}
	}
	if(mode==10){//XANADU
		switch(u)
		{
		case 24:
			{
			TCHAR s[]=_T("..\\MOVIE\\logo.avi");
			plays(s);
			break;
			}
		case 25:
			{
			TCHAR s[]=_T("..\\MOVIE\\opening.avi");
			plays(s);
			break;
			}
		}
	}
	if(mode==11){//ys1
		switch(u)
		{
		case 25:
			{
			TCHAR s[]=_T("..\\..\\data\\YS12OP.avi");
			plays(s);
			break;
			}
		}
	}
	if(mode==12){//ys2
		switch(u)
		{
		case 31:
			{
			TCHAR s[]=_T("..\\..\\data\\YS2OP_1.avi");
			plays(s);
			break;
			}
		case 32:
			{
			TCHAR s[]=_T("..\\..\\data\\YS2OP_2.avi");
			plays(s);
			break;
			}
		}
	}
	if(mode==15){//gurumin
		switch(u)
		{
		case 40:
			{
			TCHAR s[]=_T("..\\3ddata\\op.avi");
			plays(s);
			break;
			}
		}
	}
	if(mode==16){//dino
		switch(u)
		{
		case 33:
			{
			TCHAR s[]=_T("op_din.avi");
			plays(s);
			break;
			}
		}
	}
	if(mode==19){//ED4
		switch(u)
		{
		case 1:
			{
			TCHAR s[]=_T("..\\lib\\ED4OP1.AVI");
			plays(s);
			break;
			}
		case 2:
			{
			TCHAR s[]=_T("..\\lib\\ED4OP2.AVI");
			plays(s);
			break;
			}
		}
	}
	if(mode==-11){//ED4
		switch(u)
		{
		case 28:
			{
			TCHAR s[]=_T("..\\video\\logo.AVI");
			plays(s);
			break;
			}
		case 29:
			{
			TCHAR s[]=_T("..\\video\\open.AVI");
			plays(s);
			break;
			}
		case 30:
			{
			TCHAR s[]=_T("..\\video\\Team.AVI");
			plays(s);
			break;
			}
		case 31:
			{
			TCHAR s[]=_T("..\\video\\end1.AVI");
			plays(s);
			break;
			}
		case 32:
			{
			TCHAR s[]=_T("..\\video\\end2.AVI");
			plays(s);
			break;
			}
		case 33:
			{
			TCHAR s[]=_T("..\\video\\end3.AVI");
			plays(s);
			break;
			}
		case 34:
			{
			TCHAR s[]=_T("..\\video\\die.AVI");
			plays(s);
			break;
			}
		case 35:
			{
			TCHAR s[]=_T("..\\video\\NLZ-FALL.AVI");
			plays(s);
			break;
			}
		case 36:
			{
			TCHAR s[]=_T("..\\video\\SING.AVI");
			plays(s);
			break;
			}
		case 37:
			{
			TCHAR s[]=_T("..\\video\\YYF-FALL.AVI");
			plays(s);
			break;
			}
		case 38:
			{
			TCHAR s[]=_T("..\\video\\ZX-FIRST.AVI");
			plays(s);
			break;
			}
		}
	}
	if(mode==-13){//arcturus
		switch(u)
		{
		case 0:
			{
			TCHAR s[]=_T("movie\\arcturus.avi");
			plays(s);
			break;
			}
		}
	}
	if(mode==-14){//arcturus
		switch(u)
		{
		case 43:
			{
			TCHAR s[]=_T("FS43.bik");
			plays(s);
			break;
			}
		case 45:
			{
			TCHAR s[]=_T("FS45.bik");
			plays(s);
			break;
			}
		case 46:
			{
			TCHAR s[]=_T("FS46.bik");
			plays(s);
			break;
			}
		case 47:
			{
			TCHAR s[]=_T("FS47.bik");
			plays(s);
			break;
			}
		}
	}
	if(mode==-15){//arcturus
		switch(u)
		{
		case 49:
			{
			TCHAR s[]=_T("falcom.bik");
			plays(s);
			break;
			}
		case 50:
			{
			TCHAR s[]=_T("FS250.bik");
			plays(s);
			break;
			}
		case 51:
			{
			TCHAR s[]=_T("FS251.bik");
			plays(s);
			break;
			}
		}
	}
}
IAMStreamSelect *ia=NULL;

HRESULT CDouga::EnumFilters (IGraphBuilder *pGraph,int no) 
{
    IEnumFilters *pEnum = NULL;
    IBaseFilter *pFilter;
    ULONG cFetched;
	CString s,ss;
	int i=0;

    HRESULT hr = pGraph->EnumFilters(&pEnum);
    if (FAILED(hr)) return hr;

    while(pEnum->Next(1, &pFilter, &cFetched) == S_OK)
    {
		IEnumPins *p;
		IPin *pPin;
        FILTER_INFO FilterInfo,FilterInfo1;
        pFilter->QueryFilterInfo(&FilterInfo);
		pFilter->EnumPins(&p);
        char szName[MAX_FILTER_NAME];
        char szName1[MAX_FILTER_NAME];
        int cch = WideCharToMultiByte(CP_ACP, 0, FilterInfo.achName,
            -1, szName, MAX_FILTER_NAME, 0, 0);
		if (cch > 0){
			ss=szName;
		}
		while(p->Next(1, &pPin, 0) == S_OK)
		{
			PIN_DIRECTION PinDirThis;
			pPin->QueryDirection(&PinDirThis);
			if (PinDirThis == PINDIR_OUTPUT){
				PIN_INFO pp;
				IPin *pn;
				if(pPin->ConnectedTo(&pn)==S_OK){
					pn->QueryPinInfo(&pp);
					pp.pFilter->QueryFilterInfo(&FilterInfo1);
					WideCharToMultiByte(CP_ACP, 0, FilterInfo1.achName,
						-1, szName1, MAX_FILTER_NAME, 0, 0);
					s=szName1;
					if(s.Right(10)==_T("d Renderer")){
						if(st12==0 && pBasicAudio) pBasicAudio->Release();
						if(st12==0)
							pp.pFilter->QueryInterface(IID_IBasicAudio,(LPVOID *)&pBasicAudio);
						else{
							IBasicAudio *pBasicAudio1=NULL;
							pp.pFilter->QueryInterface(IID_IBasicAudio,(LPVOID *)&pBasicAudio1);
							pBasicAudio1->put_Volume(-10000);
							pBasicAudio1->Release();
						}
					}
					if(s.Right(11)==_T("d Renderer2")){
						if(st12==1 && pBasicAudio) pBasicAudio->Release();
						if(st12==1)
							pp.pFilter->QueryInterface(IID_IBasicAudio,(LPVOID *)&pBasicAudio);
						else{
							IBasicAudio *pBasicAudio1=NULL;
							pp.pFilter->QueryInterface(IID_IBasicAudio,(LPVOID *)&pBasicAudio1);
							pBasicAudio1->put_Volume(-10000);
							pBasicAudio1->Release();
						}
					}
					if(s.Right(11)==_T("d Renderer3")){
						if(st12==2 && pBasicAudio) pBasicAudio->Release();
						if(st12==2)
							pp.pFilter->QueryInterface(IID_IBasicAudio,(LPVOID *)&pBasicAudio);
						else{
							IBasicAudio *pBasicAudio1=NULL;
							pp.pFilter->QueryInterface(IID_IBasicAudio,(LPVOID *)&pBasicAudio1);
							pBasicAudio1->put_Volume(-10000);
							pBasicAudio1->Release();
						}
					}
					if(s.Right(11)==_T("d Renderer4")){
						if(st12==3 && pBasicAudio) pBasicAudio->Release();
						if(st12==3)
							pp.pFilter->QueryInterface(IID_IBasicAudio,(LPVOID *)&pBasicAudio);
						else{
							IBasicAudio *pBasicAudio1=NULL;
							pp.pFilter->QueryInterface(IID_IBasicAudio,(LPVOID *)&pBasicAudio1);
							pBasicAudio1->put_Volume(-10000);
							pBasicAudio1->Release();
						}
					}
					if(s.Right(11)==_T("d Renderer5")){
						if(st12==4 && pBasicAudio) pBasicAudio->Release();
						if(st12==4)
							pp.pFilter->QueryInterface(IID_IBasicAudio,(LPVOID *)&pBasicAudio);
						else{
							IBasicAudio *pBasicAudio1=NULL;
							pp.pFilter->QueryInterface(IID_IBasicAudio,(LPVOID *)&pBasicAudio1);
							pBasicAudio1->put_Volume(-10000);
							pBasicAudio1->Release();
						}
					}
					if(s.Right(11)==_T("d Renderer6")){
						if(st12==5 && pBasicAudio) pBasicAudio->Release();
						if(st12==5)
							pp.pFilter->QueryInterface(IID_IBasicAudio,(LPVOID *)&pBasicAudio);
						else{
							IBasicAudio *pBasicAudio1=NULL;
							pp.pFilter->QueryInterface(IID_IBasicAudio,(LPVOID *)&pBasicAudio1);
							pBasicAudio1->put_Volume(-10000);
							pBasicAudio1->Release();
						}
					}
					if(s.Right(11)==_T("d Renderer7")){
						if(st12==6 && pBasicAudio) pBasicAudio->Release();
						if(st12==6)
							pp.pFilter->QueryInterface(IID_IBasicAudio,(LPVOID *)&pBasicAudio);
						else{
							IBasicAudio *pBasicAudio1=NULL;
							pp.pFilter->QueryInterface(IID_IBasicAudio,(LPVOID *)&pBasicAudio1);
							pBasicAudio1->put_Volume(-10000);
							pBasicAudio1->Release();
						}
					}
					if(s.Right(11)==_T("d Renderer8")){
						if(st12==7 && pBasicAudio) pBasicAudio->Release();
						if(st12==7)
							pp.pFilter->QueryInterface(IID_IBasicAudio,(LPVOID *)&pBasicAudio);
						else{
							IBasicAudio *pBasicAudio1=NULL;
							pp.pFilter->QueryInterface(IID_IBasicAudio,(LPVOID *)&pBasicAudio1);
							pBasicAudio1->put_Volume(-10000);
							pBasicAudio1->Release();
						}
					}
					if(s.Right(11)==_T("d Renderer9")){
						if(st12==8 && pBasicAudio) pBasicAudio->Release();
						if(st12==8)
							pp.pFilter->QueryInterface(IID_IBasicAudio,(LPVOID *)&pBasicAudio);
						else{
							IBasicAudio *pBasicAudio1=NULL;
							pp.pFilter->QueryInterface(IID_IBasicAudio,(LPVOID *)&pBasicAudio1);
							pBasicAudio1->put_Volume(-10000);
							pBasicAudio1->Release();
						}
					}
					if(s.Right(11)==_T("d Renderer10")){
						if(st12==9 && pBasicAudio) pBasicAudio->Release();
						if(st12==9)
							pp.pFilter->QueryInterface(IID_IBasicAudio,(LPVOID *)&pBasicAudio);
						else{
							IBasicAudio *pBasicAudio1=NULL;
							pp.pFilter->QueryInterface(IID_IBasicAudio,(LPVOID *)&pBasicAudio1);
							pBasicAudio1->put_Volume(-10000);
							pBasicAudio1->Release();
						}
					}
					pn->Release();
				}
			}
		}
		p->Release();
        // FILTER_INFO 構造体はフィルタ グラフ マネージャへのポインタを保持する。
        // その参照カウントは解放しなければならない。
        if (FilterInfo.pGraph != NULL)
            FilterInfo.pGraph->Release();
        pFilter->Release();
    }

    pEnum->Release();
    return S_OK;
}

long height=0, width=0;

void CDouga::plays2()
{
	videocnt3=0;
	height=0; width=0;
//	if(pGraphBuilder)pGraphBuilder->RenderFile(douga,NULL);
	if(pGraphBuilder)EnumFilters(pGraphBuilder,0);
	if(pVideoWindow)pVideoWindow->put_Owner((OAHWND)m_hWnd);
	if(pVideoWindow)pVideoWindow->put_WindowStyle(WS_CHILD|WS_CLIPSIBLINGS);
	if(pVideoWindow)pVideoWindow->put_MessageDrain((OAHWND)m_hWnd);
	if(pGraphBuilder)pGraphBuilder->QueryInterface(IID_IBasicVideo,(LPVOID *)&pBasicVideo);
	//音量
//	if(pGraphBuilder)pGraphBuilder->QueryInterface(IID_IBasicAudio,(LPVOID *)&pBasicAudio);
//	if(pSplitter)pSplitter->QueryInterface(IID_IAMStreamSelect,(LPVOID *)&ia);
	if(savedata.dsvol==-498)
		if(pBasicAudio)pBasicAudio->put_Volume(-10000);
	else
		if(pBasicAudio)pBasicAudio->put_Volume((savedata.dsvol-1)*7);

//	pSourceFilter->QueryInterface(IID_IAMStreamSelect,(LPVOID*)&ia);
//	if(ia==NULL) if(pSplitter)pSplitter->QueryInterface(IID_IAMStreamSelect,(LPVOID *)&ia);
//
//	DWORD c=0;
//	ia->Count(&c);

	width=0;
	//ev = 0;
	if(ev){
		SIZE a={0},b={0};
		Vdc->GetNativeVideoSize(&a,&b);
		width=a.cx;
		height=a.cy;
	}else{
		if(pBasicVideo)pBasicVideo->get_VideoHeight(&height);
		if(pBasicVideo)pBasicVideo->get_VideoWidth(&width);
		if(pVideoWindow)pVideoWindow->SetWindowPosition(0,0,height,width);
	}

//	pVideoWindow->SetWindowPosition(0,-::GetSystemMetrics(SM_CYCAPTION)+::GetSystemMetrics(SM_CYEDGE)*2+::GetSystemMetrics(SM_CYDLGFRAME)*2,height,width);
//	pBasicVideo->put_DestinationTop(0);
//	pBasicVideo->put_DestinationLeft(0);
	rc.top=0;rc.left=0;rc.right=width;rc.bottom=height;
	rcm.top=0;rcm.left=0;rcm.right=width;rcm.bottom=height;
	if(rcm.right==352&&rcm.bottom==480){
		rcm.right=640;
	}
	if(rcm.right==1440&&rcm.bottom==1080){
		rcm.right=1920;
	}
	if(rcm.right==1440&&rcm.bottom==1088){
		rcm.right=1920;
	}
	if(rcm.right==704&&rcm.bottom==480){
		rcm.bottom=396;
	}
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	if(rc.left<0) rc.left=0;
	if(rc.top<0) rc.top=0;
    MoveWindow(rc.left+10, rc.top+10,rc.right - rc.left+10, rc.bottom - rc.top+10,TRUE);
//    MoveWindow(0,0,height,width,TRUE);
//	MCIWndCanPlay(hMCIWnd);
//	MCIWndPlay(hMCIWnd);
	if(width==0){ShowWindow(SW_HIDE);}else{
		if(pVideoWindow)pVideoWindow->put_Visible(OATRUE);
		ShowWindow(SW_SHOWNORMAL);
		UpdateWindow();
		SetTimer(155,200,NULL);
	}
	if(savedata.gx==-10000){
	}else{
			MoveWindow(savedata.gx,savedata.gy,100,100);
	}
	switch(savedata.douga){
	case 0:OnMenuitem32771();break;
	case 1:OnMenuitem32772();break;
	case 2:OnMenuitem32773();break;
	case 3:OnMenuitem32774();break;
	}
	SetTimer(1255,200,NULL);
}
extern REFTIME aa2,aa;
void CDouga::seek(LONGLONG l)
{
	if(pMediaSeeking)pMediaSeeking->SetTimeFormat(&TIME_FORMAT_MEDIA_TIME);
	REFERENCE_TIME rtpos = l;
/*	if(aa2==0){}else{
		REFTIME t;
		pMediaPosition->get_CurrentPosition(&t);
		LONGLONG te=(LONGLONG)SeekPoint(filesize,(float)(t*100/aa));
//		pMediaSeeking->ConvertTimeFormat(&rtpos,NULL,te,&TIME_FORMAT_SAMPLE);
		rtpos=te*100;
	}*/
	if(pMediaSeeking)pMediaSeeking->SetPositions(&rtpos,AM_SEEKING_AbsolutePositioning,NULL,AM_SEEKING_NoPositioning);

}

extern int ps;
void CDouga::pause(int a)
{
	if(a==0)
	{
		pMediaControl->Pause();
		ps=1;og->m_ps.SetWindowText(_T("再開"));
	}else{
		pMediaControl->Run();
		ps=0;og->m_ps.SetWindowText(_T("一時停止"));
	}
}

void CDouga::stops()
{
	CRect r,rr;
	GetWindowRect(&r);
	savedata.gx=r.left;
	savedata.gy=r.top;
	if(savedata.douga==3){
		rr.top=r.top-savedata.p.top;
		rr.left=r.left-savedata.p.left;
		savedata.p.top+=rr.top;
		savedata.p.left+=rr.left;
		savedata.p.bottom+=rr.top;
		savedata.p.right+=rr.left;
	}
	if(pMediaControl)pMediaControl->Stop();
	REFERENCE_TIME rtpos = 0;
	if(pMediaSeeking)pMediaSeeking->SetPositions(&rtpos,AM_SEEKING_AbsolutePositioning,NULL,AM_SEEKING_NoPositioning);
//	pMediaControl->Pause();
	if(pVideoWindow)pVideoWindow->put_Visible(OAFALSE);
	if(pVideoWindow)pVideoWindow->put_Owner(NULL);
	
	RELEASE(pop);
	RELEASE(vr);
	RELEASE(pMediaPosition);
	RELEASE(pBasicAudio);
	RELEASE(service);
	RELEASE(Vdc);
	RELEASE(prenda);
	RELEASE(prenda2);
	RELEASE(prenda3);
	RELEASE(prenda4);
	RELEASE(prenda5);
	RELEASE(prenda6);
	RELEASE(prenda7);
	RELEASE(prenda8);
	RELEASE(prenda9);
	RELEASE(prenda10);
	RELEASE(prend);
	RELEASE(pDSRenderer);
	RELEASE(pDSRenderer2);
	RELEASE(pDSRenderer3);
	RELEASE(pDSRenderer4);
	RELEASE(pDSRenderer5);
	RELEASE(pDSRenderer6);
	RELEASE(pDSRenderer7);
	RELEASE(pDSRenderer8);
	RELEASE(pDSRenderer9);
	RELEASE(pDSRenderer10);
	RELEASE(pACM);
	RELEASE(pRenderer0);
	RELEASE(pRenderer0_);
	RELEASE(pRenderer1);
	RELEASE(pRenderer);
	RELEASE(pColour);
	RELEASE(pAviDecomp);
	RELEASE(pSourceFilter);
	RELEASE(Haali);
	RELEASE(pSplitter);
	RELEASE(pCaptureGraphBuilder2);
	RELEASE(pSource2);
	RELEASE(pSource1);
	RELEASE(pSource);
	RELEASE(pVmr9);
	RELEASE(pMediaControl);
	RELEASE(pBasicVideo);
	RELEASE(pVideoWindow);
	RELEASE(pMediaSeeking);
	RELEASE(iam);
	RELEASE1(pGraphBuilder);
	CoUninitialize();
	if(mode==-14) Sleep(500);
	ev=FALSE;
}

void CDouga::stop()
{
	if(mode==-2) stops();
	if(u1!=0)
	{
		if (mode == -1) {//ED6SC
				stops();
     	}
		if(mode==1){//ED6SC
			switch(u1)
			{
			case 98:
			case 99:
			case 100:
			case 101:
			case 102:
			case 103:
			case 104:
			case 105:
			case 106:
			case 107:
					stops();
					break;
			}
		}
	}
	if(mode==2){//ED6FC
		switch(u1)
		{
		case 55:
		case 56:
		case 57:
		case 58:
					stops();
					break;
		}
	}
	if(mode==3){//YSF
		switch(u1)
		{
		case 32:
		case 33:
		case 25:
		case 31:
					stops();
					break;
		}
	}
	if(mode==4){//YS6
		switch(u1)
		{
		case 1:
		case 25:
		case 26:
		case 27:
		case 28:
					stops();
					break;

		}
	}
	if(mode==5){//YSF
		switch(u1+1)
		{
		case 41:
		case 42:
		case 43:
		case 44:
		case 45:
		case 46:
		case 47:
		case 48:
				stops();
				break;
		}
	}
	if(mode==6){//YSF
		switch(u1)
		{
		case 141:
		case 142:
		case 143:
		case 144:
		case 145:
		case 146:
								stops();
								break;
		}
	}
	if(mode==7){//YSF
		switch(u1)
		{
		case 65:
		case 66:
			{
					stops();
				break;
			}
		}
	}
	if(mode==8){//YSC1
		switch(u1)
		{
		case 72:
		case 73:
		case 74:
			{
					stops();
				break;
			}
		}
	}
	if(mode==9){//YSC1
		switch(u1)
		{
		case 93:
		case 94:
		case 95:
		case 96:
		case 97:
		case 98:
		case 99:
		case 100:
		case 101:
			{
					stops();
				break;
			}
		}
	}
	if(mode==10){//XANADU
		switch(u1)
		{
		case 24:
		case 25:
			{
					stops();
				break;
			}
		}
	}
	if(mode==11){//ys1
		switch(u1)
		{
		case 25:
			{
					stops();
				break;
			}
		}
	}
	if(mode==12){//ys2
		switch(u1)
		{
		case 31:
		case 32:
			{
					stops();
				break;
			}
		}
	}
	if(mode==15){//gurumin
		switch(u1)
		{
		case 40:
			{
					stops();
				break;
			}
		}
	}
	if(mode==16){//dino
		switch(u1)
		{
		case 33:
			{
					stops();
				break;
			}
		}
	}
	if(mode==19){//ed4
		switch(u1)
		{
		case 1:
		case 2:
			{
					stops();
				break;
			}
		}
	}
	if(mode==-11){//ed4
		switch(u1)
		{
		case 28:
		case 29:
		case 30:
		case 31:
		case 32:
		case 33:
		case 34:
		case 35:
		case 36:
		case 37:
		case 38:
			{
					stops();
				break;
			}
		}
	}
	if(mode==-13){//arc
		switch(u1)
		{
		case 0:
			{
					stops();
				break;
			}
		}
	}
	if(mode==-14){//arc
		switch(u1)
		{
		case 43:
		case 47:
		case 46:
		case 45:
			{
					stops();
					
				break;
			}
		}
	}
	if(mode==-15){//arc
		switch(u1)
		{
		case 50:
		case 51:
		case 49:
			{
					stops();
					
				break;
			}
		}
	}
	u1=0;
	ShowWindow(SW_HIDE);
}

	int x,y,x1,y1_,lu=0;
	double xx,yy,xx1,yy1_,t;

	int mousecnt=0,mousecnt1=0;
	int poix,poiy;
#if WIN64
void CDouga::OnTimer(UINT_PTR nIDEvent) 
#else
void CDouga::OnTimer(UINT nIDEvent) 
#endif
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください

	if(nIDEvent==1255){
		if(savedata.fs==0){
			CRect r,rr;
			GetWindowRect(&r);
			savedata.gx=r.left;
			savedata.gy=r.top;
			if(savedata.douga==3){
				rr.top=r.top-savedata.p.top;
				rr.left=r.left-savedata.p.left;
				savedata.p.top+=rr.top;
				savedata.p.left+=rr.left;
				savedata.p.bottom+=rr.top;
				savedata.p.right+=rr.left;
			}
		}
	}
	if(nIDEvent==155){
		KillTimer(155);
		::SetWindowPos(m_hWnd,HWND_NOTOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
		SetFocus();
	}
	if(nIDEvent==3366){
		mousecnt++;if(mousecnt1==0 && mousecnt>3){
			mousecnt1=1;
			int j;
			for(;;){
				j=ShowCursor(FALSE);if(j<0) break;
			}
		}
	}
	if(nIDEvent==1597){
		KillTimer(1597);
		si=1;
		PostMessage(WM_SIZE,0,0);
	}
	if(nIDEvent==2987){
		pcnt++;if(pcnt==10)KillTimer(2987);
		int cx=GetSystemMetrics(SM_CXSCREEN);
		int cy=GetSystemMetrics(SM_CYSCREEN);
		RECT rect;
		rect.top   = 0;
		rect.left  = 0;
		rect.bottom= cy;
		rect.right = cx;
		InvalidateRect(&rect,TRUE);
	}
	CFrameWnd::OnTimer(nIDEvent);
}

void CDouga::OnSizing(UINT fwSide, LPRECT pRect) 
{
	CFrameWnd::OnSizing(fwSide, pRect);
//	if(lu==1){lu=0; return;}
	RECT r,rr;
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください
	 //左右比を保つ
	r.bottom=rcm.bottom;r.top=rcm.top;
	r.right=rcm.right;r.left=rcm.left;
    int     width,height;
	double _x1,_y1;
    width=r.right-r.left;
    height=r.bottom-r.top;
	x=r.bottom-r.top; y=r.right-r.left;xx=(double)y; yy=(double)x;//動画の画像の大きさを獲得
	r.bottom=pRect->bottom;	r.top=pRect->top;
	r.right=pRect->right;	r.left=pRect->left;
	x1=r.bottom - r.top; y1_=r.right - r.left;xx1=(double)y1_; yy1_=(double)x1;//現在のサイズ獲得
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
	savedata.p.top=pRect->top;
	savedata.p.left=pRect->left;
	savedata.p.bottom=pRect->bottom;
	savedata.p.right=pRect->right;
	savedata.douga=3;
//    SetWindowPos(NULL, 0,0,(int)yy1_, (int)xx1,   SWP_NOMOVE|SWP_NOOWNERZORDER);
//	RY=xx1; RX=yy1_;
//	CheckSize(fwSide,(LPARAM)pRect);
	GetClientRect(&rr);
	GetWindowRect(&r);
	MoveWindow(&r);
	if(ev){
		MFVideoNormalizedRect mvnr={0, 0, 1, 1};
		Vdc->SetVideoPosition(&mvnr, &rr);
	}else{
		pBasicVideo->put_DestinationWidth(rr.right);
		pBasicVideo->put_DestinationHeight(rr.bottom);
		pVideoWindow->put_Top(0);
		pVideoWindow->put_Left(0);
		pVideoWindow->put_Height(rr.bottom);
		pVideoWindow->put_Width(rr.right);
	}
	si=1;
//	SetTimer(1597,30,NULL);
	/**/
}



void CDouga::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);
	if(si==1){
		si=0;
		OnMenuitem32774();
	}
}

void CDouga::OnClose() 
{

	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	CFrameWnd::OnClose();
}


void CDouga::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CFrameWnd::OnShowWindow(bShow, nStatus);
	
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください
	
}
void CDouga::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	CFrameWnd::OnRButtonDown(nFlags, point);
}
void CDouga::OnNcRButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	int iii;
	if (ev)
	{
		if (point.x == -1 && point.y == -1) {
			//キーストロークの発動
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

		CMenu menu, *sub1, *sub2;
		if(savedata.fs)
			VERIFY(menu.LoadMenu(CG_IDR_POPUP_DOUGA));
		else
			VERIFY(menu.LoadMenu(CG_IDR_POPUP_DOUGA1));
		//映像ストリーム
		int eizou = 0,etcs=0;
		for (iii = 0; iii < 10; iii++) {
			if (streamname1[iii] == "") { eizou = iii - 1; break; }
		}
		for (iii = 0; iii < 10; iii++) {
			if (streamname2[iii] == "") { etcs = iii - 1; break; }
		}
		{
			sub1 = menu.GetSubMenu(0);
			sub2 = sub1->GetSubMenu(6);
			{
				CString buf;
				buf.Format(L"映像10:%s", streamname1[9]);
				MENUITEMINFO mii = { sizeof(mii) };
				mii.fMask = MIIM_STRING;
				mii.dwTypeData = buf.GetBuffer();
				sub2->SetMenuItemInfo(9, &mii, TRUE);
			}
			{
				CString buf;
				buf.Format(L"映像 9:%s", streamname1[8]);
				MENUITEMINFO mii = { sizeof(mii) };
				mii.fMask = MIIM_STRING;
				mii.dwTypeData = buf.GetBuffer();
				sub2->SetMenuItemInfo(8, &mii, TRUE);
			}
			{
				CString buf;
				buf.Format(L"映像 8:%s", streamname1[7]);
				MENUITEMINFO mii = { sizeof(mii) };
				mii.fMask = MIIM_STRING;
				mii.dwTypeData = buf.GetBuffer();
				sub2->SetMenuItemInfo(7, &mii, TRUE);
			}
			{
				CString buf;
				buf.Format(L"映像 7:%s", streamname1[6]);
				MENUITEMINFO mii = { sizeof(mii) };
				mii.fMask = MIIM_STRING;
				mii.dwTypeData = buf.GetBuffer();
				sub2->SetMenuItemInfo(6, &mii, TRUE);
			}
			{
				CString buf;
				buf.Format(L"映像 6:%s", streamname1[5]);
				MENUITEMINFO mii = { sizeof(mii) };
				mii.fMask = MIIM_STRING;
				mii.dwTypeData = buf.GetBuffer();
				sub2->SetMenuItemInfo(5, &mii, TRUE);
			}
			{
				CString buf;
				buf.Format(L"映像 5:%s", streamname1[4]);
				MENUITEMINFO mii = { sizeof(mii) };
				mii.fMask = MIIM_STRING;
				mii.dwTypeData = buf.GetBuffer();
				sub2->SetMenuItemInfo(4, &mii, TRUE);
			}
			{
				CString buf;
				buf.Format(L"映像 4:%s", streamname1[3]);
				MENUITEMINFO mii = { sizeof(mii) };
				mii.fMask = MIIM_STRING;
				mii.dwTypeData = buf.GetBuffer();
				sub2->SetMenuItemInfo(3, &mii, TRUE);
			}
			{
				CString buf;
				buf.Format(L"映像 3:%s", streamname1[2]);
				MENUITEMINFO mii = { sizeof(mii) };
				mii.fMask = MIIM_STRING;
				mii.dwTypeData = buf.GetBuffer();
				sub2->SetMenuItemInfo(2, &mii, TRUE);
			}
			{
				CString buf;
				buf.Format(L"映像 2:%s", streamname1[1]);
				MENUITEMINFO mii = { sizeof(mii) };
				mii.fMask = MIIM_STRING;
				mii.dwTypeData = buf.GetBuffer();
				sub2->SetMenuItemInfo(1, &mii, TRUE);
			}
			{
				CString buf;
				buf.Format(L"映像 1:%s", streamname1[0]);
				MENUITEMINFO mii = { sizeof(mii) };
				mii.fMask = MIIM_STRING;
				mii.dwTypeData = buf.GetBuffer();
				sub2->SetMenuItemInfo(0, &mii, TRUE);
			}
		}
		{
			sub1 = menu.GetSubMenu(0);
			sub2 = sub1->GetSubMenu(7);
			{
				CString buf;
				buf.Format(L"音声10:%s", streamname[9]);
				MENUITEMINFO mii = { sizeof(mii) };
				mii.fMask = MIIM_STRING;
				mii.dwTypeData = buf.GetBuffer();
				sub2->SetMenuItemInfo(9, &mii, TRUE);
			}
			{
				CString buf;
				buf.Format(L"音声 9:%s", streamname[8]);
				MENUITEMINFO mii = { sizeof(mii) };
				mii.fMask = MIIM_STRING;
				mii.dwTypeData = buf.GetBuffer();
				sub2->SetMenuItemInfo(8, &mii, TRUE);
			}
			{
				CString buf;
				buf.Format(L"音声 8:%s", streamname[7]);
				MENUITEMINFO mii = { sizeof(mii) };
				mii.fMask = MIIM_STRING;
				mii.dwTypeData = buf.GetBuffer();
				sub2->SetMenuItemInfo(7, &mii, TRUE);
			}
			{
				CString buf;
				buf.Format(L"音声 7:%s", streamname[6]);
				MENUITEMINFO mii = { sizeof(mii) };
				mii.fMask = MIIM_STRING;
				mii.dwTypeData = buf.GetBuffer();
				sub2->SetMenuItemInfo(6, &mii, TRUE);
			}
			{
				CString buf;
				buf.Format(L"音声 6:%s", streamname[5]);
				MENUITEMINFO mii = { sizeof(mii) };
				mii.fMask = MIIM_STRING;
				mii.dwTypeData = buf.GetBuffer();
				sub2->SetMenuItemInfo(5, &mii, TRUE);
			}
			{
				CString buf;
				buf.Format(L"音声 5:%s", streamname[4]);
				MENUITEMINFO mii = { sizeof(mii) };
				mii.fMask = MIIM_STRING;
				mii.dwTypeData = buf.GetBuffer();
				sub2->SetMenuItemInfo(4, &mii, TRUE);
			}
			{
				CString buf;
				buf.Format(L"音声 4:%s", streamname[3]);
				MENUITEMINFO mii = { sizeof(mii) };
				mii.fMask = MIIM_STRING;
				mii.dwTypeData = buf.GetBuffer();
				sub2->SetMenuItemInfo(3, &mii, TRUE);
			}
			{
				CString buf;
				buf.Format(L"音声 3:%s", streamname[2]);
				MENUITEMINFO mii = { sizeof(mii) };
				mii.fMask = MIIM_STRING;
				mii.dwTypeData = buf.GetBuffer();
				sub2->SetMenuItemInfo(2, &mii, TRUE);
			}
			{
				CString buf;
				buf.Format(L"音声 2:%s", streamname[1]);
				MENUITEMINFO mii = { sizeof(mii) };
				mii.fMask = MIIM_STRING;
				mii.dwTypeData = buf.GetBuffer();
				sub2->SetMenuItemInfo(1, &mii, TRUE);
			}
			{
				CString buf;
				buf.Format(L"音声 1:%s", streamname[0]);
				MENUITEMINFO mii = { sizeof(mii) };
				mii.fMask = MIIM_STRING;
				mii.dwTypeData = buf.GetBuffer();
				sub2->SetMenuItemInfo(0, &mii, TRUE);
			}
		}
		{
			sub1 = menu.GetSubMenu(0);
			sub2 = sub1->GetSubMenu(8);
			{
				CString buf;
				buf.Format(L"%s", streamname2[9]);
				MENUITEMINFO mii = { sizeof(mii) };
				mii.fMask = MIIM_STRING;
				mii.dwTypeData = buf.GetBuffer();
				sub2->SetMenuItemInfo(9, &mii, TRUE);
			}
			{
				CString buf;
				buf.Format(L"%s", streamname2[8]);
				MENUITEMINFO mii = { sizeof(mii) };
				mii.fMask = MIIM_STRING;
				mii.dwTypeData = buf.GetBuffer();
				sub2->SetMenuItemInfo(8, &mii, TRUE);
			}
			{
				CString buf;
				buf.Format(L"%s", streamname2[7]);
				MENUITEMINFO mii = { sizeof(mii) };
				mii.fMask = MIIM_STRING;
				mii.dwTypeData = buf.GetBuffer();
				sub2->SetMenuItemInfo(7, &mii, TRUE);
			}
			{
				CString buf;
				buf.Format(L"%s", streamname2[6]);
				MENUITEMINFO mii = { sizeof(mii) };
				mii.fMask = MIIM_STRING;
				mii.dwTypeData = buf.GetBuffer();
				sub2->SetMenuItemInfo(6, &mii, TRUE);
			}
			{
				CString buf;
				buf.Format(L"%s", streamname2[5]);
				MENUITEMINFO mii = { sizeof(mii) };
				mii.fMask = MIIM_STRING;
				mii.dwTypeData = buf.GetBuffer();
				sub2->SetMenuItemInfo(5, &mii, TRUE);
			}
			{
				CString buf;
				buf.Format(L"%s", streamname2[4]);
				MENUITEMINFO mii = { sizeof(mii) };
				mii.fMask = MIIM_STRING;
				mii.dwTypeData = buf.GetBuffer();
				sub2->SetMenuItemInfo(4, &mii, TRUE);
			}
			{
				CString buf;
				buf.Format(L"%s", streamname2[3]);
				MENUITEMINFO mii = { sizeof(mii) };
				mii.fMask = MIIM_STRING;
				mii.dwTypeData = buf.GetBuffer();
				sub2->SetMenuItemInfo(3, &mii, TRUE);
			}
			{
				CString buf;
				buf.Format(L"%s", streamname2[2]);
				MENUITEMINFO mii = { sizeof(mii) };
				mii.fMask = MIIM_STRING;
				mii.dwTypeData = buf.GetBuffer();
				sub2->SetMenuItemInfo(2, &mii, TRUE);
			}
			{
				CString buf;
				buf.Format(L"%s", streamname2[1]);
				MENUITEMINFO mii = { sizeof(mii) };
				mii.fMask = MIIM_STRING;
				mii.dwTypeData = buf.GetBuffer();
				sub2->SetMenuItemInfo(1, &mii, TRUE);
			}
			{
				CString buf;
				buf.Format(L"%s", streamname2[0]);
				MENUITEMINFO mii = { sizeof(mii) };
				mii.fMask = MIIM_STRING;
				mii.dwTypeData = buf.GetBuffer();
				sub2->SetMenuItemInfo(0, &mii, TRUE);
			}
		}
		if (audionum <= 9) {
			menu.DeleteMenu(ID_ST10, MF_BYCOMMAND);
		}
		if (audionum <= 8) {
			menu.DeleteMenu(ID_ST9, MF_BYCOMMAND);
		}
		if (audionum <= 7) {
			menu.DeleteMenu(ID_ST8, MF_BYCOMMAND);
		}
		if (audionum <= 6) {
			menu.DeleteMenu(ID_ST7, MF_BYCOMMAND);
		}
		if (audionum <= 5) {
			menu.DeleteMenu(ID_ST6, MF_BYCOMMAND);
		}
		if (audionum <= 4) {
			menu.DeleteMenu(ID_ST5, MF_BYCOMMAND);
		}
		if (audionum <= 3) {
			menu.DeleteMenu(ID_ST4, MF_BYCOMMAND);
		}
		if (audionum <= 2) {
			menu.DeleteMenu(ID_ST3, MF_BYCOMMAND);
		}
		if (audionum <= 1) {
			menu.DeleteMenu(ID_ST2, MF_BYCOMMAND);
		}

		if (streamname1[9] == "") {
			menu.DeleteMenu(ID_MV10, MF_BYCOMMAND);
		}
		if (streamname1[8] == "") {
			menu.DeleteMenu(ID_MV9, MF_BYCOMMAND);
		}
		if (streamname1[7] == "") {
			menu.DeleteMenu(ID_MV8, MF_BYCOMMAND);
		}
		if (streamname1[6] == "") {
			menu.DeleteMenu(ID_MV7, MF_BYCOMMAND);
		}
		if (streamname1[5] == "") {
			menu.DeleteMenu(ID_MV6, MF_BYCOMMAND);
		}
		if (streamname1[4] == "") {
			menu.DeleteMenu(ID_MV5, MF_BYCOMMAND);
		}
		if (streamname1[3] == "") {
			menu.DeleteMenu(ID_MV4, MF_BYCOMMAND);
		}
		if (streamname1[2] == "") {
			menu.DeleteMenu(ID_MV3, MF_BYCOMMAND);
		}
		if (streamname1[1] == "") {
			menu.DeleteMenu(ID_MV2, MF_BYCOMMAND);
		}
		if (streamname1[0] == "") {
			menu.DeleteMenu(ID_MV1, MF_BYCOMMAND);
		}

		if (streamname2[9] == "") {
			menu.DeleteMenu(ID_ETC10, MF_BYCOMMAND);
		}
		if (streamname2[8] == "") {
			menu.DeleteMenu(ID_ETC9, MF_BYCOMMAND);
		}
		if (streamname2[7] == "") {
			menu.DeleteMenu(ID_ETC8, MF_BYCOMMAND);
		}
		if (streamname2[6] == "") {
			menu.DeleteMenu(ID_ETC7, MF_BYCOMMAND);
		}
		if (streamname2[5] == "") {
			menu.DeleteMenu(ID_ETC6, MF_BYCOMMAND);
		}
		if (streamname2[4] == "") {
			menu.DeleteMenu(ID_ETC5, MF_BYCOMMAND);
		}
		if (streamname2[3] == "") {
			menu.DeleteMenu(ID_ETC4, MF_BYCOMMAND);
		}
		if (streamname2[2] == "") {
			menu.DeleteMenu(ID_ETC3, MF_BYCOMMAND);
		}
		if (streamname2[1] == "") {
			menu.DeleteMenu(ID_ETC2, MF_BYCOMMAND);
		}
		if (streamname2[0] == "") {
			menu.DeleteMenu(ID_ETC1, MF_BYCOMMAND);
		}

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
	CFrameWnd::OnNcRButtonDown(nHitTest, point);
}

//void CDouga::OnNcLButtonDown(UINT nHitTest, CPoint point)
//{
//	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
//	int a=0;
//	a=a;
//}

void CDouga::OnContextMenu(CWnd*, CPoint point)
{
	if(savedata.fs)return;
	// CG: このブロックはポップアップ メニュー コンポーネントによって追加されました
	{
		if (point.x == -1 && point.y == -1){
			//キーストロークの発動
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

		CMenu menu;
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_DOUGA));
		if(audionum<=9)
			menu.DeleteMenu(ID_ST10,MF_BYCOMMAND);
		if(audionum<=8)
			menu.DeleteMenu(ID_ST9,MF_BYCOMMAND);
		if(audionum<=7)
			menu.DeleteMenu(ID_ST8,MF_BYCOMMAND);
		if(audionum<=6)
			menu.DeleteMenu(ID_ST7,MF_BYCOMMAND);
		if(audionum<=5)
			menu.DeleteMenu(ID_ST6,MF_BYCOMMAND);
		if(audionum<=4)
			menu.DeleteMenu(ID_ST5,MF_BYCOMMAND);
		if(audionum<=3)
			menu.DeleteMenu(ID_ST4,MF_BYCOMMAND);
		if(audionum<=2)
			menu.DeleteMenu(ID_ST3,MF_BYCOMMAND);
		if(audionum<=1)
			menu.DeleteMenu(ID_ST2,MF_BYCOMMAND);
		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
}

void CDouga::OnMV1()
{
	if (pGraphBuilder && iam) {
		iam->Enable(0, AMSTREAMSELECTENABLE_ENABLE);
	}
}

void CDouga::OnMV2()
{
	if (pGraphBuilder && iam) {
		iam->Enable(1, AMSTREAMSELECTENABLE_ENABLE);
	}
}

void CDouga::OnMV3()
{
	if (pGraphBuilder && iam) {
		iam->Enable(2, AMSTREAMSELECTENABLE_ENABLE);
	}
}

void CDouga::OnMV4()
{
	if (pGraphBuilder && iam) {
		iam->Enable(3, AMSTREAMSELECTENABLE_ENABLE);
	}
}

void CDouga::OnMV5()
{
	if (pGraphBuilder && iam) {
		iam->Enable(4, AMSTREAMSELECTENABLE_ENABLE);
	}
}

void CDouga::OnMV6()
{
	if (pGraphBuilder && iam) {
		iam->Enable(5, AMSTREAMSELECTENABLE_ENABLE);
	}
}

void CDouga::OnMV7()
{
	if (pGraphBuilder && iam) {
		iam->Enable(6, AMSTREAMSELECTENABLE_ENABLE);
	}
}

void CDouga::OnMV8()
{
	if (pGraphBuilder && iam) {
		iam->Enable(7, AMSTREAMSELECTENABLE_ENABLE);
	}
}

void CDouga::OnMV9()
{
	if (pGraphBuilder && iam) {
		iam->Enable(8, AMSTREAMSELECTENABLE_ENABLE);
	}
}

void CDouga::OnMV10()
{
	if (pGraphBuilder && iam) {
		iam->Enable(9, AMSTREAMSELECTENABLE_ENABLE);
	}
}


void CDouga::OnST1() 
{
	st12=1;
//	if(pGraphBuilder)EnumFilters(pGraphBuilder,0);
	if (pGraphBuilder && iam) {
		iam->Enable(au, AMSTREAMSELECTENABLE_ENABLE);
	}
}

void CDouga::OnST2() 
{
	st12=2;
	if (pGraphBuilder && iam) {
		iam->Enable(au+1, AMSTREAMSELECTENABLE_ENABLE);
	}
}

void CDouga::OnST3() 
{
	st12=3;
	if (pGraphBuilder && iam) {
		iam->Enable(au+2, AMSTREAMSELECTENABLE_ENABLE);
	}
}

void CDouga::OnST4() 
{
	st12=4;
	if (pGraphBuilder && iam) {
		iam->Enable(au+3, AMSTREAMSELECTENABLE_ENABLE);
	}
}

void CDouga::OnST5() 
{
	st12=5;
	if (pGraphBuilder && iam) {
		iam->Enable(au+4, AMSTREAMSELECTENABLE_ENABLE);
	}
}

void CDouga::OnST6() 
{
	st12=6;
	if (pGraphBuilder && iam) {
		iam->Enable(au+5, AMSTREAMSELECTENABLE_ENABLE);
	}
}

void CDouga::OnST7() 
{
	st12=7;
	if (pGraphBuilder && iam) {
		iam->Enable(au+6, AMSTREAMSELECTENABLE_ENABLE);
	}
}

void CDouga::OnST8() 
{
	st12=8;
	if (pGraphBuilder && iam) {
		iam->Enable(au+7, AMSTREAMSELECTENABLE_ENABLE);
	}
}

void CDouga::OnST9() 
{
	st12=9;
	if (pGraphBuilder && iam) {
		iam->Enable(au+8, AMSTREAMSELECTENABLE_ENABLE);
	}
}

void CDouga::OnST10() 
{
	st12=9;
	if (pGraphBuilder && iam) {
		iam->Enable(au+9, AMSTREAMSELECTENABLE_ENABLE);
	}
}

void CDouga::OnETC1()
{
	if (pGraphBuilder && iam) {
		iam->Enable(etc+0, AMSTREAMSELECTENABLE_ENABLE);
	}
}

void CDouga::OnETC2()
{
	if (pGraphBuilder && iam) {
		iam->Enable(etc + 1, AMSTREAMSELECTENABLE_ENABLE);
	}
}

void CDouga::OnETC3()
{
	if (pGraphBuilder && iam) {
		iam->Enable(etc + 2, AMSTREAMSELECTENABLE_ENABLE);
	}
}

void CDouga::OnETC4()
{
	if (pGraphBuilder && iam) {
		iam->Enable(etc + 3, AMSTREAMSELECTENABLE_ENABLE);
	}
}

void CDouga::OnETC5()
{
	if (pGraphBuilder && iam) {
		iam->Enable(etc + 4, AMSTREAMSELECTENABLE_ENABLE);
	}
}

void CDouga::OnETC6()
{
	if (pGraphBuilder && iam) {
		iam->Enable(etc + 5, AMSTREAMSELECTENABLE_ENABLE);
	}
}

void CDouga::OnETC7()
{
	if (pGraphBuilder && iam) {
		iam->Enable(etc + 6, AMSTREAMSELECTENABLE_ENABLE);
	}
}

void CDouga::OnETC8()
{
	if (pGraphBuilder && iam) {
		iam->Enable(etc + 7, AMSTREAMSELECTENABLE_ENABLE);
	}
}

void CDouga::OnETC9()
{
	if (pGraphBuilder && iam) {
		iam->Enable(etc + 8, AMSTREAMSELECTENABLE_ENABLE);
	}
}

void CDouga::OnETC10()
{
	if (pGraphBuilder && iam) {
		iam->Enable(etc + 9, AMSTREAMSELECTENABLE_ENABLE);
	}
}

void CDouga::OnMenuitem32771() 
{
	RECT r,rr;
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	r.bottom=rcm.bottom;
	r.top=rcm.top;
	r.right=rcm.right;
	r.left=rcm.left;
//	AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, FALSE);
	y=r.bottom-r.top; x=r.right-r.left;
	y1_=rcm.bottom-rcm.top; x1=rcm.right-rcm.left;
//	x+=GetSystemMetrics(SM_CXSIZEFRAME)*2;
//	y=y+(GetSystemMetrics(SM_CYSIZEFRAME)+::GetSystemMetrics(SM_CYCAPTION));
	si=0;
	SetWindowPos(NULL,
				0,0,x, y+(GetSystemMetrics(SM_CYSIZEFRAME)+::GetSystemMetrics(SM_CYCAPTION)),   SWP_NOMOVE|SWP_NOOWNERZORDER);
	GetClientRect(&rr);
	GetWindowRect(&r);
	MoveWindow(&r);
	if(ev){
		MFVideoNormalizedRect mvnr={0, 0, 1, 1};
		Vdc->SetVideoPosition(&mvnr, &rr);
	}else{
		if(pBasicVideo){
			pBasicVideo->put_DestinationWidth(rr.right);
			pBasicVideo->put_DestinationHeight(rr.bottom);
		}
		if(pVideoWindow){
			pVideoWindow->put_Top(0);
			pVideoWindow->put_Left(0);
			pVideoWindow->put_Height(rr.bottom);
			pVideoWindow->put_Width(rr.right);
		}
	}
	savedata.douga=0;

	savedata.p.top=r.top;
	savedata.p.left=r.left;
	savedata.p.bottom=r.bottom;
	savedata.p.right=r.right;
	si=1;
	SetTimer(1597,30,NULL);
}

void CDouga::OnMenuitem32772() 
{
	RECT r,rr;
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	r.bottom=rcm.bottom;
	r.top=rcm.top;
	r.right=rcm.right;
	r.left=rcm.left;
//	AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, FALSE);
	y=r.bottom-r.top; x=r.right-r.left;
//	x+=GetSystemMetrics(SM_CXSIZEFRAME)*2;
//	y=y+(GetSystemMetrics(SM_CYSIZEFRAME)*2+::GetSystemMetrics(SM_CYCAPTION));
	si=0;
	SetWindowPos(NULL,
				0,0,x*2, y*2+(GetSystemMetrics(SM_CYSIZEFRAME)+::GetSystemMetrics(SM_CYCAPTION)),   SWP_NOMOVE|SWP_NOOWNERZORDER);
	GetClientRect(&rr);
	GetWindowRect(&r);
	MoveWindow(&r);
	if(ev){
		MFVideoNormalizedRect mvnr={0, 0, 1, 1};
		Vdc->SetVideoPosition(&mvnr, &rr);
	}else{
		if(pBasicVideo){
			pBasicVideo->put_DestinationWidth(rr.right);
			pBasicVideo->put_DestinationHeight(rr.bottom);
		}
		if(pVideoWindow){
			pVideoWindow->put_Top(0);
			pVideoWindow->put_Left(0);
			pVideoWindow->put_Height(rr.bottom);
			pVideoWindow->put_Width(rr.right);
		}
	}
	savedata.douga=1;	
	savedata.p.top=r.top;
	savedata.p.left=r.left;
	savedata.p.bottom=r.bottom;
	savedata.p.right=r.right;
	si=1;
	SetTimer(1597,30,NULL);
	
}

void CDouga::OnMenuitem32773() 
{
	RECT r,rr;
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	r.bottom=rcm.bottom;
	r.top=rcm.top;
	r.right=rcm.right;
	r.left=rcm.left;
//	AdjustWindowRect(&r, (WS_OVERLAPPEDWINDOW)& ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX & ~WS_SYSMENU, FALSE);
	y=r.bottom-r.top; x=r.right-r.left;
//	x-=GetSystemMetrics(SM_CXSIZEFRAME)*2;
//	y=y-(GetSystemMetrics(SM_CYSIZEFRAME)+::GetSystemMetrics(SM_CYCAPTION));
	si=0;
	SetWindowPos(NULL,
				0,0,(int)((double)x*1.5), (int)((double)y*1.5)+(GetSystemMetrics(SM_CYSIZEFRAME)+::GetSystemMetrics(SM_CYCAPTION)),   SWP_NOMOVE|SWP_NOOWNERZORDER);
	GetClientRect(&rr);
	GetWindowRect(&r);
	MoveWindow(&r);
	if(ev){
		MFVideoNormalizedRect mvnr={0, 0, 1, 1};
		Vdc->SetVideoPosition(&mvnr, &rr);
	}else{
		if(pBasicVideo){
			pBasicVideo->put_DestinationWidth(rr.right);
			pBasicVideo->put_DestinationHeight(rr.bottom);
		}
		if(pVideoWindow){
			pVideoWindow->put_Top(0);
			pVideoWindow->put_Left(0);
			pVideoWindow->put_Height(rr.bottom);
			pVideoWindow->put_Width(rr.right);
		}
	}
	savedata.douga=2;	
	savedata.p.top=r.top;
	savedata.p.left=r.left;
	savedata.p.bottom=r.bottom;
	savedata.p.right=r.right;
	si=1;
	SetTimer(1597,30,NULL);
}

void CDouga::OnMenuitem32774() 
{
	if(pBasicVideo==NULL) return;
	RECT r,rr;
	double i;
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	r.bottom=rcm.bottom;
	r.top=rcm.top;
	r.right=rcm.right;
	r.left=rcm.left;
	i=(double)(savedata.p.right-savedata.p.left)/(double)rcm.right;
	SetWindowPos(NULL,
				savedata.p.left,savedata.p.top,(int)(i*(double)(rcm.right-rcm.left)),
				(int)(i*(double)(rcm.bottom-rcm.top)+(GetSystemMetrics(SM_CYSIZEFRAME)+::GetSystemMetrics(SM_CYCAPTION))),  SWP_NOOWNERZORDER);
	GetClientRect(&rr);
	GetWindowRect(&r);
	MoveWindow(&r);
	if(ev){
		MFVideoNormalizedRect mvnr={0, 0, 1, 1};
		Vdc->SetVideoPosition(&mvnr, &rr);
	}else{
		if(pBasicVideo){
			pBasicVideo->put_DestinationWidth(rr.right);
			pBasicVideo->put_DestinationHeight(rr.bottom);
		}
		if(pVideoWindow){
			pVideoWindow->put_Top(0);
			pVideoWindow->put_Left(0);
			pVideoWindow->put_Height(rr.bottom);
			pVideoWindow->put_Width(rr.right);
		}
	}
//	savedata.douga=3;	
}

int dd2=0;
void CDouga::OnPaint() 
{
	CPaintDC dcc(this); // 描画用のデバイス コンテキスト
	
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください
/*	DWORD dwStyle = GetWindowLong(m_hWnd, GWL_STYLE);
	dwStyle &= ~WS_CAPTION;
	dwStyle |= WS_SIZEBOX;
	SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);
	SetWindowPos(NULL, 0, 0, 0, 0,
			SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER | SWP_FRAMECHANGED);
*/	RECT r;
	GetWindowRect(&r);
	MoveWindow(&r);
	if(dd2==1){
		dcc.BitBlt(0,0,GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN),&dc,0,0,SRCCOPY);
		dd2=0;
	}
	if(ev){
		Vdc->RepaintVideo();
	}

	// 描画用メッセージとして CFrameWnd::OnPaint() を呼び出してはいけません
}
extern int killw;
void CDouga::PostNcDestroy() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
//	killw=1;
//	delete this;
	CFrameWnd::PostNcDestroy();
}


LRESULT CDouga::OnNcHitTest(CPoint point) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	
//	return CFrameWnd::OnNcHitTest(point);
	if(savedata.fs==0){
		UINT nHit = CFrameWnd::OnNcHitTest(point);
		return (nHit == HTCLIENT)? HTCAPTION : nHit;
	}else{
		int cx=GetSystemMetrics(SM_CXSCREEN);
		int cy=GetSystemMetrics(SM_CYSCREEN);
		SetWindowPos(NULL,0,0,cx,cy,SWP_NOOWNERZORDER);
		return HTBORDER ;
	}
//	return HTCAPTION;
}

void CDouga::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
//	if(si==1){
//		lpMMI->ptMinTrackSize.y=(int)xx1-20;
//		lpMMI->ptMinTrackSize.x=(int)yy1_-20;
//		lpMMI->ptMaxTrackSize.y=(int)xx1+20;
//		lpMMI->ptMaxTrackSize.x=(int)yy1_+20;
//	}
	CFrameWnd::OnGetMinMaxInfo(lpMMI);
}

int CDouga::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	if(savedata.fs==0)
		nHitTest =(nHitTest == HTCLIENT)? HTCAPTION : nHitTest;
	return CFrameWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

LRESULT CDouga::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	
	return CFrameWnd::DefWindowProc(message, wParam, lParam);
}

CPoint m_pointOld;
BOOL m_bMoving=FALSE;

void CDouga::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	lu=1;

	if( m_bMoving == TRUE ) {
		// ドラッグ中だった場合
		m_bMoving = FALSE;
		::ReleaseCapture();	
	}
	CFrameWnd::OnLButtonUp(nFlags, point);
}

void CDouga::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	if(savedata.fs) return;
   m_bMoving = TRUE;
	SetCapture();
	m_pointOld = point;
	
	CFrameWnd::OnLButtonDown(nFlags, point);
}

void CDouga::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	if(savedata.fs && (poix!=point.x || poiy!=point.y)){
		int j;
		for(;;){
			j=ShowCursor(TRUE);if(j>=0) break;
		}
		mousecnt=mousecnt1=0;
	}
	if(savedata.fs){
		poix=point.x;
		poiy=point.y;
	}
	CFrameWnd::OnNcMouseMove(nHitTest, point);
}

void CDouga::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	if( m_bMoving == TRUE ) {
		CRect rect;
		GetWindowRect(&rect);
		rect.left += (point.x - m_pointOld.x);
		rect.right += (point.x - m_pointOld.x);
		rect.top += (point.y - m_pointOld.y);
		rect.bottom += (point.y - m_pointOld.y);
		SetWindowPos(NULL, rect.left, rect.top,
		rect.right - rect.left, rect.bottom - rect.top,
		SWP_SHOWWINDOW|SWP_NOOWNERZORDER);
	}
	if(savedata.fs && (poix!=point.x || poiy!=point.y)){
		int j;
		for(;;){
			j=ShowCursor(TRUE);if(j>=0) break;
		}
		mousecnt=mousecnt1=0;
	}
	if(savedata.fs){
		poix=point.x;
		poiy=point.y;
	}
	
	CFrameWnd::OnMouseMove(nFlags, point);
}

BOOL CDouga::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	RECT r;
	GetWindowRect(&r);
	MoveWindow(&r);
	
	return CFrameWnd::OnEraseBkgnd(pDC);
}

extern CDouga *pMainFrame1;
BOOL CDouga::DestroyWindow() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	KillTimer(1255);
	stop();	
	bmp.DeleteObject();
	dc.DeleteDC();
	HMODULE hDLL;
	typedef DWORD (WINAPI *PFUNC)(UINT);
	PFUNC pFunc;
	hDLL=::LoadLibrary(_T("Dwmapi"));
	pFunc=(PFUNC)::GetProcAddress(hDLL,"DwmEnableComposition");

	if(pFunc){
		pFunc(DWM_EC_ENABLECOMPOSITION  );
	}
	::FreeLibrary(hDLL);
	KillTimer(155);
	KillTimer(3366);
	KillTimer(1597);
	KillTimer(2987);
	BOOL rr=CFrameWnd::DestroyWindow();
//	delete this;

	return rr;
}

BOOL CDouga::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
//	cs.style&=~WS_CAPTION;
	return CFrameWnd::PreCreateWindow(cs);
}

void CDouga::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CFrameWnd::OnWindowPosChanging(lpwndpos);
}

void CDouga::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CFrameWnd::OnWindowPosChanged(lpwndpos);

	// TODO: ここにメッセージ ハンドラ コードを追加します。
}

int CDouga::SeekPoint(int file_bytes, float percent)
{
// interpolate in TOC to get file seek point in bytes
int a, seekpoint;
float fa, fb, fx;
if( percent < 0.0f )   percent = 0.0f;
if( percent > 100.0f ) percent = 100.0f;
a = (int)percent;
if( a > 99 ) a = 99;
fa = toc[a];
if( a < 99 ) {
    fb = toc[a+1];
}else {
    fb = 256.0f;
}
fx = fa + (fb-fa)*(percent-a);
seekpoint = (int)((1.0f/256.0f)*fx*file_bytes); 
return seekpoint;
}
extern BOOL videoonly;

void CDouga::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	if(pMediaSeeking && (mode==-2 || (mode>0 && videoonly==TRUE))){
		LONGLONG a;
		pMediaSeeking->GetCurrentPosition(&a);
		if(nChar==VK_RIGHT){
			a+=10*10000000;
			pMediaSeeking->SetPositions(&a,AM_SEEKING_AbsolutePositioning,NULL,AM_SEEKING_NoPositioning);
		}
		if(nChar==VK_LEFT){
			a-=10*10000000;
			pMediaSeeking->SetPositions(&a,AM_SEEKING_AbsolutePositioning,NULL,AM_SEEKING_NoPositioning);
		}
		if(nChar==VK_UP){
			og->m_dsval.SetPos(og->m_dsval.GetPos()+5);
		}
		if(nChar==VK_DOWN){
			og->m_dsval.SetPos(og->m_dsval.GetPos()-5);
		}
		if(nChar=='C'){
			On32775();
		}
	}else{
		if(nChar==VK_RIGHT){
			og->rl(1);
		}
		if(nChar==VK_LEFT){
			og->rl(-1);
		}
		if(nChar==VK_UP){
			og->m_dsval.SetPos(og->m_dsval.GetPos()+5);
		}
		if(nChar==VK_DOWN){
			og->m_dsval.SetPos(og->m_dsval.GetPos()-5);
		}
	}
	CFrameWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CDouga::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	if(savedata.fs)return CFrameWnd::OnMouseWheel(nFlags, zDelta, pt);
	if(zDelta>0){
		savedata.p.right+=20;
	}else{
		savedata.p.right-=20;
		if(savedata.p.right<savedata.p.left)savedata.p.right=savedata.p.left;
	}
	savedata.douga=3;
	OnMenuitem32774();
	return CFrameWnd::OnMouseWheel(nFlags, zDelta, pt);
}

void CDouga::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	RECT rr;
	if(ev){	CFrameWnd::OnLButtonDblClk(nFlags, point);return;}
	if(savedata.fs){
		savedata.fs=0;
		SetWindowLong(m_hWnd,GWL_EXSTYLE,WS_EX_OVERLAPPEDWINDOW|WS_EX_ACCEPTFILES);
		int i=GetWindowLong(m_hWnd,GWL_STYLE);
		SetWindowLong(m_hWnd,GWL_STYLE,((i | WS_OVERLAPPEDWINDOW)& ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX & ~WS_SYSMENU));
		OnMenuitem32774();
		KillTimer(3366);
		int j;
		for(;;){
			j=ShowCursor(TRUE);if(j>=0) break;
		}
	}else{
		savedata.fs=1;
		int cx=GetSystemMetrics(SM_CXSCREEN);
		int cy=GetSystemMetrics(SM_CYSCREEN);
		int i=GetWindowLong(m_hWnd,GWL_STYLE);
		SetWindowLong(m_hWnd,GWL_EXSTYLE,0);
		SetWindowLong(m_hWnd,GWL_STYLE,i & ~WS_CAPTION & ~WS_BORDER & ~WS_THICKFRAME);
		SetWindowPos(NULL,0,0,cx,cy,SWP_NOOWNERZORDER);
		double ii;int cyy,cxx;
		if(rcm.bottom<rcm.right){
			ii=(double)(cx)/(double)rcm.right;
			cyy=cy/2-(int)(((double)rcm.bottom*ii)/2);
			cxx=cx;
			rr.top=cyy;rr.bottom=cyy+(int)((double)rcm.bottom*ii); rr.left=0;rr.right=cxx;
		}else{
			ii=(double)(cy)/(double)rcm.bottom;
			cxx=cx/2-(int)(((double)rcm.right*ii)/2);
			cyy=cy;
			rr.top=0;rr.bottom=cyy; rr.left=cxx;rr.right=cxx+(int)((double)rcm.right*ii);
		}
		if(savedata.render==0){
			pBasicVideo->put_DestinationWidth(rr.right-rr.left);
			pBasicVideo->put_DestinationHeight(rr.bottom-rr.top);
			pVideoWindow->put_Top(rr.top);
			pVideoWindow->put_Left(rr.left);
			pVideoWindow->put_Height(rr.bottom);
			pVideoWindow->put_Width(rr.right);
		}else{
			GetClientRect(&rr);
			pBasicVideo->put_DestinationWidth(rr.right-rr.left);
			pBasicVideo->put_DestinationHeight(rr.bottom-rr.top);
			pVideoWindow->put_Top(rr.top);
			pVideoWindow->put_Left(rr.left);
			pVideoWindow->put_Height(rr.bottom);
			pVideoWindow->put_Width(rr.right);
		}
		mousecnt=mousecnt1=0;
		SetTimer(3366,500,NULL);
	}
	GetClientRect(&rr);
	InvalidateRect(&rr,TRUE);
	dd2=1;
	CFrameWnd::OnLButtonDblClk(nFlags, point);
}
extern void DoEvent();
void CDouga::OnNcLButtonDblClk(UINT nHitTest, CPoint point)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	//if(ev){CFrameWnd::OnNcLButtonDblClk(nHitTest, point);return;}
	if(savedata.fs){
		savedata.fs=0;
		SetWindowLong(m_hWnd,GWL_EXSTYLE,WS_EX_OVERLAPPEDWINDOW|WS_EX_ACCEPTFILES);
		int i=GetWindowLong(m_hWnd,GWL_STYLE);
		SetWindowLong(m_hWnd,GWL_STYLE,((i | WS_OVERLAPPEDWINDOW)& ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX & ~WS_SYSMENU));
		OnMenuitem32774();
		KillTimer(3366);
		int j;
		for(;;){
			j=ShowCursor(TRUE);if(j>=0) break;
		}
	}else{
		savedata.fs=1;
		int cx=GetSystemMetrics(SM_CXSCREEN);
		int cy=GetSystemMetrics(SM_CYSCREEN);
		int i=GetWindowLong(m_hWnd,GWL_STYLE);
		SetWindowLong(m_hWnd,GWL_EXSTYLE,0);
		SetWindowLong(m_hWnd,GWL_STYLE,i & ~WS_CAPTION & ~WS_BORDER & ~WS_THICKFRAME);
		SetWindowPos(NULL,0,0,cx,cy,SWP_NOOWNERZORDER);
		pcnt=0;
		double ii=(double)(cx)/(double)rcm.right;
		int cyy=cy/2-(int)(((double)rcm.bottom*ii)/2);
		int cxx=cx;
		RECT rr;
		MFVideoNormalizedRect mvnr={0, 0, 1, 1};
		GetClientRect(&rr);
		Vdc->SetVideoPosition(&mvnr, &rr);
		mousecnt=mousecnt1=0;
		SetTimer(3366,500,NULL);
	}
	
	CFrameWnd::OnNcLButtonDblClk(nHitTest, point);
}

void CDouga::On32775()
{
	// TODO: ここにコマンド ハンドラ コードを追加します。
	static BOOL pp=0;
	if(!(videoonly==TRUE || mode==-2))return;
	pause(pp);
	pp++;if(pp>1) pp=0;
}


void CDouga::OnDropFiles(HDROP hDropInfo)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	::PostMessage(og->m_hWnd,WM_DROPFILES,(WPARAM)hDropInfo,NULL);
//	CFrameWnd::OnDropFiles(hDropInfo);
}


void CDouga::OnNcDestroy()
{
	CFrameWnd::OnNcDestroy();

	// TODO: ここにメッセージ ハンドラ コードを追加します。
	killw=1;
}

void CDouga::OnNcRButtonUp(UINT nHitTest, CPoint point)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	CFrameWnd::OnNcRButtonUp(nHitTest, point);
}

void CDouga::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	CFrameWnd::OnRButtonUp(nFlags, point);
}
