	Subroutine LoadStep_1_iter_1(D)
	Implicit Real(kind=8) (a-h,o-z)
!========================================================================
	real(kind = 8)	D     
	dimension		D(6,6)
!
	common A(1000000)
!
	common/LoadStepIter/iStep,iNut,bReset
	common/general/	   Trace
	common/Wpointers/  nSx,nRoCOld,nCuCOld,nRoKSav,nCKKSav,n1a,n1b,
     &				   n2,n2a,n2b,n3a,n3b,n3,n4,n4b,n5,nxo,nx,nBfors,
     &                   nStifK,nBo,nB,nPLoad,nGuLam,nUm,nUmO,nxmR,
     &				   nxm,nxmO,ndeltaUi,ndeltaUi1,ndeltaUi2,ndelUi,
     &				   ndelUiO,ndelUip11,ndelUip12,n7,n6,n6R,n2c,
     &				   nEndwSav	
	common/Addpoints/  ndelUiEL,n1c
	common/SizeVar/	  iGeom,iCont,nDim,nQc,nSup,nDof,nQd,nElem,
     &                  nStifEL,Nint,nCInt,nStifS,nStifC,
     &				  nStifN,nLoadLoc,NelType
      common/files/	  iFileStiff,Iout,IoutDef,IoutEnd,iRotCur
      common/Scratch/	  iRotCur1,iRotCur2
	common/SolVar/	  detKO,detK,delLmO,DelLm,iTermO,iTerRef,
     &				  delLamdaiO,SLamdam,SLamdamO,DeltaLamdai,ArcLen,
     &				  Tol,MaxSteps,MaxIt,iCutMax,Imaginary
	LOGICAL			  Imaginary		
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!========================================================================
	call DumpStringVar("Enter:LoadStep_1_iter_1",0,iOut)
!		---------------------------------------------------------------------- Stiffness Matrix
!		----|------|----------------- Surface/End Load Vector
!		Get Load Vector 
!		call Set_ExtLoad_Y(A(n5),3,Iout)
		call LV_EndLoad(A(n5),nQc,A(n7),nStifS,nLoadLoc,Iout)
!
		do 10 iEL = 1,nElem
!			-------------------------------------| Form Stiffness Matrix: 
			m1 =n1a
			m2 =n2a
			if(iEL == 2) Then
				m1 =n1b
!				m2 =n2b
			elseif(iEL == 3) Then
				m1 =n1c
!				m2 =n2d
			endif
		call Quad_QQ_STIF(A(nRoCOld),A(nCuCOld),
     &			A(nRoKSav),A(nCKKSav),nCInt,
     &			A(ndelUiEL),A(m1),nQc,iEL,
     &			NelType,Nint,
     &			D,A(m2),A(nBfors),A(nStifK),
     &			nStifEL,Iout,Trace)
!
!			Assemble Ist Elem:nSTfK only has body force integral part
!
			call Assemble_Stif(A(n2c),A(m2),
     &    		nStifEL,A(n2),nStifS,iEL,Iout,Trace)
!			------------------------------------------------------------------ Residual & End Loads
!			----|------|----------------- Surface/End Load Vector
!			Get Load Vector 
!			call Set_ExtLoad_Y(A(n5),3,Iout)
!			call LV_EndLoad(A(n5),nQc,A(n7),nStifS,nLoadLoc,Iout)
!
!			Assemble Ist Elem:nBFors only has Residual & body force integral part
!
			m7 = n7
			if(iEL.GT.1) Then
				m7 = nBFors
			endif
			call Assemble_Load(A(n2c),A(m7),
     &    		nStifEL,A(nB),nStifS,iEL,Iout)
   10		continue
!=================================================================== Update
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
!		----------|------|----------------- Supported Load Vector & State Vector
!		Add Supports: rigid body Out
!
		call Extract_ContractedLoadVector(A(n7),nStifC,A(nPLoad),	!P-EndLoad
     &						nStifN,A(nSx),nSup,iCont,iOut)
!------------------------------------------------------------------------------- Solve:Current Iteration
		call RealSym_Determinant(A(n6),A(n3),A(n7),
     &					NStifN,NStifN,NStifN,detK)
		detKO = detK
!		call DumpRealVar(detKO,"Determinant",1,iOut)
!		! Step 2a: eqn 7
		call Solve_AxEqB(A(n6),A(nPLoad),A(ndeltaUi2),
     &			nStifN,nStifN,iOut)
		call Compute_StrainEnergy(A(n6),A(nPLoad),A(ndeltaUi2),
     &			nStifN,SEnergy,PEnergy,iOut)
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
!===========================================================================================
	call DumpStringVar("Exit:LoadStep_1_iter_1",0,iOut)
	return
	end
