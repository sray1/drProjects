	Subroutine UpdateStep_Displace_Lambda(Qd,QdO,Qdm,QdmO,nA,
     &			DeltaLamdai,DelLamdaiO,DelLamdai,inut,iOut)
	Implicit Real(kind=8) (a-h,o-z)
!	At the beginning of each Loadstep
	Real(kind=8)	Qd    ,QdO    ,Qdm    ,QdmO   
	Dimension		Qd(nA),QdO(nA),Qdm(nA),QdmO(nA)
	DATA zero/0.D0/,one/1.0D0/,two/2.D0/  
!
	do 20 i = 1,nA
	    QdmO(i) = Qdm(i)
		Qdm(i)	= Qdm(i) + Qd(i) - QdO(i)
   20 continue
	DelLamdai		= DelLamdaiO + DeltaLamdai
	DelLamdaiO		= DelLamdai
!	
	do 30 i = 1,nA
	   QdO(i) = Qd(i)
   30	continue
!
!	done
!
  500 continue
	iPrt = 0
	if(iPrt == 1) Then
		write(iOut,1010) nA,(Qdm(j),j = 1,nA)
		write(iOut,1020) DelLamdai
	endif
!
	return
!
 1010 format("UpdateStep_Displace_Lambda:delUm(",I2,")"/
     &        (5(f16.10,1X)/))
 1020 format("UpdateStep_Displace_Lambda:DelLamdai = ",f10.4/)
	end
