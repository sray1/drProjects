	Subroutine Get_Loads_Str(Qf,nQ,iOut)
	Implicit Real(kind=8) (a-h,o-z)
	
	Dimension		Qf(nQ)
!
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
				nLoadLoc=  36				! Tip Pt. Moment about b-direction: Straight Beam
			elseif(nElem == 2) Then	 
				nLoadLoc=  46
			endif					! Tip Pt. Force in w-direction 
		else if (iCont == 1) Then	! Continuity 
			nLoadLoc=  18				! Tip Pt. Force in radial-direction
		endif
	endif
!	
	Qf		= 0.		! All Zero
	Qf(1)	= 6.28D0	! B-Load: Tip Moment	! Straight Beam
!	------
	return
	end