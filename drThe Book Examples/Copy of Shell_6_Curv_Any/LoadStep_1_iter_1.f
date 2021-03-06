	Subroutine LoadStep_1_iter_1()
	Implicit Real(kind=8) (a-h,o-z)
!========================================================================
	include 'Blank.h'
	include 'CurrentElem.h'
	include 'LoadStepIter.h'
	include 'general.h'
	include 'Wpointers.h'
	include 'Addpoints.h'
	include 'SizeVar.h'
	include 'files.h'
	include 'Scratch.h'
	include 'Examples.h'
	include 'solve.h'
	include 'LogParams.h'

	Real(kind=8)	Qd                   
	Dimension		Qd(nStifEL)
!========================================================================
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!========================================================================
	call DumpStringVar("Enter:LoadStep_1_iter_1",1,iOut)
!		---------------------------------------------------------------------- Stiffness Matrix
!		----|------|----------------- Surface/End Load Vector
!		Get Load Vector 
!		call Set_ExtLoad_Y(A(n5),3,Iout)
!==================================================================================================
		call LV_EndLoad(A(n5),A(n5V),nLod,A(n7),nStifS,Iout)		! External Loads only: P-Load
!==================================================================================================
!
		do 10 iEL = 1,nElem
!			-------------------------------------| Form Stiffness Matrix:
			iCEL = iEL 
!			-------------------------------------| Form Stiffness Matrix: 
			m2 =n2a
!	if(nEx == 10.AND.nElem == 4) then
!		call Hem4_Extract_DispCon(A(ndelUiEL),nStifS,Qd,nStifEL,
!     &							iEL,iOut)
!	endif
		call Quad_QQ_STIF(A(nRoCOld),A(nCuCOld),
     &			A(nRoKSav),A(nCKKSav),
     &			A(ndelUiEL),iEL,A(nDMat),A(nBMat),A(nTMat),
!     &			Qd,iEL,A(nDMat),A(nBMat),A(nTMat),
     &			A(m2),A(nBfors),A(nStifK),nStifEL,Iout,Trace)
!
!		Assemble Ist Elem:nSTfK only has body force integral part
!
!============================================================================== Later for general Scheme
!			if(nEx == 10.and.nElem.ge.4) then
			if(nEx == 9999.and.nElem.ge.4) then
				call Hem_Stif_Assemble(A(n2c),A(m2),nQd1,nDof,
     &    		nStifEL,A(n2),nStifS,iEL,Iout,Trace)
!============================================================================== END Later for general Scheme
			else
	if(nEx == 10.AND.nElem == 4) then
		call PutGetIndxEL(iIndxEL,A(n2c),nStifEL,iEL,2,iOut)	! 2 = read
	endif
				call Assemble_Stif(A(n2c),A(m2),
     &    		nStifEL,A(n2),nStifS,iEL,Iout,Trace)
			end if
!			------------------------------------------------------------------ Residual & End Loads
!			----|------|----------------- Surface/End Load Vector
!			Get Load Vector 
!			call Set_ExtLoad_Y(A(n5),3,Iout)
!			call LV_EndLoad(A(n5),nQc,A(n7),nStifS,nLoadLoc,Iout)
!====================================================================================== dropped
!			n7 already contains the whole load !!!
!======================================================================================
!			Assemble Ist Elem:nBFors only has Residual & body force integral part
!
!			m7 = n7
!			if(iEL.GT.1) Then
!				m7 = nBFors
!			endif
!			call Assemble_Load(A(n2c),A(m7),
!     &    		nStifEL,A(nB),nStifS,iEL,Iout)
 !====================================================================================== dropped end
  10		continue
!	------------------------------------------------------------------ Check rigid body modes
	nEig	= nEndW
	nEnd	= nEig + nStifS*nSzDbl
!	==========================================================
!	call Get_EigenValues(A(n2),nStifS,nStifS,A(nEig),iOut)
!	==========================================================
!-------------------------------------------------------------------------------------
!=================================================================== Update
	if(iNut.LE.1) Then
		if(iRotCur == iRotCur1) Then
			iRotCur = iRotCur2
		else
			iRotCur = iRotCur1
		endif
	endif				
!======================================================================================
!----------------------------------------------------------- Supported Stiff/Load/State
!		-----------|------|----------------- NonSingular Stiffness
!		Add Supports: rigid body Out
!
		call Extract_NonSingularStif(A(n2),nStifC,nStifC,A(n6),nStifN,
     &								A(nSx),nSup,iCont,iOut)
!	==========================================================
!	call Get_EigenValues(A(n6),nStifN,nStifN,A(nEig),iOut)
!	==========================================================
!======================================================================================
!		----------|------|----------------- Supported Load Vector & State Vector
!		Add Supports: rigid body Out
!
		call Extract_ContractedLoadVector(A(n7),nStifC,A(nPLoad),	!P-EndLoad
     &						nStifN,A(nSx),nSup,iCont,iOut)
!======================================================================================
!-------------------------------------------------------------- Solve:Current Iteration
!		! Step 2a: eqn 7
		call RealSym_Determinant(A(n6),A(n3),A(n2),
     &					NStifN,NStifN,NStifN,detK,iOut)
		detKO = detK
			call DumpRealVar(detKO,"Determinant = ",1,iOut)
!			===================
		call Solve_AxEqB(A(n6),A(nPLoad),A(ndeltaUi2),
     &			nStifN,nStifN,iOut)
!		===================
		call Compute_StrainEnergy(A(n6),A(nPLoad),A(ndeltaUi2),
     &			nStifN,SEnergy,PEnergy,iOut)
!======================================================================================
!	!------------------------------------------------------------------ Initialize
!		! Step 2a: eqn 7
!		call Calc_deltaUi2(A(n6),A(nPLoad),A(ndeltaUi2),
!     &						nStifN,iOut)
!		! Step 2b: 
		call Calc_ArcLength_Step1(A(ndeltaUi2),nStifN,
     &					DelLamdaiO,DelLmO,iOut)
!		! Step 2b: eqn 10: At the beginning of each Loadstep Linear Solution
		call LV_Initialize(A(ndeltaUi1),nStifS,Iout)		! state
		call Calc_delUi(DelLamdaiO,A(ndeltaUi1),A(ndeltaUi2),
     &					A(ndelUiO),NStifN,iOut)
		DeltaLamdai = ArcLen
		DelLm		= DelLmO	
		call Expand_BezierDispControls_C0(A(ndelUiO),nStifN,A(nxo),
     &					nStifC,A(nSx),nSup,iCont,iOut)
!======================================================================================
	call DumpStringVar("Exit:LoadStep_1_iter_1",1,iOut)
	return
	end
