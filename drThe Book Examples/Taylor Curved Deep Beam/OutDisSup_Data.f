	Subroutine OutDisSup_Data(Dof,mDof,nDis,mSup,nSup,
     &                          iDrop,inDrop,iOut)

!	Dof(nDis)			= specified displacements at degree of freedoms	
!	mDof(nDis)			= specified degree of freedoms	
!	iDrop(inDrop)		= Total degree of freedoms to be dropped	
!
	real(kind = 8)	Dof(nDis)
	integer			mDof(nDis),nDis,mSup(nSup)
	integer			iDrop(inDrop)
!--------------------------------------------------
	write(iOut,1000) (mSup(i), i = 1, nSup)
!
	write(iOut,1010)
	do i = 1, nDis
		write(iOut,1020) i,mDof(i),dof(i)
	end do
!
	write(iOut,1030) (iDrop(i), i = 1, inDrop)

!
!	done
!
	return
 1000 format(/5x,'Suppoted DOFs'/(10i5))
 1010 format(/5x,'Specified Displacement DOFs'/
     &		5x,'#s',5x,'    DOFs',5x,'   Value'/)
 1020 format( 5x, i2, 5x,i8,        5x,f8.3)
 1030 format(/5x,'To be Dropped DOFs'/(10i5))
	end

