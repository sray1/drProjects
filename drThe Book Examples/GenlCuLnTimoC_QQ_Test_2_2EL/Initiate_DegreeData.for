	Subroutine Initiate_DegreeData(nStifS,nLoadLoc,nQc,iCont,iOut)
	
	integer nStifS,nLoadLoc
!	 
	if (nQc == 5) Then	! Quartic 
		nStifS	=  27				! Singular: 2-Element
		if (iCont == 0) Then		! Continuity 
			nLoadLoc=  19				! Tip Pt. Force in radial-direction 
		else if (iCont == 1) Then	! Continuity 
			nLoadLoc=  18				! Tip Pt. Force in radial-direction
		endif	 
	elseif (nQc == 6) Then	! Quartic 
		nStifS	=  33				! Singular: 2-Element
		nLoadLoc=  18				! Tip Pt. Moment in theta-direction 
	endif
!
	return
	end
