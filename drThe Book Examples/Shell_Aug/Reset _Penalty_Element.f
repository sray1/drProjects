	Subroutine Reset_Penalty_Element(Penalt,PenaltO,
     &				AugMul,AugMulO,OldCon,xKbyalfa,Iout)
!
!
!	Notes:	Nint should be atleast 2
!
!	Inputs
!		Qd(nStif)	= Latest displacement controls: state vector
!		Nel			= Element Number
!		Nint		= Number of Gauss Points
!		Iout		= Error Output file#
!		 	
!	Outputs 
!
	Implicit Real(kind=8) (a-h,o-z)
!	===========================
	include 'Augment.h'
	include 'SizeVar.h'
	include 'Solve.h'
	include 'LoadStepIter.h'
!============================================
!
!	Input Variables & Arrays
!
	Real(kind=8)	OldCon          
	Dimension		OldCon(Nint1,Nint2)
	Real(kind=8)	Penalt             ,PenaltO          
	Dimension		Penalt(Nint1,Nint2),PenaltO(Nint1,Nint2)
	Real(kind=8)	AugMul             ,AugMulO          
	Dimension		AugMul(Nint1,Nint2),AugMulO(Nint1,Nint2)
!	=============================== 
	LOGICAL bOK
	DATA zero/0.D0/,one/1.0D0/,onm/-1.0D0/ 
!============================================================== 
	iPrt = 0
	if(iPrt == 1) then
	call DumpStringVar("Beg:Reset_Penalty_Element",iPrt,iOut)
			call DumpIntegerVar(iStep,"iStep",iPrt,iOut)
			call DumpIntegerVar(iNut,"iNut",iPrt,iOut)
	call DumpStringVar("End:",iPrt,iOut)
	endif
	iPrt = 0
!	====================
	nRec = 0
!	Loop over Gauss Locations
	do 60 iGau = 1,Nint1
	do 60 jGau = 1,Nint2
!	------------------------------------------------------------- compare
	constrain = dabs(OldCon(iGau,jGau))
!	========================================= check constrain at gauss pt
	if(constrain.gt.xKbyalfa) then
		AugMul(iGau,jGau) = AugMulO(iGau,jGau)
		Penalt(iGau,jGau) = PenaltO(iGau,jGau) * beta
	endif
!	----------
   60 continue
!	============
  	return
	end   		
	   		