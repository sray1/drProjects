# Microsoft Developer Studio Project File - Name="2DCubic_Cubic" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Standard Graphics Application" 0x0108

CFG=2DCubic_Cubic - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "2DCubic_Cubic.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "2DCubic_Cubic.mak" CFG="2DCubic_Cubic - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "2DCubic_Cubic - Win32 Release" (based on "Win32 (x86) Standard Graphics Application")
!MESSAGE "2DCubic_Cubic - Win32 Debug" (based on "Win32 (x86) Standard Graphics Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
F90=df.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "2DCubic_Cubic - Win32 Release"

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
# ADD BASE F90 /compile_only /include:"Release/" /nologo /warn:nofileopt /libs:qwins
# ADD F90 /compile_only /include:"Release/" /nologo /warn:nofileopt /libs:qwins
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
# ADD BASE LINK32 kernel32.lib /nologo /entry:"WinMainCRTStartup" /subsystem:windows /machine:I386 /nodefaultlib:"dfconsol.lib"
# ADD LINK32 kernel32.lib /nologo /entry:"WinMainCRTStartup" /subsystem:windows /machine:I386 /nodefaultlib:"dfconsol.lib"

!ELSEIF  "$(CFG)" == "2DCubic_Cubic - Win32 Debug"

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
# ADD BASE F90 /check:bounds /compile_only /debug:full /include:"Debug/" /nologo /traceback /warn:argument_checking /warn:nofileopt /libs:qwins
# ADD F90 /check:bounds /compile_only /debug:full /include:"Debug/" /nologo /traceback /warn:argument_checking /warn:nofileopt /libs:qwins
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
# ADD BASE LINK32 kernel32.lib /nologo /entry:"WinMainCRTStartup" /subsystem:windows /debug /machine:I386 /nodefaultlib:"dfconsol.lib" /pdbtype:sept
# ADD LINK32 kernel32.lib smathd.lib sf90mp.lib /nologo /stack:0x3d0900 /entry:"WinMainCRTStartup" /subsystem:windows /incremental:no /debug /machine:I386 /nodefaultlib:"dfconsol.lib" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "2DCubic_Cubic - Win32 Release"
# Name "2DCubic_Cubic - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;f90;for;f;fpp"
# Begin Source File

SOURCE=.\BZ_Coords_EL1.for
# End Source File
# Begin Source File

SOURCE=.\BZ_Coords_EL2.for
# End Source File
# Begin Source File

SOURCE=.\Compute_Displacement.for
# End Source File
# Begin Source File

SOURCE=.\Compute_StrainEnergy.f
# End Source File
# Begin Source File

SOURCE=.\Expand_BZDispControls.for
# End Source File
# Begin Source File

SOURCE=.\ExpandFrom_C1or2Sol.f
# End Source File
# Begin Source File

SOURCE=.\ExtractEL_DispCon.for
# End Source File
# Begin Source File

SOURCE=.\FormIndex_EL2.f
# End Source File
# Begin Source File

SOURCE=".\FormTransformation Matrix_C0_Lin.f"
# End Source File
# Begin Source File

SOURCE=".\FormTransformation Matrix_C1.f"
# End Source File
# Begin Source File

SOURCE=".\FormTransformation Matrix_C2.f"
# End Source File
# Begin Source File

SOURCE=.\Impose_C1or2.f
# End Source File
# Begin Source File

SOURCE=.\Jacobian.f
# End Source File
# Begin Source File

SOURCE=.\NonSingularStif.for
# End Source File
# Begin Source File

SOURCE=.\Prog_Quad_CC_WARP_YES_2ELs.f
# End Source File
# Begin Source File

SOURCE=.\QC_Disps_EL.f
# End Source File
# Begin Source File

SOURCE=.\QC_StrainDis.f
# End Source File
# Begin Source File

SOURCE=.\QC_Strains_EL.f
# End Source File
# Begin Source File

SOURCE=.\Quad_CC_STIF_ASSEMBLE.f
# End Source File
# Begin Source File

SOURCE=.\Quad_QC_LV.f
# End Source File
# Begin Source File

SOURCE=.\Quad_QC_STIF.f
# End Source File
# Begin Source File

SOURCE=.\QwinStuff.f
# End Source File
# Begin Source File

SOURCE=.\Solve_AxEqB.f
DEP_F90_SOLVE=\
	{$(INCLUDE)}"NUMERICAL_LIBRARIES.mod"\
	
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\temp.txt
# End Source File
# End Target
# End Project
