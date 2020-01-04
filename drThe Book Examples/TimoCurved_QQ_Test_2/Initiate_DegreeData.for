	Subroutine Initiate_DegreeData(nStifS,nLoadLoc,iOut,nQc)
	
	integer nStifS,nLoadLoc
!	 
	if (nQc == 4) Then	! Quartic 
		nStifS	=  12				! Singular: 1-Element
		nLoadLoc=  4				! Tip Pt. Load in w-direction 
	elseif (nQc == 5) Then	! Quartic 
		nStifS	=  15				! Singular: 1-Element
		nLoadLoc=  5				! Tip Pt. Load in w-direction 
	elseif (nQc == 6) Then	! Quartic 
		nStifS	=  18				! Singular: 1-Element
		nLoadLoc=  6				! Tip Pt. Load in w-direction 
	endif
!
	return
	end
