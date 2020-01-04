	Subroutine Get_SupportedDOFs_Str(Sx,nSup,nQd1,nQd2,iCont,iOut)
!	STraight Cantilevered strip (beam) in xy plane formulated as in 3D
!	Quartic in x and linear in y (Poisson's = 0)				nSup = 28+8(Theta3)
!	Quintic in x and linear in y (Poisson's = 0)				nSup = 32+10(Theta3)
!******************HARDCODED FOR SUPPORT ALONG Y DIRECTION WITH 2 NODES********************
	integer			Sx
	Dimension		Sx(nSup)
	integer			DropC05      
	Dimension		DropC05(36)	
	integer			DropC06      
	Dimension		DropC06(42)	! Straight Beam	
!	Dimension		DropC06(22)	! Straight Beam		! drilling blocked
!	Dimension		DropC06(12)	! Straight Beam	
!----------------------------------------------------- Support Condition for Quartic (nQd = 5)
	DATA DropC05
     &	 /	 1, 2,									!	u
     &		11,12,13,14,15,16,17,18,19,20,			!	v
     &		21,22,									!	w
     &		31,32,33,34,35,36,37,38,39,40,			!	t1
     &		41,42,									!	t2
     &		51,52,53,54,55,56,57,58,59,60/			!	t3
!---------------------------
	DATA DropC06
     &	 /	 1, 2,									!	u
     &		13,14,15,16,17,18,19,20,21,22,23,24,	!	v
!     &		13,14,											!	v
     &		25,26,									!	w
     &		37,38,39,40,41,42,43,44,45,46,47,48,	!	t1
!     &		37,38,											!	t1
     &		49,50,									!	t2
     &		61,62,63,64,65,66,67,68,69,70,71,72/	!	t3
!     &		61,62/											!	t3
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
