	Subroutine Cubic_TangentLength(Radius,Si,xK,nC,iOut)
!
	Implicit Real(kind=8) (a-h,o-z)
!
	
	real(kind = 8)	Radius,Si,Si2,cosSi2,sinSi2,xK
	integer			nR,nC
!
	if(nC.NE.4) Then
		Stop 'nC.NE.4 (Cubic)'
	endif
!	---------------------------------
	Si2		= Si/2.D0
	cosSi2	= dcos(Si2)
	sinSi2	= dsin(Si2)
!
	xK		= 4.D0*(1.D0 - cosSi2)/sinSi2
!	xK3		= xK/3.D0
!-------------------------------------
	return
	end
	
