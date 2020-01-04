	Subroutine Initiate_DegreeData(nStifS,nLoadLoc,nElem,nDof,
     &											nQc,iCont,iOut)
	
	integer nStifS,nLoadLoc
!	 
	nStifS	=  nElem*nDof*(nQc-1) + nDof		! Singular: nElems
!	-----------------------------------------
	if (nQc == 5) Then								!QUARTIC 
		if (iCont == 0) Then		! Continuity
			if(nElem == 1) Then 
				nLoadLoc=  10				! Tip Pt. Force in w-direction
!				nLoadLoc=  15				! Tip Mom Force in t-direction
			elseif(nElem == 2) Then	 
				nLoadLoc=  38
			endif					! Tip Pt. Force in w-direction 
		else if (iCont == 1) Then	! Continuity 
			nLoadLoc=  18				! Tip Pt. Force in radial-direction
		endif
	else if (nQc == 6) Then							!QUINTIC		 
		if (iCont == 0) Then		! Continuity
			if(nElem == 1) Then 
! 				nLoadLoc=  12				! Tip Pt. Force in w-direction: Palazzotto
				nLoadLoc=  18				! Tip Mom Force in t-direction: StraightBeam
			elseif(nElem == 2) Then	 
				nLoadLoc=  46
			endif					! Tip Pt. Force in w-direction 
		else if (iCont == 1) Then	! Continuity 
			nLoadLoc=  18				! Tip Pt. Force in radial-direction
		endif
	endif
!	------
	return
	end
