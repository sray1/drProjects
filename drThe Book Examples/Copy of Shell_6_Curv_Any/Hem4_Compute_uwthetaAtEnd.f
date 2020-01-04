	Subroutine Hem4_Compute_uwthetaAtEnd(ArcLen,SLamda,Qd,
     &				iter,MaxIt,Conv,Nel,iOut)
!------------------------------------------------------
	include 'Implicit.h'
!	Qd is Expanded Full after support Condition enforced
!-------------------------
	include 'SizeVar.h'
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
	Dimension		Dis1(nDim),Dis2(nDim)
!
	Data zero/0.D0/,one/1.D0/

	if(Nel.GT.2) return
!	//////////////////////--------------------------------- Computed at control node 0,0
	if(Nel == 1) then
		call CalcDis_at_a_Pt(Dis1,Qd,nQd,nDim,nQd1,nQd2,zero,zero)
	elseif(Nel == 2) then 
		call CalcDis_at_a_Pt(Dis2,Qd,nQd,nDim,nQd1,nQd2,one,zero)
	endif
!================================================================================
	iPrt = 1
	if(iter.eq.MaxIt) iPrt = 1
	if(iPrt == 1) Then
		if(Nel == 1) then
			write(iOut,1000) iter,ArcLen,SLamda,(Dis1(i),i=1,3),Conv
		elseif(Nel == 2) then 
			write(iOut,1010)                    (Dis2(i),i=1,3)
		endif
	endif
!
	return
 1000 Format(5x,"iter = ",I2,1X,"ARC =",F7.3,2x,"Lambda = ",
     &     F7.2,2x,"u = ",F10.5,2x,
!     &	"w = ",F8.5,2x,"theta = ",F8.5,2x,"Error = ",G10.5)  !for 2D:Str/Pal 
     &	"v = ",F10.5,2x,"w = ",F10.5,2x,"Error = ",G10.5)  !for 3D:Bathe
 1010 Format(5x,"       ",2X,1X,"     ",7X,2x,"         ",
     &     7X,2X,"u2= ",F10.5,2x,
!     &	"w = ",F8.5,2x,"theta = ",F8.5,2x,"Error = ",G10.5)  !for 2D:Str/Pal 
     &	"v2= ",F10.5,2x,"w2= ",F10.5,2x)  !for 3D:Bathe
	end   		
