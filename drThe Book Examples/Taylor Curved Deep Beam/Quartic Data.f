	Subroutine Quartic_Data(Dof,mDof,nDis,mSup,nSup,
     &					Nint,nDim,nDegR,nDegS,nStifS,iOut)
!
!	HARD-CODED FOR A SPECIFIC PROBLEM: QUARTIC-QUARTIC
!	displacements specified at 21,22,23,24,25
!
!	Dof(nDis)			= specified displacements at degree of freedoms	
!	mDof(nDis)			= specified degree of freedoms	
!
	real(kind = 8)	Dof(nDis)
	integer			mDof(nDis),nDis,mSup(nSup),nQcDim
!--------------------------------------------------
	Dof = -.01D0
!
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
	Nint	= 6
	nDegR	= 5  !	for Quartic
	nDegS	= 5  !	for Quartic
	nStifS	= nDim*nDegR*nDegS  !	for Cubic-Cubic
!
!	done
!
	return
	end

