	Subroutine Cubic_Data(Dof,mDof,nDis,mSup,nSup,
     &					Nint,nDim,nDegR,nDegS,nStifS,iOut)
!	HARD-CODED FOR A SPECIFIC PROBLEM: CUBIC-CUBIC
!	displacements specified at 13,14,15,16
!
!	Dof(nDis)			= specified displacements at degree of freedoms	
!	mDof(nDis)			= specified degree of freedoms	
!
	real(kind = 8)	Dof(nDis)
	integer			mDof(nDis),nDis,mSup(nSup),nQcDim
!--------------------------------------------------
	Dof = -.01D0
!
	mDof(1) = 29
	mDof(2) = 30
	mDof(3) = 31
	mDof(4) = 32
!
	mSup(1)	=  1
	mSup(2)	= 17
	mSup(3)	=  2
	mSup(4)	=  3
	mSup(5)	=  4
!

	Nint	= 5	 !	# of Gauss Pts 	
	nDegR	= 4  !	for Cubic-Cubic
	nDegS	= 4  !	for Cubic-Cubic
	nStifS	= nDim*nDegR*nDegS  !	for Cubic-Cubic
!
!	done
!
	return
	end

