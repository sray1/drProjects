; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDataVu
LastTemplate=CPropertyPage
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "database.h"
LastPage=0

ClassCount=23
Class1=CCurGeomPage
Class2=CCurIntPage
Class3=CCurSheet
Class4=CDatabaseApp
Class5=CAboutDlg
Class6=CDatabaseDoc
Class7=CDatabaseView
Class8=CDataVu
Class9=CDrListVu
Class10=CDrTreeVu
Class11=CMainFrame
Class12=CSnapView
Class13=CNodGeomPage
Class14=CNodIntPage
Class15=CNodSheet
Class16=C3WaySplitterFrame

ResourceCount=13
Resource1=IDR_DATABATYPE
Resource2=IDD_CURINT
Resource3=IDD_NODE_GEOM
Resource4=IDD_NODE_LOAD
Resource5=IDD_NODE_DISP
Resource6=IDD_ABOUTBOX
Resource7=IDD_NODE_TOPO
Resource8=IDD_NODE_REST
Resource9=IDD_CURGEOM
Resource10=IDD_NODE_DEBUG
Resource11=IDD_NODE_SUPP
Resource12=IDR_MAINFRAME
Class17=NodeInputPage
Class18=NodeDebugPage
Class19=NodeDispPage
Class20=NodeLoadPage
Class21=NodeRestPage
Class22=NodeSuppPage
Class23=NodeGeomPage
Resource13=IDD_NODE_INPUT

[CLS:CCurGeomPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=CurGeomPage.h
ImplementationFile=CurGeomPage.cpp

[CLS:CCurIntPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=CurIntPage.h
ImplementationFile=CurIntPage.cpp

[CLS:CCurSheet]
Type=0
BaseClass=CPropertySheet
HeaderFile=CurSheet.h
ImplementationFile=CurSheet.cpp

[CLS:CDatabaseApp]
Type=0
BaseClass=CWinApp
HeaderFile=database.h
ImplementationFile=database.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=database.cpp
ImplementationFile=database.cpp

[CLS:CDatabaseDoc]
Type=0
BaseClass=CDocument
HeaderFile=databaseDoc.h
ImplementationFile=databaseDoc.cpp

[CLS:CDatabaseView]
Type=0
BaseClass=CView
HeaderFile=databaseView.h
ImplementationFile=databaseView.cpp

[CLS:CDataVu]
Type=0
BaseClass=CView
HeaderFile=DataVu.h
ImplementationFile=DataVu.cpp
Filter=C
VirtualFilter=VWC
LastObject=CDataVu

[CLS:CDrListVu]
Type=0
BaseClass=CListView
HeaderFile=DrListVu.h
ImplementationFile=DrListVu.cpp

[CLS:CDrTreeVu]
Type=0
BaseClass=CTreeView
HeaderFile=DrTreeVu.h
ImplementationFile=DrTreeVu.cpp
LastObject=CDrTreeVu
Filter=C
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CSnapView]
Type=0
BaseClass=CView
HeaderFile=Nodeview.h
ImplementationFile=Nodeview.cpp

[CLS:CNodGeomPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=NodGeomPage.h
ImplementationFile=NodGeomPage.cpp

[CLS:CNodIntPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=NodIntPage.h
ImplementationFile=NodIntPage.cpp

[CLS:CNodSheet]
Type=0
BaseClass=CPropertySheet
HeaderFile=NodSheet.h
ImplementationFile=NodSheet.cpp

[CLS:C3WaySplitterFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=splitter.h
ImplementationFile=Splitter.cpp
LastObject=C3WaySplitterFrame

[DLG:IDD_CURGEOM]
Type=1
Class=CCurGeomPage
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352

[DLG:IDD_CURINT]
Type=1
Class=CCurIntPage
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352

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

[MNU:IDR_DATABATYPE]
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
Command17=ID_WINDOW_NEW
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_ARRANGE
Command21=ID_HELP_FINDER
Command22=ID_APP_ABOUT
CommandCount=22

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

[DLG:IDD_NODE_INPUT]
Type=1
Class=NodeInputPage
ControlCount=19
Control1=IDC_STATIC,static,1342308354
Control2=IDD_NODE_DX,edit,1350633472
Control3=IDC_STATIC,static,1342308354
Control4=IDD_NODE_DY,edit,1350633472
Control5=IDC_STATIC,static,1342308354
Control6=IDD_NODE_DZ,edit,1350633472
Control7=IDC_STATIC,static,1342308354
Control8=IDC_STATIC,static,1342308354
Control9=IDC_STATIC,static,1342308354
Control10=IDC_STATIC,button,1342177287
Control11=IDC_STATIC,static,1342308354
Control12=IDD_LENGTH,edit,1350633472
Control13=IDC_STATIC,button,1342177287
Control14=IDC_FROM_IS_CN,button,1342242819
Control15=IDC_REF_IS_CN,button,1342242819
Control16=IDC_TO_IS_CN,button,1342242819
Control17=IDC_EDIT1,edit,1350633600
Control18=IDC_EDIT2,edit,1350633600
Control19=IDC_EDIT3,edit,1350633600

[DLG:IDD_NODE_GEOM]
Type=1
Class=CNodGeomPage
ControlCount=11
Control1=IDD_NODE_ID,edit,1350633472
Control2=IDC_STATIC,static,1342308354
Control3=IDC_STATIC,static,1342308354
Control4=IDD_NODE_DX,edit,1350633472
Control5=IDC_STATIC,static,1342308354
Control6=IDD_NODE_DY,edit,1350633472
Control7=IDC_STATIC,static,1342308354
Control8=IDD_NODE_DZ,edit,1350633472
Control9=IDC_STATIC,button,1342177287
Control10=IDD_NODE_TYPE,edit,1350633472
Control11=IDC_STATIC,static,1342308354

[DLG:IDD_NODE_DEBUG]
Type=1
Class=NodeDebugPage
ControlCount=0

[DLG:IDD_NODE_TOPO]
Type=1
Class=CNodIntPage
ControlCount=0

[DLG:IDD_NODE_SUPP]
Type=1
Class=NodeSuppPage
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[DLG:IDD_NODE_LOAD]
Type=1
Class=NodeLoadPage
ControlCount=0

[DLG:IDD_NODE_DISP]
Type=1
Class=NodeDispPage
ControlCount=0

[DLG:IDD_NODE_REST]
Type=1
Class=NodeRestPage
ControlCount=0

[CLS:NodeInputPage]
Type=0
HeaderFile=NodeInputPage.h
ImplementationFile=NodeInputPage.cpp
BaseClass=CPropertyPage
Filter=D

[CLS:NodeDebugPage]
Type=0
HeaderFile=NodeDebugPage.h
ImplementationFile=NodeDebugPage.cpp
BaseClass=CPropertyPage
Filter=D

[CLS:NodeDispPage]
Type=0
HeaderFile=NodeDispPage.h
ImplementationFile=NodeDispPage.cpp
BaseClass=CPropertyPage
Filter=D

[CLS:NodeLoadPage]
Type=0
HeaderFile=NodeLoadPage.h
ImplementationFile=NodeLoadPage.cpp
BaseClass=CPropertyPage
Filter=D

[CLS:NodeRestPage]
Type=0
HeaderFile=NodeRestPage.h
ImplementationFile=NodeRestPage.cpp
BaseClass=CPropertyPage
Filter=D

[CLS:NodeSuppPage]
Type=0
HeaderFile=NodeSuppPage.h
ImplementationFile=NodeSuppPage.cpp
BaseClass=CPropertyPage
Filter=D

[CLS:NodeGeomPage]
Type=0
HeaderFile=nodegeompage.h
ImplementationFile=nodegeompage.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=IDD_NODE_DX

