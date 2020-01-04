	Subroutine Reset_Penalty_ALL
     &					(iAugRead,iAugWrit,iOldCon,iOut)
	Implicit Real(kind=8) (a-h,o-z)
!========================================================================
	include 'Augment.h'
	include 'LoadStepIter.h'
	include 'SizeVar.h'
	LOGICAL		bOK
!	======================
	Real(kind=8)	OldCon             ,Dummy          
	Dimension		OldCon(Nint1,Nint2),Dummy(Nint1,Nint2)
	Real(kind=8)	Penalt             ,PenaltO          
	Dimension		Penalt(Nint1,Nint2),PenaltO(Nint1,Nint2)
	Real(kind=8)	AugMul             ,AugMulO          
	Dimension		AugMul(Nint1,Nint2),AugMulO(Nint1,Nint2)
!	=============================== 
!========================================================================
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!========================================================================
	call DumpStringVar("Enter:Reset_Penalty_ALL",1,iOut)
!
	Rewind iAugRead
	Rewind iAugWrit
	Rewind iOldCon
!
	xKbyalfa = xKK/alfa
!	=========================================================== Augment Tapes end
	do 10 iEL = 1,nElem
!	-------------------------------------| Read back old Augment Multiplier/Penalty
	call PutGetAugMultiplier(PenaltO,AugMulO,Dummy,
     &			Nint1,Nint2,iAugRead,iEL,2,iOut)
!	-------------------------------------| Read Current Constraints
	call PutGetAugMultiplier(Penalt,AugMul,OldCon,
     &			Nint1,Nint2,iOldCon,iEL,2,iOut)
!	=====================================! Make changes, if needed
	call Reset_Penalty_Element(Penalt,PenaltO,
     &			AugMul,AugMulO,OldCon,xKbyalfa,Iout)
 !	-------------------------------------| Write Current Constraints
	call PutGetAugMultiplier(Penalt,AugMul,OldCon,
     &			Nint1,Nint2,iAugWrit,iEL,1,iOut)
!	=======================
   10 continue
!===========================================================================================
	call DumpStringVar("Exit:Check_Con_Elem_ALL",1,iOut)
	return
	end
