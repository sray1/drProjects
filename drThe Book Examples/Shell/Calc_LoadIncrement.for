	Subroutine Calc_LoadIncrement(delLamdai,Qd2,nA,DelLm,DetK,iOut)
	Implicit Real(kind=8) (a-h,o-z)
!	At the beginning of each Loadstep
	Real(kind=8)	Qd    ,Qd2
	Dimension		Qd(nA),Qd2(nA)
	DATA zero/0.D0/,one/1.0D0/  
	
!
	sum = zero
	do 100 i = 1,nA	 
		sum = sum + Qd2(i) * Qd2(i)
  100 continue
!
	delLamdai = DelLm/dsqrt(sum)
!
	if(detK > zero) Then
		delLamdai = dabs(delLamdai)
	else if(detK < zero) Then
		delLamdai = - dabs(delLamdai)
	endif
!
!	done
!
	iPrt = 0
	if(iPrt == 1) Then
		write(iOut,1010) nA,(Qd2(j),j = 1,nA)
	write(iOut,1020) delLamdai,detK,DelLm
  110		continue
	endif
!
	return
!
 1010 format("Calc_LoadIncrement:deltaUi2(",I2,")"/
     &        (5(f16.10,1X)/))
 1020 format("delLamdai = ",F16.7,"detK = ",F16.7,
     &         "DelLm = ",F16.7/)
	end
