	Subroutine Initiate_DegreeData(nStifS,nLoadLoc,nElem,nDof,
     &											nQc,iCont,iOut)
!	 1 STraight beam in xy plane formulated as in 3D loaded by moment about b
	
	integer nStifS,nLoadLoc
!	 
	nStifS	=  nElem*nDof*(nQc-1) + nDof		! Singular: nElems
!	-----------------------------------------
	if (nQc == 5) Then 
		if (iCont == 0) Then		! Continuity
			if(nElem == 1) Then 
				nLoadLoc=  30				! Tip Pt. Moment about b-direction
			elseif(nElem == 2) Then	 
				nLoadLoc=  38
			endif					! Tip Pt. Force in w-direction 
		else if (iCont == 1) Then	! Continuity 
			nLoadLoc=  18				! Tip Pt. Force in radial-direction
		endif
	else if (nQc == 6) Then		 
		if (iCont == 0) Then		! Continuity
			if(nElem == 1) Then 
!---------------------------
				nLoadLoc=  18				! Tip Pt. force about v-direction: Bathe
!				nLoadLoc=  12				! Tip Pt. force about v-direction: 3DLinear
!				nLoadLoc=  12				! Tip Pt. force about w-direction: Palazzotto
!				nLoadLoc=  36				! Tip Pt. Moment about b-direction: Straight Beam
!---------------------------
			elseif(nElem == 2) Then	 
!	-----------------------------------------
!				nLoadLoc=  51				! Tip Pt. Force in w-direction:Bathe 
				nLoadLoc=  51				! Tip Pt. Force in y-direction:3DLinear 
!	-----------------------------------------
			endif							
		else if (iCont == 1) Then	! Continuity 
			nLoadLoc=  18				! Tip Pt. Force in radial-direction
		endif
	endif
!	------
	return
	end
