	Subroutine FormIndex_ELEM_Hem_Any(nodEl,nQ,nodGl,nodMax,nDof,
     &							Indx,nStifEL,Nel,iOut)
!															
	Implicit Real(kind=8) (a-h,o-z)
!	===============================================
!	HARDCODED for nQd1 = nQd2 = 8 and nStifel = 216
!	===============================================
	include 'Scratch.h'
!	------------------	
!		nEqn			= nQd*nQd*ndof
	integer nodEl(nQ,nQ),nodGl(nodMax,nDof)
	
!	Outputs 
!		Indx(nStifEl)	= Indx of assembly for Element 2
!
	integer Indx(nStifEL)
	DATA	nQd1/6/,nQd2/6/
!
!	Indices of location in global stiffness
!
	Indx	= 0
	in		= 0
!	----------------------------------------------------------
	do i = 1, nQ
		do j = 1,nQ
			nod = nodEl(i,j)
			do k = 1,ndof
				in = in+1
				Indx(in) = nodGl(nod,k)	
			end do	!k
		end do	!j
	end do	!i
!	---------------------------------------------------------- Print
	iPrt = 0
	if(iPrt == 1) then
		write(iOut,1000)
		write(iOut,1010) Nel,nStifEL
		do j = 1,6	! dof
			write(iOut,1020) j
			do i = 1,6
				ij = i + 36*(j-1)
				write(iOut,1030) (Indx(ij+6*(k-1)),k = 1,6) 
			end do	! i
		end do	! j
	endif
	iPrt = 0
!	---------------------------------------------------------- Save
	call PutGetIndxEL(iIndxEL,Indx,nStifEL,Nel,1)	! 1 = write
!	---------------------------------------------------------- Save End
	return
 1000 Format(/2x,"Just before Leaving: FormIndexEL_Hem")
 1010 Format(/2x,"Indices for Element#",i2," 
     &						for Global Assembly: 1x"I3)
 1020 Format(/12x,"Degree of freedom = ",i2/)
 1030 Format(22X,6I4)
	end   		