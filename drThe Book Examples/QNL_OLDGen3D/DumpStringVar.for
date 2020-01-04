	Subroutine DumpStringVar(sA,iPrt,iOut)

	Implicit Real(kind=8) (a-h,o-z)
	character*(*) sA
!	iPrt = 0
!-------------------------------------------- 
	if(iPrt == 0) return
	write(iOut,1000) sA
!	-------------
	return
 1000 format(1X,A30)
	end
