	Subroutine Check_AugMult_Element(AugMul,AugNulO,bOK,Iout)
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
	include 'SizeVar.h'
	include 'Solve.h'
	include 'LoadStepIter.h'
!============================================
!
!	Input Variables & Arrays
!
	Real(kind=8)	AugMul             ,AugMulO          
	Dimension		AugMul(Nint1,Nint2),AugMulO(Nint1,Nint2)
!	=============================== 
	LOGICAL bOK
	DATA zero/0.D0/,one/1.0D0/,onm/-1.0D0/ 
!============================================================== 
	iPrt = 0
	if(iPrt == 1) then
	call DumpStringVar("Beg:Check_AugMult_Element",iPrt,iOut)
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
!	========================================= check constrain at gauss pt
	AMO = AugMulO(iGau,jGau)
	AM  = AugMul(iGau,jGau)
	if(dabs(AMO - AM).gt.Tol_Aug) then
		bOK = .FALSE.
		return
	endif
!	----------
   60 continue
!	------------------- OK
	bOK = .TRUE.
!	============
  	return
	end   		
	   		