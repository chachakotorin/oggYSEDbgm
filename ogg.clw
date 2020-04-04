; CLW ファイルは MFC ClassWizard の情報を含んでいます。

[General Info]
Version=1
LastClass=COggDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ogg.h"

ClassCount=15
Class1=COggApp
Class2=COggDlg
Class3=CAboutDlg

ResourceCount=15
Resource1=IDD_SENTAKU1
Resource2=IDR_MAINFRAME
Class4=CDouga
Resource3=IDD_SENTAKU2
Resource4=IDD_OGG_DIALOG
Class5=itiran
Resource5=IDD_SENTAKU5
Class6=CFolder
Resource6=IDD_SENTAKU6
Resource7=IDD_Render
Resource8=IDD_SENTAKU3
Class7=Citiran_FC
Class8=Citiran_YSF
Class9=Citiran_YS6
Resource9=IDD_SENTAKU7
Class10=Citiran_YSO
Resource10=IDD_SENTAKU4
Class11=CED63rd
Resource11=IDD_DIALOG1
Class12=CZWEIII
Resource12=IDD_SENTAKU8
Class13=CRender
Resource13=IDD_SENTAKU
Class14=CYsC1
Resource14=IDD_ABOUTBOX
Class15=CYsC2
Resource15=CG_IDR_POPUP_DOUGA

[CLS:COggApp]
Type=0
HeaderFile=ogg.h
ImplementationFile=ogg.cpp
Filter=N

[CLS:COggDlg]
Type=0
HeaderFile=oggDlg.h
ImplementationFile=oggDlg.cpp
Filter=W
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_CHECK14

[CLS:CAboutDlg]
Type=0
HeaderFile=oggDlg.h
ImplementationFile=oggDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_OGG_DIALOG]
Type=1
Class=COggDlg
ControlCount=46
Control1=IDC_BUTTON8,button,1342242816
Control2=IDC_BUTTON7,button,1342242816
Control3=IDC_BUTTON15,button,1342242816
Control4=IDC_BUTTON6,button,1342242816
Control5=IDC_BUTTON2,button,1342242816
Control6=IDC_BUTTON17,button,1342242816
Control7=IDC_BUTTON4,button,1342242816
Control8=IDC_BUTTON3,button,1342242816
Control9=IDC_BUTTON1,button,1342242816
Control10=IDC_CHECK1,button,1342246915
Control11=IDC_CHECK4,button,1342246915
Control12=IDC_BUTTON5,button,1342242816
Control13=IDC_SLIDER2,msctls_trackbar32,1342242864
Control14=IDC_BUTTON9,button,1342242816
Control15=IDOK,button,1342242817
Control16=IDC_SLIDER1,msctls_trackbar32,1342242840
Control17=IDC_BUTTON12,button,1342242816
Control18=IDC_CHECK5,button,1342242819
Control19=IDC_CHECK6,button,1342242819
Control20=IDC_CHECK7,button,1342242819
Control21=IDC_CHECK8,button,1342242819
Control22=IDC_CHECK9,button,1342242819
Control23=IDC_CHECK10,button,1342242819
Control24=IDC_CHECK11,button,1342242819
Control25=IDC_CHECK12,button,1342242819
Control26=IDC_STATIC,static,1342308352
Control27=IDC_EDIT1,edit,1350631552
Control28=IDC_BUTTON13,button,1073807360
Control29=IDC_CHECK2,button,1342242819
Control30=IDC_STATIC11,static,1073872896
Control31=IDC_CHECK3,button,1073807363
Control32=IDC_STATIC,static,1342308352
Control33=IDC_STATIC2,static,1342308352
Control34=IDC_STATIC,button,1342177287
Control35=IDC_STATIC,button,1342177287
Control36=IDC_BUTTON14,button,1342242816
Control37=IDC_BUTTON19,button,1342242816
Control38=IDC_CHECK13,button,1342242819
Control39=IDC_STATIC,static,1342308352
Control40=IDC_SLIDER3,msctls_trackbar32,1342242840
Control41=IDC_STATICds,static,1342308352
Control42=IDC_BUTTON21,button,1342242816
Control43=IDC_BUTTON23,button,1342242816
Control44=IDC_BUTTON24,button,1342242816
Control45=IDC_CHECK14,button,1342242819
Control46=IDC_CHECK15,button,1342242819

[CLS:CDouga]
Type=0
HeaderFile=Douga.h
ImplementationFile=Douga.cpp
BaseClass=CFrameWnd
Filter=W
VirtualFilter=fWC
LastObject=CDouga

[MNU:CG_IDR_POPUP_DOUGA]
Type=1
Class=?
Command1=ID_MENUITEM32771
Command2=ID_MENUITEM32773
Command3=ID_MENUITEM32772
CommandCount=3

[DLG:IDD_SENTAKU]
Type=1
Class=itiran
ControlCount=2
Control1=IDOK,button,1342242816
Control2=IDC_LIST1,listbox,1352728961

[CLS:itiran]
Type=0
HeaderFile=itiran.h
ImplementationFile=itiran.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_LIST1
VirtualFilter=dWC

[DLG:IDD_DIALOG1]
Type=1
Class=CFolder
ControlCount=27
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1073807360
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350633600
Control5=IDC_BUTTON1,button,1342242816
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT2,edit,1350633600
Control9=IDC_BUTTON5,button,1342242816
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EDIT3,edit,1350633600
Control12=IDC_BUTTON10,button,1342242816
Control13=IDC_STATIC,static,1342308352
Control14=IDC_EDIT4,edit,1350633600
Control15=IDC_BUTTON11,button,1342242816
Control16=IDC_STATIC,static,1342308352
Control17=IDC_EDIT5,edit,1350633600
Control18=IDC_BUTTON16,button,1342242816
Control19=IDC_STATIC,static,1342308352
Control20=IDC_EDIT6,edit,1350633600
Control21=IDC_BUTTON18,button,1342242816
Control22=IDC_STATIC,static,1342308352
Control23=IDC_EDIT7,edit,1350633600
Control24=IDC_BUTTON20,button,1342242816
Control25=IDC_STATIC,static,1342308352
Control26=IDC_EDIT8,edit,1350633600
Control27=IDC_BUTTON22,button,1342242816

[CLS:CFolder]
Type=0
HeaderFile=Folder.h
ImplementationFile=Folder.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_BUTTON22
VirtualFilter=dWC

[DLG:IDD_SENTAKU1]
Type=1
Class=Citiran_FC
ControlCount=2
Control1=IDOK,button,1342242816
Control2=IDC_LIST1,listbox,1352728961

[DLG:IDD_SENTAKU2]
Type=1
Class=Citiran_YSF
ControlCount=2
Control1=IDOK,button,1342242816
Control2=IDC_LIST1,listbox,1352728961

[DLG:IDD_SENTAKU3]
Type=1
Class=Citiran_YS6
ControlCount=2
Control1=IDOK,button,1342242816
Control2=IDC_LIST1,listbox,1352728961

[CLS:Citiran_FC]
Type=0
HeaderFile=itiran_FC.h
ImplementationFile=itiran_FC.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_LIST1
VirtualFilter=dWC

[CLS:Citiran_YSF]
Type=0
HeaderFile=itiran_YSF.h
ImplementationFile=itiran_YSF.cpp
BaseClass=CDialog
Filter=D
LastObject=Citiran_YSF

[CLS:Citiran_YS6]
Type=0
HeaderFile=itiran_YS6.h
ImplementationFile=itiran_YS6.cpp
BaseClass=CDialog
Filter=D
LastObject=Citiran_YS6

[DLG:IDD_SENTAKU4]
Type=1
Class=Citiran_YSO
ControlCount=2
Control1=IDOK,button,1342242816
Control2=IDC_LIST1,listbox,1353777537

[CLS:Citiran_YSO]
Type=0
HeaderFile=itiran_YSO.h
ImplementationFile=itiran_YSO.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_LIST1

[DLG:IDD_SENTAKU5]
Type=1
Class=CED63rd
ControlCount=2
Control1=IDOK,button,1342242816
Control2=IDC_LIST1,listbox,1352728961

[CLS:CED63rd]
Type=0
HeaderFile=ED63rd.h
ImplementationFile=ED63rd.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_LIST1

[DLG:IDD_SENTAKU6]
Type=1
Class=CZWEIII
ControlCount=2
Control1=IDOK,button,1342242816
Control2=IDC_LIST1,listbox,1352728961

[CLS:CZWEIII]
Type=0
HeaderFile=ZWEIII.h
ImplementationFile=ZWEIII.cpp
BaseClass=CDialog
Filter=D
LastObject=CZWEIII

[DLG:IDD_Render]
Type=1
Class=CRender
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_COMBO1,combobox,1344339971
Control4=IDC_STATIC,static,1342308352

[CLS:CRender]
Type=0
HeaderFile=Render.h
ImplementationFile=Render.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CRender

[DLG:IDD_SENTAKU7]
Type=1
Class=CYsC1
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_LIST1,listbox,1352728961

[CLS:CYsC1]
Type=0
HeaderFile=YsC1.h
ImplementationFile=YsC1.cpp
BaseClass=CDialog
Filter=D
LastObject=CYsC1

[DLG:IDD_SENTAKU8]
Type=1
Class=CYsC2
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_LIST1,listbox,1352728961

[CLS:CYsC2]
Type=0
HeaderFile=YsC2.h
ImplementationFile=YsC2.cpp
BaseClass=CDialog
Filter=D
LastObject=CYsC2

