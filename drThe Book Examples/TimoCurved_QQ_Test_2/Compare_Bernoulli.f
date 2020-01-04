	Subroutine Compare_EulerBernoulli(P,xLen,E,PoiR,Rad,Dep,Wid,
     &											Qd,nQd,iOut)
!	Qd is Expanded Full after support Condition enforced
!	Compute Exact Solution By Castigliano: 
!
!		wc = -[PL**3/3EI]	Cantilever Beam Deflection
!		uc =  [0]			Tip Axial
!		tc =  [PL**2/2EI ]	Tip Rotation
!------------------------------------------------------
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays
!
	Real(kind=8)	P,xLen,E,Rad,Dep,Wid,PR,XK,pi        
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	wc,uc,tc,wf,uf,tf,rh
	Real(kind=8)	Qd
	Dimension		Qd(nQd)
	
!	//////////////////////
	rh = DSQRT(12.D0)*xLen/Dep
!	//////////////////////
	AM = E*Wid*Dep*Dep*Dep/12.D0			! EI
!
!	Tip Values
!
	wc = -P*xLen*xLen*xLen/(3.D0*AM)
	uc = 0.D0
	tc = P*xLen*xLen/(2.D0*AM)												
!
	write(iOut,1000)
!	----------------------------
	wf = Qd(5)
	uf = Qd(10) 
	tf = Qd(15) 
	write(iOut,1010) rh,wc,wf,uc,uf,tc,tf,
     &				dabs(wf/wc),dabs(tf/tc)
!	----------------------------
	return
 1000 Format(/2x,"Just before Leaving: Compute Bernoulli"/)
 1010 Format(/2x,"Slenderness Ratio(Sqrt(12)L/h)			= ",F16.5/
     &		2x,"Exact Radial Tip Disp    = ",F16.10,"*P"/
     &		2x,"c-Type Radial Tip Disp   = ",F16.10,"*P"/
     &        2x,"Exact Axial Tip Disp     = ",F16.10,"*P"/
     &        2x,"c-Type Axial Tip Disp    = ",F16.10,"*P"/
     &        2x,"Exact Tip Rotation       = ",F16.10,"*P"/
     &        2x,"c-Type Tip Rotation      = ",F16.10,"*P"//
     &		2x,"Radial Tip Disp Ratio(wf/wc)			= ",F10.5/
     &		2x,"Tip Rotation Ratio(tf/tc)				= ",F10.5)

	end   		