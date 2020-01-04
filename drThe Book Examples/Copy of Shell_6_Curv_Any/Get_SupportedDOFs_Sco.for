	Subroutine Get_SupportedDOFs_Sco(Sx,nSup,nQc1,nQc2,iCont,iOut)
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
!	=========================================================== Quintic/Cubic
!	Dimension		DropC06(40)	! Curved Shell						
!	=========================================================== Quintic/Quintic
	Dimension		DropC06(52)	! Curved Shell						
!	=========================================================== Quintic/Cubic
!	DATA DropC06
!     &	 /	 1,  2,  3,  4, 21, 22, 23, 24,         !	u
!     &		25, 26, 27, 28, 32, 36, 40, 44, 48, 	!	v
!     &		49, 50, 51, 52,							!	w
!     &		76, 80, 84, 88, 92, 96,					!	t1
!     &		117,118,119,120,						!	t2
!     &		124,128,132,136,140,141,142,143,144/	!	t3
!	=========================================================== Quintic/Quintic
	DATA DropC06
     &	 /	 1,  2,  3,  4,  5,  6, 31, 32, 33, 34, 35, 36,         !	u
     &		37, 38, 39, 40, 41, 42, 48, 54, 60, 66, 72,			 	!	v
     &		73, 74, 75, 76, 77, 78,									!	w
     &	   114,120,126,132,138,144,									!	t1
     &	   175,176,177,178,179,180,									!	t2
     &	   186,192,198,204,210,211,212,213,214,215,216/				!	t3
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
