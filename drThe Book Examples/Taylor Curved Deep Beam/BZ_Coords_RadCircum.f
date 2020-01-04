	Subroutine BZ_Coords_RadCircum(Qc,nDim,nQc1,nQc2,R_In,R_Out,
     &								Thk,iEl,nElems,iOut)
	
	Implicit Real(kind=8) (a-h,o-z)
!
	real(kind = 8)	Qc       
	Dimension		Qc(nDim,nQc1,nQc2)
	real(kind = 8)	R_In,R_Out,Thk
	integer			nDim,nQc1,nQc2
!
	real*8			zero,one3,two3,one,two
!
	zero		= 0.D0
	one3		= 1.D0/3.D0
	two3		= 2.D0/3.D0
	one			= 1.D0
	two			= 2.D0
!
	piby2		= DATAN(one)*(two - nElems + one)
!
	Qc			= 0.D0			! zero all

!	--------------------------------------------------- Circum:Inner Radius
	Qc(1,1,1)		= 0.0D0
	Qc(1,2,1)		= one3*R_In*piby2
	Qc(1,3,1)		= two3*R_In*piby2
	Qc(1,4,1)		=      R_In*piby2
!	--------------------------------------------------- Radial
	Qc(2,1,1)		= 0.D0
	Qc(2,2,1)		= 0.D0
	Qc(2,3,1)		= 0.D0
	Qc(2,4,1)		= 0.D0
!	--------------------------------------------------- Circum:onethird Radius
	Rad = R_In + one3*Thk
	Qc(1,1,2)		= 0.0D0
	Qc(1,2,2)		= one3*Rad*piby2
	Qc(1,3,2)		= two3*Rad*piby2
	Qc(1,4,2)		=      Rad*piby2
!	--------------------------------------------------- Radial
	Qc(2,1,2)		= one3*Thk
	Qc(2,2,2)		= one3*Thk
	Qc(2,3,2)		= one3*Thk
	Qc(2,4,2)		= one3*Thk
!	--------------------------------------------------- Circum:twothirds Radius
	Rad = R_In + two3*Thk
	Qc(1,1,3)		= 0.0D0
	Qc(1,2,3)		= one3*Rad*piby2
	Qc(1,3,3)		= two3*Rad*piby2
	Qc(1,4,3)		=      Rad*piby2
!	--------------------------------------------------- Radial
	Qc(2,1,3)		= two3*Thk
	Qc(2,2,3)		= two3*Thk
	Qc(2,3,3)		= two3*Thk
	Qc(2,4,3)		= two3*Thk
!	--------------------------------------------------- x:Outer Radius
	Qc(1,1,nQc2)	= 0.0D0
	Qc(1,2,nQc2)	= one3*(R_In+Thk)*piby2
	Qc(1,3,nQc2)	= two3*(R_In+Thk)*piby2
	Qc(1,4,nQc2)	=      (R_In+Thk)*piby2
!	--------------------------------------------------- y
	Qc(2,1,nQc2)	= Thk
	Qc(2,2,nQc2)	= Thk
	Qc(2,3,nQc2)	= Thk
	Qc(2,4,nQc2)	= Thk
!--------------------------------------------------- Print
	write(iOut,"(//2x,A9,i2,A80/)") "Element #",iEl,
     & ": Curvilinear Coordinates:Inside Radius -> Outside Radius"
	do k = 1,nDim
		if(k==1) write (iOut,'(/a30/)') " Circumferential:"
		if(k==2) write (iOut,'(/a30/)') " Radial: "
		do j = 1,nQc2
			write(iOut,1001) (Qc(k,i,j), i =1, nQc1)
		end do !j
	end do !k
!--------------------------------------------------- Print End
	return

 1001 format(5x,4(2x,f10.5))
!
 1000 format(2x,"Circumferential Coordinates..."/5x,4(2x,f10.5),
     &			2x,"Inner Radius")
 1010 format(5x,4(2x,f10.5),2x,"Outer Radius")
 1020 format(2x,"Radial Coordinates..."/5x,4(2x,f10.5),
     &			2x,"Inner Radius")
 1030 format(5x,4(2x,f10.5),2x,"Outer Radius")
	end
