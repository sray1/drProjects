	Subroutine FormStiffness_Load_Aug(iAugRead,iAugWrit)
	Implicit Real(kind=8) (a-h,o-z)
!========================================================================
	include 'Blank.h'
	include 'Drill.h'
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
	include 'Augment.h'
	LOGICAL bOK
!========================================================================
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!========================================================================
	call DumpStringVar("Enter:FormStiffness_Load_Aug",1,iOut)
!	----|------|---------------------------------------------------------- Surface/End Load Vector
	if((iStep==0).and.(iNut==0)) then
		call LV_EndLoad(A(n5),A(n5V),nLod,A(n7),nStifS,Iout)
!	elseif((iStep.gt.1).and.(iNut.gt.1)) then
	elseif((iStep.gt.1).and.(iNut.gt.0)) then
		call LV_Initialize(A(nB),nStifS,Iout)	! Current Load Vector
	endif
!	---------------------------------------------------------------------- Stiffness Matrix
	do 10 iEL = 1,nElem
!	-------------------------------------| Read Current Augment Multiplier/Constraints
	call PutGetAugMultiplier(A(nPenalt),A(nAugMul),A(nOldCon),
     &			Nint1,Nint2,iAugRead,iEL,2,iOut)
!	----------
	iCEL = iEL 
	m2 =n2a
	if((iStep.gt.1)) then
		call Extract_DispCon(A(nxm),nStifS,A(ndelUiEL),	!Extract DisRotCOntrols
     &		nStifEL,iEL,iOut)
	endif
	if(bOpt1) then
		call Opt1_Quad_QQ_STIF(A(nRoCOld),A(nCuCOld),
     &			A(nRoKSav),A(nCKKSav),
     &			A(ndelUiEL),iEL,A(nDMat),A(nBMat),A(nTMat),
     &			A(m2),A(nBfors),A(nStifK),nStifEL,Iout,Trace)
	elseif(bAug) then
		call Quad_QQ_STIF_Aug(A(nPenalt),A(nAugMul),A(nOldCon),
     &			A(nRoCOld),A(nCuCOld),
     &			A(nRoKSav),A(nCKKSav),
     &			A(ndelUiEL),iEL,A(nDMat),A(nBMat),A(nTMat),
     &			A(m2),A(nBfors),A(nStifK),nStifEL,Iout,Trace)
	else
		call Quad_QQ_STIF(A(nRoCOld),A(nCuCOld),
     &			A(nRoKSav),A(nCKKSav),
     &			A(ndelUiEL),iEL,A(nDMat),A(nBMat),A(nTMat),
     &			A(m2),A(nBfors),A(nStifK),nStifEL,Iout,Trace)
	endif
!	Assemble Ist Elem:nSTfK only has body force integral part
	call Assemble_Stif(A(n2c),A(m2),
     &   		nStifEL,A(n2),nStifS,iEL,Iout,Trace)
!	------------------------------------------------------------------ Residual & End Loads
!	Assemble Ist Elem:nBFors only has Residual & body force integral part
!	if((iStep.gt.1).and.(iNut.gt.1)) then
	if((iStep.gt.1).and.(iNut.gt.0)) then
!		----|------|----------------- Residual - lamda*P Load Vector
		call Extract_DispCon(A(n7),nStifS,A(ndelUiEL),	!Extract LoadVector
     &			nStifEL,iEL,iOut)
		call LV_minus_EndLoad(SLamdam+delLamdaiO,A(ndelUiEL),
     &			A(nBfors),nStifEL,iOut)
	endif
!
	if((iStep==0).and.(iNut==0)) then
		m7 = n7
		if(iEL.GT.1) Then
			m7 = nBFors
		endif
	elseif((iStep.gt.1)) then
		m7 = nBFors
	endif
!
	call Assemble_Load(A(n2c),A(m7),
     &   		nStifEL,A(nB),nStifS,iEL,Iout)
   10	continue
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
!	-----------|------|----------------- NonSingular Stiffness: rigid body Out
	call Extract_NonSingularStif(A(n2),nStifC,nStifC,A(n6),nStifN,
     &							A(nSx),nSup,iCont,iOut)
!	----------|------|----------------- Supported Load Vector & State Vector: rigid body Out
	if((iStep==0).and.(iNut==0)) then
		call Extract_ContractedLoadVector(A(n7),nStifC,A(nPLoad),	!P-EndLoad
     &						nStifN,A(nSx),nSup,iCont,iOut)
!	elseif((iStep.gt.1).and.(iNut.gt.1)) then
	elseif((iStep.gt.1).and.(iNut.gt.0)) then
		call Extract_ContractedLoadVector(A(nB),nStifC,A(nGuLam),	!Residual
     &						nStifN,A(nSx),nSup,iCont,iOut)
		call Extract_ContractedLoadVector(A(nxO),nStifC,A(ndelUiO),	!State
     &						nStifN,A(nSx),nSup,iCont,iOut)
	endif		
!===========================================================================================
	call DumpStringVar("Exit:FormStiffness_Load_Aug",1,iOut)
	return
	end
