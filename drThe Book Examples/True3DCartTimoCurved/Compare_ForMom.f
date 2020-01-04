	Subroutine Compare_Moment_2ELModel(E,R,Dep,Wid,Qd,nQd,Nel,iOut)
!	Qd is Expanded Full after support Condition enforced
!	Compute Exact Solution By Castigliano:
!	M(si) = -PR*(2/pi - sin(si))	 
!
!------------------------------------------------------
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays
!
	Real(kind=8)	E,R,Dep,Wid,pi        
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	rh,si,delsi,AM,ri,delri
	Real(kind=8)	Qd     ,FeMom    ,ExMom
	Dimension		Qd(nQd),FeMom(51),ExMom(51)
	Real(kind=8)	B1Dr  
	Dimension		B1Dr(5)
	
!	//////////////////////
	pi = DATAN(1.D0)*4.0D0
	P2  = 100.D0/2.D0
	delsi = pi/2.D0/50.D0
!	//////////////////////--------------------------------- Exact
	do 10 i = 1,51
	si = delsi*(i-1)
	ExMom(i) = -P2*R*(2.D0/pi - DSIN(si))
   10 continue
!	//////////////////////--------------------------------- Computed
	AM = E*Wid*Dep*Dep*Dep/12.D0			! EI
	xMult = 4.D0*AM*P2/(pi*R)
	delri = 1.D0/50.D0
	do 20 i = 1,51
	ri = delri*(51-i)
!-------------------------------------------------- Deriv.Rotation = Curvature
	B1Dr(1) = -4.D0*(1.D0-ri)*(1.D0-ri)*(1.D0-ri)
	B1Dr(2) = 4.D0*(-3.D0*(1.D0-ri)*(1.D0-ri)*ri 
     &			+(1.D0-ri)*(1.D0-ri)*(1.D0-ri))
	B1Dr(3) = 6.D0*(-2.D0*(1.0D0-ri)*ri*ri
     &			+2.0D0*(1.0D0-ri)*(1.0D0-ri)*ri)
	B1Dr(4) = 4.D0*(-ri*ri*ri+3.0D0*(1.0D0-ri)*ri*ri) 
	B1Dr(5) = 4.D0*ri*ri*ri 
!--------------------------------------------------	
	sum = 0.D0
	do 15 j= 1,5
   15 sum = sum + B1Dr(j)*Qd(j+10) 
	FeMom(i) = xMult*sum 
   20 continue
!	------
	return
	write(iOut,1000)
!	----------------------------
 1000 Format(/2x,"Just before Leaving: Compare_Moment_2ELModel"/)
 1010 Format(/2x,"R/h (Radius/Depth)       = ",F16.4/
     &		2x,"Exact Radial Tip Disp    = ",F16.4,"*P"/
     &		2x,"c-Type Radial Tip Disp   = ",F16.4,"*P"/
     &		2x,"Radial Tip Disp Ratio(wf/wc)        = ",F10.5)

	end   		