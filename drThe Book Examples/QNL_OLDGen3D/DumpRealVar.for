	Subroutine DumpRealVar(A,cName,iPrt,iOut)

	Implicit Real(kind=8) (a-h,o-z)
	character*(*) cName
!	iPrt = 0
!-------------------------------------------- 
	if(iPrt == 0) return
	write(iOut,1000) cName,A
!	-------------
	return
 1000 format(1X,A10, " = ",G16.7)
	end
