	Subroutine Compute_uwthetaAtEnd(ArcLen,SLamda,Qd,nQd,nQc,
     &				iter,MaxIt,Conv,iOut)
!	Qd is Expanded Full after support Condition enforced
!------------------------------------------------------
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays
!
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	Qd     		! Displacements 
	Dimension		Qd(nQd)
	Real(kind=8)	Br  
	Dimension		Br(nQc)
	Data one/1.D0/
!	//////////////////////--------------------------------- Computed
!------------------------------------- Displacement/Bernstein
	call Bernstein(Br,nQc,one,iOut)
!-------------------------------------	
	sumU = 0.D0
	sumW = 0.D0
	sumV = 0.D0
	sum1 = 0.D0
	sum2 = 0.D0
	sum3 = 0.D0
	do 10 j= 1,nQc
      sumU = sumU + Br(j)*Qd(j) 
      sumW = sumW + Br(j)*Qd(j+  nQc) 
!      sumt = sumt + Br(j)*Qd(j+5*nQc)		!for 2D:Str/Pal 
      sumV = sumV + Br(j)*Qd(j+2*nQc)		!for 3D:Bathe 
      sum1 = sum1 + Br(j)*Qd(j+3*nQc)		!for 3D:Bathe 
      sum2 = sum2 + Br(j)*Qd(j+4*nQc)		!for 3D:Bathe 
      sum3 = sum3 + Br(j)*Qd(j+5*nQc)		!for 3D:Bathe 
   10 continue
!================================================================================
	iPrt = 1
	if(iter.eq.MaxIt) iPrt = 1
	if(iPrt == 1) Then
		write(iOut,1000) iter,ArcLen,SLamda,sumU,sumW,sumV,Conv
		write(iOut,1010)                    sum1,sum2,sum3
	endif
!
	return
 1000 Format(5x,"iter = ",I2,1X,"ARC =",F7.3,2x,"Lambda = ",
     &     F7.2,2x,"u = ",F10.5,2x,
!     &	"w = ",F8.5,2x,"theta = ",F8.5,2x,"Error = ",G10.5)  !for 2D:Str/Pal 
     &	"w = ",F10.5,2x,"v = ",F10.5,2x,"Error = ",G10.5)  !for 3D:Bathe
 1010 Format(5x,"       ",2X,1X,"     ",7X,2x,"         ",
     &     7X,2X,"tt= ",F10.5,2x,
!     &	"w = ",F8.5,2x,"theta = ",F8.5,2x,"Error = ",G10.5)  !for 2D:Str/Pal 
     &	"tm= ",F10.5,2x,"tb= ",F10.5,2x)  !for 3D:Bathe
	end   		
