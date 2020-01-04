	Subroutine DumpRealMatrix(A,nR,nC,cName,iPrt,iOut)

	Implicit Real(kind=8) (a-h,o-z)
	dimension A(nR,nC)
	character*(*) cName
!	iPrt = 0
!-------------------------------------------- 
	if(iPrt == 0) return
	write(iOut,1000) cName,nR,nC
	do 110 i = 1,nR
	write(iOut,1010) i,(A(i,j),j = 1,nC)
  110	continue
!	-------------
	return
 1000 format(1X,A20, "(",I3,",",I3,") Matrix"/)
 1010 format(I5,5x,(4(F20.10,1X)) )
	end
