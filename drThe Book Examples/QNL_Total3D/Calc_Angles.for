	Subroutine Calc_Angles(Qd,Qd1p,Qd2p,nA,T1,T2,iOut)
	Implicit Real(kind=8) (a-h,o-z)
!	At the beginning of each Loadstep
	Real(kind=8)	Qd    ,Qd1p    ,Qd2p
	Dimension		Qd(nA),Qd1p(nA),Qd2p(nA)
	DATA zero/0.D0/,one/1.0D0/,two/2.D0/  
!
	T1 = zero
	T2 = zero
	do 20 i = 1,nA	 
		T1 = T1 + Qd(i) * Qd1p(i)
		T2 = T2 + Qd(i) * Qd2p(i)
   20 continue
!
!	done
!
	iPrt = 0
	if(iPrt == 1) Then
		write(iOut,1010) T1,T2
	endif
!
	return
!
 1010 format("Calc_Angles:Theta1 = ",f10.4,2x,"Theta2 = ",f10.4/)
	end
