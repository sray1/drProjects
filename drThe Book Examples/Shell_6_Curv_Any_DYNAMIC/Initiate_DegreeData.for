	Subroutine Initiate_DegreeData(iOut)
!	 1 STraight beam in xy plane formulated as in 3D loaded by moment about b
	common/SizeVar/	  iGeom,iCont,nDim,nQc,nSup,nDof,nQd,nElem,
     &                  nStifEL,Nint,nCInt,nStifS,nStifC,
     &				  nStifN,nLoadLoc,NelType
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
!				nLoadLoc=  12				! Tip Pt. force about w-direction: Palazzotto
				nLoadLoc=  36				! Tip Pt. Moment about b-direction: Straight Beam
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
