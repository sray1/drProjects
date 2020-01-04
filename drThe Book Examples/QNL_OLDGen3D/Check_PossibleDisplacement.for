	Subroutine Check_PossibleDisplacement(Qd,Qd1,Qd2,
     &				Qdp1,Qdp2,
     &				nA,DeltaLamdai1,DeltaLamdai2,iOut)
	Implicit Real(kind=8) (a-h,o-z)
!	At the beginning of each Loadstep
	Real(kind=8)	Qd    ,Qd1    ,Qd2    ,Qdp1    ,Qdp2
	Dimension		Qd(nA),Qd1(nA),Qd2(nA),Qdp1(nA),Qdp2(nA)
	Logical Imaginary
	DATA zero/0.D0/,one/1.0D0/,two/2.D0/  
!
	do 20 i = 1,nA	 
		Qdp1(i) = Qd(i) + Qd1(i) + DeltaLamdai1 * Qd2(i)
		Qdp2(i) = Qd(i) + Qd1(i) + DeltaLamdai2 * Qd2(i)
   20 continue
!
!
!	done
!
	iPrt = 0
	if(iPrt == 1) Then
		write(iOut,1010) nA,(Qdp1(j),j = 1,nA)
		write(iOut,1020) nA,(Qdp2(j),j = 1,nA)
	endif
!
	return
!
 1010 format("Check_PossibleDisplacement:delUi1p(",I2,")"/
     &        (5(f16.10,1X)/))
 1020 format("Check_PossibleDisplacement:delUi2p(",I2,")"/
     &        (5(f16.10,1X)/))
	end
