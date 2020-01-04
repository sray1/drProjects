	Subroutine Initiate_Support(Sx,nSup,nQc,iCont,iOut)
	
	integer			Sx
	Dimension		Sx(nSup)
	integer			DropC05      
	Dimension		DropC05(4)	
	integer			DropC06      
	Dimension		DropC06(4)	
!---------------------------
	DATA DropC05 / 6,10,11,15/		! Support Condition for Quartic (nQc = 5)
!
	DATA DropC06 / 7,14,15,18/		! Support Condition for Quintic (nQc = 6)
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
