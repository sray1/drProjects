	Subroutine Augment_STIF_Arclen(Qdo,Qd,Fs,Stif,nStif,Iout)
!
!	Coerced Isoparametric Quadrilateral_Cubic_Cubic Element
!
!
!	Inputs
!		Nel				= Element Number
!		nStif			= Row or Col size of Stiffness matrix
!		Stif			= Assembled Stiffness matrix (Contracted)
!		Qdo				= Starting State control vector
!		Qd				= Current State control vector
!		Iout			= Error Output file#
!		 	
!	Outputs 
!		Stif(64,64)		= Desired Stiffness Matrix
!		Trace			= trace of the matrix
!
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays
!
	Real(kind=8)	Fs       
	Dimension		Fs(nStif)
	Real(kind=8)	Qdo       ,Qd       ,Stif			  ,Add
	Dimension		Qdo(nStif),Qd(nStif),Stif(nStif,nStif),Add(nStif)
	Data two/2.D0/
!	////////////////////// End load part:Klamda Surface load part to last column
		nS1 = nStif - 1 
		do 10 i = 1,nS1
		Stif(i,nStif) = Stif(i,nStif) - Fs(i)/Qd(nStif)		! take Lambda out
   10		continue
!	////////////////////// Arclen part: to last Row
	do 60 j = 1,nStif
   60	Stif(nStif,j) = Stif(nStif,j) + two*(Qd(j) - Qdo(j))
!
!	done
!
	iPrt = 0
	if(iPrt == 1) Then
		do 110 i = 1,nStif
		write(iOut,1010)nStif,nStif, i,(Stif(i,j),j = 1,nStif)
  110		continue
	endif
!
	return
!
 1010 format("Augmented Stiffness Matrix:Stif(",I2,",",I2,")"/
     &        I5/(3(5(f10.6,1X)/)/))
	return
	end   	
