	Subroutine Initiate_DegreeData(nStifS,nLoadLoc,iOut,nQc)
	
	integer nStifS,nLoadLoc
!	 
	if (nQc == 5) Then	! Quartic 
		nStifS	=  27				! Singular: 2-Element
		nLoadLoc=  15				! Tip Pt. Moment in theta-direction 
	elseif (nQc == 6) Then	! Quartic 
		nStifS	=  33				! Singular: 2-Element
		nLoadLoc=  18				! Tip Pt. Moment in theta-direction 
	endif
!
	return
	end
