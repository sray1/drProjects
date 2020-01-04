; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDlg_HNet
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "spec_dlg.h"
VbxHeaderFile=spec_dlg.h
VbxImplementationFile=spec_dlg.cpp
LastPage=0

ClassCount=8
Class1=CDrawLayer
Class2=CPenDlg
Class3=CDrawPrecision
Class4=CDrawScale
Class5=CDrawUnit
Class6=CDlgObj3D
Class7=CDlgPatch
Class11=CSpinEditDlg

ResourceCount=9
Resource1=IDD_PRECISION
Resource2=IDD_LAYER
Resource3=IDD_SCALE_FACTOR
Resource4=IDD_OBJ3D
Resource5=IDD_UNIT
Resource6=IDD_INSTANCE
Resource7=IDD_PATCH
Resource8=IDD_HITNET
Class8=CDlg_HNet
Resource9=IDD_PEN

[CLS:CDrawLayer]
Type=0
HeaderFile=dlg_layr.h
ImplementationFile=dlg_layr.cpp

[CLS:CPenDlg]
Type=0
HeaderFile=dlg_pen.h
ImplementationFile=dlg_pen.cpp
Filter=D
LastObject=CPenDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CDrawPrecision]
Type=0
HeaderFile=dlg_prec.h
ImplementationFile=dlg_prec.cpp
LastObject=CDrawPrecision

[CLS:CDrawScale]
Type=0
HeaderFile=dlg_sfac.h
ImplementationFile=dlg_sfac.cpp

[CLS:CDrawUnit]
Type=0
HeaderFile=dlg_unit.h
ImplementationFile=dlg_unit.cpp
LastObject=CDrawUnit

[CLS:CDlgObj3D]
Type=0
HeaderFile=dlgobj3d.h
ImplementationFile=dlgobj3d.cpp

[CLS:CDlgPatch]
Type=0
HeaderFile=dlgpatch.h
ImplementationFile=dlgpatch.cpp
Filter=D
LastObject=IDC_PATCH_ID

[CLS:CSpinEditDlg]
Type=0
HeaderFile=spintest.cpp
ImplementationFile=spintest.cpp

[DLG:IDD_LAYER]
Type=1
Class=CDrawLayer
ControlCount=9
Control1=IDOK,button,1342242827
Control2=IDCANCEL,button,1342242827
Control3=IDC_DRAW_LIST,listbox,1352728833
Control4=IDC_STATIC,button,1342177287
Control5=IDC_DRAW_ALLACTIVE,button,1342177289
Control6=IDC_TOGGLE_ALL,button,1342177289
Control7=IDC_CHANGE,button,1342177289
Control8=IDC_CURRENT,button,1342177289
Control9=IDC_STATIC,static,1342308352

[DLG:IDD_PEN]
Type=1
Class=CPenDlg
ControlCount=9
Control1=IDOK,button,1342242827
Control2=IDCANCEL,button,1342242827
Control3=IDC_LIST_COLOR,listbox,1352728851
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_COMBO_STYLE,combobox,1344339970
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_WIDTH,edit,1350631552
Control9=IDC_SPIN_WIDTH,msctls_updown32,1342177430

[DLG:IDD_PRECISION]
Type=1
Class=CDrawPrecision
ControlCount=4
Control1=IDOK,button,1342242827
Control2=IDCANCEL,button,1342242827
Control3=IDC_STATIC,static,1342308352
Control4=IDC_PRECISION,edit,1350631552

[DLG:IDD_SCALE_FACTOR]
Type=1
Class=CDrawScale
ControlCount=4
Control1=IDOK,button,1342242827
Control2=IDCANCEL,button,1342242827
Control3=IDC_STATIC,static,1342308352
Control4=IDC_SCALE_FACTOR,edit,1350631552

[DLG:IDD_UNIT]
Type=1
Class=CDrawUnit
ControlCount=4
Control1=IDOK,button,1342242827
Control2=IDCANCEL,button,1342242827
Control3=IDC_COMBO_UNITS,combobox,1344339971
Control4=IDC_STATIC,static,1342308352

[DLG:IDD_OBJ3D]
Type=1
Class=CDlgObj3D
ControlCount=9
Control1=IDOK,button,1342242827
Control2=IDCANCEL,button,1342242827
Control3=IDC_DRAW_LIST,listbox,1352728833
Control4=IDC_STATIC,button,1342177287
Control5=IDC_DRAW_ALLACTIVE,button,1342177289
Control6=IDC_TOGGLE_ALL,button,1342177289
Control7=IDC_CHANGE,button,1342177289
Control8=IDC_CURRENT,button,1342177289
Control9=IDC_STATIC,static,1342308352

[DLG:IDD_PATCH]
Type=1
Class=CDlgPatch
ControlCount=9
Control1=IDOK,button,1342242827
Control2=IDCANCEL,button,1342242827
Control3=IDC_DRAW_LIST,listbox,1352728833
Control4=IDC_STATIC,button,1342177287
Control5=IDC_DRAW_ALLACTIVE,button,1342177289
Control6=IDC_TOGGLE_ALL,button,1342177289
Control7=IDC_CHANGE,button,1342177289
Control8=IDC_CURRENT,button,1342177289
Control9=IDC_STATIC,static,1342308352

[DLG:IDD_SPIN_EDIT]
Class=CSpinEditDlg

[DLG:IDD_INSTANCE]
Type=1
ControlCount=14
Control1=IDOK,button,1342242827
Control2=IDCANCEL,button,1342242827
Control3=IDC_IN_PITCH,edit,1350631552
Control4=IDC_IN_ROLL,edit,1350631552
Control5=IDC_IN_YAW,edit,1350631552
Control6=IDC_STATIC,static,1342308354
Control7=IDC_STATIC,static,1342308354
Control8=IDC_STATIC,static,1342308354
Control9=IDC_IN_TRANS,edit,1350631552
Control10=IDC_STATIC,static,1342308354
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_IN_SCALE,edit,1350631552
Control14=IDC_STATIC,static,1342308354

[DLG:IDD_HITNET]
Type=1
Class=CDlg_HNet
ControlCount=21
Control1=IDOK,button,1342242827
Control2=IDCANCEL,button,1342242827
Control3=IDC_STATIC,static,1342308353
Control4=IDC_PIXELNET,edit,1350631552
Control5=IDC_STATIC,static,1342308353
Control6=IDC_PHYSNET,edit,1350631552
Control7=IDC_STATIC,button,1342177287
Control8=IDC_STATIC,button,1342177287
Control9=IDC_DRATIO,edit,1350631552
Control10=IDC_COLINEAR,edit,1350631552
Control11=IDC_COPLANAR,edit,1350631552
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_NODEMERGE_X,edit,1350631552
Control16=IDC_NODEMERGE_Y,edit,1350631552
Control17=IDC_NODEMERGE_Z,edit,1350631552
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,button,1342177287

[CLS:CDlg_HNet]
Type=0
HeaderFile=dlg_hnet.h
ImplementationFile=dlg_hnet.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlg_HNet

