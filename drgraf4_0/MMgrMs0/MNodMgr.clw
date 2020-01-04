; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDlg_NodI
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "mnodmgr.h"
LastPage=0

ClassCount=8
Class1=CDlg_ENoA
Class2=CDlg_ENod
Class3=CDlg_Node
Class4=CDlg_NodI
Class5=CMNodMgr

ResourceCount=11
Resource1=IDD_NODE_EDIT_ADV
Resource2=IDD_ELP_NODE
Resource3=IDD_NODE_EDIT_SIMPLE
Resource4=IDD_XFORM_ALL
Resource5="IDD_N_SPAWN"
Resource6=IDD_LSYM_TYPE
Resource7=IDD_N_SPAWN
Resource8=IDD_XFORM_SYM3
Resource9=IDD_CRO_IN
Resource10=IDD_XFORM_SYMM
Class6=CDlg_CrOI
Class7=CDlg_LALL
Class8=CDlg_SpnN
Resource11=IDD_NOD_IN

[CLS:CDlg_ENoA]
Type=0
BaseClass=CDialog
HeaderFile=dlg_enoA.h
ImplementationFile=dlg_enoA.cpp
LastObject=CDlg_ENoA

[CLS:CDlg_ENod]
Type=0
BaseClass=CDialog
HeaderFile=dlg_enod.h
ImplementationFile=dlg_ENod.cpp
Filter=D
VirtualFilter=dWC
LastObject=CDlg_ENod

[CLS:CDlg_Node]
Type=0
BaseClass=CDialog
HeaderFile=Dlg_node.h
ImplementationFile=Dlg_node.cpp

[CLS:CDlg_NodI]
Type=0
BaseClass=CDialog
HeaderFile=dlg_nodi.h
ImplementationFile=dlg_nodi.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_MULTIPLE

[CLS:CMNodMgr]
Type=0
HeaderFile=MNodmgr.h
ImplementationFile=MNodMgr.cpp

[DLG:IDD_NODE_EDIT_ADV]
Type=1
Class=CDlg_ENoA
ControlCount=34
Control1=IDD_NODE_ID,edit,1350631424
Control2=IDC_STATIC,static,1342308354
Control3=IDD_NODE_DX,edit,1350631424
Control4=IDC_STATIC,static,1342308354
Control5=IDD_NODE_DY,edit,1350631424
Control6=IDC_STATIC,static,1342308354
Control7=IDD_NODE_DZ,edit,1350631424
Control8=IDC_STATIC,static,1342308354
Control9=IDOK,button,1342242827
Control10=IDCANCEL,button,1342242827
Control11=IDD_LIST,listbox,1352728579
Control12=IDC_STATIC,static,1342308354
Control13=IDC_STATIC,static,1342177283
Control14=IDC_STATIC,static,1342308352
Control15=IDC_COORD,button,1342177289
Control16=IDC_DIRECTION,button,1342177289
Control17=IDC_STATIC,button,1342177287
Control18=IDC_STATIC,button,1342177287
Control19=IDC_CNODE_FROM,combobox,1344340227
Control20=IDC_STATIC,static,1342308354
Control21=IDC_CNODE_TO,combobox,1344340227
Control22=IDC_STATIC,static,1342308354
Control23=IDC_STATIC,button,1342177287
Control24=IDC_STATIC,static,1342308354
Control25=IDD_LENGTH,edit,1350631424
Control26=IDD_NODE_NID_R,combobox,1344340227
Control27=IDC_STATIC,button,1342177287
Control28=IDC_STATIC,static,1342308354
Control29=IDD_NODE_X2,edit,1350633472
Control30=IDC_STATIC,static,1342308354
Control31=IDD_NODE_Y2,edit,1350633472
Control32=IDC_STATIC,static,1342308354
Control33=IDD_NODE_Z2,edit,1350633472
Control34=IDC_STARTOVER,button,1342242816

[DLG:IDD_NODE_EDIT_SIMPLE]
Type=1
Class=CDlg_ENod
ControlCount=12
Control1=IDC_STATIC,static,1342308354
Control2=IDC_COORD_X,edit,1350631552
Control3=IDC_ADVANCED,button,1342242816
Control4=IDC_COORD_Y,edit,1350631552
Control5=IDC_COORD_Z,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDCANCEL,button,1342242827
Control10=IDOK,button,1342242827
Control11=IDC_NID,edit,1350631552
Control12=IDC_STARTOVER2,button,1342242816

[DLG:IDD_ELP_NODE]
Type=1
Class=CDlg_Node
ControlCount=36
Control1=IDD_NODE_ID,edit,1350631424
Control2=IDC_STATIC,static,1342308354
Control3=IDD_NODE_DX,edit,1350631424
Control4=IDC_STATIC,static,1342308354
Control5=IDD_NODE_DY,edit,1350631424
Control6=IDC_STATIC,static,1342308354
Control7=IDD_NODE_DZ,edit,1350631424
Control8=IDC_STATIC,static,1342308354
Control9=IDOK,button,1342242827
Control10=IDCANCEL,button,1342242827
Control11=IDD_ADD,button,1342242817
Control12=IDD_DEL,button,1342242817
Control13=IDD_EDIT,button,1342242817
Control14=IDD_LIST,listbox,1352728579
Control15=IDC_STATIC,static,1342308354
Control16=IDC_STATIC,static,1342177283
Control17=IDC_STATIC,static,1342308352
Control18=IDC_COORD,button,1342177289
Control19=IDC_DIRECTION,button,1342177289
Control20=IDC_STATIC,button,1342177287
Control21=IDC_STATIC,button,1342177287
Control22=IDC_CNODE_FROM,combobox,1344340227
Control23=IDC_STATIC,static,1342308354
Control24=IDC_CNODE_TO,combobox,1344340227
Control25=IDC_STATIC,static,1342308354
Control26=IDC_STATIC,button,1342177287
Control27=IDC_STATIC,static,1342308354
Control28=IDD_LENGTH,edit,1350631424
Control29=IDD_NODE_NID_R,combobox,1344340227
Control30=IDC_STATIC,button,1342177287
Control31=IDC_STATIC,static,1342308354
Control32=IDD_NODE_X2,edit,1350633472
Control33=IDC_STATIC,static,1342308354
Control34=IDD_NODE_Y2,edit,1350633472
Control35=IDC_STATIC,static,1342308354
Control36=IDD_NODE_Z2,edit,1350633472

[DLG:IDD_NOD_IN]
Type=1
Class=CDlg_NodI
ControlCount=20
Control1=IDC_UPDATE,button,1342242816
Control2=IDD_CANCEL,button,1342242816
Control3=IDC_ADVANCED,button,1342242851
Control4=IDC_TRANHEAD,static,1342308352
Control5=IDC_ROT_X,edit,1350631424
Control6=IDC_ROT_Z,edit,1350631424
Control7=IDC_ROT_Y,edit,1350631424
Control8=IDC_OJECTHEAD,static,1342308354
Control9=IDC_XHEAD,static,1342308353
Control10=IDC_YHEAD,static,1342308353
Control11=IDC_OTHER,static,1342308353
Control12=IDC_OBJID,edit,1350631552
Control13=IDC_TRANPT,edit,1350633600
Control14=IDC_COORDHEAD,static,1342308352
Control15=IDC_DIRECT,button,1342251011
Control16=IDC_DOMINANT,button,1342242819
Control17=IDC_INCREMENT,button,1342177289
Control18=IDC_DIRECTION,button,1342177289
Control19=IDC_STATIC,button,1342177287
Control20=IDC_MULTIPLE,button,1342177289

[DLG:"IDD_N_SPAWN"]
Type=1
ControlCount=11
Control1=IDOK,button,1342242827
Control2=IDCANCEL,button,1342242827
Control3=IDC_STATIC,static,1342308354
Control4=IDC_STATIC,static,1342308354
Control5=IDC_SPNID,edit,1350631552
Control6=IDC_STATIC,static,1342177283
Control7=IDD_LIST,listbox,1352728834
Control8=IDC_XFORM,button,1342177289
Control9=IDC_SYMM,button,1342177289
Control10=IDC_STATIC,button,1342177287
Control11=IDC_CID,edit,1350633600

[DLG:IDD_LSYM_TYPE]
Type=1
ControlCount=6
Control1=IDOK,button,1342242827
Control2=IDCANCEL,button,1342242827
Control3=IDC_TYPE_1,button,1342185481
Control4=IDC_TYPE_2,button,1342185481
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,static,1342177283

[DLG:IDD_XFORM_ALL]
Type=1
Class=CDlg_LALL
ControlCount=39
Control1=IDOK,button,1342242827
Control2=IDCANCEL,button,1342242827
Control3=IDC_STATIC,static,1342308354
Control4=IDC_TRAN_X,edit,1350631424
Control5=IDC_TRAN_Z,edit,1350631424
Control6=IDC_TRAN_Y,edit,1350631424
Control7=IDC_STATIC,static,1342308354
Control8=IDC_STATIC,static,1342177283
Control9=IDC_CNODE_FROM_R,combobox,1344340227
Control10=IDC_STATIC,static,1342308354
Control11=IDC_CNODE_TO_R,combobox,1344340227
Control12=IDC_STATIC,static,1342308354
Control13=IDC_ROT_X,edit,1350631424
Control14=IDC_ROT_Z,edit,1350631424
Control15=IDC_ROT_Y,edit,1350631424
Control16=IDC_STATIC,static,1342308354
Control17=IDC_ROTPT,combobox,1344340227
Control18=IDC_TRANPT,combobox,1344340227
Control19=IDC_SCALE_X,edit,1350631424
Control20=IDC_SCALE_Z,edit,1350631424
Control21=IDC_SCALE_Y,edit,1350631424
Control22=IDC_STATIC,static,1342308353
Control23=IDC_STATIC,static,1342308353
Control24=IDC_STATIC,static,1342308353
Control25=IDC_SHEAR_X2,edit,1350631424
Control26=IDC_SHEAR_Z2,edit,1350631424
Control27=IDC_SHEAR_Y2,edit,1350631424
Control28=IDC_ANGLE_INPUT,button,1342251011
Control29=IDC_COORD_INPUT,button,1342251011
Control30=IDC_STATIC,static,1342308352
Control31=IDC_STATIC,static,1342308352
Control32=IDC_STATIC,static,1342308352
Control33=IDC_DIRCOS,button,1342242819
Control34=IDC_CNODE_FROM_T,combobox,1344340227
Control35=IDC_STATIC,static,1342308354
Control36=IDC_CNODE_TO_T,combobox,1344340227
Control37=IDC_STATIC,static,1342308354
Control38=IDC_STATIC,static,1342308352
Control39=IDC_STATIC,static,1342308352

[DLG:IDD_XFORM_SYM3]
Type=1
ControlCount=10
Control1=IDD_ADD,button,1342242817
Control2=IDD_DEL,button,1342242817
Control3=IDD_SELECTLIST,listbox,1352728577
Control4=IDD_POOLLIST,listbox,1352728579
Control5=65535,static,1342308353
Control6=65535,static,1342308353
Control7=65535,static,1342177283
Control8=65535,button,1342177287
Control9=IDOK,button,1342242827
Control10=IDCANCEL,button,1342242827

[DLG:IDD_XFORM_SYMM]
Type=1
ControlCount=22
Control1=IDOK,button,1342242827
Control2=IDCANCEL,button,1342242827
Control3=IDC_STATIC,static,1342177283
Control4=IDC_CNODE_FROM,combobox,1344340227
Control5=IDC_STATIC,static,1342308354
Control6=IDC_CNODE_TO,combobox,1344340227
Control7=IDC_STATIC,static,1342308354
Control8=IDC_STATIC,static,1342308354
Control9=IDC_ROTPT,combobox,1344340227
Control10=IDC_COORD_INPUT,button,1342251011
Control11=IDC_ROT_X,edit,1350631424
Control12=IDC_ROT_Z,edit,1350631424
Control13=IDC_ROT_Y,edit,1350631424
Control14=IDC_STATIC,static,1342308352
Control15=IDC_TRAN_X,edit,1350631424
Control16=IDC_TRAN_Z,edit,1350631424
Control17=IDC_TRAN_Y,edit,1350631424
Control18=IDC_STATIC,static,1342308352
Control19=IDC_ANGLE_INPUT,button,1342251011
Control20=IDC_STATIC,static,1342308353
Control21=IDC_STATIC,static,1342308353
Control22=IDC_STATIC,static,1342308353

[DLG:IDD_N_SPAWN]
Type=1
Class=CDlg_SpnN
ControlCount=11
Control1=IDOK,button,1342242827
Control2=IDCANCEL,button,1342242827
Control3=IDC_STATIC,static,1342308354
Control4=IDC_STATIC,static,1342308354
Control5=IDC_SPNID,edit,1350631552
Control6=IDC_STATIC,static,1342177283
Control7=IDD_LIST,listbox,1352728834
Control8=IDC_XFORM,button,1342177289
Control9=IDC_SYMM,button,1342177289
Control10=IDC_STATIC,button,1342177287
Control11=IDC_CID,edit,1350633600

[DLG:IDD_CRO_IN]
Type=1
Class=CDlg_CrOI
ControlCount=17
Control1=IDC_UPDATE,button,1342242816
Control2=IDD_CANCEL,button,1342242816
Control3=IDC_TRANHEAD,static,1342308354
Control4=IDC_ROT_X,edit,1350631424
Control5=IDC_ROT_Z,edit,1350631424
Control6=IDC_ROT_Y,edit,1350631424
Control7=IDC_OJECTHEAD,static,1342308354
Control8=IDC_XHEAD,static,1342308353
Control9=IDC_YHEAD,static,1342308353
Control10=IDC_OTHER,static,1342308353
Control11=IDC_COORD_INPUT,button,1342251011
Control12=IDC_OBJID,edit,1350631552
Control13=IDC_TRANPT,edit,1350633600
Control14=IDC_DOMINANT,button,1342242819
Control15=IDC_COORDHEAD,static,1342308352
Control16=IDC_ANGLE_INPUT,button,1342242819
Control17=IDC_DIRCOS,button,1342242819

[CLS:CDlg_CrOI]
Type=0
HeaderFile=dlg_croi.h
ImplementationFile=dlg_croi.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_DOMINANT

[CLS:CDlg_LALL]
Type=0
HeaderFile=dlg_lall.h
ImplementationFile=dlg_lall.cpp
BaseClass=CDialog
LastObject=IDC_CID
Filter=D
VirtualFilter=dWC

[CLS:CDlg_SpnN]
Type=0
HeaderFile=dlg_spnn.h
ImplementationFile=dlg_spnn.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlg_SpnN
