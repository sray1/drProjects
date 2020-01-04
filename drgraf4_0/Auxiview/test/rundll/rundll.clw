; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "rundll.h"
LastPage=0

ClassCount=15
Class1=CChildFrame
Class2=CDrawVw
Class3=CDrGrafApp
Class4=CHistVw
Class5=CInputView
Class6=CMainFrame
Class7=CMyButton
Class8=CMySlider
Class9=CODDialog
Class10=CRundllApp
Class11=CAboutDlg
Class12=CRundllDoc
Class13=CRundllView
Class14=CSpecVw
Class15=CSplitterFrame

ResourceCount=7
Resource1=IDR_RUNDLLTYPE
Resource2=IDR_MAINFRAME
Resource3=IDD_INPUTFORM
Resource4=IDD_CHANGEDATA
Resource5=IDD_ABOUTBOX
Resource6=IDD_INPUTFORM1
Resource7=IDD_ODDIALOG

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp

[CLS:CDrawVw]
Type=0
BaseClass=CView
HeaderFile=DrawVw.h
ImplementationFile=DrawVw.cpp

[CLS:CDrGrafApp]
Type=0
BaseClass=CWinApp
HeaderFile=Drgraf.h
ImplementationFile=Drgraf.cpp

[CLS:CHistVw]
Type=0
BaseClass=CDrawVw
HeaderFile=HistVw.h
ImplementationFile=HistVw.cpp
Filter=C
VirtualFilter=VWC
LastObject=CHistVw

[CLS:CInputView]
Type=0
BaseClass=CFormView
HeaderFile=inputvw.h
ImplementationFile=Inputvw.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
LastObject=CMainFrame

[CLS:CMyButton]
Type=0
BaseClass=CButton
HeaderFile=MyButton.h
ImplementationFile=MyButton.cpp
LastObject=CMyButton
Filter=W
VirtualFilter=BWC

[CLS:CMySlider]
Type=0
BaseClass=CSliderCtrl
HeaderFile=MySlider.h
ImplementationFile=MySlider.cpp

[CLS:CODDialog]
Type=0
BaseClass=CDialog
HeaderFile=ODDialog.h
ImplementationFile=ODDialog.cpp

[CLS:CRundllApp]
Type=0
BaseClass=CWinApp
HeaderFile=rundll.h
ImplementationFile=rundll.cpp
Filter=N
VirtualFilter=AC
LastObject=CRundllApp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=rundll.cpp
ImplementationFile=rundll.cpp
LastObject=CAboutDlg

[CLS:CRundllDoc]
Type=0
BaseClass=CDocument
HeaderFile=rundllDoc.h
ImplementationFile=rundllDoc.cpp

[CLS:CRundllView]
Type=0
BaseClass=CView
HeaderFile=rundllView.h
ImplementationFile=rundllView.cpp

[CLS:CSpecVw]
Type=0
BaseClass=CDrawVw
HeaderFile=SpecVw.h
ImplementationFile=SpecVw.cpp

[CLS:CSplitterFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=splitter.h
ImplementationFile=Splitter.cpp

[DLG:IDD_INPUTFORM]
Type=1
Class=CInputView
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT1,edit,1350631552
Control3=IDC_GROUPBOX1,button,1342177287
Control4=IDC_RADIO1,button,1342373897
Control5=IDC_RADIO2,button,1342242825
Control6=IDC_RADIO3,button,1342242825

[DLG:IDD_ODDIALOG]
Type=1
Class=CODDialog
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_ODBUTTON,button,1342242827

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
Command9=ID_CONTEXT_HELP
CommandCount=9

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_HELP_FINDER
Command9=ID_APP_ABOUT
CommandCount=9

[MNU:IDR_RUNDLLTYPE]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_VIEW_NEWDIALOG
Command18=ID_WINDOW_NEW
Command19=ID_WINDOW_CASCADE
Command20=ID_WINDOW_TILE_HORZ
Command21=ID_WINDOW_ARRANGE
Command22=ID_HELP_FINDER
Command23=ID_APP_ABOUT
CommandCount=23

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
Command15=ID_CONTEXT_HELP
Command16=ID_HELP
CommandCount=16

[DLG:IDD_CHANGEDATA]
Type=1
Class=?
ControlCount=4
Control1=IDC_EDIT1,edit,1350631552
Control2=IDC_STATIC,static,1342308352
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816

[DLG:IDD_INPUTFORM1]
Type=1
Class=?
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT1,edit,1350631552
Control3=IDC_GROUPBOX1,button,1342177287
Control4=IDC_RADIO1,button,1342373897
Control5=IDC_RADIO2,button,1342242825
Control6=IDC_RADIO3,button,1342242825

