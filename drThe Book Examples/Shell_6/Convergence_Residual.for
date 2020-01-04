	Subroutine Convergence_Residual(bo,b,nb,Conv,iter,iOut)
!
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	bo    ,b
	Dimension		bo(nb),b(nb)
	
!
	iPrt = 0
	if(iPrt == 1) Then
		write(iOut,1000)
		write(iOut,1010) (bo(i),i = 1,nb)
		write(iOut,1020) (b(i),i = 1,nb)
	endif
!   		 
	bLen = 0.D0
	Conv = 0.D0
	do 100 i = 1,nb
		bLen = bLen + bo(i)*bo(i)
		Conv = Conv + (b(i)-bo(i))*(b(i)-bo(i))
  100 continue
	bLen = dsqrt(bLen)
	Conv = dsqrt(Conv)/bLen
!
!	done
!
	return
 1000 Format(/2x,"Just in: Convergence_Residual"/)
 1010 Format(/2x,"bo - Vector"/
     &        3(2x,5F16.10/) )
 1020 Format(/2x,"b - Vector"/
     &        3(2x,5F16.10/) )
	end
