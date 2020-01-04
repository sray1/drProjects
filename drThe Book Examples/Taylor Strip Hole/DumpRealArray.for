	Subroutine DumpRealArray(A,nA,cName,iPrt,iOut)

	Implicit Real(kind=8) (a-h,o-z)
	dimension A(nA)
	character*30 cName
!-------------------------------------------- 
	if(iPrt == 0) return
	write(iOut,1000) cName,nA
	write(iOut,1010) (A(i),i = 1,nA)
!	-------------
	return
 1000 format(1X,A30, "(",I3,") Array"/)
 1010 format(4(F20.10,1X))
	end
