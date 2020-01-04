	Subroutine Compare_Castig_2ELModel(E,PoiR,R,Dep,Wid,P,
     &								Qd,nQd,nQc,Nel,iOut)
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
	Real(kind=8)	R,Dep,PR,XK,pi        
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	wc,uc,rc,wf,uf,rf,rh
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
!	Center Values
!
	wc = 0.D0
	uc = -0.0100489*P*R*R/AM	! 
	rc = 0.1211846*P*R/AM	
	write(iOut,1000)
!	----------------------------
!	wf = Qd(1)
	wf = P*Qd(1)		! Moment
	uf = P*Qd(nQc+1)	! Moment
	rf = P*Qd(2*nQc+1)	! Moment
	write(iOut,1010) rh,wc,wf,uc,uf,dabs(uf/uc),rc,rf,dabs(rf/rc)
!	----------------------------
	return
 1000 Format(/2x,"Just before Leaving: Compute Castiglianos"/)
 1010 Format(/2x,"R/h (Radius/Depth)       = ",F16.4/
     &		2x,"Exact Radial Mid Disp    = ",F16.4/
     &		2x,"c-Type Radial Mid Disp   = ",F16.4/
     &		2x,"Exact Axial Mid Disp     = ",F16.4/
     &		2x,"c-Type Axial Mid Disp    = ",F16.4/
     &		2x,"Axial Mid Disp Ratio(uf/uc)        = ",F10.5/
     &		2x,"Exact Mid Rotation       = ",F16.4/
     &		2x,"c-Type Mid Rotation      = ",F16.4/
     &		2x,"Mid Rotatn.Disp Ratio(rf/rc)       = ",F10.5)

	end   		