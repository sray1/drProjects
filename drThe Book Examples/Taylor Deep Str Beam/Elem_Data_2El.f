	Subroutine Elem_Data_2El(cElemTyp,nCommon,Dof,mDof,nDis,
     &					mSup,nSup,
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
		nCommon	= 12
		mDof(1) = 127
		mDof(2) = 128
		mDof(3) = 129
		mDof(4) = 130
		mDof(5) = 131
		mDof(6) = 132
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
		nCommon	= 10
		mDof(1) = 86
		mDof(2) = 87
		mDof(3) = 88
		mDof(4) = 89
		mDof(5) = 90
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
	elseif(cElemTyp == "33") then		! Cubic/cubic
		nCommon	=  8
		mDof(1) = 53
		mDof(2) = 54
		mDof(3) = 55
		mDof(4) = 56
!
		mSup(1)	=  1
		mSup(2)	= 17
		mSup(3)	=  2
		mSup(4)	=  3
		mSup(5)	=  4
!
		Nint	= 4	 !	# of Gauss Pts 	! OPTIMAL
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

