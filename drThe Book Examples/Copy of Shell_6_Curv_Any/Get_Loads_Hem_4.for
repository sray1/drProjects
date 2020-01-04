	Subroutine Get_Loads_Hem_4(LocF,ValF,nLod,nQd1,nQd2,iCont,iOut)
!	Strip shell (Curved Arch) Palazotto
!	Quintic in xy and linear in xz (Poisson's = 0)				nLod = 2
	Real*8			ValF      ,Fact      
	Dimension		ValF(nLod),Fact(nLod)
	integer			LocF
	Dimension		LocF(nLod)
	integer			AddC05      
	Dimension		AddC05(2)	
	integer			AddC06      
	Dimension		AddC06(2)		
!---------------------------
	DATA AddC05 / 29,30/! Load Condition for Quartic (nQd = 5) tipForce freeend dis3
!---------------------------
!	=========================================================== Quintic/Cubic
!	DATA AddC06 / 72/! Load Condition for Quintic (nQd = 6) tipForce freeend dis3
!	=========================================================== Quintic/Quintic
	DATA AddC06 /73,301/! Load Condition for Quintic (nQd = 6) tipForce freeend dis3
!------------------------------------
	Fact(1) = 1.D0
	Fact(2) = -1.D0
	if (nQd1 == 5) Then	! Quartic 
		do 10 i = 1,nLod
   		LocF(i) = AddC05(i)
   		ValF(i) = 0.5D0*Fact(i)
!   		ValF(i) = tupi
   10		continue
	elseif (nQd1 == 6) Then	! Quintic 
		do 40 i = 1,nLod
   		LocF(i) = AddC06(i)
   		ValF(i) = Fact(i)
   40		continue
	endif
!	-----------   	
	return
	end
