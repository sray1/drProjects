	Subroutine FormDisRot_N_Derivs(Qd,nQd,Br,H1D,nQc,AJI,HD,nG,nC,
     &								Iout)
!	----------------------------------------------------------------------------- 
!	t		= column vector
!	----------------------------------------------------------------------------- 
!	Inputs
!		nQc				= Order of the Bezier
!		Qd(nQd)		= Current Equilibrated Displacement Controls				
!		r				= location Pt:between [0,1]
!		det				= Jacobian
!		nG				= 12
!		nC				= 3
! 	
!	Outputs 
!		HD(nG)			= {dis,rot,disPrimed,rotPrimed}
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	Qd           
	Dimension		Qd(nQd)
	Real(kind=8)	Br   
	Dimension		Br(nQc)
	Real(kind=8)	H1D                	 
	Dimension		H1D(nQc)
	Real(kind=8)	HD    ,Ro                           
	Dimension		HD(nG),Ro(nC)
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!-------------------------------------------------- Prepare:Displacement/Derivatives
	HD	= zero ! all
!------------------------------------------------- ! Current Displacements & derivatives
	do 10 i = 1,nC
	n1 = (i-1)*nQc
	i3 = i+3
	n3 = (i3-1)*nQc
	i6 = i+6
	n6 = (i6-1)*nQc
	i9 = i+9
	n9 = (i9-1)*nQc
	do 10 j = 1,nQc			 
	HD(i)	= HD(i)  + Br(j)*Qd(n1+j)		!dis	
	HD(i3)	= HD(i3) + Br(j)*Qd(n3+j)		!rot		
!	-------------------------------------------- derivatives 
	HD(i6)	= HD(i6) + H1D(j)*Qd(n6+j)*AJI	!dis-primed
	HD(i9)	= HD(i9) + H1D(j)*Qd(n9+j)*AJI	!rot-primed
   10	continue
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
		write(Iout,1010) (HD(j),j = 1,nG)
	endif
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format(1X,"Current DisRot vector..."/2X,3(f10.7,1X))
	end
