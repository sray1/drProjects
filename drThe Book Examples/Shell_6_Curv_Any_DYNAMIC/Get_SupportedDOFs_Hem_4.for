	Subroutine Get_SupportedDOFs_Hem_4(Sx,nSup,nQc1,nQc2,iCont,iOut)
!******************HARDCODED FOR SUPPORT ALONG Y DIRECTION WITH 2 NODES********************
	integer			Sx
	Dimension		Sx(nSup)
!========================================================================   NO DRILL
	integer			DropC05      
	Dimension		DropC05(38)	
	integer			DropC06      
!	=========================================================== Quintic/Quintic
!	Dimension		DropC06(66)	! Curved Shell						
	Dimension		DropC06(67)	! Curved Shell						
!	=========================================================== Quintic/Quintic
	DATA DropC06
     &	 /	 1,  2,  3,  4,  5,  6,241,242,243,244,245,246,         !	u
     &	   397,398,399,400,401,597,598,599,600,601,                                     
     &	   37,													 	!	v
     &																!	w
     &																!	t1
     &	   145,146,147,148,149,150,361,362,363,364,365,366,			!	t2
     &	   517,518,519,520,521,697,698,699,700,701,         			
     &       181,182,183,184,185,186,391,392,393,394,395,396,			!	t3
     &       547,548,549,550,551,722,723,724,725,726/			
!	=========================================================== 
	if (nQc1 == 5) Then	! Quartic 
		do 20 i = 1,nSup
   20		Sx(i) = DropC05(i)
	elseif (nQc1 == 6) Then	! Quintic 
		do 50 i = 1,nSup
   50		Sx(i) = DropC06(i)
	endif
!-----------   	
	return
	end
