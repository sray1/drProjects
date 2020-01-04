	Subroutine BZ_Coords_EL1(Qc,nR,nC,Radius,xLen,iOut)
!	First Describe 45 deg Circle by Cubic 	
!	Degree Elevate to Quartic
	Implicit Real(kind=8) (a-h,o-z)
!
	real(kind = 8)	Qc       ,QcI     ,QcS     ,QcO
	Dimension		Qc(nR,nC),QcI(2,8),QcS(2,8),QcO(2,8)
	real(kind = 8)	Radius,xLen
	real(kind = 8)	xK,pi,Si
	integer			nR,nC
!	We Will Start from nDegStart upto nC-1
!	For now, nDegStart = 3, cubic ALWAYS	

!	-----------------------------
	rut2		= dsqrt(2.0D0)
	xK			= 4.0D0*(rut2 -1.0D0)/3.0D0
!
!--------------------------------------------------- x & y: Cubic Starting
!													for pi/2
!													TOO APPROXIMATE for 
!													CONICS SUBDIVISION		
	nCs				= 4
!
	QcI(1,3)		= (1.0D0 - xK)*RADIUS	
	QcI(1,4)		= RADIUS
	QcI(2,2)		= xK*RADIUS
	QcI(2,3)		= RADIUS
	QcI(2,4)		= RADIUS
!--------------------------------------------------- x & y: Cubic Subdivide
!													for rs = (2/pi)*Si
	pi = DATAN(1.D0)*4.0D0
	Si = xLen/Radius
	rs = (2.D0/pi)*Si
!------------------------------------------------------------------			
!	call Cubic_Subdivide(QcI,nR,nCs,QcS,rs,iOut) ! TOO APPROXIMATE for CONICS
	call Cubic_ArbitrarySi(QcS,nR,nCs,Radius,Si,iOut)
!--------------------------------------------------- x & y: Elevate
	nCo			= nC
!
	Qc			= 0.0D0			! zero all
!------------------------------------ Loop
	nDegElev	= nC - nCs
	nCi			= nCs
	nCo			= nCi + 1	
	do 100 i = 1,nDegElev
!
	call DegreeElevate(QcS,nR,nCi,QcO,nCo,iOut)
!
	QcI			= QcO
	nCi			= nCo
	nCo			= nCi + 1	
  100 continue
!------------------------------------ Set
	do 200 i = 1,nR
	do 200 j = 1,nC
	Qc(i,j)		= QcO(i,j)
  200 continue
!------------------------------------  	
	return
	end
