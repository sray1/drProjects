	Subroutine Get_Loads_Str_D(LocF,ValF,nLod,nQd1,nQd2,iCont,iOut)
!	STraight strip (beam) in xy plane formulated as in 3D
!	Quartic in x and linear in y (Poisson's = 0)				nLod = 2	           TODO LATER		
!	Quintic in x and Cubic in y (Poisson's = 0)					nLod = 4
!******************HARDCODED FOR MOMENT ABOUT Y DIRECTION WITH 2 NODES********************
	Real*8			ValF      
	Dimension		ValF(nLod)
	integer			LocF
	Dimension		LocF(nLod)
	integer			AddC05      
	Dimension		AddC05(2)	
	integer			AddC06      
	Dimension		AddC06(5)	! Straight Beam	
!---------------------------
	DATA AddC05 / 49,50/! Load Condition for Quartic (nQd = 5) tipMomat freeend theta2
!---------------------------
	DATA AddC06 / 146,147,148,149,150/! (nQd = 6) tipMomat freeend theta2
!------------------------------------
	tupi = DACOS(-1.D0)*2.D0
	if (nQd1 == 5) Then	! Quartic 
		do 10 i = 1,nLod
   		LocF(i) = AddC05(i)
   		ValF(i) = 0.5D0*tupi
!   		ValF(i) = tupi
   10		continue
	elseif (nQd1 == 6) Then	! Quintic 
		do 40 i = 1,nLod
   		LocF(i) = AddC06(i)
   		ValF(i) = 0.2D0*tupi
!   		ValF(i) = tupi
   40		continue
	endif
!-----------   	
	return
	end
