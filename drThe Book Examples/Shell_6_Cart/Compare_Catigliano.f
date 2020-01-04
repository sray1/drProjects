	Subroutine Compare_Castig_2ELModel(E,PoiR,R,Dep,Wid,P,
     &								Qd,nQd,Nel,iOut)
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
	wc = (R*R*R*(pi*pi - 8.D0)/(8.D0*pi*AM)) + (pi*R/(8.D0*CM)) 
     &		+ (pi*R)/(8.D0*BM)	
	wc = wc*P*2.D0	! 
	write(iOut,1000)
!	----------------------------
!	wf = Qd(1)
	if (nQd ==30) Then ! Quartic
		wf = dabs(P)*Qd(10)	! Load = P/2
	else if (nQd ==36) Then ! Quintic
		wf = dabs(P)*Qd(12)	! Load = P/2
	endif
	write(iOut,1010) rh,wc,wf,dabs(wf/wc)
!	----------------------------
	return
 1000 Format(/2x,"Just before Leaving: Compute Castiglianos"/)
 1010 Format(/2x,"R/h (Radius/Depth)       = ",F16.4/
     &		2x,"Exact Radial Tip Disp    = ",F16.4/
     &		2x,"c-Type Radial Tip Disp   = ",F16.4/
     &		2x,"Radial Tip Disp Ratio(wf/wc)        = ",F10.5)

	end   		