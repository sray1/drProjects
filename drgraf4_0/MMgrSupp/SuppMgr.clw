; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDlg_Uniform
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "suppmgr.h"
LastPage=0

ClassCount=7
Class1=CDlg_SupI
Class2=CMSupMgr

ResourceCount=6
Resource1=IDD_STIFFNESS
Class3=CDlg_NodeSupA
Resource2=IDD_JOINTCOORD
Resource3=IDD_SUP_IN
Class4=CDlg_SupE
Class5=CDlg_Stif
Class6=CDlg_JointCoord
Resource4=IDD_SUP_EDIT
Resource5=IDD_UNIFORM
Class7=CDlg_Uniform
Resource6="IDD_UNIFORM"

[CLS:CDlg_SupI]
Type=0
BaseClass=CDialog
HeaderFile=dlg_Supi.h
ImplementationFile=dlg_Supi.cpp
LastObject=CDlg_SupI
Filter=D
VirtualFilter=dWC

[CLS:CMSupMgr]
Type=0
HeaderFile=MSupMgr.h
ImplementationFile=MSupMgr.cpp

[DLG:IDD_SUP_IN]
Type=1
Class=CDlg_SupI
ControlCount=21
Control1=IDC_UPDATE,button,1342242816
Control2=IDC_STATIC,static,1342308354
Control3=IDC_SUPID,combobox,1344340226
Control4=IDC_TX,button,1342242819
Control5=IDC_TY,button,1342242819
Control6=IDC_TZ,button,1342242819
Control7=IDC_RX,button,1342242819
Control8=IDC_RY,button,1342242819
Control9=IDC_RZ,button,1342242819
Control10=IDD_CANCEL,button,1342242816
Control11=IDC_STIFFNESS,button,1342242816
Control12=IDC_GX,button,1342242819
Control13=IDC_GY,button,1342242819
Control14=IDC_GZ,button,1342242819
Control15=IDC_GRX,button,1342242819
Control16=IDC_GRY,button,1342242819
Control17=IDC_GRZ,button,1342242819
Control18=IDC_STATIC,button,1342177287
Control19=IDC_STATIC,button,1342177287
Control20=IDC_COMBO_JCTYPE,combobox,1344339971
Control21=IDC_STATIC,static,1342308352

[DLG:IDD_SUP_EDIT]
Type=1
Class=CDlg_SupE
ControlCount=37
Control1=IDC_STATIC,static,1342308352
Control2=IDC_TX,button,1342242819
Control3=IDC_TY,button,1342242819
Control4=IDC_TZ,button,1342242819
Control5=IDC_RX,button,1342242819
Control6=IDC_RY,button,1342242819
Control7=IDC_RZ,button,1342242819
Control8=IDC_TX2,button,1342242819
Control9=IDC_TY2,button,1342242819
Control10=IDC_TZ2,button,1342242819
Control11=IDC_RX2,button,1342242819
Control12=IDC_RY2,button,1342242819
Control13=IDC_RZ2,button,1342242819
Control14=IDC_STATIC,button,1342177287
Control15=IDC_NIDHEAD,static,1342308352
Control16=IDC_NID,combobox,1344340226
Control17=IDC_TANGENT,button,1342242819
Control18=IDC_SKEWHEAD,button,1342177287
Control19=IDC_NIDHEADB,static,1342308352
Control20=IDC_NIDB2,combobox,1344340226
Control21=IDC_SUPID,edit,1350631552
Control22=IDC_SUPPROC,edit,1350631552
Control23=IDC_STATIC,static,1342308352
Control24=IDOK,button,1342242827
Control25=IDD_CANCEL,button,1342242827
Control26=IDC_STATIC,button,1342177287
Control27=IDC_FX,edit,1350631552
Control28=IDC_MX,edit,1350631552
Control29=IDC_FY,edit,1350631552
Control30=IDC_MY,edit,1350631552
Control31=IDC_FZ,edit,1350631552
Control32=IDC_MZ,edit,1350631552
Control33=IDC_TRANHEAD,static,1342308353
Control34=IDC_ROTHEAD,static,1342308353
Control35=IDC_STATIC,button,1342177287
Control36=IDC_CN_A,button,1342242851
Control37=IDC_CN_B,button,1342242851

[CLS:CDlg_SupE]
Type=0
HeaderFile=dlg_supe.h
ImplementationFile=dlg_supe.cpp
BaseClass=CDialog
LastObject=CDlg_SupE
Filter=D
VirtualFilter=dWC

[DLG:IDD_STIFFNESS]
Type=1
Class=CDlg_Stif
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

[CLS:CDlg_Stif]
Type=0
HeaderFile=dlg_stif.h
ImplementationFile=dlg_stif.cpp
BaseClass=CDialog
LastObject=CDlg_Stif

[CLS:CDlg_NodeSupA]
Type=0
HeaderFile=dlg_nodesupa.h
ImplementationFile=dlg_nodesupa.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_CN_A

[DLG:IDD_JOINTCOORD]
Type=1
Class=CDlg_JointCoord
ControlCount=6
Control1=IDD_CANCEL,button,1342242827
Control2=IDOK,button,1342242827
Control3=IDC_RADIOFIXEDDIR,button,1342189577
Control4=IDC_RADIOCURVE,button,1342189577
Control5=IDC_RADIOPATCH,button,1342189577
Control6=IDC_DEFAULT,button,1342189577

[CLS:CDlg_JointCoord]
Type=0
HeaderFile=dlg_jointcoord.h
ImplementationFile=dlg_jointcoord.cpp
BaseClass=CDialog
LastObject=IDC_RADIOFIXEDDIR

[DLG:IDD_UNIFORM]
Type=1
Class=CDlg_Uniform
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

[CLS:CDlg_Uniform]
Type=0
HeaderFile=Dlg_Uniform.h
ImplementationFile=Dlg_Uniform.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlg_Uniform

[DLG:"IDD_UNIFORM"]
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

