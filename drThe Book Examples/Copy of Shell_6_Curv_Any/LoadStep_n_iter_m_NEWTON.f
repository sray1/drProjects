	Subroutine LoadStep_n_iter_m_NEWTON()
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
	include 'solve.h'
	include 'LogParams.h'
	include 'Examples.h'
!========================================================================
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!========================================================================
	call DumpStringVar("Enter:LoadStep_n_iter_m",0,iOut)
!		-------------------------------------------------------- Debug : End
!		===================
		call LV_Initialize(A(nB),nStifS,Iout)	! Current Load Vector
!		---------------------------------------------------------------------- Stiffness Matrix
		do 20 iEL = 1,nElem
!			-------------------------------------| Form Stiffness Matrix:
			iCEL = iEL 
!			-------------------------------------| Form Stiffness Matrix: 
			m2 =n2a
!		--------------------------------------------------------- 
			call Extract_DispCon(A(nxm),nStifS,A(ndelUiEL),	!Extract DisRotCOntrols
     &			nStifEL,iEL,iOut)
			call Quad_QQ_STIF(A(nRoCOld),A(nCuCOld),
     &			A(nRoKSav),A(nCKKSav),
     &			A(ndelUiEL),iEL,A(nDMat),A(nBMat),A(nTMat),
     &			A(m2),A(nBfors),A(nStifK),nStifEL,Iout,Trace)
!
!			Assemble Ist Elem:nSTfK only has body force integral part
!
!============================================================================== Later for general Scheme
			if(nEx == 10.AND.nElem == 4) then
				call PutGetIndxEL(iIndxEL,A(n2c),nStifEL,iEL,2,iOut)	! 2 = read
			endif
			call Assemble_Stif(A(n2c),A(m2),
     &    		nStifEL,A(n2),nStifS,iEL,Iout,Trace)
!			------------------------------------------------------------------ Residual & End Loads
!		----|------|----------------- Residual - lamda*P Load Vector
			call Extract_DispCon(A(n7),nStifS,A(ndelUiEL),	!Extract LoadVector
     &			nStifEL,iEL,iOut)
			call LV_minus_EndLoad(ArcLen,A(ndelUiEL),
     &			A(nBfors),nStifEL,iOut)
!
!			Assemble Elem:nBFors only has Residual & body force integral part
!
			if(nEx == 10.and.nElem.ge.4) then
				call Assemble_Load(A(n2c),A(nBFors),
     &    			nStifEL,A(nB),nStifS,iEL,Iout)
			else
				call Assemble_Load(A(n2c),A(nBFors),
     &    			nStifEL,A(nB),nStifS,iEL,Iout)
			end if
   20		continue
!=================================================================== Update
!	------------------------------------------------------------------ Check rigid body modes
	nEig	= nEndW
	nEnd	= nEig + nStifS*nSzDbl
!	call Get_EigenValues(A(n2),nStifS,nStifS,A(nEig),iOut)
!-------------------------------------------------------------------------------------
	if(iNut.LE.1) Then
		if(iRotCur == iRotCur1) Then
			iRotCur = iRotCur2
		else
			iRotCur = iRotCur1
		endif
	endif				
!===================================================================
!------------------------------------------------------------------------------- Supported Stiff/Load/State
!		-----------|------|----------------- NonSingular Stiffness
!		Add Supports: rigid body Out
!
		call Extract_NonSingularStif(A(n2),nStifC,nStifC,A(n6),nStifN,
     &								A(nSx),nSup,iCont,iOut)
		call RealSym_Determinant(A(n6),A(n3),A(n2),
     &					NStifN,NStifN,NStifN,detK,iOut)
		detKO = detK
		call DumpRealVar(detKO,"Determinant = ",1,iOut)
!		----------|------|----------------- Supported Load Vector & State Vector
!		Add Supports: rigid body Out
!
		call Extract_ContractedLoadVector(A(nB),nStifC,A(nGuLam),	!Residual
     &						nStifN,A(nSx),nSup,iCont,iOut)
!-------------------------------------------------------------------------------------
		call Solve_AxEqB(A(n6),A(nGuLam),A(ndelUiO),
     &			nStifN,nStifN,iOut)
!		=========================================================
		call Expand_BezierDispControls_C0(A(ndelUiO),nStifN,A(nxm),
     &					nStifC,A(nSx),nSup,iCont,iOut)
!======================================================================================
!------------------
	call DumpStringVar("Exit:LoadStep_n_iter_m",0,iOut)
      return
	end

