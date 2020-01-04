# Microsoft Developer Studio Project File - Name="Taylor Strip Hole" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=Taylor Strip Hole - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Taylor Strip Hole.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Taylor Strip Hole.mak" CFG="Taylor Strip Hole - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Taylor Strip Hole - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "Taylor Strip Hole - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
F90=df.exe
RSC=rc.exe

!IF  "$(CFG)" == "Taylor Strip Hole - Win32 Release"

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
# ADD BASE F90 /compile_only /nologo /warn:nofileopt
# ADD F90 /compile_only /nologo /warn:nofileopt
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "Taylor Strip Hole - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Taylor_Strip_Hole___Win32_Debug"
# PROP BASE Intermediate_Dir "Taylor_Strip_Hole___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Taylor_Strip_Hole___Win32_Debug"
# PROP Intermediate_Dir "Taylor_Strip_Hole___Win32_Debug"
# PROP Target_Dir ""
# ADD BASE F90 /check:bounds /compile_only /dbglibs /debug:full /nologo /traceback /warn:argument_checking /warn:nofileopt
# ADD F90 /check:bounds /compile_only /dbglibs /debug:full /nologo /traceback /warn:argument_checking /warn:nofileopt
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ  /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ  /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Taylor Strip Hole - Win32 Release"
# Name "Taylor Strip Hole - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;f90;for;f;fpp"
# Begin Source File

SOURCE=.\BernStein.for
# End Source File
# Begin Source File

SOURCE=.\BernStein_IstDerivative.for
# End Source File
# Begin Source File

SOURCE=.\Bez_Coords_2.f
# End Source File
# Begin Source File

SOURCE=.\Bez_GeomControls.f
# End Source File
# Begin Source File

SOURCE=.\BZ_Coords_1.f
# End Source File
# Begin Source File

SOURCE=.\BZ_Coords_CircumConnect.f
# End Source File
# Begin Source File

SOURCE=.\BZ_Coords_OneCubicXY.f
# End Source File
# Begin Source File

SOURCE=.\BZ_Coords_OneRatBez.f
# End Source File
# Begin Source File

SOURCE=.\BZ_Coords_Rational.f
# End Source File
# Begin Source File

SOURCE=.\Calc_A1_Hat.for
# End Source File
# Begin Source File

SOURCE=.\Calc_A2_Hat.for
# End Source File
# Begin Source File

SOURCE=.\Calc_Coords_at_a_Pt.for
# End Source File
# Begin Source File

SOURCE=.\Calc_Coords_at_a_Pt_RAT.for
# End Source File
# Begin Source File

SOURCE=.\Calc_Determinant.for
# End Source File
# Begin Source File

SOURCE=.\Calc_Dis_at_a_Pt.for
# End Source File
# Begin Source File

SOURCE=.\Calc_DispAtDOFs.for
# End Source File
# Begin Source File

SOURCE=.\Calc_P1_Hat.for
# End Source File
# Begin Source File

SOURCE=.\Calc_P2_Hat.for
# End Source File
# Begin Source File

SOURCE=.\Calc_ReferenceProps.for
# End Source File
# Begin Source File

SOURCE=.\CC_StrainDis.f
# End Source File
# Begin Source File

SOURCE=.\CC_StrainDis4.f
# End Source File
# Begin Source File

SOURCE=.\CC_StrainDis_2Methods.f
# End Source File
# Begin Source File

SOURCE=.\CC_StrainDis_2MethodsCart.f
# End Source File
# Begin Source File

SOURCE=.\CC_StrainDis_2MethodsRAT.f
# End Source File
# Begin Source File

SOURCE=.\CC_StrainDis_Actual.f
# End Source File
# Begin Source File

SOURCE=.\Compute_ExternalWork.f
# End Source File
# Begin Source File

SOURCE=.\Compute_StrainEnergy.f
# End Source File
# Begin Source File

SOURCE=.\Create_DropDOFs.f
# End Source File
# Begin Source File

SOURCE=.\CubicTangent_Length.for
# End Source File
# Begin Source File

SOURCE=.\Define_ElementTypes.for
# End Source File
# Begin Source File

SOURCE=.\DeformOut_MatCar.for
# End Source File
# Begin Source File

SOURCE=.\DeformOut_MatLab.for
# End Source File
# Begin Source File

SOURCE=.\DeformOut_MatLabCart.for
# End Source File
# Begin Source File

SOURCE=.\DeformOut_PLCar.for
# End Source File
# Begin Source File

SOURCE=.\DeformOut_PrCar.for
# End Source File
# Begin Source File

SOURCE=.\DeformOut_Print.for
# End Source File
# Begin Source File

SOURCE=.\DeformOut_Print_Sco.for
# End Source File
# Begin Source File

SOURCE=.\DegreeElevate2D.for
# End Source File
# Begin Source File

SOURCE=.\DifferenceOp_1.for
# End Source File
# Begin Source File

SOURCE=.\DifferenceOp_1_RAT.for
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

SOURCE=.\Elem_Data.f
# End Source File
# Begin Source File

SOURCE=.\Elem_Data_1Cart.f
# End Source File
# Begin Source File

SOURCE=.\Elem_Data_1Elem.f
# End Source File
# Begin Source File

SOURCE=.\Elem_Data_2CircumElems.f
# End Source File
# Begin Source File

SOURCE=.\Elem_Data_2El.f
# End Source File
# Begin Source File

SOURCE=.\Elem_Data_2RadialElems.f
# End Source File
# Begin Source File

SOURCE=.\Elem_Data_3CircumElems.f
# End Source File
# Begin Source File

SOURCE=.\Elem_Data_4CircumElems.f
# End Source File
# Begin Source File

SOURCE=.\Expand_BzDispCons.for
# End Source File
# Begin Source File

SOURCE=.\ExpandFrom_C1or2Sol.f
# End Source File
# Begin Source File

SOURCE=.\Extract_ContractedLoadVector.f
# End Source File
# Begin Source File

SOURCE=.\Extract_NonSingularStif.f
# End Source File
# Begin Source File

SOURCE=.\ExtractEL_DispCon.for
# End Source File
# Begin Source File

SOURCE=.\fileStuff.f
# End Source File
# Begin Source File

SOURCE=.\FormBC_r0_Matrix.f
# End Source File
# Begin Source File

SOURCE=.\FormIndex_EL2.f
# End Source File
# Begin Source File

SOURCE=.\FormIndex_EL2_Circum.f
# End Source File
# Begin Source File

SOURCE=.\FormLoadfromSpecifiedDisps.f
# End Source File
# Begin Source File

SOURCE=".\FormTransformation Matrix_C2.f"
# End Source File
# Begin Source File

SOURCE=.\GaussPtVal.f
# End Source File
# Begin Source File

SOURCE=.\GeometryPlot_Cart.for
# End Source File
# Begin Source File

SOURCE=.\GeometryPlot_RAT.for
# End Source File
# Begin Source File

SOURCE=.\Impose_BC_r0_Constraints.f
# End Source File
# Begin Source File

SOURCE=.\Impose_C1or2.f
# End Source File
# Begin Source File

SOURCE=.\Initiate_ExtractionIndex.for
# End Source File
# Begin Source File

SOURCE=.\Jacobian_N_Determinant.for
# End Source File
# Begin Source File

SOURCE=.\Jacobian_N_DeterminantRAT.for
# End Source File
# Begin Source File

SOURCE=.\OutDisSup_Data.f
# End Source File
# Begin Source File

SOURCE=.\PlotDataEndw.for
# End Source File
# Begin Source File

SOURCE=".\Prog_TaylorHole 2 El.f"
# End Source File
# Begin Source File

SOURCE=.\Quad_CC_LV.f
# End Source File
# Begin Source File

SOURCE=.\Quad_CC_LV4.f
# End Source File
# Begin Source File

SOURCE=.\Set_Files.for
# End Source File
# Begin Source File

SOURCE=.\Set_Files_Scratch.for
# End Source File
# Begin Source File

SOURCE=.\Set_TimeDate.for
# End Source File
# Begin Source File

SOURCE=.\Solve_AxEqB.f
# End Source File
# Begin Source File

SOURCE=.\Stif_Assemble.f
# End Source File
# Begin Source File

SOURCE=.\Stif_Element.f
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

SOURCE=.\VectorOperations.f
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
# End Target
# End Project
