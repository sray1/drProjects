	Subroutine BZ_Coords_1(Qc,nDim,nQc1,nQc2,R_In,R_Out,Thk,iOut)
!	Describe 45 deg Circle by Cubic 	
	
	real(kind = 8)	Qc       
	Dimension		Qc(nDim,nQc1,nQc2)
	real(kind = 8)	R_In,R_Out,Thk
	integer			nDim,nQc1,nQc2
!
	Qc			= 0.			! zero all

	Subroutine BZ_Coords_EL1(Qc,nR,nC,Radius,iOut)
	real(kind = 8)	Qc       ,QcI     ,QcO
	Dimension		Qc(nR,nC),QcI(2,8),QcO(2,8)
	real(kind = 8)	Radius
	real(kind = 8)	xK,xK3,pi,Si,sinSi,cosSi
	integer			nR,nC
!	-----------------------------
	pi		= DATAN(1.D0)*4.0D0
	Si		= pi/4.D0
	sinSi	= DSIN(Si)
	cosSi	= DCOS(Si)
!
	call Cubic_TangentLength(Radius,Si,xK,4,iOut)
!--------------------------------------------------- x & y: Cubic Starting
	nCs				= 4
	rut2			= dsqrt(2.0D0)
	xK3				= xK/3.D0
!
	Qc(1,1)		= 0.D0
	Qc(2,1)		= 0.D0
	Qc(1,2)		= Qc(1,1)
	Qc(2,2)		= Qc(2,1) + xK3*RADIUS
	Qc(1,4)		= (1.D0 - 1.D0/rut2)*RADIUS
	Qc(2,4)		= (       1.D0/rut2)*RADIUS
	Qc(1,3)		= Qc(1,4) - (xK3*sinSi)*RADIUS	
	Qc(2,3)		= Qc(2,4) - (xK3*cosSi)*RADIUS
!------------------------------------  	
	return
	end
