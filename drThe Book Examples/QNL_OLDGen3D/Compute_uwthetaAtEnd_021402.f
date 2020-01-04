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
!	do 10 j= 1,nQc
!      sumU = sumU + Br(j)*Qd(j) 
!      sumW = sumW + Br(j)*Qd(j+  nQc) 
!      sumt = sumt + Br(j)*Qd(j+5*nQc)		!for 2D:Str/Pal 
!      sumt = sumt + Br(j)*Qd(j+2*nQc)			!for 3D:Bathe 
!   10 continue
!================================================================================
!	call DumpRealArray(Qd,nQd,"Qd(nQd)",1,iOut)
	sumU = 0.D0
      sumU = sumU + Br(1)*Qd( 6)			!for 3D:Linear HardCoded for 2Elements
      sumU = sumU + Br(2)*Qd(37)			!for 3D:Linear HardCoded for 2Elements
      sumU = sumU + Br(3)*Qd(38)			!for 3D:Linear HardCoded for 2Elements
      sumU = sumU + Br(4)*Qd(39)			!for 3D:Linear HardCoded for 2Elements
      sumU = sumU + Br(5)*Qd(40)			!for 3D:Linear HardCoded for 2Elements
      sumU = sumU + Br(6)*Qd(41)			!for 3D:Linear HardCoded for 2Elements
	sumt = 0.D0
      sumt = sumt + Br(1)*Qd(12)			!for 3D:Linear HardCoded for 2Elements
      sumt = sumt + Br(2)*Qd(42)			!for 3D:Linear HardCoded for 2Elements
      sumt = sumt + Br(3)*Qd(43)			!for 3D:Linear HardCoded for 2Elements
      sumt = sumt + Br(4)*Qd(44)			!for 3D:Linear HardCoded for 2Elements
      sumt = sumt + Br(5)*Qd(45)			!for 3D:Linear HardCoded for 2Elements
      sumt = sumt + Br(6)*Qd(46)			!for 3D:Linear HardCoded for 2Elements
	sumW = 0.D0
      sumW = sumW + Br(1)*Qd(18)			!for 3D:Linear HardCoded for 2Elements
      sumW = sumW + Br(2)*Qd(47)			!for 3D:Linear HardCoded for 2Elements
      sumW = sumW + Br(3)*Qd(48)			!for 3D:Linear HardCoded for 2Elements
      sumW = sumW + Br(4)*Qd(49)			!for 3D:Linear HardCoded for 2Elements
      sumW = sumW + Br(5)*Qd(50)			!for 3D:Linear HardCoded for 2Elements
      sumW = sumW + Br(6)*Qd(51)			!for 3D:Linear HardCoded for 2Elements
!================================================================================
	iPrt = 1
	if(iter.eq.MaxIt) iPrt = 1
	if(iPrt == 1) Then
		write(iOut,1000) iter,ArcLen,SLamda,sumU,sumW,sumt,Conv
	endif
!
	return
 1000 Format(5x,"iter = ",I2,1X,"ARC =",F7.3,2x,"Lambda = ",
     &     F7.2,2x,"u = ",F10.5,2x,
!     &	"w = ",F8.5,2x,"theta = ",F8.5,2x,"Error = ",G10.5)  !for 2D:Str/Pal 
     &	"w = ",F8.5,2x,"v = ",F8.5,2x,"Error = ",G10.5)  !for 3D:Bathe
	end   		
