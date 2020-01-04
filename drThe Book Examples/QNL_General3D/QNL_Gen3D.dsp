# Microsoft Developer Studio Project File - Name="QNL_Gen3D" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) QuickWin Application" 0x0107

CFG=QNL_Gen3D - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "QNL_Gen3D.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "QNL_Gen3D.mak" CFG="QNL_Gen3D - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "QNL_Gen3D - Win32 Release" (based on "Win32 (x86) QuickWin Application")
!MESSAGE "QNL_Gen3D - Win32 Debug" (based on "Win32 (x86) QuickWin Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
F90=df.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "QNL_Gen3D - Win32 Release"

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

!ELSEIF  "$(CFG)" == "QNL_Gen3D - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
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

# Name "QNL_Gen3D - Win32 Release"
# Name "QNL_Gen3D - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;f90;for;f;fpp"
# Begin Source File

SOURCE=.\Augment_Load_ArcLen.f
# End Source File
# Begin Source File

SOURCE=.\Augment_STIF_ArcLen.f
# End Source File
# Begin Source File

SOURCE=.\BernStein.for
# End Source File
# Begin Source File

SOURCE=.\BernStein_IstDerivative.for
# End Source File
# Begin Source File

SOURCE=.\Bez_QQ_EL_1_Bat.f
# End Source File
# Begin Source File

SOURCE=.\Bez_QQ_EL_1_LIN.for
# End Source File
# Begin Source File

SOURCE=.\Bez_QQ_EL_1_Str.f
# End Source File
# Begin Source File

SOURCE=.\Bez_QQ_EL_1Pal.f
# End Source File
# Begin Source File

SOURCE=.\Bez_QQ_EL_2.f
# End Source File
# Begin Source File

SOURCE=.\Bez_QQ_EL_2_Bat.f
# End Source File
# Begin Source File

SOURCE=.\Bez_QQ_EL_2_LIN.for
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

SOURCE=.\Calc_deltaUi.for
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

SOURCE=.\Calc_LoadIncrement.for
# End Source File
# Begin Source File

SOURCE=.\Check_PossibleDisplacement.for
# End Source File
# Begin Source File

SOURCE=.\Compute_StrainEnergy.f
# End Source File
# Begin Source File

SOURCE=.\Compute_UpdatedCoordinates.for
# End Source File
# Begin Source File

SOURCE=.\Compute_UpdatedState.for
# End Source File
# Begin Source File

SOURCE=.\Compute_uwthetaAtEnd.f
# End Source File
# Begin Source File

SOURCE=.\Convergence_Residual.for
# End Source File
# Begin Source File

SOURCE=.\CubicTangent_Length.for
# End Source File
# Begin Source File

SOURCE=.\Define_ElementTypes.for
# End Source File
# Begin Source File

SOURCE=.\DeformOut_MatLab.for
# End Source File
# Begin Source File

SOURCE=.\DeformOut_MatLab_Bat.for
# End Source File
# Begin Source File

SOURCE=.\DeformOut_MatLab_Lin.for
# End Source File
# Begin Source File

SOURCE=.\DeformOut_MatLab_Pal.for
# End Source File
# Begin Source File

SOURCE=.\DeformOut_MatLab_Str.for
# End Source File
# Begin Source File

SOURCE=.\DegreeElevate.for
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

SOURCE=.\Extract_Vector.f
# End Source File
# Begin Source File

SOURCE=.\ExtractEL_DispCon.for
# End Source File
# Begin Source File

SOURCE=.\Form_a_N_kc_N_AMat.f
# End Source File
# Begin Source File

SOURCE=.\Form_B_and_Tmatrices.f
# End Source File
# Begin Source File

SOURCE=.\Form_ConstitutiveMatrix.for
# End Source File
# Begin Source File

SOURCE=.\Form_EBlocks.f
# End Source File
# Begin Source File

SOURCE=.\Form_EMatrix.f
# End Source File
# Begin Source File

SOURCE=.\Form_EtranDEplusG.f
# End Source File
# Begin Source File

SOURCE=.\Form_F_a_Part.f
# End Source File
# Begin Source File

SOURCE=.\Form_ForMom.f
# End Source File
# Begin Source File

SOURCE=.\Form_GBlocks.f
# End Source File
# Begin Source File

SOURCE=.\Form_GMatrix.f
# End Source File
# Begin Source File

SOURCE=.\Form_RealStrains_Ncoords.f
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
# End Source File
# Begin Source File

SOURCE=.\Get_Geometry.for
# End Source File
# Begin Source File

SOURCE=.\Get_Loads.for
# End Source File
# Begin Source File

SOURCE=.\Get_Loads_Bat.for
# End Source File
# Begin Source File

SOURCE=.\Get_Loads_LIN.for
# End Source File
# Begin Source File

SOURCE=.\Get_Loads_Pal.for
# End Source File
# Begin Source File

SOURCE=.\Get_Loads_Str.for
# End Source File
# Begin Source File

SOURCE=.\Get_Material.for
# End Source File
# Begin Source File

SOURCE=.\Get_ReferenceInfo.f
# End Source File
# Begin Source File

SOURCE=.\Get_SupportedDOFs.for
# End Source File
# Begin Source File

SOURCE=.\Get_SupportedDOFs_Bat.for
# End Source File
# Begin Source File

SOURCE=.\Get_SupportedDOFs_LIN.for
# End Source File
# Begin Source File

SOURCE=.\Get_SupportedDOFs_Pal.for
# End Source File
# Begin Source File

SOURCE=.\Get_SupportedDOFs_Str.for
# End Source File
# Begin Source File

SOURCE=.\Initialize_StateVector.for
# End Source File
# Begin Source File

SOURCE=.\Initiate_ExtractionIndex.for
# End Source File
# Begin Source File

SOURCE=.\Initiate_SolutionData.for
# End Source File
# Begin Source File

SOURCE=.\Invert_A.for
# End Source File
# Begin Source File

SOURCE=.\InvertedTangentStiffness.for
# End Source File
# Begin Source File

SOURCE=.\LoadParamChange.for
# End Source File
# Begin Source File

SOURCE=.\LoadStep_1_iter_1.f
# End Source File
# Begin Source File

SOURCE=.\LoadStep_n_iter_1.f
# End Source File
# Begin Source File

SOURCE=.\LoadStep_n_iter_m.f
# End Source File
# Begin Source File

SOURCE=.\Non_Singular_QQ.for
# End Source File
# Begin Source File

SOURCE=.\PlotDataEndw.for
# End Source File
# Begin Source File

SOURCE=.\Prog_NL_General3D_2ELs.f
DEP_F90_PROG_=\
	".\Debug\DeformationPlot.mod"\
	".\Debug\SCIGRAPH.mod"\
	{$(INCLUDE)}"linear_operators.mod"\
	
# End Source File
# Begin Source File

SOURCE=.\PutGetRotCur.for
# End Source File
# Begin Source File

SOURCE=.\Quad_QQ_LOAD_ASSEMBLE.f
# End Source File
# Begin Source File

SOURCE=.\Quad_QQ_LVY.f
# End Source File
# Begin Source File

SOURCE=.\Quad_QQ_STIF.f
# End Source File
# Begin Source File

SOURCE=.\Quad_QQ_STIF_ASSEMBLE.f
# End Source File
# Begin Source File

SOURCE=.\Reset_Reference.f
# End Source File
# Begin Source File

SOURCE=.\Scigraph.f90
DEP_F90_SCIGR=\
	".\Debug\SGADMIN.mod"\
	".\Debug\SGPLOT.mod"\
	
# End Source File
# Begin Source File

SOURCE=.\Set_ExampleType.for
# End Source File
# Begin Source File

SOURCE=.\Set_Files.for
# End Source File
# Begin Source File

SOURCE=.\Set_Files_Scratch.for
# End Source File
# Begin Source File

SOURCE=.\Set_IntegerControls.for
# End Source File
# Begin Source File

SOURCE=.\Set_TimeDate.for
# End Source File
# Begin Source File

SOURCE=.\Set_WorkArrayPointers.for
# End Source File
# Begin Source File

SOURCE=.\Sgadmin.f90
DEP_F90_SGADM=\
	".\Debug\SGDRAW.MOD"\
	
# End Source File
# Begin Source File

SOURCE=.\Sgdata.f90
# End Source File
# Begin Source File

SOURCE=.\Sgdraw.f90
DEP_F90_SGDRA=\
	".\Debug\SGLOWLVL.MOD"\
	
# End Source File
# Begin Source File

SOURCE=.\Sglowlvl.f90
DEP_F90_SGLOW=\
	".\Debug\SGDATA.MOD"\
	
# End Source File
# Begin Source File

SOURCE=.\Sgplot.f90
DEP_F90_SGPLO=\
	".\Debug\SGDRAW.MOD"\
	
# End Source File
# Begin Source File

SOURCE=.\SgXYPlot.f90
DEP_F90_SGXYP=\
	".\Debug\SCIGRAPH.mod"\
	
# End Source File
# Begin Source File

SOURCE=.\Solve_AxEqB.f
DEP_F90_SOLVE=\
	{$(INCLUDE)}"NUMERICAL_LIBRARIES.mod"\
	
# End Source File
# Begin Source File

SOURCE=.\StateatStartofIter.for
# End Source File
# Begin Source File

SOURCE=.\ThetaNeedUpdate.for
# End Source File
# Begin Source File

SOURCE=.\TMB_Axes.f
# End Source File
# Begin Source File

SOURCE=.\TMB_Axes_Cur_Tor_Det.f
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
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\Data_TipMoment.txt
# End Source File
# End Target
# End Project
