	Subroutine RatGeometryProps(Qx,Qy,Wt,nQc,R,Det,RadOfCur,Axes,
     &							Nel,Iout)
!	Get all relevant geometric Properties
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	Qx,     Qy     ,Wt
	Dimension		Qx(nQc),Qy(nQc),Wt(nQc)
	Real(kind=8)	AT,   AM   ,AB   ,tangent
	Dimension		AT(3),AM(3),AB(3),tangent(2)
	Real(kind=8)	Det,RadOfCur
	integer			nDeg,Nel,Iout
!
!		ndegR					= Bezier degree in r-dir = 4
!		ndegS					= Bezier degree in s-dir = 4
!
	Real(kind=8)	Axes      	 
	Dimension		Axes(3,3)
	Real(kind=8)	AJ,     AJI   
!	---------------------------------------------------------------	
	nDeg		= 2		! CONICS
!	---------------------------- Check
	iCheck = 0
!	----------
	if(iCheck == 1) Then
		r = 0.5
	endif
!	----------------------------			
	det			= RatJacobian(nDeg,Qx,Qy,Wt,nQc,r,tangent,Nel,Iout)
	RadOfCur	= 1.D0/
     &				DABS(RatCurvature(nDeg,Qx,Qy,Wt,nQc,r,Nel,Iout))
!	--------------------------------------------------------------- Axes: TMB
	AT(1)	= tangent(1)
	AT(2)	= tangent(2)
	AT(3)	= 0.D0
!	------
	AJ	= dsqrt(AT(1)*AT(1)+AT(2)*AT(2)+AT(3)*AT(3))
	AJI = 1.D0/AJ
!
	Axes(1,1) = AT(1) * AJI
	Axes(1,2) = AT(2) * AJI
	Axes(1,3) = AT(3) * AJI
!	------------------------------- B
	AB(1)	= 0.D0
	AB(2)	= 0.D0
	AB(3)	= 1.D0
!	------
	AJ	= dsqrt(AB(1)*AB(1)+AB(2)*AB(2)+AB(3)*AB(3))
	AJI = 1.D0/AJ
!
	Axes(3,1) = AB(1) * AJI
	Axes(3,2) = AB(2) * AJI
	Axes(3,3) = AB(3) * AJI
!	------------------------
	call CrossProduct(AT,AB,AM)
!	------
	AJ	= dsqrt(AM(1)*AM(1)+AM(2)*AM(2)+AM(3)*AM(3))
	AJI = 1.D0/AJ
!
	AM(1) = AM(1) * AJI
	AM(2) = AM(2) * AJI
	AM(3) = AM(3) * AJI
!
	Axes (2,1) = AM(1)
	Axes (2,2) = AM(2)
	Axes (2,3) = AM(3)
!	-----------------------
	return
	end
