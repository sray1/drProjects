	Subroutine Get_SupportedDOFs_Hem(Sx,nSup,nQc1,nQc2,iCont,iOut)
!******************HARDCODED FOR SUPPORT ALONG Y DIRECTION WITH 2 NODES********************
	integer			Sx
	Dimension		Sx(nSup)
!========================================================================   NO DRILL
	integer			DropC05      
	Dimension		DropC05(38)	
	integer			DropC06      
!	Dimension		DropC06(36)	! Curved Shell						
	Dimension		DropC06(37)	! Curved Shell						
	integer			DropC07      
	Dimension		DropC07(48)	! Curved Shell						
	integer			DropC08      
	Dimension		DropC08(54)	! Curved Shell						
!	=========================================================== Quintic/Quintic
	DATA DropC06
     &	 /	 1,  2,  3,  4,  5,  6, 31, 32, 33, 34, 35, 36,         !	u
     &		37,															 	!	v
     &																!	w
     &																!	t1
     &	   145,146,147,148,149,150,175,176,177,178,179,180,			!	t2
     &       181,182,183,184,185,186,211,212,213,214,215,216/			!	t3
!	=========================================================== Septic/Septic
	DATA DropC07
     &/ 1,  2,  3,  4,  5,  6,  7,  8, 57, 58, 59, 60, 61, 62, 63, 64,    !	u
     &															 		!	v
     &																	!	w
     &																	!	t1
     &257,258,259,260,261,262,263,264,									!	t2
     &313,314,315,316,317,318,319,320,										
     &321,322,323,324,325,326,327,328,									!	t3
     &377,378,379,380,381,382,383,384/									
!	=========================================================== Octic/Octic
	DATA DropC08
     &/ 1,  2,  3,  4,  5,  6,  7,  8,  9,
     & 73, 74, 75, 76, 77, 78, 79, 80, 81,								!	u
     &															 		!	v
     &																	!	w
     &																	!	t1
     &325,326,327,328,329,330,331,332,333,								!	t2
     &397,398,399,400,401,402,403,404,405,										
     &406,407,408,409,410,411,412,413,414,								!	t3
     &478,479,480,481,482,483,484,485,486/									
!	=========================================================== 
	if (nQc1 == 5) Then	! Quartic 
		do 20 i = 1,nSup
   20		Sx(i) = DropC05(i)
	elseif (nQc1 == 6) Then	! Quintic 
		do 50 i = 1,nSup
   50		Sx(i) = DropC06(i)
	elseif (nQc1 == 8) Then	! Septic 
		do 60 i = 1,nSup
   60		Sx(i) = DropC07(i)
	elseif (nQc1 == 9) Then	! Septic 
		do 70 i = 1,nSup
   70		Sx(i) = DropC08(i)
	endif
!-----------   	
	return
	end
