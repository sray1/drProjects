	Subroutine Hem_FormIndex_ELEM(nodEl,nQ,nodGl,nodMax,nDof,
     &							Indx,nStifEL,Nel,iOut)
!															
	Implicit Real(kind=8) (a-h,o-z)
!	===============================================
!	HARDCODED for nQd1 = nQd2 = 6 and nStifel = 216
!	HARDCODED for nQd1 = nQd2 = 3 and nStifel = 54
!	===============================================
	include 'Scratch.h'
!	------------------	
!		nEqn			= nQd*nQd*ndof
	integer nodEl(nQ,nQ),nodGl(nodMax,nDof)
	
!	Outputs 
!		Indx(nStifEl)	= Indx of assembly for Element 2
!
	integer Indx(nQ,nQ,nDof)
	DATA	nQd1/6/,nQd2/6/
!	DATA	nQd1/3/,nQd2/3/
!
!	Indices of location in global stiffness
!
	Indx	= 0
	in		= 0
!	----------------------------------------------------------
	do k = 1,ndof
		do i = 1, nQ
			do j = 1,nQ
				Indx(i,j,k) = nodGl(nodEl(i,j),k)	
			end do	!j
		end do	!i
	end do	!k
!	---------------------------------------------------------- Print
	iPrt = 1
	if(iPrt == 1) then
		write(iOut,1000)
		write(iOut,1010) Nel,nStifEL
		write(iOut,2040) ((nodEl(i,j),i = 1,nQ),j = nQ,1,-1)
		do k = 1,6	! dof
			write(iOut,1020) k
			write(iOut,1030) ((Indx(i,j,k),i = 1,nQ),j = nQ,1,-1)
		end do	! k
	endif
	iPrt = 0
!	===========
	return
 1000 Format(/2x,"Just before Leaving: Hem_FormIndex_ELEM")
 2040 Format(/12x,"nodEl(i,j),i = 1,nQ),j = nQ,1,-1"/(6I10))
 1010 Format(/2x,"Indices for Element#",i2," 
     &						for Global Assembly: 1x"I3)
 1020 Format(/12x,"Degree of freedom = ",i2/)
 1030 Format(/12x,"Indx(i,j),i = 1,nQ),j = nQ,1,-1"/(6I10))
	end   		