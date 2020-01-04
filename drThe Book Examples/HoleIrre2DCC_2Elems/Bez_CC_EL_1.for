	Subroutine BZ_Coords_EL1(Qc,nR,nC,alfa,beta,Rad,iOut)
	Implicit Real(kind=8) (a-h,o-z)
	real(kind = 8)	Qc
	Dimension		Qc(nR,nC)
	real(kind = 8)	alfa,beta,Rad
	real(kind = 8)	a_x,a_y,b_x,b_y,c_x,c_y,d_x,d_y,d

	integer			nR,nC
!
	Qc			= 0.D0			! zero all
!	-------------------------------------------------	
	xk			= (4.D0/3.D0) * (Dsqrt(2.D0) - 1.D0);
	rut2		= 1.D0/Dsqrt(2.D0);
!	-------------------------------------------------	
	Qc(1, 1)		= 0.0D0
	Qc(2, 1)		= Rad
	Qc(1, 2)		= 0.5D0*xk*Rad
	Qc(2, 2)		= Rad
	Qc(1, 3)		= (.25D0 + (.50D0*xk))*Rad
	Qc(2, 3)		= (.75D0 + (.25D0*xk))*Rad
	Qc(1, 4)		= rut2*Rad
	Qc(2, 4)		= rut2*Rad
	Qc(1, 5)		= 0.0D0
	Qc(2, 5)		= Rad + (     Rad/3.D0)*(beta - 1.D0)
	Qc(1, 9)		= 0.0D0
	Qc(2, 9)		= Rad + (2.D0*Rad/3.D0)*(beta - 1.D0)
	Qc(1,13)		= 0.0D0
	Qc(2,13)		= Rad*beta
	Qc(1,14)		= (1.D0/3.D0)*alfa*Rad
	Qc(2,14)		= Rad*beta
	Qc(1,15)		= (2.D0/3.D0)*alfa*Rad
	Qc(2,15)		= Rad*beta
	Qc(1,16)		= Rad*alfa
	Qc(2,16)		= Rad*beta
!
	Qc(1, 8)		= Qc(1,4) + (Qc(1,16) - Qc(1,4))/3.D0
	Qc(2, 8)		= Qc(2,4) + (Qc(2,16) - Qc(2,4))/3.D0
	Qc(1,12)		= Qc(1,4) + 2.D0*(Qc(1,16) - Qc(1,4))/3.D0
	Qc(2,12)		= Qc(2,4) + 2.D0*(Qc(2,16) - Qc(2,4))/3.D0
!	----------------------------------------------------------------------qc11 
	a_x = Qc(1, 5);
	a_y = Qc(2, 5);
	b_x = Qc(1, 8);
	b_y = Qc(2, 8);
	c_x = Qc(1, 2);
	c_y = Qc(2, 2);
	d_x = Qc(1,14);
	d_y = Qc(2,14);
!	determinant
	d = (b_x - a_x)*(c_y - d_y) - (b_y - a_y)*(c_x - d_x);
!	--------
	Qc(1, 6)		= (1/d)*((b_x - a_x)*((c_y - d_y)*
     &					(c_x - a_x) - (c_x - d_x)*(c_y - a_y))) + a_x
	Qc(2, 6)		= (1/d)*((b_y - a_y)*((c_y - d_y)*
     &					(c_x - a_x) - (c_x - d_x)*(c_y - a_y))) + a_y
!	----------------------------------------------------------------------qc12 
	a_x = Qc(1, 9);
	a_y = Qc(2, 9);
	b_x = Qc(1,12);
	b_y = Qc(2,12);
	c_x = Qc(1, 2);
	c_y = Qc(2, 2);
	d_x = Qc(1,14);
	d_y = Qc(2,14);
!	determinant
	d = (b_x - a_x)*(c_y - d_y) - (b_y - a_y)*(c_x - d_x);
!	--------
	Qc(1,10)		= (1/d)*((b_x - a_x)*((c_y - d_y)*
     &					(c_x - a_x) - (c_x - d_x)*(c_y - a_y))) + a_x
	Qc(2,10)		= (1/d)*((b_y - a_y)*((c_y - d_y)*
     &					(c_x - a_x) - (c_x - d_x)*(c_y - a_y))) + a_y
!	----------------------------------------------------------------------qc21 
	a_x = Qc(1, 5);
	a_y = Qc(2, 5);
	b_x = Qc(1, 8);
	b_y = Qc(2, 8);
	c_x = Qc(1, 3);
	c_y = Qc(2, 3);
	d_x = Qc(1,15);
	d_y = Qc(2,15);
!	determinant
	d = (b_x - a_x)*(c_y - d_y) - (b_y - a_y)*(c_x - d_x);
!	--------
	Qc(1, 7)		= (1/d)*((b_x - a_x)*((c_y - d_y)*
     &					(c_x - a_x) - (c_x - d_x)*(c_y - a_y))) + a_x
	Qc(2, 7)		= (1/d)*((b_y - a_y)*((c_y - d_y)*
     &					(c_x - a_x) - (c_x - d_x)*(c_y - a_y))) + a_y
!	----------------------------------------------------------------------qc22 
	a_x = Qc(1, 9);
	a_y = Qc(2, 9);
	b_x = Qc(1,12);
	b_y = Qc(2,12);
	c_x = Qc(1, 3);
	c_y = Qc(2, 3);
	d_x = Qc(1,15);
	d_y = Qc(2,15);
!	determinant
	d = (b_x - a_x)*(c_y - d_y) - (b_y - a_y)*(c_x - d_x);
!	--------
	Qc(1,11)		= (1/d)*((b_x - a_x)*((c_y - d_y)*
     &					(c_x - a_x) - (c_x - d_x)*(c_y - a_y))) + a_x
	Qc(2,11)		= (1/d)*((b_y - a_y)*((c_y - d_y)*
     &					(c_x - a_x) - (c_x - d_x)*(c_y - a_y))) + a_y
!	---------------------------------------------------------
  100 continue
!
	return
	end
	
