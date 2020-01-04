	Subroutine Compute_StrainEnergy(Stif,D,nStif,SEnergy)
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
	Real(kind=8)	Stif		     ,D        
	Dimension		Stif(nStif,nStif),D(nStif)
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	SEnergy
	
!	//////////////////////
!
!	Strain Energy Calculation: DN-transpose*StifN*DN
!
	SEnergy =0.0D0
	do 20 i = 1,nStif
	do 20 j = 1,nStif
	SEnergy = SEnergy + D(i)*Stif(i,j)*D(j)
   20	continue
!
	SEnergy = 0.5D0 * SEnergy
!   		 
	return
	end   		