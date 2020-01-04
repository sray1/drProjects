	Subroutine LoadParamChange(Qd1,Qd2,Qd,nA,DelLm,Imaginary,
     &				DeltaLamdai1,DeltaLamdai2,aa,bb,cc,iOut)
	Implicit Real(kind=8) (a-h,o-z)
!	At the beginning of each Loadstep
	Real(kind=8)	Qd    ,Qd1    ,Qd2
	Dimension		Qd(nA),Qd1(nA),Qd2(nA)
	Logical Imaginary
	DATA zero/0.D0/,one/1.0D0/,two/2.D0/  
!
	Imaginary = .FALSE.
!
	suma = zero	
	sumb = zero	
	sumc = zero	
	do 20 i = 1,nA	 
		suma = suma + Qd2(i) * Qd2(i)
		sumb = sumb + (Qd(i)+Qd1(i)) * Qd2(i)
		sumc = sumc + (Qd(i)+Qd1(i)) * (Qd(i)+Qd1(i))
   20 continue
!
	aa = suma 
	bb = sumb
	cc = sumc - DelLm*DelLm
!
	b2ac = bb*bb - aa*cc 
	if(b2ac.LT.zero) Then
		Imaginary = .TRUE.
		DelLm = DelLm/two
		return
	endif
!	----------------------- roots
	DeltaLamdai1 = (-bb + dsqrt(b2ac))/aa
	DeltaLamdai2 = (-bb - dsqrt(b2ac))/aa
!
!	done
!
	iPrt = 0
	if(iPrt == 1) Then
		write(iOut,1020) DeltaLamdai1,DeltaLamdai2
	endif
!
	return
!
 1020 format("LoadParamChange:DeltaLamdai1 = ",F16.7,
     &						"DeltaLamdai1 = ",F16.7/)
	end
