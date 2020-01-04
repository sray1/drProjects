	Subroutine Get_SupportedDOFs_Pal(Sx,nSup,nQc1,nQc2,iCont,iOut)
!	Strip shell (Curved Arch) Palazotto
!	Quartic in x and linear in y (Poisson's = 0)				nSup = 30+  8(Theta3)
!	Quintic in x and linear in y (Poisson's = 0)				nSup = 34+ 10(Theta3)
!******************HARDCODED FOR SUPPORT ALONG Y DIRECTION WITH 2 NODES********************
	integer			Sx
	Dimension		Sx(nSup)
!========================================================================   NO DRILL
	integer			DropC05      
	Dimension		DropC05(38)	
	integer			DropC06      
	Dimension		DropC06(44)	! Curved Arch						
!========================================================================   DRILL
	integer			DropC05D      
	Dimension		DropC05D(32)	
	integer			DropC06D      
	Dimension		DropC06D(36)! Curved Arch					
!==========================================================================================
	DATA DropC05
     &	 /	 1, 2, 9,10,							!	u
     &		11,12,13,14,15,16,17,18,19,20,			!	v
     &		21,22,									!	w
     &		31,32,33,34,35,36,37,38,39,40,			!	t1
     &		49,50,									!	t2
     &		51,52,53,54,55,56,57,58,59,60/			!	t3
	DATA DropC06
     &	 /	 1, 2,11,12,							!	u
     &		13,14,15,16,17,18,19,20,21,22,23,24,	!	v
     &		25,26,									!	w
     &		37,38,39,40,41,42,43,44,45,46,47,48,	!	t1
     &		59,60,									!	t2
     &		61,62,63,64,65,66,67,68,69,70,71,72/	!	t3
!==========================================================================================
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
