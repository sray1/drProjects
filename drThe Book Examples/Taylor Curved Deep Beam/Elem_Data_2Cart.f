	Subroutine Elem_Data_2Cart(cElemTyp,Dof,mDof,nDis,mSup,nSup,
     &					Nint,nDim,nDegR,nDegS,nStifS,iOut)
!
!	Dof(nDis)			= specified displacements at degree of freedoms	
!	mDof(nDis)			= specified degree of freedoms	
!
	real(kind = 8)	Dof(nDis)
	integer			mDof(nDis),nDis,mSup(nSup),nQcDim
	character*2		cElemTyp
!--------------------------------------------------
	Dof = .01D0					! all specified displacement are same
!
	if(cElemTyp == "55") then		! Quintic/Quintic
		mDof(1) = 42
		mDof(2) = 48
		mDof(3) = 54
		mDof(4) = 60
		mDof(5) = 66
		mDof(6) = 72
!
		mSup(1)	= 31
		mSup(2)	= 37
		mSup(3)	= 43
		mSup(4)	= 49
		mSup(5)	= 55
		mSup(6)	= 61
		mSup(7)	= 67
!
!		Nint	= 5		! 5 = Too Low: Unstable
		Nint	= 6		! 6 = nQd is Optimal/ 5 = Too Low: Unstable
		nDegR	= 6  !	for Quintic
		nDegS	= 6  !	for Quintic
	elseif(cElemTyp == "44") then		! Quartic/Quartic
		mDof(1) = 30
		mDof(2) = 35
		mDof(3) = 40
		mDof(4) = 45
		mDof(5) = 50
!
		mSup(1)	= 21
		mSup(2)	= 26
		mSup(3)	= 31
		mSup(4)	= 36
		mSup(5)	= 41
		mSup(6)	= 46
!
		Nint	= 4	 	!# of Gauss Pts 	
		Nint	= 5		! OPTIMAL
		nDegR	= 5  !	for Quartic
		nDegS	= 5  !	for Quartic
	elseif(cElemTyp == "33") then		! Cubic/Cubic
		mDof(1) = 47		! displacement specified
		mDof(2) = 50
		mDof(3) = 53
		mDof(4) = 56

		mSup(1)	= 13		! Support specified
		mSup(2)	= 17
		mSup(3)	= 21
		mSup(4)	= 25
		mSup(5)	= 29
	!
!		mSup(6)	= 18	! for radial support also
!		mSup(7)	= 19
!		mSup(8)	= 20
!
		Nint	= 3	 !	# of Gauss Pts 	! Oscillating: Too Low
		Nint	= 5	 !	# of Gauss Pts 	! not needed
		Nint	= 6	 !	# of Gauss Pts 	! not needed
		Nint	=16	 !	# of Gauss Pts 	! not needed
		Nint	= 4	 !	# of Gauss Pts 	! OPTIMAL
		nDegR	= 4  !	for Cubic-Cubic
		nDegS	= 4  !	for Cubic-Cubic
	endif
!
	nStifS	= nDim*nDegR*nDegS  !	for elem
!
!	done
!
	return
	end

