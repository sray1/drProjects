	Subroutine Compute_uwthetaAtEnd(ArcLen,SLamda,Qd,
     &				iter,MaxIt,Conv,iOut)
!	Qd is Expanded Full after support Condition enforced
!------------------------------------------------------
!-------------------------
	include 'Implicit.h'
!========================================================================
	include 'SizeVar.h'
!	include 'solve.h'
!========================================================================
!
!	Input Variables & Arrays
!
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	Qd     		! Displacements 
	Dimension		Qd(nQd)
	Real(kind=8)	Dis   ,Rot  
	Dimension		Dis(nDim),Rot(nDim)
!
	Data zero/0.D0/,one/1.D0/
!	//////////////////////--------------------------------- Computed at control node 1,0
	call CalcDis_at_a_Pt(Dis,Qd,nQd,nDim,nQd1,nQd2,one,zero)
	call CalcRot_at_a_Pt(Rot,Qd,nQd,nDim,nQd1,nQd2,one,zero)
!================================================================================
	iPrt = 1
	if(iter.eq.MaxIt) iPrt = 1
	if(iPrt == 1) Then
		write(iOut,1000) iter,ArcLen,SLamda,(Dis(i),i=1,3),Conv
		write(iOut,1010)                    (Rot(i),i=1,3)
	endif
!
	return
 1000 Format(5x,"iter = ",I2,1X,"ARC =",F7.3,2x,"Lambda = ",
     &     F7.2,2x,"u = ",F10.5,2x,
!     &	"w = ",F8.5,2x,"theta = ",F8.5,2x,"Error = ",G10.5)  !for 2D:Str/Pal 
     &	"v = ",F10.5,2x,"w = ",F10.5,2x,"Error = ",G10.5)  !for 3D:Bathe
 1010 Format(5x,"       ",2X,1X,"     ",7X,2x,"         ",
     &     7X,2X,"tt= ",F10.5,2x,
!     &	"w = ",F8.5,2x,"theta = ",F8.5,2x,"Error = ",G10.5)  !for 2D:Str/Pal 
     &	"tm= ",F10.5,2x,"tb= ",F10.5,2x)  !for 3D:Bathe
	end   		
