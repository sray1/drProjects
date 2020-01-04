	Subroutine Calc_deltaUi1(A,b,Qd,nA,iOut)
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	A
	Dimension		A(nA,nA),b(nA),Qd(nA)
	DATA zero/0.D0/,one/1.0D0/  
	
!
	do 100 i = 1,nA
	sum = zero	
	do 50 j = 1,nA	 
		sum = sum - A(i,j)*b(j)
   50 continue
	Qd(i) = sum
  100 continue
!
!	done
!
	iPrt = 0
	if(iPrt == 1) Then
		write(iOut,1010) nA,(Qd(j),j = 1,nA)
  110		continue
	endif
!
	return
!
 1010 format("Calc_deltaUi1:deltaUi1(",I2,")"/
     &        (5(f16.10,1X)/))
	end
