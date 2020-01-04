	Subroutine Initialize_AugmentMethod(iAugRead,iAugWrit,iOut)
	
	Implicit Real(kind=8) (a-h,o-z)
!	===================
	include 'Blank.h'
	include 'Scratch.h'
	include 'Wpointers.h'
	include 'SizeVar.h'
	include 'Augment.h'
!	===================
	Real(kind=8)	Augmult
	Dimension		Augmult(Nint1,Nint2) 
	Data			zero/0.D0/,two/2.D0/                         
	
!
!     -------------------------------------------------------------- Augment Initialize
		iAugRead = iAugTape1	! just the other one 
		iAugWrit = iAugTape2	!  
		call Initialize_Penalty(A(nPenalt),Nint1,Nint2,iOut)
		call Initialize_AugMultipliers(A(nAugMul),Nint1,Nint2,iOut)
		call Initialize_Constraints(A(nOldCon),Nint1,Nint2,iOut)
!
		do 7 iEL = 1,nElem
		call PutGetAugMultiplier(A(nPenalt),A(nAugMul),A(nOldCon),
     &				Nint1,Nint2,iAugWrit,iEL,1,iOut)
    7		continue
!	--------------------------------------------------------------
	return
!
 1010 format("AugMult(",I2,")"/(5(f16.6,1X)/))
	end
