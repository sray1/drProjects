	Subroutine BZ_Coords_RatBez(Qc,W,nDim,nQc1,nQc2,R_In,R_Out,
     &								Thk,Angle,nElems,iOut)
	
	Implicit Real(kind=8) (a-h,o-z)
!
	real(kind = 8)	Qc(nDim,nQc1,nQc2),W(nDim,nQc1,nQc2)
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
	angRad		= DATAN(1.D0)*Angle/45.D0
!
	Qc			= 0.D0			! zero all
!	--------------------------------------------------- Weights
	cosalf			= DCOS(.5D0*angRad)
!	--------------------------------------------------- X:Outer Radius
	w(1,1,1)		= one
	w(1,1,2)		= cosalf
	w(1,1,3)		= one
!
	Qc(1,1,1)		= 0.0D0
	Qc(1,1,2)		= 0.0D0
	Qc(1,1,3)		= R_Out
!	--------------------------------------------------- Y
	w(2,1,1)		= one
	w(2,1,2)		= cosalf
	w(2,1,3)		= one
!
	Qc(2,1,1)		= 0.D0
	Qc(2,1,2)		= R_Out
	Qc(2,1,3)		= R_Out
!	--------------------------------------------------- X:Inner Radius: 1=Dim/2=i/3=j
	w(1,2,1)		= one
	w(1,2,2)		= cosalf
	w(1,2,3)		= one
!
	Qc(1,2,1)		= R_Out - R_In
	Qc(1,2,2)		= R_Out - R_In
	Qc(1,2,3)		= R_Out
!	--------------------------------------------------- Y
	w(2,2,1)		= one
	w(2,2,2)		= cosalf
	w(2,2,3)		= one
!
	Qc(2,2,1)		= 0.D0
	Qc(2,2,2)		= R_in
	Qc(2,2,3)		= R_In
!--------------------------------------------------- Print Controls
	write(iOut,"(//2x,A9,i2/A70/)") "Element #",1,
     & " Cartesian Coordinates:Inside Radius -> Outside Radius."
!
		write(iOut,1000) (Qc(1,1,j), j =1, nQc2)	! X
		write(iOut,1010) (Qc(2,1,j), j =1, nQc2)
!
		write(iOut,1020) (Qc(1,2,j), j =1, nQc2)
		write(iOut,1030) (Qc(2,2,j), j =1, nQc2)
!--------------------------------------------------- Print Weightss
		write(iOut,2000) (W(1,1,j), j =1, nQc2)	! X
		write(iOut,2010) (W(2,1,j), j =1, nQc2)
!
		write(iOut,2020) (W(1,2,j), j =1, nQc2)
		write(iOut,2030) (W(2,2,j), j =1, nQc2)
!--------------------------------------------------- Plot Geometry


	return

 1001 format(5x,4(2x,f10.5))
!
 1000 format(2x,"Outer Radius..."/5x,3(2x,f10.5),
     &			2x,"X-coordinates")
 1010 format(5x,3(2x,f10.5),2x,"Y-coordinates")
 1020 format(2x,"Inner Radius..."/5x,3(2x,f10.5),
     &			2x,"X-coordinates")
 1030 format(5x,3(2x,f10.5),2x,"Y-coordinates")

 2000 format(2x,"Outer Radius..."/5x,3(2x,f10.5),
     &			2x,"X-Weights")
 2010 format(5x,3(2x,f10.5),2x,"Y-Weights")
 2020 format(2x,"Inner Radius..."/5x,3(2x,f10.5),
     &			2x,"Weights")
 2030 format(5x,3(2x,f10.5),2x,"Y-Weights")
	end
