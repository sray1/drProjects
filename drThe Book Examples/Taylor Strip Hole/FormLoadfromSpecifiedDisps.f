	Subroutine LoadfromDis(Ss,nSsI,nSsJ,Dof,mDof,
     &					nDis,mSup,nSup,F,iOut)
!
!
!	Ss(nSsI,nSsJ)		= Stiffness-Singular Matrix (INPUT)	
!	Dof(nDis)			= specified displacements at degree of freedoms	
!	mDof(nDis)			= specified degree of freedoms	
!	F(nDis)				= Force created from specified dof(nDis)	
!
	Implicit Real(kind=8) (a-h,o-z)
	real(kind = 8)	Ss
	Dimension		Ss(nSsI,nSsJ)
	real(kind = 8)	Dof(nDis),F(nSsI),Ftem(nSsI),fsum
	integer			nSsI,nSsJ
	integer			mDof(nDis),nDis,mSup(nSup),nQcDim
!--------------------------------------------------
	integer			i,j,ii
	real*8			dVal
!
	F		= 0.D0	!initialize	
	ii		= 0
	Ftem	= 0.D0	!initialize temporary for checking
!
      do id = 1,nDis	
		nVal = mDof(id)
		dVal = Dof(id)
!
		iPrt = 0
		if(iPrt == 1) then
			write(iOut,1000) nVal, dVal
		endif
!		----------------- pick up the column and mult by spec. dis and save in F
		do i = 1,nSsI
!			if(i == nVal) then
!				go to 30				! it is
!			else
!			do is = 1,nSup					! check if it is supported DOF
!				if(i == mSup(is)) then		! yes? do not add; assumed support is rigid
!					go to 30				! it is
!				endif
!   			end do !is
!
			do k = 1,nDis					! check if the DOF is specified displacement
				if(i == mDof(k)) then		! yes? do not add; displacement specified
 					go to 30				! it is				
				end if
   			end do !k
!
!			ii = ii + 1						! Not supported nor displacement specified
!			Ftem(ii) = Ss(i,nVal)*dVal		! temporary for checking by print
			Ftem(i) = Ss(i,nVal)*dVal		! temporary for checking by print
!			F(ii) = F(ii) - Ss(i,nVal)*dVal		! negative for right hand side
   30			continue
		end do !i
!
		F = F - Ftem		! negative for right hand side
!
		iPrt = 0
		if(iPrt == 1) then
			write(iOut,1020) (Ftem(jj),jj = 1,nSsI)
			write(iOut,1010) (F(jj),jj = 1,nSsI)
!			Pause
		endif
!
		Ftem = 0.D0
		ii		= 0
      end do !id
!	-------------------------------- done
	return
!
 1000 format(//"Specified DOF = ",i3,5x,
     &            " Specified Displacement = ",f7.3/)
 1010 format("Force vector"/ (6(5x,f10.4)))
 1020 format("Debug Force vector:Ftem"/ (6(5x,f10.4)))
 1030 format(//"Total Load = ",F16.10//)
!
	return
	end

