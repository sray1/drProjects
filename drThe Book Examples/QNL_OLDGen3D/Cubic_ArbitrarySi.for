	Subroutine Cubic_ArbitrarySi(QcO,nR,nC,Radius,Si,iOut)
!
	Implicit Real(kind=8) (a-h,o-z)
!
	
	real(kind = 8)	QcO       
	Dimension		QcO(nR,nC)
	real(kind = 8)	Radius,Si,Si2,cosSi,sinSi,cosSi2,sinSi2,xK,xK3
	integer			nR,nC
!
	if(nC.NE.4) Then
		Stop 'nC.NE.4 (Cubic)'
	endif
!	---------------------------------
	Si2		= Si/2.D0
	cosSi	= dcos(Si)
	sinSi	= dsin(Si)
	cosSi2	= dcos(Si2)
	sinSi2	= dsin(Si2)
!
	xK		= 4.D0*(1.D0 - cosSi2)/sinSi2
	xK3		= xK/3.D0
!	-----------------
	QcO		= 0.D0	!ALL
!
!	QcO(1,2)	= 0.D0 
	QcO(2,2)	= xK3 * Radius
!
	QcO(1,3)	= (1.D0 - cosSi - xK3 * sinSi) * Radius
	QcO(2,3)	= (       sinSi - xK3 * cosSi) * Radius
!
	QcO(1,4)	= (1.D0 - cosSi) * Radius
	QcO(2,4)	= (       sinSi) * Radius
!-------------------------------------
	return
	end
	
