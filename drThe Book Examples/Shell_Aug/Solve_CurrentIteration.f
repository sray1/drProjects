	Subroutine Solve_CurrentIteration()
	Implicit Real(kind=8) (a-h,o-z)
!========================================================================
	include 'Blank.h'
	include 'Drill.h'
	include 'LoadStepIter.h'
	include 'Wpointers.h'
	include 'SizeVar.h'
	include 'files.h'
	include 'solve.h'
	include 'LogParams.h'
	include 'Augment.h'
!========================================================================
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!========================================================================
	call DumpStringVar("Enter:Solve_CurrentIteration",1,iOut)
!	------------------------------------------------------------------- Solve:Current Iteration
	nxxx = n2
	if((iStep==0).and.(iNut==0)) then
		nxxx = n7
	endif
	call RealSym_Determinant(A(n6),A(n3),A(nxxx),
     &					NStifN,NStifN,NStifN,detK,iOut)
	detKO = detK
	call DumpRealVar(detKO,"Determinant = ",1,iOut)
!	------------------------------------------------------------------ Initialize
!		! Step 2a: eqn 7
!		! Step 3aii: eqn 7
	if(bDrill) then
!			call Solve_AxEqB_Drill(A(n6),A(nPLoad),A(ndeltaUi2),
!     &			nStifN,nStifR,nStif3,Iout)
!		else
!	===================
		call Solve_AxEqB(A(n6),A(nPLoad),A(ndeltaUi2),
     &			nStifN,nStifN,iOut)
!		if((iStep.gt.1).and.(iNut.gt.1)) then
		if(iNut.gt.0) then
!			===================
!			call Solve_AxEqB_Drill(A(n6),A(nGuLam),A(ndeltaUi1),
!     &			nStifN,nStifR,nStif3,Iout)
!			else
			call Solve_AxEqB(A(n6),A(nGuLam),A(ndeltaUi1),
     &			nStifN,nStifN,iOut)
		endif
		call ScaleVector(A(ndeltaUi1),A(ndeltaUi1),-1.D0,nStifN,Iout)
	endif
!	=========================================================
	call Compute_StrainEnergy(A(n6),A(nPLoad),A(ndeltaUi2),
     &			nStifN,SEnergy,PEnergy,iOut)
!===========================================================================================
	call DumpStringVar("Exit:Solve_CurrentIteration",1,iOut)
	return
	end
