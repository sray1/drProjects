	Subroutine Get_SupportedDOFs_Str_TT_D(Sx,nSup,nQd1,nQd2,iCont,iOut)
!	STraight Cantilevered strip (beam) in xy plane formulated as in 3D
!	Quartic in x and Cubic in y (Poisson's = 0)				nSup = ??
!	Quintic in x and Quartic in y (Poisson's = 0)				nSup = 30
!******************HARDCODED FOR SUPPORT ALONG Y DIRECTION WITH 2 NODES********************
	integer			Sx
	Dimension		Sx(nSup)
	integer			DropC05      
	Dimension		DropC05(36)	
	integer			DropC06      
	Dimension		DropC06(24)	! Straight Beam	
!----------------------------------------------------- Support Condition for Quartic (nQd = 5)
	DATA DropC05											!                 WILL CHANGE LATER
     &	 /	 1, 2,									!	u
     &		11,12,13,14,15,16,17,18,19,20,			!	v
     &		21,22,									!	w
     &		31,32,33,34,35,36,37,38,39,40,			!	t1
     &		41,42,									!	t2
     &		51,52,53,54,55,56,57,58,59,60/			!	t3
!---------------------------
	DATA DropC06
     &	 /	 1, 2, 3, 4, 						!	u
     &		25,26,27,28, 						!	v
     &		49,50,51,52, 						!	w
     &		73,74,75,76, 						!	t1
     &		97,98,99,100,						!	t2
     &		121,122,133,124/					!	t3
!------------------------------------
	if (nQd1 == 5) Then	! Quartic 
		do 10 i = 1,nSup
   10		Sx(i) = DropC05(i)
	elseif (nQd1 == 6) Then	! Quintic 
		do 40 i = 1,nSup
   40		Sx(i) = DropC06(i)
	endif
!-----------   	
	return
	end
