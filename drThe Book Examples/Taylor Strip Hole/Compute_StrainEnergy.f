	Subroutine Compute_StrainEnergy(Stif,F,D,nStif,SEnergy,PEnergy
     &														,iOut)
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
	Real(kind=8)	Stif		     ,F       ,D        
	Dimension		Stif(nStif,nStif),F(nStif),D(nStif)
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	Energy,SEnergy,PEnergy
	DATA Exact		/.02964966844238D0/	
!	//////////////////////
!
!	Strain Energy Calculation: DN-transpose*StifN*DN
!
	Energy	= 0.0D0
	F		= 0.0D0
	do i = 1,nStif
		do j = 1,nStif
			F(i) = F(i) + Stif(i,j)*D(j)
		end do !j
		Energy = Energy + D(i)*F(i)
	end do!i
!
	SEnergy = 0.5D0 * Energy
	EEnergy = 0.5D0 * Energy
	Error	= (Energy - Exact)*100.D0/Energy
!	//////////////////////
	iPrt = 1
	if(iPrt == 1) then
		write(iOut,1000)
		write(iOut,1010) Energy,Exact,Error
	endif
!   		 
	return
 1000 Format(/2x,"Just before Leaving: Compute Strain Energy"/)
 1010 Format(/2x,"Total Potential Energy     =",F20.14/
     &        2x,"Exact (Taylor Chapter 2)   =",F20.14/
     &        2x,"Error                      =",F20.14,1X,"%")
	end   		