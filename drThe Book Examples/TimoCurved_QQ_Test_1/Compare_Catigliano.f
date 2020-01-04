	Subroutine Compare_Castig_1ELModel(E,PoiR,R,Dep,Wid,
     &								Qd,nQd,iOut)
!	Qd is Expanded Full after support Condition enforced
!	Compute Exact Solution By Castigliano: 
!
!		wc = -[(piPR^3/4EI) + (pi*RP/4kAG) + (piPR)/4EA ]	Tip Radial
!		uc =  [(  PR^3/2EI) - (   RP/2kAG) - (  PR)/2EA ]	Tip Axial
!		tc =  [   PR^2/ EI ]								Tip Rotation
!------------------------------------------------------
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays
!
	Real(kind=8)	Rad,Dep,PR,XK,pi        
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	wc,uc,tc,wf,uf,tf,rh
	Real(kind=8)	Qd
	Dimension		Qd(nQd)
	
!	//////////////////////
	rh = R/Dep
	pi = DATAN(1.D0)*4.0D0
!	//////////////////////
	XK = 5.D0/6.D0							! Shear Factor	
	AM = E*Wid*Dep*Dep*Dep/12.D0			! EI
	BM = E*Wid*Dep							! EA 
	CM = XK*BM*E/(2.D0*(1.D0+PoiR))			! kGA
!
!	Tip Values
!
	wc = (pi*R*R*R/(4.D0*AM)) + (pi*R/(4.D0*CM)) + (pi*R)/(4.D0*BM)	
	wc = -wc
	uc = (   R*R*R/(2.D0*AM)) - (   R/(2.D0*CM)) - (   R)/(2.D0*BM)	
	tc =     R*R/ AM 												
!
	write(iOut,1000)
!	----------------------------
	wf = Qd(5)
	uf = Qd(10) 
	tf = Qd(15) 
	write(iOut,1010) rh,wc,wf,uc,uf,tc,tf,
     &				dabs(wf/wc),dabs(uf/uc),dabs(tf/tc)
!	----------------------------
	Stop
 1000 Format(/2x,"Just before Leaving: Compute Castiglianos"/)
 1010 Format(/2x,"R/h (Radius/Depth)       = ",F16.10/
     &		2x,"Exact Radial Tip Disp    = ",F16.10,"*P"/
     &		2x,"c-Type Radial Tip Disp   = ",F16.10,"*P"/
     &        2x,"Exact Axial Tip Disp     = ",F16.10,"*P"/
     &        2x,"c-Type Axial Tip Disp    = ",F16.10,"*P"/
     &        2x,"Exact Tip Rotation       = ",F16.10,"*P"/
     &        2x,"c-Type Tip Rotation      = ",F16.10,"*P"//
     &		2x,"Radial Tip Disp Ratio(wf/wc)        = ",F10.5/
     &		2x,"Axial Tip Disp Ratio(uf/uc)         = ",F10.5/
     &		2x,"Tip Rotation Ratio(tf/tc)           = ",F10.5)

	end   		