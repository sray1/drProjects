	Subroutine Quintic_Data(Dof,mDof,nDis,mSup,nSup,
     &					Nint,nDim,nDegR,nDegS,nStifS,iOut)
!
!	Dof(nDis)			= specified displacements at degree of freedoms	
!	mDof(nDis)			= specified degree of freedoms	
!
	real(kind = 8)	Dof(nDis)
	integer			mDof(nDis),nDis,mSup(nSup),nQcDim
!--------------------------------------------------
	Dof = -.01D0
!
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
	Nint	= 16
	nDegR	= 6  !	for Quintic
	nDegS	= 6  !	for Quintic
	nStifS	= nDim*nDegR*nDegS  !	for Cubic-Cubic
!
!	done
!
	return
	end

