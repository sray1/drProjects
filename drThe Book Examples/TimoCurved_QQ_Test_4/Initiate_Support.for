	Subroutine Initiate_Support(Sx,nSup,nQc,iCont,iOut)
	
	integer			Sx
	Dimension		Sx(nSup)
	integer			DropC05      
	Dimension		DropC05(3)	
	integer			DropC06      
	Dimension		DropC06(3)	
!---------------------------
	DATA DropC05 / 1, 6,11/		! Support Condition for Quartic (nQc = 5)
!
	DATA DropC06 / 1, 7,13/		! Support Condition for Quintic (nQc = 6)
!------------------------------------
	if (nQc == 5) Then	! Quartic 
		if (iCont == 0) Then 
			do 10 i = 1,nSup
   10			Sx(i) = DropC05(i)
		endif
	elseif (nQc == 6) Then	! Quintic 
		if (iCont == 0) Then 
			do 40 i = 1,nSup
   40			Sx(i) = DropC06(i)
		endif
	endif
!-----------   	
	return
	end
