	Subroutine Get_SupportedDOFs_Hem(Sx,nSup,nQc1,nQc2,iCont,iOut)
!******************HARDCODED FOR SUPPORT ALONG Y DIRECTION WITH 2 NODES********************
	integer			Sx
	Dimension		Sx(nSup)
!========================================================================   NO DRILL
	integer			DropC05      
	Dimension		DropC05(38)	
	integer			DropC06      
!	=========================================================== Quintic/Quintic
	Dimension		DropC06(36)	! Curved Shell						
!	=========================================================== Quintic/Quintic
	DATA DropC06
     &	 /	 1,  2,  3,  4,  5,  6, 31, 32, 33, 34, 35, 36,         !	u
     &															 	!	v
     &																!	w
     &																!	t1
     &	   145,146,147,148,149,150,175,176,177,178,179,180,			!	t2
     &       181,182,183,184,185,186,211,212,213,214,215,216/			!	t3
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
