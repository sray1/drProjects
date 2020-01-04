	Subroutine Compute_Castigliano(E,PoiR,R,Dep,Wid,wc,uc,tc,iOut)
!
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
	Real(kind=8)	wc,uc,tc
	
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
	write(iOut,1010) rh,wc,uc,tc
	return
 1000 Format(/2x,"Just before Leaving: Compute Castiglianos"/)
 1010 Format(/2x,"R/h (Radius/Depth)       = ",F20.4/
     &		2x,"Exact Radial Tip Disp    = ",F20.4,"*P"/
     &        2x,"Exact Axial Tip Dis      = ",F20.4,"*P"/
     &        2x,"Exact Tip Rotation       = ",F20.4,"*P"/)

	end   		