	Subroutine DumpRealVar(A,cName,iPrt,iOut)

	Implicit Real(kind=8) (a-h,o-z)
	character*(*) cName
!-------------------------------------------- 
	if(iPrt == 0) return
	write(iOut,1000) cName,A
!	-------------
	return
 1000 format(1X,A30, " = ",F20.15)
	end
