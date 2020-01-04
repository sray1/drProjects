# Microsoft Developer Studio Generated NMAKE File, Based on OLD_Gen3D.dsp
!IF "$(CFG)" == ""
CFG=OLD_Gen3D - Win32 Debug
!MESSAGE No configuration specified. Defaulting to OLD_Gen3D - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "OLD_Gen3D - Win32 Release" && "$(CFG)" != "OLD_Gen3D - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "OLD_Gen3D.mak" CFG="OLD_Gen3D - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "OLD_Gen3D - Win32 Release" (based on "Win32 (x86) QuickWin Application")
!MESSAGE "OLD_Gen3D - Win32 Debug" (based on "Win32 (x86) QuickWin Application")
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

!IF  "$(CFG)" == "OLD_Gen3D - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\OLD_Gen3D.exe"


CLEAN :
	-@erase "$(INTDIR)\Augment_Load_ArcLen.obj"
	-@erase "$(INTDIR)\Augment_STIF_ArcLen.obj"
	-@erase "$(INTDIR)\BernStein.obj"
	-@erase "$(INTDIR)\BernStein_IstDerivative.obj"
	-@erase "$(INTDIR)\Bez_QQ_EL_1.obj"
	-@erase "$(INTDIR)\Bez_QQ_EL_2.obj"
	-@erase "$(INTDIR)\Calc_Angles.obj"
	-@erase "$(INTDIR)\Calc_ArcLength_Step1.obj"
	-@erase "$(INTDIR)\Calc_ArcLength_Stepm.obj"
	-@erase "$(INTDIR)\Calc_deltaUi.obj"
	-@erase "$(INTDIR)\Calc_deltaUi1.obj"
	-@erase "$(INTDIR)\Calc_deltaUi2.obj"
	-@erase "$(INTDIR)\Calc_delUi.obj"
	-@erase "$(INTDIR)\Calc_Lamda1_Stepm.obj"
	-@erase "$(INTDIR)\Calc_LoadIncrement.obj"
	-@erase "$(INTDIR)\Check_PossibleDisplacement.obj"
	-@erase "$(INTDIR)\Compute_Curvature.obj"
	-@erase "$(INTDIR)\Compute_DisRot_2ELModel.obj"
	-@erase "$(INTDIR)\Compute_ElementReactions_EL_1.obj"
	-@erase "$(INTDIR)\Compute_ElementReactions_EL_2.obj"
	-@erase "$(INTDIR)\Compute_StrainEnergy.obj"
	-@erase "$(INTDIR)\Compute_UpdatedCoordinates.obj"
	-@erase "$(INTDIR)\Compute_UpdatedState.obj"
	-@erase "$(INTDIR)\Compute_uwthetaAtEnd.obj"
	-@erase "$(INTDIR)\ConstitutiveMatrix_D.obj"
	-@erase "$(INTDIR)\Convergence_Residual.obj"
	-@erase "$(INTDIR)\Cubic_ArbitrarySi.obj"
	-@erase "$(INTDIR)\CubicTangent_Length.obj"
	-@erase "$(INTDIR)\DegreeElevate.obj"
	-@erase "$(INTDIR)\DumpIntegerVar.obj"
	-@erase "$(INTDIR)\DumpRealArray.obj"
	-@erase "$(INTDIR)\DumpRealMatrix.obj"
	-@erase "$(INTDIR)\DumpRealVar.obj"
	-@erase "$(INTDIR)\DumpStringVar.obj"
	-@erase "$(INTDIR)\DumpVar.obj"
	-@erase "$(INTDIR)\Expand_BZCons_C0.obj"
	-@erase "$(INTDIR)\Extract_Vector.obj"
	-@erase "$(INTDIR)\ExtractEL_DispCon.obj"
	-@erase "$(INTDIR)\Form_a_N_kc_N_AMat.obj"
	-@erase "$(INTDIR)\Form_B_and_Tmatrices.obj"
	-@erase "$(INTDIR)\Form_EBlocks.obj"
	-@erase "$(INTDIR)\Form_EMatrix.obj"
	-@erase "$(INTDIR)\Form_EtranDEplusG.obj"
	-@erase "$(INTDIR)\Form_F_a_Part.obj"
	-@erase "$(INTDIR)\Form_ForMom.obj"
	-@erase "$(INTDIR)\Form_GBlocks.obj"
	-@erase "$(INTDIR)\Form_GMatrix.obj"
	-@erase "$(INTDIR)\Form_RealStrains_Ncoords.obj"
	-@erase "$(INTDIR)\Form_RMatrix.obj"
	-@erase "$(INTDIR)\Form_RotationMatrix.obj"
	-@erase "$(INTDIR)\Form_Skew.obj"
	-@erase "$(INTDIR)\Form_SMatrix.obj"
	-@erase "$(INTDIR)\Form_ThetaAlfaTransMatrix.obj"
	-@erase "$(INTDIR)\Form_ThetaConstants.obj"
	-@erase "$(INTDIR)\Form_Wmatrix.obj"
	-@erase "$(INTDIR)\FormIndex_EL2.obj"
	-@erase "$(INTDIR)\GaussPtVal.obj"
	-@erase "$(INTDIR)\Initialize_StateVector.obj"
	-@erase "$(INTDIR)\Initiate_DegreeData.obj"
	-@erase "$(INTDIR)\Initiate_ExtractionIndex.obj"
	-@erase "$(INTDIR)\Initiate_SolutionData.obj"
	-@erase "$(INTDIR)\Initiate_Support.obj"
	-@erase "$(INTDIR)\Invert_A.obj"
	-@erase "$(INTDIR)\InvertedTangentStiffness.obj"
	-@erase "$(INTDIR)\LoadParamChange.obj"
	-@erase "$(INTDIR)\Non_Singular_QQ.obj"
	-@erase "$(INTDIR)\PlotDataEndw.obj"
	-@erase "$(INTDIR)\Prog_NL_General3D_2ELs.obj"
	-@erase "$(INTDIR)\Quad_QQ_LOAD_ASSEMBLE.obj"
	-@erase "$(INTDIR)\Quad_QQ_LVY.obj"
	-@erase "$(INTDIR)\Quad_QQ_STIF.obj"
	-@erase "$(INTDIR)\Quad_QQ_STIF_ASSEMBLE.obj"
	-@erase "$(INTDIR)\Resultat DesiredSteps.obj"
	-@erase "$(INTDIR)\Resultat DesiredSteps_Bat.obj"
	-@erase "$(INTDIR)\Resultat DesiredSteps_LIN.obj"
	-@erase "$(INTDIR)\Resultat DesiredSteps_STR.obj"
	-@erase "$(INTDIR)\Scigraph.obj"
	-@erase "$(INTDIR)\Sgadmin.obj"
	-@erase "$(INTDIR)\Sgdata.obj"
	-@erase "$(INTDIR)\Sgdraw.obj"
	-@erase "$(INTDIR)\Sglowlvl.obj"
	-@erase "$(INTDIR)\Sgplot.obj"
	-@erase "$(INTDIR)\SgXYPlot.obj"
	-@erase "$(INTDIR)\Solve_AxEqB.obj"
	-@erase "$(INTDIR)\StateatStartofIter.obj"
	-@erase "$(INTDIR)\StressRecovery.obj"
	-@erase "$(INTDIR)\TMB_Axes_Cur_Tor_Det.obj"
	-@erase "$(INTDIR)\UpdateIter_Displace_Lambda.obj"
	-@erase "$(INTDIR)\UpdateStep_Displace_Lambda.obj"
	-@erase "$(INTDIR)\VectorAdd.obj"
	-@erase "$(INTDIR)\VectorCrossProduct.obj"
	-@erase "$(INTDIR)\VectorDotProduct.obj"
	-@erase "$(INTDIR)\VectorNorm.obj"
	-@erase "$(INTDIR)\VectorScale.obj"
	-@erase "$(INTDIR)\VectorSubtract.obj"
	-@erase "$(OUTDIR)\OLD_Gen3D.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90_PROJ=/compile_only /libs:qwin /nologo /warn:nofileopt /module:"Release/" /object:"Release/" 
F90_OBJS=.\Release/
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\OLD_Gen3D.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\OLD_Gen3D.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"WinMainCRTStartup" /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\OLD_Gen3D.pdb" /machine:I386 /nodefaultlib:"dfconsol.lib" /out:"$(OUTDIR)\OLD_Gen3D.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Augment_Load_ArcLen.obj" \
	"$(INTDIR)\Augment_STIF_ArcLen.obj" \
	"$(INTDIR)\BernStein.obj" \
	"$(INTDIR)\BernStein_IstDerivative.obj" \
	"$(INTDIR)\Bez_QQ_EL_1.obj" \
	"$(INTDIR)\Bez_QQ_EL_2.obj" \
	"$(INTDIR)\Calc_Angles.obj" \
	"$(INTDIR)\Calc_ArcLength_Step1.obj" \
	"$(INTDIR)\Calc_ArcLength_Stepm.obj" \
	"$(INTDIR)\Calc_deltaUi.obj" \
	"$(INTDIR)\Calc_deltaUi1.obj" \
	"$(INTDIR)\Calc_deltaUi2.obj" \
	"$(INTDIR)\Calc_delUi.obj" \
	"$(INTDIR)\Calc_Lamda1_Stepm.obj" \
	"$(INTDIR)\Calc_LoadIncrement.obj" \
	"$(INTDIR)\Check_PossibleDisplacement.obj" \
	"$(INTDIR)\Compute_Curvature.obj" \
	"$(INTDIR)\Compute_ElementReactions_EL_1.obj" \
	"$(INTDIR)\Compute_ElementReactions_EL_2.obj" \
	"$(INTDIR)\Compute_StrainEnergy.obj" \
	"$(INTDIR)\Compute_UpdatedCoordinates.obj" \
	"$(INTDIR)\Compute_UpdatedState.obj" \
	"$(INTDIR)\Compute_uwthetaAtEnd.obj" \
	"$(INTDIR)\ConstitutiveMatrix_D.obj" \
	"$(INTDIR)\Convergence_Residual.obj" \
	"$(INTDIR)\Cubic_ArbitrarySi.obj" \
	"$(INTDIR)\CubicTangent_Length.obj" \
	"$(INTDIR)\DegreeElevate.obj" \
	"$(INTDIR)\DumpIntegerVar.obj" \
	"$(INTDIR)\DumpRealArray.obj" \
	"$(INTDIR)\DumpRealMatrix.obj" \
	"$(INTDIR)\DumpRealVar.obj" \
	"$(INTDIR)\DumpStringVar.obj" \
	"$(INTDIR)\DumpVar.obj" \
	"$(INTDIR)\Expand_BZCons_C0.obj" \
	"$(INTDIR)\Extract_Vector.obj" \
	"$(INTDIR)\ExtractEL_DispCon.obj" \
	"$(INTDIR)\Form_a_N_kc_N_AMat.obj" \
	"$(INTDIR)\Form_B_and_Tmatrices.obj" \
	"$(INTDIR)\Form_EBlocks.obj" \
	"$(INTDIR)\Form_EMatrix.obj" \
	"$(INTDIR)\Form_EtranDEplusG.obj" \
	"$(INTDIR)\Form_F_a_Part.obj" \
	"$(INTDIR)\Form_ForMom.obj" \
	"$(INTDIR)\Form_GBlocks.obj" \
	"$(INTDIR)\Form_GMatrix.obj" \
	"$(INTDIR)\Form_RealStrains_Ncoords.obj" \
	"$(INTDIR)\Form_RMatrix.obj" \
	"$(INTDIR)\Form_RotationMatrix.obj" \
	"$(INTDIR)\Form_Skew.obj" \
	"$(INTDIR)\Form_SMatrix.obj" \
	"$(INTDIR)\Form_ThetaAlfaTransMatrix.obj" \
	"$(INTDIR)\Form_ThetaConstants.obj" \
	"$(INTDIR)\Form_Wmatrix.obj" \
	"$(INTDIR)\FormIndex_EL2.obj" \
	"$(INTDIR)\GaussPtVal.obj" \
	"$(INTDIR)\Initialize_StateVector.obj" \
	"$(INTDIR)\Initiate_DegreeData.obj" \
	"$(INTDIR)\Initiate_ExtractionIndex.obj" \
	"$(INTDIR)\Initiate_SolutionData.obj" \
	"$(INTDIR)\Initiate_Support.obj" \
	"$(INTDIR)\Invert_A.obj" \
	"$(INTDIR)\InvertedTangentStiffness.obj" \
	"$(INTDIR)\LoadParamChange.obj" \
	"$(INTDIR)\Non_Singular_QQ.obj" \
	"$(INTDIR)\PlotDataEndw.obj" \
	"$(INTDIR)\Prog_NL_General3D_2ELs.obj" \
	"$(INTDIR)\Quad_QQ_LOAD_ASSEMBLE.obj" \
	"$(INTDIR)\Quad_QQ_LVY.obj" \
	"$(INTDIR)\Quad_QQ_STIF.obj" \
	"$(INTDIR)\Quad_QQ_STIF_ASSEMBLE.obj" \
	"$(INTDIR)\Resultat DesiredSteps.obj" \
	"$(INTDIR)\Resultat DesiredSteps_Bat.obj" \
	"$(INTDIR)\Resultat DesiredSteps_LIN.obj" \
	"$(INTDIR)\Resultat DesiredSteps_STR.obj" \
	"$(INTDIR)\Scigraph.obj" \
	"$(INTDIR)\Sgadmin.obj" \
	"$(INTDIR)\Sgdata.obj" \
	"$(INTDIR)\Sgdraw.obj" \
	"$(INTDIR)\Sglowlvl.obj" \
	"$(INTDIR)\Sgplot.obj" \
	"$(INTDIR)\SgXYPlot.obj" \
	"$(INTDIR)\Solve_AxEqB.obj" \
	"$(INTDIR)\StateatStartofIter.obj" \
	"$(INTDIR)\StressRecovery.obj" \
	"$(INTDIR)\TMB_Axes_Cur_Tor_Det.obj" \
	"$(INTDIR)\UpdateIter_Displace_Lambda.obj" \
	"$(INTDIR)\UpdateStep_Displace_Lambda.obj" \
	"$(INTDIR)\VectorAdd.obj" \
	"$(INTDIR)\VectorCrossProduct.obj" \
	"$(INTDIR)\VectorDotProduct.obj" \
	"$(INTDIR)\VectorNorm.obj" \
	"$(INTDIR)\VectorScale.obj" \
	"$(INTDIR)\VectorSubtract.obj" \
	"$(INTDIR)\Compute_DisRot_2ELModel.obj"

"$(OUTDIR)\OLD_Gen3D.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "OLD_Gen3D - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\OLD_Gen3D.exe"


CLEAN :
	-@erase "$(INTDIR)\Augment_Load_ArcLen.obj"
	-@erase "$(INTDIR)\Augment_STIF_ArcLen.obj"
	-@erase "$(INTDIR)\BernStein.obj"
	-@erase "$(INTDIR)\BernStein_IstDerivative.obj"
	-@erase "$(INTDIR)\Bez_QQ_EL_1.obj"
	-@erase "$(INTDIR)\Bez_QQ_EL_2.obj"
	-@erase "$(INTDIR)\Calc_Angles.obj"
	-@erase "$(INTDIR)\Calc_ArcLength_Step1.obj"
	-@erase "$(INTDIR)\Calc_ArcLength_Stepm.obj"
	-@erase "$(INTDIR)\Calc_deltaUi.obj"
	-@erase "$(INTDIR)\Calc_deltaUi1.obj"
	-@erase "$(INTDIR)\Calc_deltaUi2.obj"
	-@erase "$(INTDIR)\Calc_delUi.obj"
	-@erase "$(INTDIR)\Calc_Lamda1_Stepm.obj"
	-@erase "$(INTDIR)\Calc_LoadIncrement.obj"
	-@erase "$(INTDIR)\Check_PossibleDisplacement.obj"
	-@erase "$(INTDIR)\Compute_Curvature.obj"
	-@erase "$(INTDIR)\Compute_DisRot_2ELModel.obj"
	-@erase "$(INTDIR)\Compute_ElementReactions_EL_1.obj"
	-@erase "$(INTDIR)\Compute_ElementReactions_EL_2.obj"
	-@erase "$(INTDIR)\Compute_StrainEnergy.obj"
	-@erase "$(INTDIR)\Compute_UpdatedCoordinates.obj"
	-@erase "$(INTDIR)\Compute_UpdatedState.obj"
	-@erase "$(INTDIR)\Compute_uwthetaAtEnd.obj"
	-@erase "$(INTDIR)\ConstitutiveMatrix_D.obj"
	-@erase "$(INTDIR)\Convergence_Residual.obj"
	-@erase "$(INTDIR)\Cubic_ArbitrarySi.obj"
	-@erase "$(INTDIR)\CubicTangent_Length.obj"
	-@erase "$(INTDIR)\DeformationPlot.mod"
	-@erase "$(INTDIR)\DegreeElevate.obj"
	-@erase "$(INTDIR)\DF60.PDB"
	-@erase "$(INTDIR)\DumpIntegerVar.obj"
	-@erase "$(INTDIR)\DumpRealArray.obj"
	-@erase "$(INTDIR)\DumpRealMatrix.obj"
	-@erase "$(INTDIR)\DumpRealVar.obj"
	-@erase "$(INTDIR)\DumpStringVar.obj"
	-@erase "$(INTDIR)\DumpVar.obj"
	-@erase "$(INTDIR)\Expand_BZCons_C0.obj"
	-@erase "$(INTDIR)\Extract_Vector.obj"
	-@erase "$(INTDIR)\ExtractEL_DispCon.obj"
	-@erase "$(INTDIR)\Form_a_N_kc_N_AMat.obj"
	-@erase "$(INTDIR)\Form_B_and_Tmatrices.obj"
	-@erase "$(INTDIR)\Form_EBlocks.obj"
	-@erase "$(INTDIR)\Form_EMatrix.obj"
	-@erase "$(INTDIR)\Form_EtranDEplusG.obj"
	-@erase "$(INTDIR)\Form_F_a_Part.obj"
	-@erase "$(INTDIR)\Form_ForMom.obj"
	-@erase "$(INTDIR)\Form_GBlocks.obj"
	-@erase "$(INTDIR)\Form_GMatrix.obj"
	-@erase "$(INTDIR)\Form_RealStrains_Ncoords.obj"
	-@erase "$(INTDIR)\Form_RMatrix.obj"
	-@erase "$(INTDIR)\Form_RotationMatrix.obj"
	-@erase "$(INTDIR)\Form_Skew.obj"
	-@erase "$(INTDIR)\Form_SMatrix.obj"
	-@erase "$(INTDIR)\Form_ThetaAlfaTransMatrix.obj"
	-@erase "$(INTDIR)\Form_ThetaConstants.obj"
	-@erase "$(INTDIR)\Form_Wmatrix.obj"
	-@erase "$(INTDIR)\FormIndex_EL2.obj"
	-@erase "$(INTDIR)\GaussPtVal.obj"
	-@erase "$(INTDIR)\Initialize_StateVector.obj"
	-@erase "$(INTDIR)\Initiate_DegreeData.obj"
	-@erase "$(INTDIR)\Initiate_ExtractionIndex.obj"
	-@erase "$(INTDIR)\Initiate_SolutionData.obj"
	-@erase "$(INTDIR)\Initiate_Support.obj"
	-@erase "$(INTDIR)\Invert_A.obj"
	-@erase "$(INTDIR)\InvertedTangentStiffness.obj"
	-@erase "$(INTDIR)\LoadParamChange.obj"
	-@erase "$(INTDIR)\Non_Singular_QQ.obj"
	-@erase "$(INTDIR)\PlotDataEndw.obj"
	-@erase "$(INTDIR)\Prog_NL_General3D_2ELs.obj"
	-@erase "$(INTDIR)\Quad_QQ_LOAD_ASSEMBLE.obj"
	-@erase "$(INTDIR)\Quad_QQ_LVY.obj"
	-@erase "$(INTDIR)\Quad_QQ_STIF.obj"
	-@erase "$(INTDIR)\Quad_QQ_STIF_ASSEMBLE.obj"
	-@erase "$(INTDIR)\Resultat DesiredSteps.obj"
	-@erase "$(INTDIR)\Resultat DesiredSteps_Bat.obj"
	-@erase "$(INTDIR)\Resultat DesiredSteps_LIN.obj"
	-@erase "$(INTDIR)\Resultat DesiredSteps_STR.obj"
	-@erase "$(INTDIR)\SCIGRAPH.mod"
	-@erase "$(INTDIR)\Scigraph.obj"
	-@erase "$(INTDIR)\SGADMIN.mod"
	-@erase "$(INTDIR)\Sgadmin.obj"
	-@erase "$(INTDIR)\SGDATA.MOD"
	-@erase "$(INTDIR)\Sgdata.obj"
	-@erase "$(INTDIR)\SGDRAW.MOD"
	-@erase "$(INTDIR)\Sgdraw.obj"
	-@erase "$(INTDIR)\SGLOWLVL.MOD"
	-@erase "$(INTDIR)\Sglowlvl.obj"
	-@erase "$(INTDIR)\SGPLOT.mod"
	-@erase "$(INTDIR)\Sgplot.obj"
	-@erase "$(INTDIR)\SgXYPlot.obj"
	-@erase "$(INTDIR)\Solve_AxEqB.obj"
	-@erase "$(INTDIR)\StateatStartofIter.obj"
	-@erase "$(INTDIR)\StressRecovery.obj"
	-@erase "$(INTDIR)\TMB_Axes_Cur_Tor_Det.obj"
	-@erase "$(INTDIR)\UpdateIter_Displace_Lambda.obj"
	-@erase "$(INTDIR)\UpdateStep_Displace_Lambda.obj"
	-@erase "$(INTDIR)\VectorAdd.obj"
	-@erase "$(INTDIR)\VectorCrossProduct.obj"
	-@erase "$(INTDIR)\VectorDotProduct.obj"
	-@erase "$(INTDIR)\VectorNorm.obj"
	-@erase "$(INTDIR)\VectorScale.obj"
	-@erase "$(INTDIR)\VectorSubtract.obj"
	-@erase "$(OUTDIR)\OLD_Gen3D.exe"
	-@erase "$(OUTDIR)\OLD_Gen3D.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90_PROJ=/check:bounds /compile_only /debug:full /libs:qwin /nologo /traceback /warn:argument_checking /warn:nofileopt /module:"Debug/" /object:"Debug/" /pdbfile:"Debug/DF60.PDB" 
F90_OBJS=.\Debug/
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\OLD_Gen3D.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\OLD_Gen3D.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"WinMainCRTStartup" /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\OLD_Gen3D.pdb" /debug /machine:I386 /nodefaultlib:"dfconsol.lib" /out:"$(OUTDIR)\OLD_Gen3D.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\Augment_Load_ArcLen.obj" \
	"$(INTDIR)\Augment_STIF_ArcLen.obj" \
	"$(INTDIR)\BernStein.obj" \
	"$(INTDIR)\BernStein_IstDerivative.obj" \
	"$(INTDIR)\Bez_QQ_EL_1.obj" \
	"$(INTDIR)\Bez_QQ_EL_2.obj" \
	"$(INTDIR)\Calc_Angles.obj" \
	"$(INTDIR)\Calc_ArcLength_Step1.obj" \
	"$(INTDIR)\Calc_ArcLength_Stepm.obj" \
	"$(INTDIR)\Calc_deltaUi.obj" \
	"$(INTDIR)\Calc_deltaUi1.obj" \
	"$(INTDIR)\Calc_deltaUi2.obj" \
	"$(INTDIR)\Calc_delUi.obj" \
	"$(INTDIR)\Calc_Lamda1_Stepm.obj" \
	"$(INTDIR)\Calc_LoadIncrement.obj" \
	"$(INTDIR)\Check_PossibleDisplacement.obj" \
	"$(INTDIR)\Compute_Curvature.obj" \
	"$(INTDIR)\Compute_ElementReactions_EL_1.obj" \
	"$(INTDIR)\Compute_ElementReactions_EL_2.obj" \
	"$(INTDIR)\Compute_StrainEnergy.obj" \
	"$(INTDIR)\Compute_UpdatedCoordinates.obj" \
	"$(INTDIR)\Compute_UpdatedState.obj" \
	"$(INTDIR)\Compute_uwthetaAtEnd.obj" \
	"$(INTDIR)\ConstitutiveMatrix_D.obj" \
	"$(INTDIR)\Convergence_Residual.obj" \
	"$(INTDIR)\Cubic_ArbitrarySi.obj" \
	"$(INTDIR)\CubicTangent_Length.obj" \
	"$(INTDIR)\DegreeElevate.obj" \
	"$(INTDIR)\DumpIntegerVar.obj" \
	"$(INTDIR)\DumpRealArray.obj" \
	"$(INTDIR)\DumpRealMatrix.obj" \
	"$(INTDIR)\DumpRealVar.obj" \
	"$(INTDIR)\DumpStringVar.obj" \
	"$(INTDIR)\DumpVar.obj" \
	"$(INTDIR)\Expand_BZCons_C0.obj" \
	"$(INTDIR)\Extract_Vector.obj" \
	"$(INTDIR)\ExtractEL_DispCon.obj" \
	"$(INTDIR)\Form_a_N_kc_N_AMat.obj" \
	"$(INTDIR)\Form_B_and_Tmatrices.obj" \
	"$(INTDIR)\Form_EBlocks.obj" \
	"$(INTDIR)\Form_EMatrix.obj" \
	"$(INTDIR)\Form_EtranDEplusG.obj" \
	"$(INTDIR)\Form_F_a_Part.obj" \
	"$(INTDIR)\Form_ForMom.obj" \
	"$(INTDIR)\Form_GBlocks.obj" \
	"$(INTDIR)\Form_GMatrix.obj" \
	"$(INTDIR)\Form_RealStrains_Ncoords.obj" \
	"$(INTDIR)\Form_RMatrix.obj" \
	"$(INTDIR)\Form_RotationMatrix.obj" \
	"$(INTDIR)\Form_Skew.obj" \
	"$(INTDIR)\Form_SMatrix.obj" \
	"$(INTDIR)\Form_ThetaAlfaTransMatrix.obj" \
	"$(INTDIR)\Form_ThetaConstants.obj" \
	"$(INTDIR)\Form_Wmatrix.obj" \
	"$(INTDIR)\FormIndex_EL2.obj" \
	"$(INTDIR)\GaussPtVal.obj" \
	"$(INTDIR)\Initialize_StateVector.obj" \
	"$(INTDIR)\Initiate_DegreeData.obj" \
	"$(INTDIR)\Initiate_ExtractionIndex.obj" \
	"$(INTDIR)\Initiate_SolutionData.obj" \
	"$(INTDIR)\Initiate_Support.obj" \
	"$(INTDIR)\Invert_A.obj" \
	"$(INTDIR)\InvertedTangentStiffness.obj" \
	"$(INTDIR)\LoadParamChange.obj" \
	"$(INTDIR)\Non_Singular_QQ.obj" \
	"$(INTDIR)\PlotDataEndw.obj" \
	"$(INTDIR)\Prog_NL_General3D_2ELs.obj" \
	"$(INTDIR)\Quad_QQ_LOAD_ASSEMBLE.obj" \
	"$(INTDIR)\Quad_QQ_LVY.obj" \
	"$(INTDIR)\Quad_QQ_STIF.obj" \
	"$(INTDIR)\Quad_QQ_STIF_ASSEMBLE.obj" \
	"$(INTDIR)\Resultat DesiredSteps.obj" \
	"$(INTDIR)\Resultat DesiredSteps_Bat.obj" \
	"$(INTDIR)\Resultat DesiredSteps_LIN.obj" \
	"$(INTDIR)\Resultat DesiredSteps_STR.obj" \
	"$(INTDIR)\Scigraph.obj" \
	"$(INTDIR)\Sgadmin.obj" \
	"$(INTDIR)\Sgdata.obj" \
	"$(INTDIR)\Sgdraw.obj" \
	"$(INTDIR)\Sglowlvl.obj" \
	"$(INTDIR)\Sgplot.obj" \
	"$(INTDIR)\SgXYPlot.obj" \
	"$(INTDIR)\Solve_AxEqB.obj" \
	"$(INTDIR)\StateatStartofIter.obj" \
	"$(INTDIR)\StressRecovery.obj" \
	"$(INTDIR)\TMB_Axes_Cur_Tor_Det.obj" \
	"$(INTDIR)\UpdateIter_Displace_Lambda.obj" \
	"$(INTDIR)\UpdateStep_Displace_Lambda.obj" \
	"$(INTDIR)\VectorAdd.obj" \
	"$(INTDIR)\VectorCrossProduct.obj" \
	"$(INTDIR)\VectorDotProduct.obj" \
	"$(INTDIR)\VectorNorm.obj" \
	"$(INTDIR)\VectorScale.obj" \
	"$(INTDIR)\VectorSubtract.obj" \
	"$(INTDIR)\Compute_DisRot_2ELModel.obj"

"$(OUTDIR)\OLD_Gen3D.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("OLD_Gen3D.dep")
!INCLUDE "OLD_Gen3D.dep"
!ELSE 
!MESSAGE Warning: cannot find "OLD_Gen3D.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "OLD_Gen3D - Win32 Release" || "$(CFG)" == "OLD_Gen3D - Win32 Debug"
SOURCE=.\Augment_Load_ArcLen.f

"$(INTDIR)\Augment_Load_ArcLen.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Augment_STIF_ArcLen.f

"$(INTDIR)\Augment_STIF_ArcLen.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\BernStein.for

"$(INTDIR)\BernStein.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\BernStein_IstDerivative.for

"$(INTDIR)\BernStein_IstDerivative.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Bez_QQ_EL_1.for

"$(INTDIR)\Bez_QQ_EL_1.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Bez_QQ_EL_2.for

"$(INTDIR)\Bez_QQ_EL_2.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Calc_Angles.for

"$(INTDIR)\Calc_Angles.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Calc_ArcLength_Step1.for

"$(INTDIR)\Calc_ArcLength_Step1.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Calc_ArcLength_Stepm.for

"$(INTDIR)\Calc_ArcLength_Stepm.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Calc_deltaUi.for

"$(INTDIR)\Calc_deltaUi.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Calc_deltaUi1.for

"$(INTDIR)\Calc_deltaUi1.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Calc_deltaUi2.for

"$(INTDIR)\Calc_deltaUi2.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Calc_delUi.for

"$(INTDIR)\Calc_delUi.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Calc_Lamda1_Stepm.for

"$(INTDIR)\Calc_Lamda1_Stepm.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Calc_LoadIncrement.for

"$(INTDIR)\Calc_LoadIncrement.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Check_PossibleDisplacement.for

"$(INTDIR)\Check_PossibleDisplacement.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Compute_Curvature.f

"$(INTDIR)\Compute_Curvature.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Compute_DisRot_2ELModel.f

"$(INTDIR)\Compute_DisRot_2ELModel.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Compute_ElementReactions_EL_1.f

"$(INTDIR)\Compute_ElementReactions_EL_1.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Compute_ElementReactions_EL_2.f

"$(INTDIR)\Compute_ElementReactions_EL_2.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Compute_StrainEnergy.f

"$(INTDIR)\Compute_StrainEnergy.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Compute_UpdatedCoordinates.for

"$(INTDIR)\Compute_UpdatedCoordinates.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Compute_UpdatedState.for

"$(INTDIR)\Compute_UpdatedState.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Compute_uwthetaAtEnd.f

"$(INTDIR)\Compute_uwthetaAtEnd.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ConstitutiveMatrix_D.for

"$(INTDIR)\ConstitutiveMatrix_D.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Convergence_Residual.for

"$(INTDIR)\Convergence_Residual.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Cubic_ArbitrarySi.for

"$(INTDIR)\Cubic_ArbitrarySi.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\CubicTangent_Length.for

"$(INTDIR)\CubicTangent_Length.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DegreeElevate.for

"$(INTDIR)\DegreeElevate.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DumpIntegerVar.for

"$(INTDIR)\DumpIntegerVar.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DumpRealArray.for

"$(INTDIR)\DumpRealArray.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DumpRealMatrix.for

"$(INTDIR)\DumpRealMatrix.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DumpRealVar.for

"$(INTDIR)\DumpRealVar.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DumpStringVar.for

"$(INTDIR)\DumpStringVar.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DumpVar.for

"$(INTDIR)\DumpVar.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Expand_BZCons_C0.for

"$(INTDIR)\Expand_BZCons_C0.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Extract_Vector.f

"$(INTDIR)\Extract_Vector.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ExtractEL_DispCon.for

"$(INTDIR)\ExtractEL_DispCon.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Form_a_N_kc_N_AMat.f

"$(INTDIR)\Form_a_N_kc_N_AMat.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Form_B_and_Tmatrices.f

"$(INTDIR)\Form_B_and_Tmatrices.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Form_EBlocks.f

"$(INTDIR)\Form_EBlocks.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Form_EMatrix.f

"$(INTDIR)\Form_EMatrix.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Form_EtranDEplusG.f

"$(INTDIR)\Form_EtranDEplusG.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Form_F_a_Part.f

"$(INTDIR)\Form_F_a_Part.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Form_ForMom.f

"$(INTDIR)\Form_ForMom.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Form_GBlocks.f

"$(INTDIR)\Form_GBlocks.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Form_GMatrix.f

"$(INTDIR)\Form_GMatrix.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Form_RealStrains_Ncoords.f

"$(INTDIR)\Form_RealStrains_Ncoords.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Form_RMatrix.f

"$(INTDIR)\Form_RMatrix.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Form_RotationMatrix.f

"$(INTDIR)\Form_RotationMatrix.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Form_Skew.f

"$(INTDIR)\Form_Skew.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Form_SMatrix.f

"$(INTDIR)\Form_SMatrix.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Form_ThetaAlfaTransMatrix.f

"$(INTDIR)\Form_ThetaAlfaTransMatrix.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Form_ThetaConstants.f

"$(INTDIR)\Form_ThetaConstants.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Form_Wmatrix.f

"$(INTDIR)\Form_Wmatrix.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\FormIndex_EL2.f

"$(INTDIR)\FormIndex_EL2.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\GaussPtVal.f

"$(INTDIR)\GaussPtVal.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Initialize_StateVector.for

"$(INTDIR)\Initialize_StateVector.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Initiate_DegreeData.for

"$(INTDIR)\Initiate_DegreeData.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Initiate_ExtractionIndex.for

"$(INTDIR)\Initiate_ExtractionIndex.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Initiate_SolutionData.for

"$(INTDIR)\Initiate_SolutionData.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Initiate_Support.for

"$(INTDIR)\Initiate_Support.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Invert_A.for

"$(INTDIR)\Invert_A.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\InvertedTangentStiffness.for

"$(INTDIR)\InvertedTangentStiffness.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\LoadParamChange.for

"$(INTDIR)\LoadParamChange.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Non_Singular_QQ.for

"$(INTDIR)\Non_Singular_QQ.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\PlotDataEndw.for

"$(INTDIR)\PlotDataEndw.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Prog_NL_General3D_2ELs.f

"$(INTDIR)\Prog_NL_General3D_2ELs.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Quad_QQ_LOAD_ASSEMBLE.f

"$(INTDIR)\Quad_QQ_LOAD_ASSEMBLE.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Quad_QQ_LVY.f

"$(INTDIR)\Quad_QQ_LVY.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Quad_QQ_STIF.f

"$(INTDIR)\Quad_QQ_STIF.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Quad_QQ_STIF_ASSEMBLE.f

"$(INTDIR)\Quad_QQ_STIF_ASSEMBLE.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=".\Resultat DesiredSteps.for"

"$(INTDIR)\Resultat DesiredSteps.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=".\Resultat DesiredSteps_Bat.for"

"$(INTDIR)\Resultat DesiredSteps_Bat.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=".\Resultat DesiredSteps_LIN.for"

"$(INTDIR)\Resultat DesiredSteps_LIN.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=".\Resultat DesiredSteps_STR.for"

"$(INTDIR)\Resultat DesiredSteps_STR.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Scigraph.f90

!IF  "$(CFG)" == "OLD_Gen3D - Win32 Release"


"$(INTDIR)\Scigraph.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OLD_Gen3D - Win32 Debug"

F90_MODOUT=\
	"SCIGRAPH"


"$(INTDIR)\Scigraph.obj"	"$(INTDIR)\SCIGRAPH.mod" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SGPLOT.mod" "$(INTDIR)\SGADMIN.mod"
	$(F90) $(F90_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\Sgadmin.f90

!IF  "$(CFG)" == "OLD_Gen3D - Win32 Release"


"$(INTDIR)\Sgadmin.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OLD_Gen3D - Win32 Debug"

F90_MODOUT=\
	"SGADMIN"


"$(INTDIR)\Sgadmin.obj"	"$(INTDIR)\SGADMIN.mod" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SGDRAW.MOD"
	$(F90) $(F90_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\Sgdata.f90

!IF  "$(CFG)" == "OLD_Gen3D - Win32 Release"


"$(INTDIR)\Sgdata.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OLD_Gen3D - Win32 Debug"

F90_MODOUT=\
	"SGDATA"


"$(INTDIR)\Sgdata.obj"	"$(INTDIR)\SGDATA.MOD" : $(SOURCE) "$(INTDIR)"
	$(F90) $(F90_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\Sgdraw.f90

!IF  "$(CFG)" == "OLD_Gen3D - Win32 Release"


"$(INTDIR)\Sgdraw.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OLD_Gen3D - Win32 Debug"

F90_MODOUT=\
	"SGDRAW"


"$(INTDIR)\Sgdraw.obj"	"$(INTDIR)\SGDRAW.MOD" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SGLOWLVL.MOD"
	$(F90) $(F90_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\Sglowlvl.f90

!IF  "$(CFG)" == "OLD_Gen3D - Win32 Release"


"$(INTDIR)\Sglowlvl.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OLD_Gen3D - Win32 Debug"

F90_MODOUT=\
	"SGLOWLVL"


"$(INTDIR)\Sglowlvl.obj"	"$(INTDIR)\SGLOWLVL.MOD" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SGDATA.MOD"
	$(F90) $(F90_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\Sgplot.f90

!IF  "$(CFG)" == "OLD_Gen3D - Win32 Release"


"$(INTDIR)\Sgplot.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OLD_Gen3D - Win32 Debug"

F90_MODOUT=\
	"SGPLOT"


"$(INTDIR)\Sgplot.obj"	"$(INTDIR)\SGPLOT.mod" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SGDRAW.MOD"
	$(F90) $(F90_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\SgXYPlot.f90

!IF  "$(CFG)" == "OLD_Gen3D - Win32 Release"


"$(INTDIR)\SgXYPlot.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OLD_Gen3D - Win32 Debug"

F90_MODOUT=\
	"DeformationPlot"


"$(INTDIR)\SgXYPlot.obj"	"$(INTDIR)\DeformationPlot.mod" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SCIGRAPH.mod"
	$(F90) $(F90_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\Solve_AxEqB.f

"$(INTDIR)\Solve_AxEqB.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\StateatStartofIter.for

"$(INTDIR)\StateatStartofIter.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\StressRecovery.f

"$(INTDIR)\StressRecovery.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\TMB_Axes_Cur_Tor_Det.f

"$(INTDIR)\TMB_Axes_Cur_Tor_Det.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\UpdateIter_Displace_Lambda.for

"$(INTDIR)\UpdateIter_Displace_Lambda.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\UpdateStep_Displace_Lambda.for

"$(INTDIR)\UpdateStep_Displace_Lambda.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\VectorAdd.f

"$(INTDIR)\VectorAdd.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\VectorCrossProduct.f

"$(INTDIR)\VectorCrossProduct.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\VectorDotProduct.f

"$(INTDIR)\VectorDotProduct.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\VectorNorm.f

"$(INTDIR)\VectorNorm.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\VectorScale.f

"$(INTDIR)\VectorScale.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\VectorSubtract.f

"$(INTDIR)\VectorSubtract.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

