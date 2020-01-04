	Subroutine UpdateStep_Displace_Lambda(Qd,QdO,Qdm,QdmO,nA,
     &			DeltaLamdai,DelLamdaiO,DelLamdai,jnut,iOut)
	Implicit Real(kind=8) (a-h,o-z)
	common/LoadStepIter/iStep,iNut,bReset
!	At the beginning of each Loadstep
	Real(kind=8)	Qd    ,QdO    ,Qdm    ,QdmO   
	Dimension		Qd(nA),QdO(nA),Qdm(nA),QdmO(nA)
	DATA zero/0.D0/,one/1.0D0/,two/2.D0/  
!
	iPrt = 0
	if(iStep == 9999.and.iNut == 1) then
		iPrt = 1
	endif
	if(iPrt == 1) Then
		write(iOut,1009) nA,(Qdm(j),j = 1,nA)
	endif
!
	iPrt = 0
	do 20 i = 1,nA
	    QdmO(i) = Qdm(i)
		Qdm(i)	= Qdm(i) + Qd(i) - QdO(i)
   20 continue
	DelLamdai		= DelLamdaiO + DeltaLamdai
	DelLamdaiO		= DelLamdai
!	
	iPrt = 0
	if(iStep == 9999.and.iNut == 1) then
		iPrt = 1
	endif
	if(iPrt == 1) Then
		write(iOut,1020) DelLamdai
		write(iOut,1010) nA,(QdO(j),j = 1,nA)
		write(iOut,1011) nA,(Qd(j),j = 1,nA)
		write(iOut,1012) nA,(Qdm(j),j = 1,nA)
	endif
	iPrt = 0
	if(iStep == 9999.and.iNut == 1) then
		iPrt = 0
	endif
!
  500 continue
!
	do 30 i = 1,nA
	   QdO(i) = Qd(i)
   30	continue
!
!	done
!
	return
!
 1009 format("UpStep_Dis_Lam:Qdm_Old(",I2,")"/
     &        (7(f13.8,1X)/))
 1010 format("UpStep_Dis_Lam:QdO(",I2,")"/
     &        (7(f13.8,1X)/))
 1011 format("UpStep_Dis_Lam:Qd(",I2,")"/
     &        (7(f13.8,1X)/))
 1012 format("UpStep_Dis_Lam:Qdm_delUm(",I2,")"/
     &        (7(f13.8,1X)/))
 1020 format("UpdateStep_Displace_Lambda:DelLamdai = ",f10.4/)
	end
