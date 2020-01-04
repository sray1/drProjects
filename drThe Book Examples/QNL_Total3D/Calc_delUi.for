	Subroutine Calc_delUi(delLamdai,Qd1,Qd2,Qd,nA,iOut)
	Implicit Real(kind=8) (a-h,o-z)
!	At the beginning of each Loadstep
	Real(kind=8)	Qd    ,Qd1    ,Qd2
	Dimension		Qd(nA),Qd1(nA),Qd2(nA)
	DATA zero/0.D0/,one/1.0D0/  
	
!
	do 100 i = 1,nA	 
		Qd(i) = Qd1(i) + delLamdai * Qd2(i)
  100 continue
!
!	done
!
	iPrt = 0
	if(iPrt == 1) Then
		write(iOut,1010) nA,(Qd(j),j = 1,nA)
	write(iOut,1020) delLamdai
  110		continue
	endif
!
	return
!
 1010 format("Calc_delUi:Linear_delUi(",I2,")"/
     &        (5(f16.10,1X)/))
 1020 format("delLamdai = ",F16.7/)
	end
