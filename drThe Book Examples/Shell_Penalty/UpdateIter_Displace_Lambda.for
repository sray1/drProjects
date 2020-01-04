	Subroutine UpdateIter_Displace_Lambda(Th1,Th2,Qd1,Qd2,Qd,QdO,	
     &	nA,DeltaLamdai,DeltaLamdai1,DeltaLamdai2,cc,bb,iOut)
	Implicit Real(kind=8) (a-h,o-z)
!	At the beginning of each Loadstep
	Real(kind=8)	Qd1    ,Qd2    ,Qd    ,QdO
	Dimension		Qd1(nA),Qd2(nA),Qd(nA),QdO(nA)
	Logical Imaginary
	DATA zero/0.D0/,one/1.0D0/,two/2.D0/  
!
	indx = 1	! aasumed: Th1>0
	if(Th1*Th2.GE.zero) Then
		indx = 3 
	else if(Th2.GE.zero) Then
		indx = 2
	endif
!
	go to (100,200,300),indx
  100 continue			 
	do 10 i = 1,nA
		QdO(i)	= Qd(i) 
		Qd(i)	= Qd1(i)
   10 continue
	DeltaLamdai = DeltaLamdai1
	go to 500
  200 continue			 
	do 20 i = 1,nA
		QdO(i)	= Qd(i) 
		Qd(i) = Qd2(i)
   20 continue
	DeltaLamdai = DeltaLamdai2
	go to 500
  300 continue
	dLam = -cc/two/bb
	dif1 = dabs(DeltaLamdai1 - dLam)			 
	dif2 = dabs(DeltaLamdai2 - dLam)
	if(dif1.LT.dif2) Then			 
		do 30 i = 1,nA
		QdO(i)	= Qd(i) 
		Qd(i)	= Qd1(i)
   30		continue
		DeltaLamdai = DeltaLamdai1
	else
		do 40 i = 1,nA
		QdO(i)	= Qd(i) 
		Qd(i)	= Qd2(i)
   40		continue
		DeltaLamdai = DeltaLamdai2
	endif
!
!	done
!
  500 continue
	iPrt = 0
	if(iPrt == 1) Then
		write(iOut,1010) nA,(Qd(j),j = 1,nA)
		write(iOut,1020) DeltaLamdai
	endif
!
	return
!
 1010 format("UpdateIter_Displace_Lambda:delUi1(",I2,")"/
     &        (5(f16.10,1X)/))
 1020 format("UpdateIter_Displace_Lambda:DeltaLamdai = ",f10.4/)
	end
