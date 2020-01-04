	Subroutine Calc_ArcLength_Step1(Qd,nA,delLamdaiO,DelLm,iOut)
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	Qd
	Dimension		Qd(nA)
	DATA zero/0.D0/,one/1.0D0/  
	
!
	sum = zero
	do 100 i = 1,nA	 
		sum = sum + Qd(i) * Qd(i)
  100 continue
!
	DelLm = delLamdaiO * dsqrt(sum)
!!!=============================================== Temporary
!	DelLm = one
!!!=============================================== Temporary: End
!
!	done
!
	iPrt = 0
	if(iPrt == 1) Then
		write(iOut,1010) nA,(Qd(j),j = 1,nA)
	write(iOut,1020) delLamdaiO,DelLm
  110		continue
	endif
!
	return
!
 1010 format("Calc_ArcLength_Step1:deltaUi2(",I2,")"/
     &        (5(f16.10,1X)/))
 1020 format("delLamdaiO = ",F16.7,2x,"DelLm = ",F16.7/)
	end
