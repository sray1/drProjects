# Microsoft Developer Studio Generated NMAKE File, Based on 2DCubic_Cubic.dsp
!IF "$(CFG)" == ""
CFG=2DCubic_Cubic - Win32 Debug
!MESSAGE No configuration specified. Defaulting to 2DCubic_Cubic - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "2DCubic_Cubic - Win32 Release" && "$(CFG)" != "2DCubic_Cubic - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
F90=df.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "2DCubic_Cubic - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\2DCubic_Cubic.exe"


CLEAN :
	-@erase "$(INTDIR)\BernStein.obj"
	-@erase "$(INTDIR)\BernStein_IstDerivative.obj"
	-@erase "$(INTDIR)\Bez_QQ_EL_1.obj"
	-@erase "$(INTDIR)\Bez_QQ_EL_2.obj"
	-@erase "$(INTDIR)\Compare_Catigliano.obj"
	-@erase "$(INTDIR)\Compare_DisRot.obj"
	-@erase "$(INTDIR)\Compare_StrainStress.obj"
	-@erase "$(INTDIR)\Compute_ElementReactions_EL_1.obj"
	-@erase "$(INTDIR)\Compute_ElementReactions_EL_2.obj"
	-@erase "$(INTDIR)\Compute_StrainEnergy.obj"
	-@erase "$(INTDIR)\CrossProduct.obj"
	-@erase "$(INTDIR)\CubicTangent_Length.obj"
	-@erase "$(INTDIR)\DegreeElevate.obj"
	-@erase "$(INTDIR)\Disp_QQ_EL_1.obj"
	-@erase "$(INTDIR)\Disp_QQ_EL_2.obj"
	-@erase "$(INTDIR)\DumpRealArray.obj"
	-@erase "$(INTDIR)\DumpRealMatrix.obj"
	-@erase "$(INTDIR)\Expand_BZCons_C0.obj"
	-@erase "$(INTDIR)\Expand_BZCons_C1or2.obj"
	-@erase "$(INTDIR)\ExtractEL_DispCon.obj"
	-@erase "$(INTDIR)\FormIndex_EL2.obj"
	-@erase "$(INTDIR)\FormTransformation Matrix_C1.obj"
	-@erase "$(INTDIR)\FormTransformation Matrix_C2.obj"
	-@erase "$(INTDIR)\GaussPtVal.obj"
	-@erase "$(INTDIR)\Impose_C1or2.obj"
	-@erase "$(INTDIR)\Initiate_DegreeData.obj"
	-@erase "$(INTDIR)\Initiate_ExtractionIndex.obj"
	-@erase "$(INTDIR)\Initiate_Support.obj"
	-@erase "$(INTDIR)\Non_Singular_QQ.obj"
	-@erase "$(INTDIR)\Prog_Timo_QQ_2ELs.obj"
	-@erase "$(INTDIR)\QQ_StrainDis.obj"
	-@erase "$(INTDIR)\Quad_QQ_LVY.obj"
	-@erase "$(INTDIR)\Quad_QQ_STIF.obj"
	-@erase "$(INTDIR)\Quad_QQ_STIF_ASSEMBLE.obj"
	-@erase "$(INTDIR)\Solve_AxEqB.obj"
	-@erase "$(INTDIR)\StressRecovery.obj"
	-@erase "$(INTDIR)\TMB_Axes.obj"
	-@erase "$(OUTDIR)\2DCubic_Cubic.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90_PROJ=/compile_only /include:"Release/" /libs:qwins /nologo /warn:nofileopt /module:"Release/" /object:"Release/" 
F90_OBJS=.\Release/
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\2DCubic_Cubic.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\2DCubic_Cubic.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib /nologo /entry:"WinMainCRTStartup" /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\2DCubic_Cubic.pdb" /machine:I386 /nodefaultlib:"dfconsol.lib" /out:"$(OUTDIR)\2DCubic_Cubic.exe" 
LINK32_OBJS= \
	"$(INTDIR)\BernStein.obj" \
	"$(INTDIR)\BernStein_IstDerivative.obj" \
	"$(INTDIR)\Bez_QQ_EL_1.obj" \
	"$(INTDIR)\Bez_QQ_EL_2.obj" \
	"$(INTDIR)\Compare_Catigliano.obj" \
	"$(INTDIR)\Compare_DisRot.obj" \
	"$(INTDIR)\Compare_StrainStress.obj" \
	"$(INTDIR)\Compute_ElementReactions_EL_1.obj" \
	"$(INTDIR)\Compute_ElementReactions_EL_2.obj" \
	"$(INTDIR)\Compute_StrainEnergy.obj" \
	"$(INTDIR)\CrossProduct.obj" \
	"$(INTDIR)\CubicTangent_Length.obj" \
	"$(INTDIR)\DegreeElevate.obj" \
	"$(INTDIR)\Disp_QQ_EL_1.obj" \
	"$(INTDIR)\Disp_QQ_EL_2.obj" \
	"$(INTDIR)\DumpRealArray.obj" \
	"$(INTDIR)\Expand_BZCons_C0.obj" \
	"$(INTDIR)\Expand_BZCons_C1or2.obj" \
	"$(INTDIR)\ExtractEL_DispCon.obj" \
	"$(INTDIR)\FormIndex_EL2.obj" \
	"$(INTDIR)\FormTransformation Matrix_C1.obj" \
	"$(INTDIR)\FormTransformation Matrix_C2.obj" \
	"$(INTDIR)\GaussPtVal.obj" \
	"$(INTDIR)\Impose_C1or2.obj" \
	"$(INTDIR)\Initiate_DegreeData.obj" \
	"$(INTDIR)\Initiate_ExtractionIndex.obj" \
	"$(INTDIR)\Initiate_Support.obj" \
	"$(INTDIR)\Non_Singular_QQ.obj" \
	"$(INTDIR)\Prog_Timo_QQ_2ELs.obj" \
	"$(INTDIR)\QQ_StrainDis.obj" \
	"$(INTDIR)\Quad_QQ_LVY.obj" \
	"$(INTDIR)\Quad_QQ_STIF.obj" \
	"$(INTDIR)\Quad_QQ_STIF_ASSEMBLE.obj" \
	"$(INTDIR)\Solve_AxEqB.obj" \
	"$(INTDIR)\StressRecovery.obj" \
	"$(INTDIR)\TMB_Axes.obj" \
	"$(INTDIR)\DumpRealMatrix.obj"

"$(OUTDIR)\2DCubic_Cubic.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "2DCubic_Cubic - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\TestRGeq1.exe"


CLEAN :
	-@erase "$(INTDIR)\BernStein.obj"
	-@erase "$(INTDIR)\BernStein_IstDerivative.obj"
	-@erase "$(INTDIR)\Bez_QQ_EL_1.obj"
	-@erase "$(INTDIR)\Bez_QQ_EL_2.obj"
	-@erase "$(INTDIR)\Compare_Catigliano.obj"
	-@erase "$(INTDIR)\Compare_DisRot.obj"
	-@erase "$(INTDIR)\Compare_StrainStress.obj"
	-@erase "$(INTDIR)\Compute_ElementReactions_EL_1.obj"
	-@erase "$(INTDIR)\Compute_ElementReactions_EL_2.obj"
	-@erase "$(INTDIR)\Compute_StrainEnergy.obj"
	-@erase "$(INTDIR)\CrossProduct.obj"
	-@erase "$(INTDIR)\CubicTangent_Length.obj"
	-@erase "$(INTDIR)\DegreeElevate.obj"
	-@erase "$(INTDIR)\DF60.PDB"
	-@erase "$(INTDIR)\Disp_QQ_EL_1.obj"
	-@erase "$(INTDIR)\Disp_QQ_EL_2.obj"
	-@erase "$(INTDIR)\DumpRealArray.obj"
	-@erase "$(INTDIR)\DumpRealMatrix.obj"
	-@erase "$(INTDIR)\Expand_BZCons_C0.obj"
	-@erase "$(INTDIR)\Expand_BZCons_C1or2.obj"
	-@erase "$(INTDIR)\ExtractEL_DispCon.obj"
	-@erase "$(INTDIR)\FormIndex_EL2.obj"
	-@erase "$(INTDIR)\FormTransformation Matrix_C1.obj"
	-@erase "$(INTDIR)\FormTransformation Matrix_C2.obj"
	-@erase "$(INTDIR)\GaussPtVal.obj"
	-@erase "$(INTDIR)\Impose_C1or2.obj"
	-@erase "$(INTDIR)\Initiate_DegreeData.obj"
	-@erase "$(INTDIR)\Initiate_ExtractionIndex.obj"
	-@erase "$(INTDIR)\Initiate_Support.obj"
	-@erase "$(INTDIR)\Non_Singular_QQ.obj"
	-@erase "$(INTDIR)\Prog_Timo_QQ_2ELs.obj"
	-@erase "$(INTDIR)\QQ_StrainDis.obj"
	-@erase "$(INTDIR)\Quad_QQ_LVY.obj"
	-@erase "$(INTDIR)\Quad_QQ_STIF.obj"
	-@erase "$(INTDIR)\Quad_QQ_STIF_ASSEMBLE.obj"
	-@erase "$(INTDIR)\Solve_AxEqB.obj"
	-@erase "$(INTDIR)\StressRecovery.obj"
	-@erase "$(INTDIR)\TMB_Axes.obj"
	-@erase "$(OUTDIR)\TestRGeq1.exe"
	-@erase "$(OUTDIR)\TestRGeq1.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90_PROJ=/check:bounds /compile_only /debug:full /include:"Debug/" /libs:qwins /nologo /traceback /warn:argument_checking /warn:nofileopt /module:"Debug/" /object:"Debug/" /pdbfile:"Debug/DF60.PDB" 
F90_OBJS=.\Debug/
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\2DCubic_Cubic.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\2DCubic_Cubic.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib smathd.lib sf90mp.lib /nologo /stack:0x3d0900 /entry:"WinMainCRTStartup" /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\TestRGeq1.pdb" /debug /machine:I386 /nodefaultlib:"dfconsol.lib" /out:"$(OUTDIR)\TestRGeq1.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\BernStein.obj" \
	"$(INTDIR)\BernStein_IstDerivative.obj" \
	"$(INTDIR)\Bez_QQ_EL_1.obj" \
	"$(INTDIR)\Bez_QQ_EL_2.obj" \
	"$(INTDIR)\Compare_Catigliano.obj" \
	"$(INTDIR)\Compare_DisRot.obj" \
	"$(INTDIR)\Compare_StrainStress.obj" \
	"$(INTDIR)\Compute_ElementReactions_EL_1.obj" \
	"$(INTDIR)\Compute_ElementReactions_EL_2.obj" \
	"$(INTDIR)\Compute_StrainEnergy.obj" \
	"$(INTDIR)\CrossProduct.obj" \
	"$(INTDIR)\CubicTangent_Length.obj" \
	"$(INTDIR)\DegreeElevate.obj" \
	"$(INTDIR)\Disp_QQ_EL_1.obj" \
	"$(INTDIR)\Disp_QQ_EL_2.obj" \
	"$(INTDIR)\DumpRealArray.obj" \
	"$(INTDIR)\Expand_BZCons_C0.obj" \
	"$(INTDIR)\Expand_BZCons_C1or2.obj" \
	"$(INTDIR)\ExtractEL_DispCon.obj" \
	"$(INTDIR)\FormIndex_EL2.obj" \
	"$(INTDIR)\FormTransformation Matrix_C1.obj" \
	"$(INTDIR)\FormTransformation Matrix_C2.obj" \
	"$(INTDIR)\GaussPtVal.obj" \
	"$(INTDIR)\Impose_C1or2.obj" \
	"$(INTDIR)\Initiate_DegreeData.obj" \
	"$(INTDIR)\Initiate_ExtractionIndex.obj" \
	"$(INTDIR)\Initiate_Support.obj" \
	"$(INTDIR)\Non_Singular_QQ.obj" \
	"$(INTDIR)\Prog_Timo_QQ_2ELs.obj" \
	"$(INTDIR)\QQ_StrainDis.obj" \
	"$(INTDIR)\Quad_QQ_LVY.obj" \
	"$(INTDIR)\Quad_QQ_STIF.obj" \
	"$(INTDIR)\Quad_QQ_STIF_ASSEMBLE.obj" \
	"$(INTDIR)\Solve_AxEqB.obj" \
	"$(INTDIR)\StressRecovery.obj" \
	"$(INTDIR)\TMB_Axes.obj" \
	"$(INTDIR)\DumpRealMatrix.obj"

"$(OUTDIR)\TestRGeq1.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.SUFFIXES: .fpp

.for{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

.f{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

.f90{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

.fpp{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("2DCubic_Cubic.dep")
!INCLUDE "2DCubic_Cubic.dep"
!ELSE 
!MESSAGE Warning: cannot find "2DCubic_Cubic.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "2DCubic_Cubic - Win32 Release" || "$(CFG)" == "2DCubic_Cubic - Win32 Debug"
SOURCE=.\BernStein.for

"$(INTDIR)\BernStein.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\BernStein_IstDerivative.for

"$(INTDIR)\BernStein_IstDerivative.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Bez_QQ_EL_1.for

"$(INTDIR)\Bez_QQ_EL_1.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Bez_QQ_EL_2.for

"$(INTDIR)\Bez_QQ_EL_2.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Compare_Catigliano.f

"$(INTDIR)\Compare_Catigliano.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Compare_DisRot.f

"$(INTDIR)\Compare_DisRot.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Compare_StrainStress.f

"$(INTDIR)\Compare_StrainStress.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Compute_ElementReactions_EL_1.f

"$(INTDIR)\Compute_ElementReactions_EL_1.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Compute_ElementReactions_EL_2.f

"$(INTDIR)\Compute_ElementReactions_EL_2.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Compute_StrainEnergy.f

"$(INTDIR)\Compute_StrainEnergy.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\CrossProduct.f

"$(INTDIR)\CrossProduct.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\CubicTangent_Length.for

"$(INTDIR)\CubicTangent_Length.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DegreeElevate.for

"$(INTDIR)\DegreeElevate.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Disp_QQ_EL_1.for

"$(INTDIR)\Disp_QQ_EL_1.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Disp_QQ_EL_2.for

"$(INTDIR)\Disp_QQ_EL_2.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DumpRealArray.for

"$(INTDIR)\DumpRealArray.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DumpRealMatrix.for

"$(INTDIR)\DumpRealMatrix.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Expand_BZCons_C0.for

"$(INTDIR)\Expand_BZCons_C0.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Expand_BZCons_C1or2.for

"$(INTDIR)\Expand_BZCons_C1or2.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ExtractEL_DispCon.for

"$(INTDIR)\ExtractEL_DispCon.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\FormIndex_EL2.f

"$(INTDIR)\FormIndex_EL2.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=".\FormTransformation Matrix_C1.f"

"$(INTDIR)\FormTransformation Matrix_C1.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=".\FormTransformation Matrix_C2.f"

"$(INTDIR)\FormTransformation Matrix_C2.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\GaussPtVal.f

"$(INTDIR)\GaussPtVal.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Impose_C1or2.f

"$(INTDIR)\Impose_C1or2.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Initiate_DegreeData.for

"$(INTDIR)\Initiate_DegreeData.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Initiate_ExtractionIndex.for

"$(INTDIR)\Initiate_ExtractionIndex.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Initiate_Support.for

"$(INTDIR)\Initiate_Support.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Non_Singular_QQ.for

"$(INTDIR)\Non_Singular_QQ.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Prog_Timo_QQ_2ELs.f

"$(INTDIR)\Prog_Timo_QQ_2ELs.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\QQ_StrainDis.f

"$(INTDIR)\QQ_StrainDis.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Quad_QQ_LVY.f

"$(INTDIR)\Quad_QQ_LVY.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Quad_QQ_STIF.f

"$(INTDIR)\Quad_QQ_STIF.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Quad_QQ_STIF_ASSEMBLE.f

"$(INTDIR)\Quad_QQ_STIF_ASSEMBLE.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Solve_AxEqB.f

"$(INTDIR)\Solve_AxEqB.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\StressRecovery.f

"$(INTDIR)\StressRecovery.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\TMB_Axes.f

"$(INTDIR)\TMB_Axes.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

