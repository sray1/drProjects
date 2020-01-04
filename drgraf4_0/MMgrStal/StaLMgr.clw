; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDlg_StLI
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "stalmgr.h"
LastPage=0

ClassCount=8
Class1=CDlg_D_RI
Class2=CDlg_StLA
Class3=CDlg_StLI
Class4=CDlg_LWtI
Class5=CDlg_PrsI
Class6=CDlg_ThrI

ResourceCount=9
Resource1=IDD_PRESSURE_IN
Resource2=IDD_LUMPWT_IN
Resource3=IDD_ADVANCE
Resource4=IDD_ISOPAR
Resource5=IDD_THERMAL_IN
Resource6=IDD_MANY_COMPO
Class7=CDlg_IsoP
Resource7=IDD_CURVILINEAR
Class8=CDlg_Many
Resource8=IDD_UNIFORM
Resource9=IDD_STATIC_IN

[CLS:CDlg_D_RI]
Type=0
BaseClass=CDialog
HeaderFile=dlg_D_RI.h
ImplementationFile=dlg_D_Ri.cpp
LastObject=CDlg_D_RI

[CLS:CDlg_StLA]
Type=0
BaseClass=CDialog
HeaderFile=Dlg_StLA.h
ImplementationFile=Dlg_StLA.cpp
LastObject=IDC_NIDB
Filter=D
VirtualFilter=dWC

[CLS:CDlg_StLI]
Type=0
BaseClass=CDialog
HeaderFile=dlg_StLI.h
ImplementationFile=dlg_StLi.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_UPDATE

[CLS:CDlg_LWtI]
Type=0
BaseClass=CDialog
HeaderFile=dlg_lwti.h
ImplementationFile=dlg_lwti.cpp

[CLS:CDlg_PrsI]
Type=0
BaseClass=CDialog
HeaderFile=dlg_PrsI.h
ImplementationFile=dlg_PrsI.cpp

[CLS:CDlg_ThrI]
Type=0
BaseClass=CDialog
HeaderFile=dlg_ThrI.h
ImplementationFile=dlg_ThrI.cpp

[DLG:IDD_LUMPWT_IN]
Type=1
Class=CDlg_LWtI
ControlCount=8
Control1=IDC_UPDATE,button,1342242816
Control2=IDC_STATIC,static,1342308354
Control3=IDC_LOADID,combobox,1344340226
Control4=IDC_FX,edit,1350631552
Control5=IDC_ADVANCED,button,1342242816
Control6=IDC_FY,edit,1350631552
Control7=IDC_FZ,edit,1350631552
Control8=IDC_GRAVMUL,button,1342242819

[DLG:IDD_PRESSURE_IN]
Type=1
Class=CDlg_PrsI
ControlCount=5
Control1=IDC_UPDATE,button,1342242816
Control2=IDC_STATIC,static,1342308354
Control3=IDC_LOADID,combobox,1344340226
Control4=IDC_FX,edit,1350631552
Control5=IDC_ADVANCED,button,1342242816

[DLG:IDD_THERMAL_IN]
Type=1
Class=CDlg_ThrI
ControlCount=5
Control1=IDC_UPDATE,button,1342242816
Control2=IDC_STATIC,static,1342308354
Control3=IDC_LOADID,combobox,1344340226
Control4=IDC_FX,edit,1350631552
Control5=IDC_ADVANCED,button,1342242816

[DLG:IDD_ADVANCE]
Type=1
Class=CDlg_StLA
ControlCount=8
Control1=IDOK,button,1342242827
Control2=IDCANCEL,button,1342242827
Control3=IDC_NIDHEAD,static,1342308354
Control4=IDC_NID,combobox,1344340226
Control5=IDC_TANGENT,button,1342242819
Control6=IDC_SKEWHEAD,button,1342177287
Control7=IDC_NIDHEADB,static,1342308354
Control8=IDC_NIDB,combobox,1344340226

[DLG:IDD_ISOPAR]
Type=1
Class=CDlg_IsoP
ControlCount=4
Control1=IDC_START,edit,1350631552
Control2=IDD_OK,button,1342242816
Control3=IDCANCEL,button,1342242816
Control4=IDC_TRANHEAD,static,1342308352

[CLS:CDlg_IsoP]
Type=0
HeaderFile=Dlg_IsoP.h
ImplementationFile=Dlg_IsoP.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlg_IsoP

[DLG:IDD_STATIC_IN]
Type=1
Class=CDlg_StLI
ControlCount=18
Control1=IDC_ISOPAR_CONC,button,1342177289
Control2=IDC_NONISO,button,1342177289
Control3=IDC_STATIC,button,1342177287
Control4=IDC_UPDATE,button,1342242816
Control5=IDC_STATIC,static,1342308354
Control6=IDC_LOADID,combobox,1344340226
Control7=IDC_TX,button,1342242819
Control8=IDC_TY,button,1342242819
Control9=IDC_TZ,button,1342242819
Control10=IDC_RX,button,1342242819
Control11=IDC_RY,button,1342242819
Control12=IDC_RZ,button,1342242819
Control13=IDD_CANCEL,button,1342242816
Control14=IDC_STATIC,button,1342177287
Control15=IDC_COMBO_JCTYPE,combobox,1344339971
Control16=IDC_STATIC,static,1342308352
Control17=IDC_ISOPAR_DISTRIB,button,1342177289
Control18=IDC_UNIFORM,button,1342246915

[DLG:IDD_CURVILINEAR]
Type=1
ControlCount=15
Control1=IDC_ITEMHEAD,button,1342177287
Control2=IDC_CID,combobox,1344340227
Control3=IDC_CIDHEAD,static,1342308354
Control4=IDC_STEP,edit,1350631552
Control5=IDC_STEPHEAD,static,1342308354
Control6=IDC_INCREMENT,button,1342242819
Control7=IDC_START,edit,1350633600
Control8=IDC_STARTHEAD,static,1342308354
Control9=IDC_LINEARHEAD,button,1342177287
Control10=IDC_ORIENT,combobox,1344340227
Control11=IDC_ORIENTHEAD,static,1342308354
Control12=IDC_SCALE,edit,1350633600
Control13=IDC_SCALEHEAD,static,1342308354
Control14=IDOK,button,1342242827
Control15=IDCANCEL,button,1342242827

[DLG:IDD_MANY_COMPO]
Type=1
Class=CDlg_Many
ControlCount=13
Control1=IDOK,button,1342242827
Control2=IDC_FX,edit,1350631552
Control3=IDC_MX,edit,1350631552
Control4=IDC_FY,edit,1350631552
Control5=IDC_MY,edit,1350631552
Control6=IDC_FZ,edit,1350631552
Control7=IDC_MZ,edit,1350631552
Control8=IDCANCEL,button,1342242827
Control9=IDC_STATIC,static,1342308354
Control10=IDC_STATIC,static,1342308354
Control11=IDC_STATIC,static,1342308354
Control12=IDC_TRANHEAD,static,1342308353
Control13=IDC_ROTHEAD,static,1342308353

[CLS:CDlg_Many]
Type=0
HeaderFile=dlg_many.h
ImplementationFile=dlg_many.cpp
BaseClass=CDialog
LastObject=CDlg_Many

[DLG:IDD_UNIFORM]
Type=1
ControlCount=13
Control1=IDOK,button,1342242827
Control2=IDC_FX,edit,1350631552
Control3=IDC_MX,edit,1350631552
Control4=IDC_FY,edit,1350631552
Control5=IDC_MY,edit,1350631552
Control6=IDC_FZ,edit,1350631552
Control7=IDC_MZ,edit,1350631552
Control8=IDCANCEL,button,1342242827
Control9=IDC_STATIC,static,1342308354
Control10=IDC_STATIC,static,1342308354
Control11=IDC_STATIC,static,1342308354
Control12=IDC_TRANHEAD,static,1342308353
Control13=IDC_ROTHEAD,static,1342308353

