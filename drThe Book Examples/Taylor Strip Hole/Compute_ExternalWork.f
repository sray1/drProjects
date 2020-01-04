	Subroutine Compute_ExternalWork(Stif,F,D,nStifEl,nQd12,iOut)
!
!	Coerced Isoparametric Quadrilateral_Cubic_Cubic Element
!
!
!	Inputs
!		nStif					= Row or Col size of Stiffness Control matrix 
!		Stif(nStif,nStif)		= Non-Singular global Stiffness Matrix
!		D(nStif)				= global Displacement Control Vector
!		 	
!	Outputs 
!		SEnergy					= Strain Energy
!
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays
!
	Real(kind=8)	Stif(nStifEL,nStifEL),F(nStifEL),D(nStifEL)
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	sum,nQd12
!	-------------------------------------- Nodal Force
	F	= 0.0D0
	sum	= 0.0D0
	do i = 1,nStifEL
		do j = 1,nStifEL
			F(i) = F(i) + Stif(i,j)*D(j)
		end do !j
		sum = sum + F(i) * D(i)
	end do !j
!	=============================================== Print Force
	write(iOut,1010) (F(mj),mj=1,nQd12)
	write(iOut,1020) (F(mj+nQd12),mj=1,nQd12)
!	-------------------------------------------------- 
	SEnergy = 0.5D0 * sum
!   		 
!
	iPrt = 0
	if(iPrt == 1) then
		write(iOut,1000) SEnergy
	endif
!   		 
	return
!
 1010 format(/5x,"Nodal Forces..."
     &       /5x,"Fu ..."/(8(2x,f10.7)) )
 1020 format(/5x,"Fv ..."/(8(2x,f10.7)) )
 1000 Format(/2x,"Strain Energy    =",g20.7/)
	end   		