	Subroutine PlotDataEndw(Qd,nptsi,iOutS)
	Implicit Real(kind=8) (a-h,o-z)
!
	
	Real(kind=8)	Qd         
	Dimension		Qd(2,nptsi)
!------------------------------
	write(iOutS,1020) (Qd(1,np),Qd(2,np),np = 1,nptsi)
!-------------------------------------------- need to save?
	return
!
 1010 format(i3,1x,4(3x,e12.5),i5,e12.4)
 1020 format(F15.2,",",F15.2)
 1030 format(i3,e15.5)
	end
