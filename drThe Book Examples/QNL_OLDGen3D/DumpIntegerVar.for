	Subroutine DumpIntegerVar(iA,cName,iPrt,iOut)

	Implicit Real(kind=8) (a-h,o-z)
	character*(*) cName
!	iPrt = 0
!-------------------------------------------- 
	if(iPrt == 0) return
	write(iOut,1000) cName,iA
!	-------------
	return
 1000 format(1X,A13, " = ",i16)
	end
