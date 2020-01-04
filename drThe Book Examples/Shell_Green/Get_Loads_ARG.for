	Subroutine Get_Loads_ARG(Qf,nQ,iOut)  
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
				nLoadLoc=  18				! Tip Pt. force about v-direction: Argyris
	call DumpIntegerVar(nLoadLoc,"Load DOF",1,iOut)
			elseif(nElem == 2) Then	 
				nLoadLoc=  46		! Tip Pt. Force in v-direction:Argyris 
			endif					! Tip Pt. Force in w-direction 
		else if (iCont == 1) Then	! Continuity 
			nLoadLoc=  18				! Tip Pt. Force in radial-direction
		endif
	endif
!	
	Qf		= 0.		! All Zero
	Qf(1)	= -1.D0	!	B-Load: Tip Load	! Straight Beam
!	------
	return
	end
