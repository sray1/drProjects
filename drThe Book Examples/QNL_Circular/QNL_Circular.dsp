# Microsoft Developer Studio Project File - Name="QNL_Circular" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) QuickWin Application" 0x0107

CFG=QNL_Circular - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "QNL_Circular.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "QNL_Circular.mak" CFG="QNL_Circular - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "QNL_Circular - Win32 Release" (based on "Win32 (x86) QuickWin Application")
!MESSAGE "QNL_Circular - Win32 Debug" (based on "Win32 (x86) QuickWin Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
F90=df.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "QNL_Circular - Win32 Release"

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

!ELSEIF  "$(CFG)" == "QNL_Circular - Win32 Debug"

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

# Name "QNL_Circular - Win32 Release"
# Name "QNL_Circular - Win32 Debug"
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

SOURCE=.\Bez_QQ_EL_1.for
# End Source File
# Begin Source File

SOURCE=.\Bez_QQ_EL_2.f
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

SOURCE=.\Compare_Catigliano.f
# End Source File
# Begin Source File

SOURCE=.\Compare_DisRot.f
# End Source File
# Begin Source File

SOURCE=.\Compute_Curvature.f
# End Source File
# Begin Source File

SOURCE=.\Compute_ElementReactions_EL_1.f
# End Source File
# Begin Source File

SOURCE=.\Compute_ElementReactions_EL_2.f
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

SOURCE=.\ConstitutiveDiags.for
# End Source File
# Begin Source File

SOURCE=.\Convergence_Residual.for
# End Source File
# Begin Source File

SOURCE=.\CrossProduct.f
# End Source File
# Begin Source File

SOURCE=.\CubicTangent_Length.for
# End Source File
# Begin Source File

SOURCE=.\DegreeElevate.for
# End Source File
# Begin Source File

SOURCE=.\Direct_Compute_uwthetaAtEnd.f
# End Source File
# Begin Source File

SOURCE=.\Direct_Quad_QQ_LOAD_ASSEMBLE.f
# End Source File
# Begin Source File

SOURCE=.\Direct_Quad_QQ_LVY.f
# End Source File
# Begin Source File

SOURCE=.\Direct_Quad_QQ_STIF.f
# End Source File
# Begin Source File

SOURCE=.\Direct_Quad_QQ_STIF_ASSEMBLE.f
# End Source File
# Begin Source File

SOURCE=".\Direct_Resultat DesiredSteps.for"
# End Source File
# Begin Source File

SOURCE=.\Direct_StateVector.for
# End Source File
# Begin Source File

SOURCE=.\Expand_BZCons_C0.for
# End Source File
# Begin Source File

SOURCE=.\ExtractEL_DispCon.for
# End Source File
# Begin Source File

SOURCE=.\FormIndex_EL2.f
# End Source File
# Begin Source File

SOURCE=.\GaussPtVal.f
# End Source File
# Begin Source File

SOURCE=.\Initialize_StateVector.for
# End Source File
# Begin Source File

SOURCE=.\Initiate_DegreeData.for
# End Source File
# Begin Source File

SOURCE=.\Initiate_ExtractionIndex.for
# End Source File
# Begin Source File

SOURCE=.\Initiate_SolutionData.for
# End Source File
# Begin Source File

SOURCE=.\Initiate_Support.for
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

SOURCE=.\Non_Singular_QQ.for
# End Source File
# Begin Source File

SOURCE=.\PlotDataEndw.for
# End Source File
# Begin Source File

SOURCE=.\Prog_NL_Circular_2ELs.f
DEP_F90_PROG_=\
	".\Debug\DeformationPlot.mod"\
	".\Debug\SCIGRAPH.mod"\
	{$(INCLUDE)}"linear_operators.mod"\
	
# End Source File
# Begin Source File

SOURCE=.\QQ_EtranDEplusG.f
# End Source File
# Begin Source File

SOURCE=.\QQ_StrainDis.f
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

SOURCE=".\Resultat DesiredSteps.for"
# End Source File
# Begin Source File

SOURCE=".\Resultat DesiredSteps_STR.for"
# End Source File
# Begin Source File

SOURCE=.\Scigraph.f90
# End Source File
# Begin Source File

SOURCE=.\Sgadmin.f90
# End Source File
# Begin Source File

SOURCE=.\Sgdata.f90
# End Source File
# Begin Source File

SOURCE=.\Sgdraw.f90
# End Source File
# Begin Source File

SOURCE=.\Sglowlvl.f90
# End Source File
# Begin Source File

SOURCE=.\Sgplot.f90
# End Source File
# Begin Source File

SOURCE=.\SgXYPlot.f90
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

SOURCE=.\StressRecovery.f
# End Source File
# Begin Source File

SOURCE=.\UpdateIter_Displace_Lambda.for
# End Source File
# Begin Source File

SOURCE=.\UpdateStep_Displace_Lambda.for
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
