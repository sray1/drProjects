	Subroutine Get_Loads_Str_TT(LocF,ValF,nLod,nQd1,nQd2,iCont,iOut)
!	STraight strip (beam) in xy plane formulated as in 3D
!	Quartic in x and linear in y (Poisson's = 0)				nLod = 2
!	Quirtic in x and linear in y (Poisson's = 0)				nLod = 2
!******************HARDCODED FOR MOMENT ABOUT Y DIRECTION WITH 2 NODES********************
	Real*8			ValF      
	Dimension		ValF(nLod)
	integer			LocF
	Dimension		LocF(nLod)
	integer			AddC05      
	Dimension		AddC05(2)	
	integer			AddC06      
	Dimension		AddC06(2)	! Straight Beam	
!---------------------------
	DATA AddC05 / 49,50/! Load Condition for Quartic (nQd = 5) tipMomat freeend theta2
!---------------------------
	DATA AddC06 / 47,48/! Load Condition for Quintic (nQd = 6) tipTwistat freeend theta1   ONE ELEM LinY
!	DATA AddC06 / 111,112/! Load Condition for Quintic (nQd = 6) tipTwistat freeend theta1 TWO ELEMSLinY
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
   		ValF(i) = 0.5D0*tupi
!   		ValF(i) = tupi
   40		continue
	endif
!-----------   	
	return
	end
