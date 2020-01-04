	Subroutine Invert_A(A,nDim,nA,iOut,iFileStiff)
!	Inverts A(nA,nA) with dimension (nDim,nDim)	
	Implicit Real(kind=8) (a-h,o-z)
!-------------------------------------------- for Check with Quintic
!	Real(kind=8)	B       ,C
!	Dimension		B(16,16),C(16,16)
!-------------------------------------------- for Check with Quintic End
	Real(kind=8)	A           ,B       ,C
	Dimension		A(nDim,nDim),B(16,16),C(16,16)
	Data one/1.D0/                          
!-------------------------------------------- for Check with Quintic
!	B = A
!-------------------------------------------- for Check with Quintic End
	iPrt = 0
	if(iPrt == 1) Then
		write(iOut,1001)nA,nA
		do 5 i = 1,nA
		write(iOut,1010) i,(A(i,j),j = 1,nA)
    5		continue
	endif
!	-----------------------------------------------------------------
	iPrtS = 1
	if(iPrtS == 1) Then
		do 50 i = 1,nA
		write(iFileStiff,1015) nA,nA,i,(A(i,j),j = 1,nA)
   50		continue
	endif
!	-----------------------------------------------------------------
	do 100 n = 1,nA	 
		d= A(n,n)
		do 10 j = 1,nA
		A(n,j) = -A(n,j)/d
   10		continue
!
		do 30 i = 1,nA
			if(n == i) go to 30
			do 20 j = 1,nA
			if(n .NE. j) A(i,j) = A(i,j) + a(i,n)*a(n,j)
   20			continue
			A(i,n) =A(i,n)/d
   30		continue
	A(n,n) = one/d
  100 continue
!-------------------------------------------- for Check with Quintic
!	do 6 i=1,16
!	do 6 j=1,16
!	c(i,j) = 0.D0
!	do 6 k=1,16
!	c(i,j) = c(i,j) + B(i,k)*A(k,j)
!    6 continue
!-------------------------------------------- for Check with Quintic End
!
!	done
!
	iPrt = 0
	if(iPrt == 1) Then
		write(iOut,1002)nA,nA
		do 110 i = 1,nA
		write(iOut,1020) i,(A(i,j),j = 1,nA)
  110		continue
	endif 
!
	return
!
 1001 format("Supported Stiffness Matrix:Stif(",I2,",",I2,")"/)
 1002 format("Inverted Stiffness Matrix:Stif(",I2,",",I2,")"/)
 1010 format(I5/(3(5(f16.6,1X)/)/))
 1015 format("Reduced Stiffness Matrix:Stif(",I3,",",I3,")"/
     &        I5/(3(5(f16.6,1X)/)/))
 1020 format(I5/(3(5(f16.6,1X)/)/))
	end
