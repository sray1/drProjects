	Subroutine Get_Current_AugMultiplier(Aug,Nint1,Nint2,nRec)
!	----------------------------------------------------------------------------- 
!	Inputs
!		Nint1				= # of Gauss points in direction_1
!		Nint2				= # of Gauss points in direction_2
! 	
!	Outputs 
!		Aug(Nint1,Nint2)= Current Matrix of Augment Multiplier
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!	==========================
!	include 'files.h'
	include 'files.h'
	include 'scratch.h'
	include 'CurParams.h'
	include 'LoadStepIter.h'
!	==========================
!	common/LoadStepIter/iStep,iNut,bReset
!      common/files/iFileStiff,Ioutt,IoutDef,IoutEnd,iRotCur
!
!	Input Variables & Arrays
!
!
!	Working Variables & Arrays
!
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	Aug                                            
	Dimension		Aug(Nint1,Nint2)
	character*3		readstat
!	==========================================================
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/,onm/-1.0D0/ 
!	-------------------------------------------------------------------- Read Augment Multipliers 
	inquire(iAugTape,NEXTREC = nRecShould)
	if(nRec == nRecShould) then
		call PutGetAugMultiplier(Aug,Nint1,Nint2,iAugTape,nRec,2,iOut)
	endif
!		-------------------------------------------------------- Debug 
	iPrt = 0
	if((iStep == 1).AND.(iNut == 2)) Then
		iPrt = 0
		call DumpStringVar("Beg:Get_Current AugMultiplier",iPrt,iOut)
		call DumpIntegerVar(iStep,"iStep",iPrt,iOut)
		call DumpIntegerVar(iNut,"iNut",iPrt,iOut)
		call DumpIntegerVar(kAugIter,"kAugIter",iPrt,iOut)
		call DumpRealMatrix(Aug,Nint1,Nint2,"Aug",iPrt,iOut)
		call DumpStringVar("End:Get_Current AugMultiplier",iPrt,iOut)
	endif
!	-------------------------------------------------------- Debug : End
	return
	end
