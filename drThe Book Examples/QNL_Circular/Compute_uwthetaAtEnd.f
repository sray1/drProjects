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
	sumt = 0.D0
	do 10 j= 1,nQc
      sumU = sumU + Br(j)*Qd(j) 
      sumW = sumW + Br(j)*Qd(j+  nQc) 
      sumt = sumt + Br(j)*Qd(j+2*nQc) 
   10 continue
!
	iPrt = 1
	if(iter.eq.MaxIt) iPrt = 1
	if(iPrt == 1) Then
		write(iOut,1000) iter,ArcLen,SLamda,sumU,sumW,sumt,Conv
	endif
!
	return
 1000 Format(5x,"iter = ",I2,1X,"ARC =",F7.3,2x,"Lambda = ",
     &     F7.2,2x,"u = ",F9.5,2x,
     &	"w = ",F8.5,2x,"theta = ",F8.5,2x,"Error = ",G10.5)
	end   		
