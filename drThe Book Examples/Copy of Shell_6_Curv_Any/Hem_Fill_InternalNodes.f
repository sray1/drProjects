	Subroutine Hem_Fill_InternalNodes(nodEl,nQ,
     &				nodGl,nodMax,nDof,nodAssign,nPtr,nEqnMax,
     &			     Nel,iOut)
!															
	Implicit Real(kind=8) (a-h,o-z)
!	===============================================
!	Outputs 
!
	integer nodEl(nQ,nQ),nodGl(nodMax,nDof)
!	---------------------------------------------------------- internal nodes
	if(nEl == 4) then
		abx = 1
	endif
	do i =2,nQ-1
		do j =2,nQ-1
			nodAssign	= nodAssign+1
			nPtr		= nPtr + 1
			nodEl(i,j)	= nodAssign
!			global eqn number				********** later these will be local
!												and eliminated at element level ******** 
			do kk = 1,ndof
				if(nodGl(nPtr,kk) == -1) then							
					nEqnMax = nEqnMax + 1
					nodGl(nPtr,kk) = nEqnMax
				end if
			end do	!kk
		end do	!j
	end do	!i
!	=============
	return
	end   		