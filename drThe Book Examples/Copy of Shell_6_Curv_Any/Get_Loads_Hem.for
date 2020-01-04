	Subroutine Get_Loads_Hem(LocF,ValF,nLod,nQd1,nQd2,iCont,iOut)
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
	integer			AddC08      
	Dimension		AddC08(2)		
	integer			AddC09      
	Dimension		AddC09(2)		
!---------------------------
	DATA AddC05 / 29,30/! Load Condition for Quartic (nQd = 5) tipForce freeend dis3
!---------------------------
!	=========================================================== Quintic/Cubic
!	DATA AddC06 / 72/! Load Condition for Quintic (nQd = 6) tipForce freeend dis3
!	=========================================================== Quintic/Quintic
	DATA AddC06 /73,103/! Load Condition for Quintic (nQd = 6) tipForce freeend dis3
!	=========================================================== Septic/Septic
	DATA AddC08 /129,185/! Load Condition for Septic (nQd = 8) tipForce freeend dis3
!	=========================================================== Septic/Septic
	DATA AddC09 /163,235/! Load Condition for Septic (nQd = 9) tipForce freeend dis3
!------------------------------------
	Fact(1) = -1.D0		! In      Bezier:ru=0, rv=0
	Fact(2) =  1.D0		! Out     Bezier:ru=1, rj=0
!
	Fact(1) =  1.D0		! Out
	Fact(2) = -1.D0		! In
!
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
	elseif (nQd1 == 8) Then	! Quintic 
		do 50 i = 1,nLod
   		LocF(i) = AddC08(i)
   		ValF(i) = Fact(i)
   50		continue
	elseif (nQd1 == 9) Then	! Quintic 
		do 60 i = 1,nLod
   		LocF(i) = AddC09(i)
   		ValF(i) = Fact(i)
   60		continue
	endif
!	-----------   	
	return
	end
