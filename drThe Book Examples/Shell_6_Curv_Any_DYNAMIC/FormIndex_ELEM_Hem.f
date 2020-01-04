	Subroutine FormIndex_ELEM_Hem(Indx,nStifEL,Nel,iOut)
!															
	Implicit Real(kind=8) (a-h,o-z)
!	===============================================
!	HARDCODED for nQd1 = nQd2 = 6 and nStifel = 216
!	===============================================
	include 'Scratch.h'
!	------------------	
!	Outputs 
!		Indx(nStifEl)	= Indx of assembly for Element 2
!
	integer Indx(nStifEL)
	DATA	nQd1/6/,nQd2/6/
!
!	Indices of location in global stiffness
!
	Indx = 0
!
	SELECT CASE (Nel)	
		CASE (1)															! Element # 1
			do i = 1,nStifel
				Indx(i) = i
			end do	! i
		CASE (2)															! Element # 2
			do j = 1,6	! dof										
				do i = 1,6								
					Indx(i+36*(j-1)) = 30+i+36*(j-1)		! common Ver		
				end do	! i
			end do	! j
			do j = 1,6	! dof									
				do i = 1,30													
					Indx(i+36*(j-1)+6) = 216+i+30*(j-1)		
				end do	! i
			end do	! j
		CASE (3)															! Element # 3
			do j = 1,6	! dof									
				do i = 1,6								
					Indx(6*(i-1)+36*(j-1)+1) = 6*i+36*(j-1)	! common Hor	
				end do	! i
			end do	! j
			do j = 1,6	! dof									
				do i = 1,6													
					do k = 1,5
						kk = k+6*(i-1)+36*(j-1)+1
						Indx(kk) = 396+k+5*(i-1)+30*(j-1)		
					end do	! k
				end do	! i
			end do	! j
		CASE (4)															! Element # 4
			do j = 1,6	! dof									
					Indx(36*(j-1)+1) = 36*j							! common Cor	
			end do	! j
			do j = 1,6	! dof									
				do i = 2,6								
					Indx(6*(i-1)+36*(j-1)+1) = 222+6*(i-2)+30*(j-1)	! common Hor	
				end do	! i
			end do	! j
			do j = 1,6	! dof										
				do i = 2,6								
					Indx(i+36*(j-1)) = 420+i+30*(j-1)				! common Ver		
				end do	! i
			end do	! j
			do j = 1,6	! dof									
				do i = 2,6													
					do k = 1,5
						kk = k+6*(i-2)+36*(j-1)+7
						Indx(kk) = 576+k+5*(i-2)+25*(j-1)		
					end do	! k
				end do	! i
			end do	! j
		CASE DEFAULT
			stop 'FormIndex_ELEM_Hem:# of Elements.NE.1->4'
	END SELECT
!	---------------------------------------------------------- Print
	iPrt = 1
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
	call PutGetIndxEL(iIndxEL,Indx,nStifEL,Nel,1,iOut)	! 1 = write
!	---------------------------------------------------------- Save End
	return
 1000 Format(/2x,"Just before Leaving: FormIndexEL_Hem")
 1010 Format(/2x,"Indices for Element#",i2," 
     &						for Global Assembly: 1x"I3)
 1020 Format(/12x,"Degree of freedom = ",i2/)
 1030 Format(22X,6I4)
	end   		