	Subroutine Initiate_Support(Sx,nSup,nQc,iCont,iOut)
	
	integer			Sx
	Dimension		Sx(nSup)
	integer			DropC05   ,DropC15   ,DropC25   
	Dimension		DropC05(6),DropC15(4),DropC25(4)	
	integer			DropC06   ,DropC16   ,DropC26   
	Dimension		DropC06(6),DropC16(4),DropC26(4)	
!---------------------------
	DATA DropC05 / 1,6,11,16,21,26/	! Support Condition for Quartic (nQc = 5)
	DATA DropC15 / 5,22,10,26/	! Support Condition for Quartic (nQc = 5)
	DATA DropC25 / 5,18, 9,21/	! Support Condition for Quartic (nQc = 5)
!
	DATA DropC06 / 1,7,13,19,25,31/	! Support Condition for Quintic (nQc = 6)
	DATA DropC16 / 1, 6,20,25/	! Support Condition for Quintic (nQc = 6)
!	DATA DropC26 / 9,16,17,24/	! Support Condition for Quintic (nQc = 6)
!------------------------------------
	if (nQc == 5) Then	! Quartic 
		if (iCont == 0) Then 
			do 10 i = 1,nSup
   10			Sx(i) = DropC05(i)
		elseif (iCont == 1) Then  
			do 20 i = 1,nSup
   20			Sx(i) = DropC15(i)
		elseif (iCont == 2) Then  
			do 30 i = 1,nSup
   30			Sx(i) = DropC25(i)
		endif
	elseif (nQc == 6) Then	! Quintic 
		if (iCont == 0) Then 
			do 40 i = 1,nSup
   40			Sx(i) = DropC06(i)
		elseif (iCont == 1) Then  
			do 50 i = 1,nSup
   50			Sx(i) = DropC16(i)
		elseif (iCont == 2) Then  
			do 60 i = 1,nSup
   60			Sx(i) = DropC26(i)
		endif
	endif
!-----------   	
	return
	end
