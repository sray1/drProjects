	Subroutine Check_StrainConstrain_Element_ALL
     &					(iAugRead,iAugWrit,iOldCon,bOK)
	Implicit Real(kind=8) (a-h,o-z)
!========================================================================
	include 'Blank.h'
	include 'LoadStepIter.h'
	include 'Wpointers.h'
	include 'Addpoints.h'
	include 'SizeVar.h'
	include 'files.h'
	LOGICAL		bOK
!========================================================================
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!========================================================================
	call DumpStringVar("Enter:Check_Con_Elem_ALL",1,iOut)
!
	Rewind iAugRead
	Rewind iAugWrit
	Rewind iOldCon
	bOK = .TRUE.
!	=========================================================== Augment Tapes end
	do 10 iEL = 1,nElem
!	-------------------------------------| Read old Augment Multiplier/Constraints
	call PutGetAugMultiplier(A(nPenaltO),A(nAugMulO),A(nOldCon),
     &			Nint1,Nint2,iAugRead,iEL,2,iOut)
!	--------------------------------------------------------- 
	call Extract_DispCon(A(nxm),nStifS,A(ndeltaUi2),	!Extract DisRotCOntrols
     &		nStifEL,iEL,iOut)
!	==================================
	call Check_StrainConstrain_Element
     &			(A(nPenalt),A(nAugMulO),A(nAugMul),
     &			A(nOldCon),
     &			A(ndeltaUi2),nStifEL,iEL,A(nBMat),A(nTMat),
     &					bOK,Iout)
!	-------------------------------------| Write Current Augment Multiplier/Constraints on temporary
	call PutGetAugMultiplier(A(nPenalt),A(nAugMul),A(nOldCon),
     &		Nint1,Nint2,iOldCon,iEL,1,iOut)
!	=======================
!	call Check_AugMult_Element(A(nAugMul),A(nAugMulO),bOK,Iout)
 !	=======================
   10 continue
!===========================================================================================
	call DumpStringVar("Exit:Check_Con_Elem_ALL",1,iOut)
	return
	end
