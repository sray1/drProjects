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
	Real(kind=8)	SEnergy,PEnergy
	
!----------------------------------------------------- Load Vector. L2 Norm
	sum = 0.0D0
	do 15 k = 1,nStif
   15	sum = sum + F(k)*F(k)
	sum = DSQRT(sum)
	write(iOut,4000) sum
!----------------------------------------------------- Displ.Controls L2 Norm
	sum = 0.0D0
	do 10 k = 1,nStif
   10	sum = sum + D(k)*D(k)
	sum = DSQRT(sum)
	write(iOut,3000) sum
!------------------------------------------------------
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
!	//////////////////////
!
!	Pot Energy = Strain Energy - DN-transpose*F
!
	PEnergy = SEnergy
	do 30 i = 1,nStif
	PEnergy = PEnergy - D(i)*F(i)
   30	continue
!
	write(iOut,1000)
	write(iOut,1010) SEnergy,PEnergy
!   		 
	return
 1000 Format(/2x,"Just before Leaving: Compute Strain Energy"/)
 1010 Format(/2x,"Strain Energy    =",F15.7/
     &        2x,"Potential Energy =",F15.7)
 3000 FORMAT (5X,'The L2 Norm of Displ. Controls    = ' F10.5/
     &        5X,'(RMS(d))'   )
 4000 FORMAT (5X,'The L2 Norm of Load . Controls    = ' F10.5/
     &        5X,'(RMS(F))'   )
	end   		