	Subroutine Compute_UpdatedState(A,b,Qd,nDim,nA,iOut)
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	A
	Dimension		A(nA,nA),b(nA),Qd(nA)
	
!
	do 100 i = 1,nA	 
	do 100 j = 1,nA	 
		Qd(i) = Qd(i) - A(i,j)*b(j)
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
 1010 format("Updated State for the Iteration:Qd(",I2,")"/
     &        (5(f16.10,1X)/))
	end
