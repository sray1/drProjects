# Microsoft Developer Studio Project File - Name="Shell" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) QuickWin Application" 0x0107

CFG=Shell - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Shell.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Shell.mak" CFG="Shell - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Shell - Win32 Release" (based on "Win32 (x86) QuickWin Application")
!MESSAGE "Shell - Win32 Debug" (based on "Win32 (x86) QuickWin Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
F90=df.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Shell - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE F90 /compile_only /libs:qwin /nologo /warn:nofileopt
# ADD F90 /compile_only /libs:qwin /nologo /warn:nofileopt
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"WinMainCRTStartup" /subsystem:windows /machine:I386 /nodefaultlib:"dfconsol.lib"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"WinMainCRTStartup" /subsystem:windows /machine:I386 /nodefaultlib:"dfconsol.lib"

!ELSEIF  "$(CFG)" == "Shell - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE F90 /check:bounds /compile_only /debug:full /libs:qwin /nologo /traceback /warn:argument_checking /warn:nofileopt
# ADD F90 /check:bounds /compile_only /debug:full /libs:qwin /nologo /traceback /warn:argument_checking /warn:nofileopt
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"WinMainCRTStartup" /subsystem:windows /debug /machine:I386 /nodefaultlib:"dfconsol.lib" /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"WinMainCRTStartup" /subsystem:windows /incremental:no /debug /machine:I386 /nodefaultlib:"dfconsol.lib" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Shell - Win32 Release"
# Name "Shell - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;f90;for;f;fpp"
# Begin Source File

SOURCE=.\BernStein.for
# End Source File
# Begin Source File

SOURCE=.\BernStein_IstDerivative.for
# End Source File
# Begin Source File

SOURCE=.\Bez_QQ_EL_1_Str.f
# End Source File
# Begin Source File

SOURCE=.\Bez_QQ_EL_1Pal.f
# End Source File
# Begin Source File

SOURCE=.\Calc_A1_Hat.for
# End Source File
# Begin Source File

SOURCE=.\Calc_A2_Hat.for
# End Source File
# Begin Source File

SOURCE=.\Calc_Angles.for
# End Source File
# Begin Source File

SOURCE=.\Calc_ArcLength_Step1.for
# End Source File
# Begin Source File

SOURCE=.\Calc_ArcLength_Stepm.for
# End Source File
# Begin Source File

SOURCE=.\Calc_deltaUi1.for
# End Source File
# Begin Source File

SOURCE=.\Calc_deltaUi2.for
# End Source File
# Begin Source File

SOURCE=.\Calc_delUi.for
# End Source File
# Begin Source File

SOURCE=.\Calc_Lamda1_Stepm.for
# End Source File
# Begin Source File

SOURCE=.\Calc_ReferenceProps.for
DEP_F90_CALC_=\
	".\CurParams.h"\
	".\files.h"\
	".\scratch.h"\
	".\SizeVar.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Calc_X11_Hat.for
# End Source File
# Begin Source File

SOURCE=.\Calc_X12_Hat.for
# End Source File
# Begin Source File

SOURCE=.\Calc_X22_Hat.for
# End Source File
# Begin Source File

SOURCE=.\CalcCoords_at_a_Pt.for
# End Source File
# Begin Source File

SOURCE=.\CalcDis_at_a_Pt.for
# End Source File
# Begin Source File

SOURCE=.\CalcRot_at_a_Pt.for
# End Source File
# Begin Source File

SOURCE=.\Check_PossibleDisplacement.for
# End Source File
# Begin Source File

SOURCE=.\Compute_StrainEnergy.f
# End Source File
# Begin Source File

SOURCE=.\Compute_uwthetaAtEnd.f
DEP_F90_COMPU=\
	".\Implicit.h"\
	".\SizeVar.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Convergence_Residual.for
# End Source File
# Begin Source File

SOURCE=.\Define_ElementTypes.for
DEP_F90_DEFIN=\
	".\ElementType.h"\
	
# End Source File
# Begin Source File

SOURCE=.\DeformOut_MatLab.for
DEP_F90_DEFOR=\
	".\Examples.h"\
	".\files.h"\
	".\geometry.h"\
	".\LoadStepIter.h"\
	".\material.h"\
	".\Output.h"\
	".\SizeVar.h"\
	".\solve.h"\
	".\Wpointers.h"\
	
# End Source File
# Begin Source File

SOURCE=.\DeformOut_MatLab_Pal.for
DEP_F90_DEFORM=\
	".\geometry.h"\
	".\LoadStepIter.h"\
	".\Output.h"\
	".\SizeVar.h"\
	
# End Source File
# Begin Source File

SOURCE=.\DeformOut_MatLab_Str.for
DEP_F90_DEFORMO=\
	".\geometry.h"\
	".\LoadStepIter.h"\
	".\Output.h"\
	".\SizeVar.h"\
	
# End Source File
# Begin Source File

SOURCE=.\DegreeElevate2D.for
# End Source File
# Begin Source File

SOURCE=.\DifferenceOp_1.for
# End Source File
# Begin Source File

SOURCE=.\DifferenceOp_2.for
# End Source File
# Begin Source File

SOURCE=.\DumpIntegerArray.for
# End Source File
# Begin Source File

SOURCE=.\DumpIntegerVar.for
# End Source File
# Begin Source File

SOURCE=.\DumpRealArray.for
# End Source File
# Begin Source File

SOURCE=.\DumpRealMatrix.for
# End Source File
# Begin Source File

SOURCE=.\DumpRealMatrix3.for
# End Source File
# Begin Source File

SOURCE=.\DumpRealVar.for
# End Source File
# Begin Source File

SOURCE=.\DumpStringVar.for
# End Source File
# Begin Source File

SOURCE=.\DumpVar.for
# End Source File
# Begin Source File

SOURCE=.\Expand_BZCons_C0.for
# End Source File
# Begin Source File

SOURCE=.\ExtractEL_DispCon.for
DEP_F90_EXTRA=\
	".\Drill.h"\
	".\Implicit.h"\
	".\LoadStepIter.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Form_a_N_kc_N_AMat.f
DEP_F90_FORM_=\
	".\BeamParams.h"\
	".\LoadStepIter.h"\
	".\ThetaConstants.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Form_B_and_Tmatrices.f
DEP_F90_FORM_B=\
	".\CurParams.h"\
	".\files.h"\
	".\scratch.h"\
	".\SizeVar.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Form_Constitutive_Condensed.for
DEP_F90_FORM_C=\
	".\Examples.h"\
	".\geometry.h"\
	".\material.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Form_Constitutive_Expanded.for
DEP_F90_FORM_CO=\
	".\LogParams.h"\
	".\material.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Form_EBlocks.f
DEP_F90_FORM_E=\
	".\BeamParams.h"\
	".\ThetaConstants.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Form_EMatrix_1.f
DEP_F90_FORM_EM=\
	".\BeamParams.h"\
	".\CurParams.h"\
	".\LoadStepIter.h"\
	".\material.h"\
	".\ShellParams.h"\
	".\ThetaConstants.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Form_EMatrix_2.f
DEP_F90_FORM_EMA=\
	".\BeamParams.h"\
	".\CurParams.h"\
	".\LoadStepIter.h"\
	".\material.h"\
	".\ShellParams.h"\
	".\ThetaConstants.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Form_EtranDEplusG.f
DEP_F90_FORM_ET=\
	".\BeamParams.h"\
	".\CurParams.h"\
	".\LoadStepIter.h"\
	".\ShellParams.h"\
	".\SizeVar.h"\
	".\ThetaConstants.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Form_F_a_Part.f
# End Source File
# Begin Source File

SOURCE=.\Form_ForMom.f
DEP_F90_FORM_F=\
	".\LoadStepIter.h"\
	".\Shell2BeamXforms.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Form_GBlocks.f
DEP_F90_FORM_G=\
	".\BeamParams.h"\
	".\ThetaConstants.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Form_GMatrix.f
DEP_F90_FORM_GM=\
	".\BeamParams.h"\
	".\CurParams.h"\
	".\LoadStepIter.h"\
	".\ShellParams.h"\
	".\ThetaConstants.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Form_RealStrains_Ncoords.f
DEP_F90_FORM_R=\
	".\Beam2ShellXforms.h"\
	".\BeamParams.h"\
	".\LoadStepIter.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Form_RMatrix.f
# End Source File
# Begin Source File

SOURCE=.\Form_RotationMatrix.f
# End Source File
# Begin Source File

SOURCE=.\Form_Skew.f
# End Source File
# Begin Source File

SOURCE=.\Form_SMatrix.f
# End Source File
# Begin Source File

SOURCE=.\Form_ThetaAlfaTransMatrix.f
# End Source File
# Begin Source File

SOURCE=.\Form_ThetaConstants.f
DEP_F90_FORM_T=\
	".\LoadStepIter.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Form_Wmatrix.f
# End Source File
# Begin Source File

SOURCE=.\FormIndex_EL2.f
# End Source File
# Begin Source File

SOURCE=.\GaussPtVal.f
# End Source File
# Begin Source File

SOURCE=.\Get_ElementCoords.for
DEP_F90_GET_E=\
	".\Blank.h"\
	".\Examples.h"\
	".\geometry.h"\
	".\SizeVar.h"\
	".\Wpointers.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Get_Geometry.for
DEP_F90_GET_G=\
	".\Drill.h"\
	".\Examples.h"\
	".\geometry.h"\
	".\Output.h"\
	".\SizeVar.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Get_Loads.for
DEP_F90_GET_L=\
	".\Drill.h"\
	".\Examples.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Get_Loads_Pal.for
# End Source File
# Begin Source File

SOURCE=.\Get_Loads_Pal_D.for
# End Source File
# Begin Source File

SOURCE=.\Get_Loads_Str.for
# End Source File
# Begin Source File

SOURCE=.\Get_Loads_Str_D.for
# End Source File
# Begin Source File

SOURCE=.\Get_Material.for
DEP_F90_GET_M=\
	".\Examples.h"\
	".\material.h"\
	".\SizeVar.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Get_ReferenceInfoataGaussPt.f
DEP_F90_GET_R=\
	".\CurParams.h"\
	".\files.h"\
	".\LoadStepIter.h"\
	".\scratch.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Get_SupportedDOFs.for
DEP_F90_GET_S=\
	".\Drill.h"\
	".\Examples.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Get_SupportedDOFs_Pal.for
# End Source File
# Begin Source File

SOURCE=.\Get_SupportedDOFs_Pal_D.for
# End Source File
# Begin Source File

SOURCE=.\Get_SupportedDOFs_Str.for
# End Source File
# Begin Source File

SOURCE=.\Get_SupportedDOFs_Str_D.for
# End Source File
# Begin Source File

SOURCE=.\Initialize_StateVector.for
# End Source File
# Begin Source File

SOURCE=.\Initiate_ExtractionIndex.for
# End Source File
# Begin Source File

SOURCE=.\Initiate_ExtractionIndex_D.for
# End Source File
# Begin Source File

SOURCE=.\Initiate_SolutionData.for
DEP_F90_INITI=\
	".\Examples.h"\
	".\SizeVar.h"\
	".\solve.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Invert_A.for
DEP_F90_INVER=\
	".\LoadStepIter.h"\
	".\solve.h"\
	
# End Source File
# Begin Source File

SOURCE=.\LoadParamChange.for
# End Source File
# Begin Source File

SOURCE=.\LoadStep_1_iter_1.f
DEP_F90_LOADS=\
	".\Addpoints.h"\
	".\Blank.h"\
	".\CurrentElem.h"\
	".\Drill.h"\
	".\files.h"\
	".\general.h"\
	".\LoadStepIter.h"\
	".\LogParams.h"\
	".\scratch.h"\
	".\SizeVar.h"\
	".\solve.h"\
	".\Wpointers.h"\
	
# End Source File
# Begin Source File

SOURCE=.\LoadStep_n_iter_1.f
DEP_F90_LOADST=\
	".\Addpoints.h"\
	".\Blank.h"\
	".\CurrentElem.h"\
	".\Drill.h"\
	".\files.h"\
	".\general.h"\
	".\LoadStepIter.h"\
	".\scratch.h"\
	".\SizeVar.h"\
	".\solve.h"\
	".\Wpointers.h"\
	
# End Source File
# Begin Source File

SOURCE=.\LoadStep_n_iter_m.f
DEP_F90_LOADSTE=\
	".\Addpoints.h"\
	".\Blank.h"\
	".\CurrentElem.h"\
	".\Drill.h"\
	".\files.h"\
	".\general.h"\
	".\LoadStepIter.h"\
	".\scratch.h"\
	".\SizeVar.h"\
	".\solve.h"\
	".\Wpointers.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Non_Singular_QQ.for
DEP_F90_NON_S=\
	".\LoadStepIter.h"\
	".\solve.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Opt1_Calc_ReferenceProps.for
DEP_F90_OPT1_=\
	".\CurParams.h"\
	".\files.h"\
	".\scratch.h"\
	".\SizeVar.h"\
	
# End Source File
# Begin Source File

SOURCE=.\opt1_Form_EMatrix_1.f
DEP_F90_OPT1_F=\
	".\Beam2ShellXforms.h"\
	".\BeamParams.h"\
	".\CurParams.h"\
	".\LoadStepIter.h"\
	".\LogParams.h"\
	".\material.h"\
	".\Opt1_ShellParams.h"\
	".\ThetaConstants.h"\
	
# End Source File
# Begin Source File

SOURCE=.\opt1_Form_EMatrix_2.f
DEP_F90_OPT1_FO=\
	".\Beam2ShellXforms.h"\
	".\BeamParams.h"\
	".\CurParams.h"\
	".\LoadStepIter.h"\
	".\LogParams.h"\
	".\material.h"\
	".\ShellParams.h"\
	".\ThetaConstants.h"\
	
# End Source File
# Begin Source File

SOURCE=.\opt1_Form_EtranDEplusG.f
DEP_F90_OPT1_FOR=\
	".\BeamParams.h"\
	".\CurParams.h"\
	".\LoadStepIter.h"\
	".\Opt1_ShellParams.h"\
	".\SizeVar.h"\
	".\ThetaConstants.h"\
	
# End Source File
# Begin Source File

SOURCE=.\opt1_Form_ForMom.f
DEP_F90_OPT1_FORM=\
	".\LoadStepIter.h"\
	".\Shell2BeamXforms.h"\
	
# End Source File
# Begin Source File

SOURCE=.\opt1_Form_GMatrix.f
DEP_F90_OPT1_FORM_=\
	".\BeamParams.h"\
	".\CurParams.h"\
	".\LoadStepIter.h"\
	".\Opt1_ShellParams.h"\
	".\ThetaConstants.h"\
	
# End Source File
# Begin Source File

SOURCE=.\opt1_Form_RealStrains_Ncoords.f
DEP_F90_OPT1_FORM_R=\
	".\Beam2ShellXforms.h"\
	".\BeamParams.h"\
	".\LoadStepIter.h"\
	
# End Source File
# Begin Source File

SOURCE=.\opt1_Form_Xforms.f
DEP_F90_OPT1_FORM_X=\
	".\Beam2ShellXforms.h"\
	".\LogParams.h"\
	".\Shell2BeamXforms.h"\
	
# End Source File
# Begin Source File

SOURCE=.\opt1_Quad_QQ_STIF.f
DEP_F90_OPT1_Q=\
	".\CurParams.h"\
	".\LoadStepIter.h"\
	".\LogParams.h"\
	".\material.h"\
	".\Opt1_ShellParams.h"\
	".\scratch.h"\
	".\SizeVar.h"\
	
# End Source File
# Begin Source File

SOURCE=.\opt1_Split_Dis_Rot_Deriv.f
DEP_F90_OPT1_S=\
	".\CurParams.h"\
	".\LoadStepIter.h"\
	".\Opt1_ShellParams.h"\
	".\SizeVar.h"\
	
# End Source File
# Begin Source File

SOURCE=.\PhaseI_Shell.f
DEP_F90_PHASE=\
	".\Blank.h"\
	".\debug.h"\
	".\files.h"\
	".\geometry.h"\
	".\Implicit.h"\
	".\material.h"\
	".\SizeVar.h"\
	".\solve.h"\
	".\Wpointers.h"\
	
# End Source File
# Begin Source File

SOURCE=.\PhaseII_Shell.f
DEP_F90_PHASEI=\
	".\Addpoints.h"\
	".\Blank.h"\
	".\CurParams.h"\
	".\CurrentElem.h"\
	".\Examples.h"\
	".\files.h"\
	".\general.h"\
	".\geometry.h"\
	".\Implicit.h"\
	".\LoadStepIter.h"\
	".\material.h"\
	".\Output.h"\
	".\scratch.h"\
	".\SizeVar.h"\
	".\solve.h"\
	".\Wpointers.h"\
	
# End Source File
# Begin Source File

SOURCE=.\PlotDataEndw.for
# End Source File
# Begin Source File

SOURCE=.\ProgShell_NL_Total3D_2ELs.f
DEP_F90_PROGS=\
	".\Addpoints.h"\
	".\Blank.h"\
	".\Debug\DeformationPlot.mod"\
	".\Drill.h"\
	".\Examples.h"\
	".\files.h"\
	".\general.h"\
	".\geometry.h"\
	".\Implicit.h"\
	".\LoadStepIter.h"\
	".\material.h"\
	".\Output.h"\
	".\SizeVar.h"\
	".\solve.h"\
	".\Wpointers.h"\
	{$(INCLUDE)}"linear_operators.mod"\
	
# End Source File
# Begin Source File

SOURCE=.\Put_ReferenceInfo_AllGauss.f
DEP_F90_PUT_R=\
	".\CurParams.h"\
	".\files.h"\
	".\LoadStepIter.h"\
	".\LogParams.h"\
	".\SizeVar.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Put_ReferenceInfoataGaussPt.f
DEP_F90_PUT_RE=\
	".\CurParams.h"\
	".\files.h"\
	".\LogParams.h"\
	".\scratch.h"\
	".\SizeVar.h"\
	
# End Source File
# Begin Source File

SOURCE=.\PutGetRefPropsatGaussPt.for
DEP_F90_PUTGE=\
	".\CurParams.h"\
	".\files.h"\
	
# End Source File
# Begin Source File

SOURCE=.\PutGetRotCur.for
# End Source File
# Begin Source File

SOURCE=.\PutGetTBatGaussPt.for
DEP_F90_PUTGET=\
	".\files.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Quad_QQ_LOAD_ASSEMBLE.f
DEP_F90_QUAD_=\
	".\Examples.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Quad_QQ_LVY.f
# End Source File
# Begin Source File

SOURCE=.\Quad_QQ_STIF.f
DEP_F90_QUAD_Q=\
	".\CurParams.h"\
	".\LoadStepIter.h"\
	".\LogParams.h"\
	".\material.h"\
	".\scratch.h"\
	".\ShellParams.h"\
	".\SizeVar.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Quad_QQ_STIF_ASSEMBLE.f
# End Source File
# Begin Source File

SOURCE=.\Set_ExampleType.for
DEP_F90_SET_E=\
	".\Examples.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Set_Files.for
DEP_F90_SET_F=\
	".\Drill.h"\
	".\files.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Set_Files_Scratch.for
DEP_F90_SET_FI=\
	".\files.h"\
	".\scratch.h"\
	".\SizeVar.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Set_IntegerControls.for
DEP_F90_SET_I=\
	".\Drill.h"\
	".\ElementType.h"\
	".\Examples.h"\
	".\SizeVar.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Set_TimeDate.for
# End Source File
# Begin Source File

SOURCE=.\Set_WorkArrayPointers.for
DEP_F90_SET_W=\
	".\Addpoints.h"\
	".\Output.h"\
	".\SizeVar.h"\
	".\solve.h"\
	".\Wpointers.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Solve_AxEqB.f
DEP_F90_SOLVE=\
	{$(INCLUDE)}"NUMERICAL_LIBRARIES.mod"\
	
# End Source File
# Begin Source File

SOURCE=.\Solve_AxEqB_Drill.f
DEP_F90_SOLVE_=\
	".\LoadStepIter.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Split_Dis_Rot_Deriv.f
DEP_F90_SPLIT=\
	".\CurParams.h"\
	".\LoadStepIter.h"\
	".\ShellParams.h"\
	".\SizeVar.h"\
	
# End Source File
# Begin Source File

SOURCE=.\StateatStartofIter.for
# End Source File
# Begin Source File

SOURCE=.\UpdateIter_Displace_Lambda.for
# End Source File
# Begin Source File

SOURCE=.\UpdateStep_Displace_Lambda.for
# End Source File
# Begin Source File

SOURCE=.\VectorAdd.f
# End Source File
# Begin Source File

SOURCE=.\VectorCrossProduct.f
# End Source File
# Begin Source File

SOURCE=.\VectorDotProduct.f
# End Source File
# Begin Source File

SOURCE=.\VectorExtract_Matrix2D.f
# End Source File
# Begin Source File

SOURCE=.\VectorExtract_Vector.f
# End Source File
# Begin Source File

SOURCE=.\VectorInsert_Vector.f
# End Source File
# Begin Source File

SOURCE=.\VectorNorm.f
# End Source File
# Begin Source File

SOURCE=.\VectorScale.f
# End Source File
# Begin Source File

SOURCE=.\VectorSubtract.f
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\Addpoints.h
# End Source File
# Begin Source File

SOURCE=.\Beam2ShellXforms.h
# End Source File
# Begin Source File

SOURCE=.\BeamParams.h
# End Source File
# Begin Source File

SOURCE=.\Blank.h
# End Source File
# Begin Source File

SOURCE=.\CurParams.h
# End Source File
# Begin Source File

SOURCE=.\CurrentElem.h
# End Source File
# Begin Source File

SOURCE=.\debug.h
# End Source File
# Begin Source File

SOURCE=.\Drill.h
# End Source File
# Begin Source File

SOURCE=.\ElementType.h
# End Source File
# Begin Source File

SOURCE=.\Examples.h
# End Source File
# Begin Source File

SOURCE=.\files.h
# End Source File
# Begin Source File

SOURCE=.\general.h
# End Source File
# Begin Source File

SOURCE=.\geometry.h
# End Source File
# Begin Source File

SOURCE=.\Implicit.h
# End Source File
# Begin Source File

SOURCE=.\LoadStepIter.h
# End Source File
# Begin Source File

SOURCE=.\LogParams.h
# End Source File
# Begin Source File

SOURCE=.\material.h
# End Source File
# Begin Source File

SOURCE=.\Output.h
# End Source File
# Begin Source File

SOURCE=.\scratch.h
# End Source File
# Begin Source File

SOURCE=.\Shell2BeamXforms.h
# End Source File
# Begin Source File

SOURCE=.\ShellParams.h
# End Source File
# Begin Source File

SOURCE=.\SizeVar.h
# End Source File
# Begin Source File

SOURCE=.\solve.h
# End Source File
# Begin Source File

SOURCE=.\ThetaConstants.h
# End Source File
# Begin Source File

SOURCE=.\Wpointers.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
