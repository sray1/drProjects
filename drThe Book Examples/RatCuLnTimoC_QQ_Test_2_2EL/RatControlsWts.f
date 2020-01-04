	Subroutine RatControlsWts(Qc,Qx,Qy,Wt,nQc,Nel,Iout)
!	Get all relevant geometric Properties
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	Qc       ,Qx,     Qy     ,Wt
	Dimension		Qc(3,nQc),Qx(nQc),Qy(nQc),Wt(nQc)
	integer			Nel,Iout
!	----------------------------
	do 10 i = 1,nQc
	Qx(i) = Qc(1,i)
	Qy(i) = Qc(2,i)
	Wt(i) = Qc(3,i)
   10 continue 
!	-----------------------
	return
	end
