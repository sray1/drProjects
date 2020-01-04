# Microsoft Developer Studio Generated NMAKE File, Based on Shell.dsp
!IF "$(CFG)" == ""
CFG=Shell - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Shell - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Shell - Win32 Release" && "$(CFG)" != "Shell - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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

!IF  "$(CFG)" == "Shell - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\Shell.exe"


CLEAN :
	-@erase "$(INTDIR)\BernStein.obj"
	-@erase "$(INTDIR)\BernStein_IstDerivative.obj"
	-@erase "$(INTDIR)\Bez_QQ_EL_1_Str.obj"
	-@erase "$(INTDIR)\Bez_QQ_EL_1Pal.obj"
	-@erase "$(INTDIR)\Calc_A1_Hat.obj"
	-@erase "$(INTDIR)\Calc_A2_Hat.obj"
	-@erase "$(INTDIR)\Calc_Angles.obj"
	-@erase "$(INTDIR)\Calc_ArcLength_Step1.obj"
	-@erase "$(INTDIR)\Calc_ArcLength_Stepm.obj"
	-@erase "$(INTDIR)\Calc_deltaUi1.obj"
	-@erase "$(INTDIR)\Calc_deltaUi2.obj"
	-@erase "$(INTDIR)\Calc_delUi.obj"
	-@erase "$(INTDIR)\Calc_Lamda1_Stepm.obj"
	-@erase "$(INTDIR)\Calc_ReferenceProps.obj"
	-@erase "$(INTDIR)\Calc_X11_Hat.obj"
	-@erase "$(INTDIR)\Calc_X12_Hat.obj"
	-@erase "$(INTDIR)\Calc_X22_Hat.obj"
	-@erase "$(INTDIR)\CalcCoords_at_a_Pt.obj"
	-@erase "$(INTDIR)\CalcDis_at_a_Pt.obj"
	-@erase "$(INTDIR)\CalcRot_at_a_Pt.obj"
	-@erase "$(INTDIR)\Check_PossibleDisplacement.obj"
	-@erase "$(INTDIR)\Compute_StrainEnergy.obj"
	-@erase "$(INTDIR)\Compute_uwthetaAtEnd.obj"
	-@erase "$(INTDIR)\Convergence_Residual.obj"
	-@erase "$(INTDIR)\Define_ElementTypes.obj"
	-@erase "$(INTDIR)\DeformOut_MatLab.obj"
	-@erase "$(INTDIR)\DeformOut_MatLab_Pal.obj"
	-@erase "$(INTDIR)\DeformOut_MatLab_Str.obj"
	-@erase "$(INTDIR)\DegreeElevate2D.obj"
	-@erase "$(INTDIR)\DifferenceOp_1.obj"
	-@erase "$(INTDIR)\DifferenceOp_2.obj"
	-@erase "$(INTDIR)\DumpIntegerArray.obj"
	-@erase "$(INTDIR)\DumpIntegerVar.obj"
	-@erase "$(INTDIR)\DumpRealArray.obj"
	-@erase "$(INTDIR)\DumpRealMatrix.obj"
	-@erase "$(INTDIR)\DumpRealMatrix3.obj"
	-@erase "$(INTDIR)\DumpRealVar.obj"
	-@erase "$(INTDIR)\DumpStringVar.obj"
	-@erase "$(INTDIR)\DumpVar.obj"
	-@erase "$(INTDIR)\Expand_BZCons_C0.obj"
	-@erase "$(INTDIR)\ExtractEL_DispCon.obj"
	-@erase "$(INTDIR)\Form_a_N_kc_N_AMat.obj"
	-@erase "$(INTDIR)\Form_B_and_Tmatrices.obj"
	-@erase "$(INTDIR)\Form_ConstitutiveMatrix.obj"
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
	-@erase "$(INTDIR)\Get_ElementCoords.obj"
	-@erase "$(INTDIR)\Get_Geometry.obj"
	-@erase "$(INTDIR)\Get_Loads.obj"
	-@erase "$(INTDIR)\Get_Loads_Pal.obj"
	-@erase "$(INTDIR)\Get_Loads_Pal_D.obj"
	-@erase "$(INTDIR)\Get_Loads_Str.obj"
	-@erase "$(INTDIR)\Get_Loads_Str_D.obj"
	-@erase "$(INTDIR)\Get_Material.obj"
	-@erase "$(INTDIR)\Get_ReferenceInfoataGaussPt.obj"
	-@erase "$(INTDIR)\Get_SupportedDOFs.obj"
	-@erase "$(INTDIR)\Get_SupportedDOFs_Pal.obj"
	-@erase "$(INTDIR)\Get_SupportedDOFs_Pal_D.obj"
	-@erase "$(INTDIR)\Get_SupportedDOFs_Str.obj"
	-@erase "$(INTDIR)\Get_SupportedDOFs_Str_D.obj"
	-@erase "$(INTDIR)\Initialize_StateVector.obj"
	-@erase "$(INTDIR)\Initiate_ExtractionIndex.obj"
	-@erase "$(INTDIR)\Initiate_ExtractionIndex_D.obj"
	-@erase "$(INTDIR)\Initiate_SolutionData.obj"
	-@erase "$(INTDIR)\Invert_A.obj"
	-@erase "$(INTDIR)\LoadParamChange.obj"
	-@erase "$(INTDIR)\LoadStep_1_iter_1.obj"
	-@erase "$(INTDIR)\LoadStep_n_iter_1.obj"
	-@erase "$(INTDIR)\LoadStep_n_iter_m.obj"
	-@erase "$(INTDIR)\Non_Singular_QQ.obj"
	-@erase "$(INTDIR)\PhaseI_Shell.obj"
	-@erase "$(INTDIR)\PhaseII_Shell.obj"
	-@erase "$(INTDIR)\PlotDataEndw.obj"
	-@erase "$(INTDIR)\ProgShell_NL_Total3D_2ELs.obj"
	-@erase "$(INTDIR)\Put_ReferenceInfo_AllGauss.obj"
	-@erase "$(INTDIR)\Put_ReferenceInfoataGaussPt.obj"
	-@erase "$(INTDIR)\PutGetRefPropsatGaussPt.obj"
	-@erase "$(INTDIR)\PutGetRotCur.obj"
	-@erase "$(INTDIR)\PutGetTBatGaussPt.obj"
	-@erase "$(INTDIR)\Quad_QQ_LOAD_ASSEMBLE.obj"
	-@erase "$(INTDIR)\Quad_QQ_LVY.obj"
	-@erase "$(INTDIR)\Quad_QQ_STIF.obj"
	-@erase "$(INTDIR)\Quad_QQ_STIF_ASSEMBLE.obj"
	-@erase "$(INTDIR)\Set_ExampleType.obj"
	-@erase "$(INTDIR)\Set_Files.obj"
	-@erase "$(INTDIR)\Set_Files_Scratch.obj"
	-@erase "$(INTDIR)\Set_IntegerControls.obj"
	-@erase "$(INTDIR)\Set_TimeDate.obj"
	-@erase "$(INTDIR)\Set_WorkArrayPointers.obj"
	-@erase "$(INTDIR)\Solve_AxEqB.obj"
	-@erase "$(INTDIR)\Solve_AxEqB_Drill.obj"
	-@erase "$(INTDIR)\StateatStartofIter.obj"
	-@erase "$(INTDIR)\UpdateIter_Displace_Lambda.obj"
	-@erase "$(INTDIR)\UpdateStep_Displace_Lambda.obj"
	-@erase "$(INTDIR)\VectorAdd.obj"
	-@erase "$(INTDIR)\VectorCrossProduct.obj"
	-@erase "$(INTDIR)\VectorDotProduct.obj"
	-@erase "$(INTDIR)\VectorExtract_Matrix2D.obj"
	-@erase "$(INTDIR)\VectorExtract_Vector.obj"
	-@erase "$(INTDIR)\VectorInsert_Vector.obj"
	-@erase "$(INTDIR)\VectorNorm.obj"
	-@erase "$(INTDIR)\VectorScale.obj"
	-@erase "$(INTDIR)\VectorSubtract.obj"
	-@erase "$(OUTDIR)\Shell.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90_PROJ=/compile_only /libs:qwin /nologo /warn:nofileopt /module:"Release/" /object:"Release/" 
F90_OBJS=.\Release/
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\Shell.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Shell.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"WinMainCRTStartup" /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\Shell.pdb" /machine:I386 /nodefaultlib:"dfconsol.lib" /out:"$(OUTDIR)\Shell.exe" 
LINK32_OBJS= \
	"$(INTDIR)\BernStein.obj" \
	"$(INTDIR)\BernStein_IstDerivative.obj" \
	"$(INTDIR)\Bez_QQ_EL_1_Str.obj" \
	"$(INTDIR)\Bez_QQ_EL_1Pal.obj" \
	"$(INTDIR)\Calc_A1_Hat.obj" \
	"$(INTDIR)\Calc_A2_Hat.obj" \
	"$(INTDIR)\Calc_Angles.obj" \
	"$(INTDIR)\Calc_ArcLength_Step1.obj" \
	"$(INTDIR)\Calc_ArcLength_Stepm.obj" \
	"$(INTDIR)\Calc_deltaUi1.obj" \
	"$(INTDIR)\Calc_deltaUi2.obj" \
	"$(INTDIR)\Calc_delUi.obj" \
	"$(INTDIR)\Calc_Lamda1_Stepm.obj" \
	"$(INTDIR)\Calc_ReferenceProps.obj" \
	"$(INTDIR)\Calc_X11_Hat.obj" \
	"$(INTDIR)\Calc_X12_Hat.obj" \
	"$(INTDIR)\Calc_X22_Hat.obj" \
	"$(INTDIR)\CalcCoords_at_a_Pt.obj" \
	"$(INTDIR)\CalcDis_at_a_Pt.obj" \
	"$(INTDIR)\CalcRot_at_a_Pt.obj" \
	"$(INTDIR)\Check_PossibleDisplacement.obj" \
	"$(INTDIR)\Compute_StrainEnergy.obj" \
	"$(INTDIR)\Compute_uwthetaAtEnd.obj" \
	"$(INTDIR)\Convergence_Residual.obj" \
	"$(INTDIR)\Define_ElementTypes.obj" \
	"$(INTDIR)\DeformOut_MatLab.obj" \
	"$(INTDIR)\DeformOut_MatLab_Pal.obj" \
	"$(INTDIR)\DeformOut_MatLab_Str.obj" \
	"$(INTDIR)\DegreeElevate2D.obj" \
	"$(INTDIR)\DifferenceOp_1.obj" \
	"$(INTDIR)\DifferenceOp_2.obj" \
	"$(INTDIR)\DumpIntegerArray.obj" \
	"$(INTDIR)\DumpIntegerVar.obj" \
	"$(INTDIR)\DumpRealArray.obj" \
	"$(INTDIR)\DumpRealMatrix.obj" \
	"$(INTDIR)\DumpRealMatrix3.obj" \
	"$(INTDIR)\DumpRealVar.obj" \
	"$(INTDIR)\DumpStringVar.obj" \
	"$(INTDIR)\DumpVar.obj" \
	"$(INTDIR)\Expand_BZCons_C0.obj" \
	"$(INTDIR)\ExtractEL_DispCon.obj" \
	"$(INTDIR)\Form_a_N_kc_N_AMat.obj" \
	"$(INTDIR)\Form_B_and_Tmatrices.obj" \
	"$(INTDIR)\Form_ConstitutiveMatrix.obj" \
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
	"$(INTDIR)\Get_ElementCoords.obj" \
	"$(INTDIR)\Get_Geometry.obj" \
	"$(INTDIR)\Get_Loads.obj" \
	"$(INTDIR)\Get_Loads_Pal.obj" \
	"$(INTDIR)\Get_Loads_Pal_D.obj" \
	"$(INTDIR)\Get_Loads_Str.obj" \
	"$(INTDIR)\Get_Loads_Str_D.obj" \
	"$(INTDIR)\Get_Material.obj" \
	"$(INTDIR)\Get_ReferenceInfoataGaussPt.obj" \
	"$(INTDIR)\Get_SupportedDOFs.obj" \
	"$(INTDIR)\Get_SupportedDOFs_Pal.obj" \
	"$(INTDIR)\Get_SupportedDOFs_Pal_D.obj" \
	"$(INTDIR)\Get_SupportedDOFs_Str.obj" \
	"$(INTDIR)\Get_SupportedDOFs_Str_D.obj" \
	"$(INTDIR)\Initialize_StateVector.obj" \
	"$(INTDIR)\Initiate_ExtractionIndex.obj" \
	"$(INTDIR)\Initiate_ExtractionIndex_D.obj" \
	"$(INTDIR)\Initiate_SolutionData.obj" \
	"$(INTDIR)\Invert_A.obj" \
	"$(INTDIR)\LoadParamChange.obj" \
	"$(INTDIR)\LoadStep_1_iter_1.obj" \
	"$(INTDIR)\LoadStep_n_iter_1.obj" \
	"$(INTDIR)\LoadStep_n_iter_m.obj" \
	"$(INTDIR)\Non_Singular_QQ.obj" \
	"$(INTDIR)\PhaseI_Shell.obj" \
	"$(INTDIR)\PhaseII_Shell.obj" \
	"$(INTDIR)\PlotDataEndw.obj" \
	"$(INTDIR)\ProgShell_NL_Total3D_2ELs.obj" \
	"$(INTDIR)\Put_ReferenceInfo_AllGauss.obj" \
	"$(INTDIR)\Put_ReferenceInfoataGaussPt.obj" \
	"$(INTDIR)\PutGetRefPropsatGaussPt.obj" \
	"$(INTDIR)\PutGetRotCur.obj" \
	"$(INTDIR)\PutGetTBatGaussPt.obj" \
	"$(INTDIR)\Quad_QQ_LOAD_ASSEMBLE.obj" \
	"$(INTDIR)\Quad_QQ_LVY.obj" \
	"$(INTDIR)\Quad_QQ_STIF.obj" \
	"$(INTDIR)\Quad_QQ_STIF_ASSEMBLE.obj" \
	"$(INTDIR)\Set_ExampleType.obj" \
	"$(INTDIR)\Set_Files.obj" \
	"$(INTDIR)\Set_Files_Scratch.obj" \
	"$(INTDIR)\Set_IntegerControls.obj" \
	"$(INTDIR)\Set_TimeDate.obj" \
	"$(INTDIR)\Set_WorkArrayPointers.obj" \
	"$(INTDIR)\Solve_AxEqB.obj" \
	"$(INTDIR)\Solve_AxEqB_Drill.obj" \
	"$(INTDIR)\StateatStartofIter.obj" \
	"$(INTDIR)\UpdateIter_Displace_Lambda.obj" \
	"$(INTDIR)\UpdateStep_Displace_Lambda.obj" \
	"$(INTDIR)\VectorAdd.obj" \
	"$(INTDIR)\VectorCrossProduct.obj" \
	"$(INTDIR)\VectorDotProduct.obj" \
	"$(INTDIR)\VectorExtract_Matrix2D.obj" \
	"$(INTDIR)\VectorExtract_Vector.obj" \
	"$(INTDIR)\VectorInsert_Vector.obj" \
	"$(INTDIR)\VectorNorm.obj" \
	"$(INTDIR)\VectorScale.obj" \
	"$(INTDIR)\VectorSubtract.obj"

"$(OUTDIR)\Shell.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Shell - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Shell.exe"


CLEAN :
	-@erase "$(INTDIR)\BernStein.obj"
	-@erase "$(INTDIR)\BernStein_IstDerivative.obj"
	-@erase "$(INTDIR)\Bez_QQ_EL_1_Str.obj"
	-@erase "$(INTDIR)\Bez_QQ_EL_1Pal.obj"
	-@erase "$(INTDIR)\Calc_A1_Hat.obj"
	-@erase "$(INTDIR)\Calc_A2_Hat.obj"
	-@erase "$(INTDIR)\Calc_Angles.obj"
	-@erase "$(INTDIR)\Calc_ArcLength_Step1.obj"
	-@erase "$(INTDIR)\Calc_ArcLength_Stepm.obj"
	-@erase "$(INTDIR)\Calc_deltaUi1.obj"
	-@erase "$(INTDIR)\Calc_deltaUi2.obj"
	-@erase "$(INTDIR)\Calc_delUi.obj"
	-@erase "$(INTDIR)\Calc_Lamda1_Stepm.obj"
	-@erase "$(INTDIR)\Calc_ReferenceProps.obj"
	-@erase "$(INTDIR)\Calc_X11_Hat.obj"
	-@erase "$(INTDIR)\Calc_X12_Hat.obj"
	-@erase "$(INTDIR)\Calc_X22_Hat.obj"
	-@erase "$(INTDIR)\CalcCoords_at_a_Pt.obj"
	-@erase "$(INTDIR)\CalcDis_at_a_Pt.obj"
	-@erase "$(INTDIR)\CalcRot_at_a_Pt.obj"
	-@erase "$(INTDIR)\Check_PossibleDisplacement.obj"
	-@erase "$(INTDIR)\Compute_StrainEnergy.obj"
	-@erase "$(INTDIR)\Compute_uwthetaAtEnd.obj"
	-@erase "$(INTDIR)\Convergence_Residual.obj"
	-@erase "$(INTDIR)\Define_ElementTypes.obj"
	-@erase "$(INTDIR)\DeformOut_MatLab.obj"
	-@erase "$(INTDIR)\DeformOut_MatLab_Pal.obj"
	-@erase "$(INTDIR)\DeformOut_MatLab_Str.obj"
	-@erase "$(INTDIR)\DegreeElevate2D.obj"
	-@erase "$(INTDIR)\DF60.PDB"
	-@erase "$(INTDIR)\DifferenceOp_1.obj"
	-@erase "$(INTDIR)\DifferenceOp_2.obj"
	-@erase "$(INTDIR)\DumpIntegerArray.obj"
	-@erase "$(INTDIR)\DumpIntegerVar.obj"
	-@erase "$(INTDIR)\DumpRealArray.obj"
	-@erase "$(INTDIR)\DumpRealMatrix.obj"
	-@erase "$(INTDIR)\DumpRealMatrix3.obj"
	-@erase "$(INTDIR)\DumpRealVar.obj"
	-@erase "$(INTDIR)\DumpStringVar.obj"
	-@erase "$(INTDIR)\DumpVar.obj"
	-@erase "$(INTDIR)\Expand_BZCons_C0.obj"
	-@erase "$(INTDIR)\ExtractEL_DispCon.obj"
	-@erase "$(INTDIR)\Form_a_N_kc_N_AMat.obj"
	-@erase "$(INTDIR)\Form_B_and_Tmatrices.obj"
	-@erase "$(INTDIR)\Form_ConstitutiveMatrix.obj"
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
	-@erase "$(INTDIR)\Get_ElementCoords.obj"
	-@erase "$(INTDIR)\Get_Geometry.obj"
	-@erase "$(INTDIR)\Get_Loads.obj"
	-@erase "$(INTDIR)\Get_Loads_Pal.obj"
	-@erase "$(INTDIR)\Get_Loads_Pal_D.obj"
	-@erase "$(INTDIR)\Get_Loads_Str.obj"
	-@erase "$(INTDIR)\Get_Loads_Str_D.obj"
	-@erase "$(INTDIR)\Get_Material.obj"
	-@erase "$(INTDIR)\Get_ReferenceInfoataGaussPt.obj"
	-@erase "$(INTDIR)\Get_SupportedDOFs.obj"
	-@erase "$(INTDIR)\Get_SupportedDOFs_Pal.obj"
	-@erase "$(INTDIR)\Get_SupportedDOFs_Pal_D.obj"
	-@erase "$(INTDIR)\Get_SupportedDOFs_Str.obj"
	-@erase "$(INTDIR)\Get_SupportedDOFs_Str_D.obj"
	-@erase "$(INTDIR)\Initialize_StateVector.obj"
	-@erase "$(INTDIR)\Initiate_ExtractionIndex.obj"
	-@erase "$(INTDIR)\Initiate_ExtractionIndex_D.obj"
	-@erase "$(INTDIR)\Initiate_SolutionData.obj"
	-@erase "$(INTDIR)\Invert_A.obj"
	-@erase "$(INTDIR)\LoadParamChange.obj"
	-@erase "$(INTDIR)\LoadStep_1_iter_1.obj"
	-@erase "$(INTDIR)\LoadStep_n_iter_1.obj"
	-@erase "$(INTDIR)\LoadStep_n_iter_m.obj"
	-@erase "$(INTDIR)\Non_Singular_QQ.obj"
	-@erase "$(INTDIR)\PhaseI_Shell.obj"
	-@erase "$(INTDIR)\PhaseII_Shell.obj"
	-@erase "$(INTDIR)\PlotDataEndw.obj"
	-@erase "$(INTDIR)\ProgShell_NL_Total3D_2ELs.obj"
	-@erase "$(INTDIR)\Put_ReferenceInfo_AllGauss.obj"
	-@erase "$(INTDIR)\Put_ReferenceInfoataGaussPt.obj"
	-@erase "$(INTDIR)\PutGetRefPropsatGaussPt.obj"
	-@erase "$(INTDIR)\PutGetRotCur.obj"
	-@erase "$(INTDIR)\PutGetTBatGaussPt.obj"
	-@erase "$(INTDIR)\Quad_QQ_LOAD_ASSEMBLE.obj"
	-@erase "$(INTDIR)\Quad_QQ_LVY.obj"
	-@erase "$(INTDIR)\Quad_QQ_STIF.obj"
	-@erase "$(INTDIR)\Quad_QQ_STIF_ASSEMBLE.obj"
	-@erase "$(INTDIR)\Set_ExampleType.obj"
	-@erase "$(INTDIR)\Set_Files.obj"
	-@erase "$(INTDIR)\Set_Files_Scratch.obj"
	-@erase "$(INTDIR)\Set_IntegerControls.obj"
	-@erase "$(INTDIR)\Set_TimeDate.obj"
	-@erase "$(INTDIR)\Set_WorkArrayPointers.obj"
	-@erase "$(INTDIR)\Solve_AxEqB.obj"
	-@erase "$(INTDIR)\Solve_AxEqB_Drill.obj"
	-@erase "$(INTDIR)\StateatStartofIter.obj"
	-@erase "$(INTDIR)\UpdateIter_Displace_Lambda.obj"
	-@erase "$(INTDIR)\UpdateStep_Displace_Lambda.obj"
	-@erase "$(INTDIR)\VectorAdd.obj"
	-@erase "$(INTDIR)\VectorCrossProduct.obj"
	-@erase "$(INTDIR)\VectorDotProduct.obj"
	-@erase "$(INTDIR)\VectorExtract_Matrix2D.obj"
	-@erase "$(INTDIR)\VectorExtract_Vector.obj"
	-@erase "$(INTDIR)\VectorInsert_Vector.obj"
	-@erase "$(INTDIR)\VectorNorm.obj"
	-@erase "$(INTDIR)\VectorScale.obj"
	-@erase "$(INTDIR)\VectorSubtract.obj"
	-@erase "$(OUTDIR)\Shell.exe"
	-@erase "$(OUTDIR)\Shell.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90_PROJ=/check:bounds /compile_only /debug:full /libs:qwin /nologo /traceback /warn:argument_checking /warn:nofileopt /module:"Debug/" /object:"Debug/" /pdbfile:"Debug/DF60.PDB" 
F90_OBJS=.\Debug/
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\Shell.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Shell.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"WinMainCRTStartup" /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\Shell.pdb" /debug /machine:I386 /nodefaultlib:"dfconsol.lib" /out:"$(OUTDIR)\Shell.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\BernStein.obj" \
	"$(INTDIR)\BernStein_IstDerivative.obj" \
	"$(INTDIR)\Bez_QQ_EL_1_Str.obj" \
	"$(INTDIR)\Bez_QQ_EL_1Pal.obj" \
	"$(INTDIR)\Calc_A1_Hat.obj" \
	"$(INTDIR)\Calc_A2_Hat.obj" \
	"$(INTDIR)\Calc_Angles.obj" \
	"$(INTDIR)\Calc_ArcLength_Step1.obj" \
	"$(INTDIR)\Calc_ArcLength_Stepm.obj" \
	"$(INTDIR)\Calc_deltaUi1.obj" \
	"$(INTDIR)\Calc_deltaUi2.obj" \
	"$(INTDIR)\Calc_delUi.obj" \
	"$(INTDIR)\Calc_Lamda1_Stepm.obj" \
	"$(INTDIR)\Calc_ReferenceProps.obj" \
	"$(INTDIR)\Calc_X11_Hat.obj" \
	"$(INTDIR)\Calc_X12_Hat.obj" \
	"$(INTDIR)\Calc_X22_Hat.obj" \
	"$(INTDIR)\CalcCoords_at_a_Pt.obj" \
	"$(INTDIR)\CalcDis_at_a_Pt.obj" \
	"$(INTDIR)\CalcRot_at_a_Pt.obj" \
	"$(INTDIR)\Check_PossibleDisplacement.obj" \
	"$(INTDIR)\Compute_StrainEnergy.obj" \
	"$(INTDIR)\Compute_uwthetaAtEnd.obj" \
	"$(INTDIR)\Convergence_Residual.obj" \
	"$(INTDIR)\Define_ElementTypes.obj" \
	"$(INTDIR)\DeformOut_MatLab.obj" \
	"$(INTDIR)\DeformOut_MatLab_Pal.obj" \
	"$(INTDIR)\DeformOut_MatLab_Str.obj" \
	"$(INTDIR)\DegreeElevate2D.obj" \
	"$(INTDIR)\DifferenceOp_1.obj" \
	"$(INTDIR)\DifferenceOp_2.obj" \
	"$(INTDIR)\DumpIntegerArray.obj" \
	"$(INTDIR)\DumpIntegerVar.obj" \
	"$(INTDIR)\DumpRealArray.obj" \
	"$(INTDIR)\DumpRealMatrix.obj" \
	"$(INTDIR)\DumpRealMatrix3.obj" \
	"$(INTDIR)\DumpRealVar.obj" \
	"$(INTDIR)\DumpStringVar.obj" \
	"$(INTDIR)\DumpVar.obj" \
	"$(INTDIR)\Expand_BZCons_C0.obj" \
	"$(INTDIR)\ExtractEL_DispCon.obj" \
	"$(INTDIR)\Form_a_N_kc_N_AMat.obj" \
	"$(INTDIR)\Form_B_and_Tmatrices.obj" \
	"$(INTDIR)\Form_ConstitutiveMatrix.obj" \
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
	"$(INTDIR)\Get_ElementCoords.obj" \
	"$(INTDIR)\Get_Geometry.obj" \
	"$(INTDIR)\Get_Loads.obj" \
	"$(INTDIR)\Get_Loads_Pal.obj" \
	"$(INTDIR)\Get_Loads_Pal_D.obj" \
	"$(INTDIR)\Get_Loads_Str.obj" \
	"$(INTDIR)\Get_Loads_Str_D.obj" \
	"$(INTDIR)\Get_Material.obj" \
	"$(INTDIR)\Get_ReferenceInfoataGaussPt.obj" \
	"$(INTDIR)\Get_SupportedDOFs.obj" \
	"$(INTDIR)\Get_SupportedDOFs_Pal.obj" \
	"$(INTDIR)\Get_SupportedDOFs_Pal_D.obj" \
	"$(INTDIR)\Get_SupportedDOFs_Str.obj" \
	"$(INTDIR)\Get_SupportedDOFs_Str_D.obj" \
	"$(INTDIR)\Initialize_StateVector.obj" \
	"$(INTDIR)\Initiate_ExtractionIndex.obj" \
	"$(INTDIR)\Initiate_ExtractionIndex_D.obj" \
	"$(INTDIR)\Initiate_SolutionData.obj" \
	"$(INTDIR)\Invert_A.obj" \
	"$(INTDIR)\LoadParamChange.obj" \
	"$(INTDIR)\LoadStep_1_iter_1.obj" \
	"$(INTDIR)\LoadStep_n_iter_1.obj" \
	"$(INTDIR)\LoadStep_n_iter_m.obj" \
	"$(INTDIR)\Non_Singular_QQ.obj" \
	"$(INTDIR)\PhaseI_Shell.obj" \
	"$(INTDIR)\PhaseII_Shell.obj" \
	"$(INTDIR)\PlotDataEndw.obj" \
	"$(INTDIR)\ProgShell_NL_Total3D_2ELs.obj" \
	"$(INTDIR)\Put_ReferenceInfo_AllGauss.obj" \
	"$(INTDIR)\Put_ReferenceInfoataGaussPt.obj" \
	"$(INTDIR)\PutGetRefPropsatGaussPt.obj" \
	"$(INTDIR)\PutGetRotCur.obj" \
	"$(INTDIR)\PutGetTBatGaussPt.obj" \
	"$(INTDIR)\Quad_QQ_LOAD_ASSEMBLE.obj" \
	"$(INTDIR)\Quad_QQ_LVY.obj" \
	"$(INTDIR)\Quad_QQ_STIF.obj" \
	"$(INTDIR)\Quad_QQ_STIF_ASSEMBLE.obj" \
	"$(INTDIR)\Set_ExampleType.obj" \
	"$(INTDIR)\Set_Files.obj" \
	"$(INTDIR)\Set_Files_Scratch.obj" \
	"$(INTDIR)\Set_IntegerControls.obj" \
	"$(INTDIR)\Set_TimeDate.obj" \
	"$(INTDIR)\Set_WorkArrayPointers.obj" \
	"$(INTDIR)\Solve_AxEqB.obj" \
	"$(INTDIR)\Solve_AxEqB_Drill.obj" \
	"$(INTDIR)\StateatStartofIter.obj" \
	"$(INTDIR)\UpdateIter_Displace_Lambda.obj" \
	"$(INTDIR)\UpdateStep_Displace_Lambda.obj" \
	"$(INTDIR)\VectorAdd.obj" \
	"$(INTDIR)\VectorCrossProduct.obj" \
	"$(INTDIR)\VectorDotProduct.obj" \
	"$(INTDIR)\VectorExtract_Matrix2D.obj" \
	"$(INTDIR)\VectorExtract_Vector.obj" \
	"$(INTDIR)\VectorInsert_Vector.obj" \
	"$(INTDIR)\VectorNorm.obj" \
	"$(INTDIR)\VectorScale.obj" \
	"$(INTDIR)\VectorSubtract.obj"

"$(OUTDIR)\Shell.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("Shell.dep")
!INCLUDE "Shell.dep"
!ELSE 
!MESSAGE Warning: cannot find "Shell.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Shell - Win32 Release" || "$(CFG)" == "Shell - Win32 Debug"
SOURCE=.\BernStein.for

"$(INTDIR)\BernStein.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\BernStein_IstDerivative.for

"$(INTDIR)\BernStein_IstDerivative.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Bez_QQ_EL_1_Str.f

"$(INTDIR)\Bez_QQ_EL_1_Str.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Bez_QQ_EL_1Pal.f

"$(INTDIR)\Bez_QQ_EL_1Pal.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Calc_A1_Hat.for

"$(INTDIR)\Calc_A1_Hat.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Calc_A2_Hat.for

"$(INTDIR)\Calc_A2_Hat.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Calc_Angles.for

"$(INTDIR)\Calc_Angles.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Calc_ArcLength_Step1.for

"$(INTDIR)\Calc_ArcLength_Step1.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Calc_ArcLength_Stepm.for

"$(INTDIR)\Calc_ArcLength_Stepm.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Calc_deltaUi1.for

"$(INTDIR)\Calc_deltaUi1.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Calc_deltaUi2.for

"$(INTDIR)\Calc_deltaUi2.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Calc_delUi.for

"$(INTDIR)\Calc_delUi.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Calc_Lamda1_Stepm.for

"$(INTDIR)\Calc_Lamda1_Stepm.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Calc_ReferenceProps.for

"$(INTDIR)\Calc_ReferenceProps.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Calc_X11_Hat.for

"$(INTDIR)\Calc_X11_Hat.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Calc_X12_Hat.for

"$(INTDIR)\Calc_X12_Hat.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Calc_X22_Hat.for

"$(INTDIR)\Calc_X22_Hat.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\CalcCoords_at_a_Pt.for

"$(INTDIR)\CalcCoords_at_a_Pt.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\CalcDis_at_a_Pt.for

"$(INTDIR)\CalcDis_at_a_Pt.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\CalcRot_at_a_Pt.for

"$(INTDIR)\CalcRot_at_a_Pt.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Check_PossibleDisplacement.for

"$(INTDIR)\Check_PossibleDisplacement.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Compute_StrainEnergy.f

"$(INTDIR)\Compute_StrainEnergy.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Compute_uwthetaAtEnd.f

"$(INTDIR)\Compute_uwthetaAtEnd.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Convergence_Residual.for

"$(INTDIR)\Convergence_Residual.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Define_ElementTypes.for

"$(INTDIR)\Define_ElementTypes.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DeformOut_MatLab.for

"$(INTDIR)\DeformOut_MatLab.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DeformOut_MatLab_Pal.for

"$(INTDIR)\DeformOut_MatLab_Pal.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DeformOut_MatLab_Str.for

"$(INTDIR)\DeformOut_MatLab_Str.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DegreeElevate2D.for

"$(INTDIR)\DegreeElevate2D.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DifferenceOp_1.for

"$(INTDIR)\DifferenceOp_1.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DifferenceOp_2.for

"$(INTDIR)\DifferenceOp_2.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DumpIntegerArray.for

"$(INTDIR)\DumpIntegerArray.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DumpIntegerVar.for

"$(INTDIR)\DumpIntegerVar.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DumpRealArray.for

"$(INTDIR)\DumpRealArray.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DumpRealMatrix.for

"$(INTDIR)\DumpRealMatrix.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DumpRealMatrix3.for

"$(INTDIR)\DumpRealMatrix3.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DumpRealVar.for

"$(INTDIR)\DumpRealVar.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DumpStringVar.for

"$(INTDIR)\DumpStringVar.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DumpVar.for

"$(INTDIR)\DumpVar.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Expand_BZCons_C0.for

"$(INTDIR)\Expand_BZCons_C0.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ExtractEL_DispCon.for

"$(INTDIR)\ExtractEL_DispCon.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Form_a_N_kc_N_AMat.f

"$(INTDIR)\Form_a_N_kc_N_AMat.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Form_B_and_Tmatrices.f

"$(INTDIR)\Form_B_and_Tmatrices.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Form_ConstitutiveMatrix.for

"$(INTDIR)\Form_ConstitutiveMatrix.obj" : $(SOURCE) "$(INTDIR)"


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


SOURCE=.\Get_ElementCoords.for

"$(INTDIR)\Get_ElementCoords.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Get_Geometry.for

"$(INTDIR)\Get_Geometry.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Get_Loads.for

"$(INTDIR)\Get_Loads.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Get_Loads_Pal.for

"$(INTDIR)\Get_Loads_Pal.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Get_Loads_Pal_D.for

"$(INTDIR)\Get_Loads_Pal_D.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Get_Loads_Str.for

"$(INTDIR)\Get_Loads_Str.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Get_Loads_Str_D.for

"$(INTDIR)\Get_Loads_Str_D.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Get_Material.for

"$(INTDIR)\Get_Material.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Get_ReferenceInfoataGaussPt.f

"$(INTDIR)\Get_ReferenceInfoataGaussPt.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Get_SupportedDOFs.for

"$(INTDIR)\Get_SupportedDOFs.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Get_SupportedDOFs_Pal.for

"$(INTDIR)\Get_SupportedDOFs_Pal.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Get_SupportedDOFs_Pal_D.for

"$(INTDIR)\Get_SupportedDOFs_Pal_D.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Get_SupportedDOFs_Str.for

"$(INTDIR)\Get_SupportedDOFs_Str.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Get_SupportedDOFs_Str_D.for

"$(INTDIR)\Get_SupportedDOFs_Str_D.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Initialize_StateVector.for

"$(INTDIR)\Initialize_StateVector.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Initiate_ExtractionIndex.for

"$(INTDIR)\Initiate_ExtractionIndex.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Initiate_ExtractionIndex_D.for

"$(INTDIR)\Initiate_ExtractionIndex_D.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Initiate_SolutionData.for

"$(INTDIR)\Initiate_SolutionData.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Invert_A.for

"$(INTDIR)\Invert_A.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\LoadParamChange.for

"$(INTDIR)\LoadParamChange.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\LoadStep_1_iter_1.f

"$(INTDIR)\LoadStep_1_iter_1.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\LoadStep_n_iter_1.f

"$(INTDIR)\LoadStep_n_iter_1.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\LoadStep_n_iter_m.f

"$(INTDIR)\LoadStep_n_iter_m.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Non_Singular_QQ.for

"$(INTDIR)\Non_Singular_QQ.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\PhaseI_Shell.f

"$(INTDIR)\PhaseI_Shell.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\PhaseII_Shell.f

"$(INTDIR)\PhaseII_Shell.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\PlotDataEndw.for

"$(INTDIR)\PlotDataEndw.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ProgShell_NL_Total3D_2ELs.f

"$(INTDIR)\ProgShell_NL_Total3D_2ELs.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Put_ReferenceInfo_AllGauss.f

"$(INTDIR)\Put_ReferenceInfo_AllGauss.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Put_ReferenceInfoataGaussPt.f

"$(INTDIR)\Put_ReferenceInfoataGaussPt.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\PutGetRefPropsatGaussPt.for

"$(INTDIR)\PutGetRefPropsatGaussPt.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\PutGetRotCur.for

"$(INTDIR)\PutGetRotCur.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\PutGetTBatGaussPt.for

"$(INTDIR)\PutGetTBatGaussPt.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Quad_QQ_LOAD_ASSEMBLE.f

"$(INTDIR)\Quad_QQ_LOAD_ASSEMBLE.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Quad_QQ_LVY.f

"$(INTDIR)\Quad_QQ_LVY.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Quad_QQ_STIF.f

"$(INTDIR)\Quad_QQ_STIF.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Quad_QQ_STIF_ASSEMBLE.f

"$(INTDIR)\Quad_QQ_STIF_ASSEMBLE.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Set_ExampleType.for

"$(INTDIR)\Set_ExampleType.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Set_Files.for

"$(INTDIR)\Set_Files.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Set_Files_Scratch.for

"$(INTDIR)\Set_Files_Scratch.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Set_IntegerControls.for

"$(INTDIR)\Set_IntegerControls.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Set_TimeDate.for

"$(INTDIR)\Set_TimeDate.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Set_WorkArrayPointers.for

"$(INTDIR)\Set_WorkArrayPointers.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Solve_AxEqB.f

"$(INTDIR)\Solve_AxEqB.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Solve_AxEqB_Drill.f

"$(INTDIR)\Solve_AxEqB_Drill.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\StateatStartofIter.for

"$(INTDIR)\StateatStartofIter.obj" : $(SOURCE) "$(INTDIR)"


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


SOURCE=.\VectorExtract_Matrix2D.f

"$(INTDIR)\VectorExtract_Matrix2D.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\VectorExtract_Vector.f

"$(INTDIR)\VectorExtract_Vector.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\VectorInsert_Vector.f

"$(INTDIR)\VectorInsert_Vector.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\VectorNorm.f

"$(INTDIR)\VectorNorm.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\VectorScale.f

"$(INTDIR)\VectorScale.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\VectorSubtract.f

"$(INTDIR)\VectorSubtract.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

