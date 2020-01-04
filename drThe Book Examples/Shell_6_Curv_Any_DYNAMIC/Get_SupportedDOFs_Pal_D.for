	Subroutine Get_SupportedDOFs_Pal_D(Sx,nSup,nQc1,nQc2,iCont,iOut)
!	Strip shell (Curved Arch) Palazotto
!	Quartic in x and linear in y (Poisson's = 0)				nSup = 30+  8(Theta3)
!	Quintic in x and Cubic in y (Poisson's = 0)				nSup = 34+ 10(Theta3)
!******************HARDCODED FOR SUPPORT ALONG Y DIRECTION WITH 2 NODES********************
!========================================================================   DRILL
	integer			DropC05D      
	Dimension		DropC05D(32)	
	integer			DropC06D      
	Dimension		DropC06D(16)! Curved Arch		LINEAR					
!	Dimension		DropC06D(32)! Curved Arch		CUBIC					
!==========================================================================================
	integer			Sx
	Dimension		Sx(nSup)
!==========================================================================================
	DATA DropC05D
     &	 /	 1, 2, 9,10,							!	u
     &		11,12,13,14,15,16,17,18,19,20,			!	v
     &		21,22,									!	w
     &		31,32,33,34,35,36,37,38,39,40,			!	t1
     &		49,50,									!	t2
     &		51,52,59,60/							!	t3
!	DATA DropC06D
!     &	 /	 1, 2, 3, 4,21,22,23,24,				!	u
!     &		25,26,27,28,45,46,47,48,				!	v
!     &		49,50,51,52,							!	w
!     &		93,94,95,96,							!	t1
!     &		117,118,119,120,						!	t2
!     &		141,142,143,144/						!	t3
	DATA DropC06D									!								SAVE 01/28/04
     &	 /	 1, 2,                        11,12,	!	u
     &		13,14,                        23,24,   	!	v
     &		25,26,									!	w
     &		                              47,48,	!	t1
     &		                              59,60,	!	t2
     &		                              71,72/	!	t3
!==========================================================================================
	if (nQc1 == 5) Then	! Quartic 
		do 10 i = 1,nSup
   10		Sx(i) = DropC05D(i)
	elseif (nQc1 == 6) Then	! Quintic 
		do 40 i = 1,nSup
   40		Sx(i) = DropC06D(i)
	endif
!-----------   	
	return
	end
