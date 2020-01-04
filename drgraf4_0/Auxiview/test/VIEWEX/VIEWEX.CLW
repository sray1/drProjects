; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMyAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "viewex.h"

ClassCount=9
Class1=CEnterDlg
Class2=CInputView
Class3=CMainDoc
Class4=CTextView
Class5=CColorView
Class6=CSplitterFrame
Class7=C3WaySplitterFrame
Class8=CViewExApp

ResourceCount=6
Resource1=IDD_CHANGEDATA
Resource2=IDR_MAINFRAME (_MAC)
Resource3=IDD_ABOUTBOX
Resource4=IDD_INPUTFORM
Resource5=IDR_MAINFRAME
Class9=CMyAboutDlg
Resource6=IDD_MYABOUT

[CLS:CEnterDlg]
Type=0
HeaderFile=enterdlg.h
ImplementationFile=enterdlg.cpp

[CLS:CInputView]
Type=0
HeaderFile=inputvw.h
ImplementationFile=inputvw.cpp
LastObject=IDD_MYABOUT
Filter=D
BaseClass=CFormView
VirtualFilter=VWC

[CLS:CMainDoc]
Type=0
HeaderFile=maindoc.h
ImplementationFile=maindoc.cpp
LastObject=ID_APP_ABOUT
Filter=N
BaseClass=CDocument
VirtualFilter=DC

[CLS:CTextView]
Type=0
HeaderFile=simpvw.h
ImplementationFile=simpvw.cpp

[CLS:CColorView]
Type=0
HeaderFile=simpvw.h
ImplementationFile=simpvw.cpp
LastObject=CColorView

[CLS:CSplitterFrame]
Type=0
HeaderFile=splitter.h
ImplementationFile=splitter.cpp
LastObject=ID_APP_ABOUT
Filter=M
BaseClass=CMDIChildWnd
VirtualFilter=mfWC

[CLS:C3WaySplitterFrame]
Type=0
HeaderFile=splitter.h
ImplementationFile=splitter.cpp

[CLS:CViewExApp]
Type=0
HeaderFile=viewex.h
ImplementationFile=viewex.cpp
Filter=Not a Window
LastObject=CViewExApp

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_CLOSE
Command3=ID_APP_EXIT
Command4=IDM_CHANGEDATA
Command5=IDD_MYABOUT
Command6=ID_WINDOW_NEW
Command7=ID_WINDOW_CASCADE
Command8=ID_WINDOW_TILE_HORZ
Command9=ID_WINDOW_ARRANGE
Command10=ID_WINDOW_SPLIT
Command11=ID_APP_ABOUT
CommandCount=11

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
CommandCount=1

[DLG:IDD_ABOUTBOX]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_INPUTFORM]
Type=1
Class=?
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT1,edit,1350631552
Control3=IDC_GROUPBOX1,button,1342177287
Control4=IDC_RADIO1,button,1342373897
Control5=IDC_RADIO2,button,1342242825
Control6=IDC_RADIO3,button,1342242825

[DLG:IDD_CHANGEDATA]
Type=1
Class=?
ControlCount=4
Control1=IDC_EDIT1,edit,1350631552
Control2=IDC_STATIC,static,1342308352
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816

[MNU:IDR_MAINFRAME (_MAC)]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_CLOSE
Command3=ID_APP_EXIT
Command4=IDM_CHANGEDATA
Command5=ID_WINDOW_NEW
Command6=ID_WINDOW_CASCADE
Command7=ID_WINDOW_TILE_HORZ
Command8=ID_WINDOW_SPLIT
CommandCount=8

[ACL:IDR_MAINFRAME (_MAC)]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_CLOSE
Command3=ID_APP_EXIT
CommandCount=3

[DLG:IDD_MYABOUT]
Type=1
Class=CMyAboutDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_MYSTATIC,static,1342308352
Control4=IDC_CHECK1,button,1342242819

[CLS:CMyAboutDlg]
Type=0
HeaderFile=MyAboutDlg.h
ImplementationFile=MyAboutDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_CHECK1
VirtualFilter=dWC

