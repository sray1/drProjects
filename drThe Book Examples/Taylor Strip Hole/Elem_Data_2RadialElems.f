	Subroutine Elem_Data_2RadialElems(cElemTyp,nCommon,Dof,mDof,
     &					nDis,mSup,nSup,
     &					Nint,nDim,nDegR,nDegS,nStifEl,iOut)
!
!	Dof(nDis)			= specified displacements at degree of freedoms	
!	mDof(nDis)			= specified degree of freedoms	
!
	real(kind = 8)	Dof(nDis)
	integer			mDof(nDis),nDis,mSup(nSup),nQcDim
	character*2		cElemTyp
!--------------------------------------------------
	Dof = -.01D0
!
	if(cElemTyp == "55") then		! Quintic/Quintic
		mDof(1) = 67
		mDof(2) = 68
		mDof(3) = 69
		mDof(4) = 70
		mDof(5) = 71
		mDof(6) = 72
!
		mSup(1)	=  1
		mSup(2)	= 37
		mSup(3)	=  2
		mSup(4)	=  3
		mSup(5)	=  4
		mSup(6)	=  5
		mSup(7)	=  6
!
		Nint	= 6		! 6 = nQd is Optimal/ 5 = Too Low: Unstable
!		Nint	= 5		! 5 = Too Low: Unstable
		nDegR	= 6  !	for Quintic
		nDegS	= 6  !	for Quintic
	elseif(cElemTyp == "44") then		! Quartic/Quartic
		mDof(1) = 46
		mDof(2) = 47
		mDof(3) = 48
		mDof(4) = 49
		mDof(5) = 50
!
		mSup(1)	=  1
		mSup(2)	= 26
		mSup(3)	=  2
		mSup(4)	=  3
		mSup(5)	=  4
		mSup(6)	=  5
!
		Nint	= 4	 	!# of Gauss Pts 	! OPTIMAL
!		Nint	= 5		! UnStable
		nDegR	= 5  !	for Quartic
		nDegS	= 5  !	for Quartic
	elseif(cElemTyp == "33") then		! Cubic/Cubic
		nCommon	=  8
		mDof(1) = 29
		mDof(2) = 30
		mDof(3) = 31
		mDof(4) = 32
		mDof(5) = 54
		mDof(6) = 55
		mDof(7) = 56
!
		mSup(1)	=  1
		mSup(2)	=  2
		mSup(3)	=  3
		mSup(4)	=  4
		mSup(5)	= 17
		mSup(6)	= 33
		mSup(7)	= 34
		mSup(8)	= 35
!
		Nint	= 4	 !	# of Gauss Pts 	! SubOPTIMAL
		Nint	=16	 !	# of Gauss Pts 	! NOT OPTIMAL
		Nint	= 5	 !	# of Gauss Pts 	! Better
		nDegR	= 4  !	for Cubic-Cubic
		nDegS	= 4  !	for Cubic-Cubic
	endif
!
	nStifEl	= nDim*nDegR*nDegS  !	for elem
!
!	done
!
	return
	end

