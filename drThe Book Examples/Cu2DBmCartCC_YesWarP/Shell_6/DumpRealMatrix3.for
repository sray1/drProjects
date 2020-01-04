	Subroutine DumpRealMatrix3(A,nR,nC1,nC2,cName,iPrt,iOut)

	Implicit Real(kind=8) (a-h,o-z)
	dimension A(nR,nC1,nC2)
	character*30 cName
!	iPrt = 0
!-------------------------------------------- 
	if(iPrt == 0) return
	write(iOut,1000) cName,nR,nC1,nC2
	do 110 i = 1,nC1
	do 110 j = 1,nC2
	write(iOut,1010) i,j,(A(k,i,j),k = 1,nR)
  110	continue
!	-------------
	return
 1000 format(1X,A20, "(",I3,",",I3,",",I3,") Matrix"/
     &"  i      j           X              Y                Z"/)
 1010 format(I5,2x,I5,2X,(3(g16.5,1X)) )
	end
