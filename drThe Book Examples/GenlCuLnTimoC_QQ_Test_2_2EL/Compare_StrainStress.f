	Subroutine Compare_StrainStress_2EL(Qc,nQc,Qd,nQd,P2,
     &                    E,PR,Radius,Depth,Width,
     &					FeM,FeS,FeA,nDim,nPts,Nel,iOut)
!	Qd is Expanded Full after support Condition enforced
!	Compute Exact Solution By Castigliano:
!	M(si) = -PR*(2/pi - sin(si))	 
!
!------------------------------------------------------
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays
!
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	Qc       ,E,R,Depth,Width,Radius,P2
	Real(kind=8)	pi,ri,delri
	Real(kind=8)	Qd     ,FeM      ,FeS      ,FeA    
	Dimension		Qd(nQd),FeM(nDim),FeS(nDim),FeA(nDim)
	Real(kind=8)	Br        
	Dimension		Br(3,nQd)
	Real(kind=8)	AM,BM,CM,Xk,sum
!	//////////////////////
	pi = DATAN(1.D0)*4.0D0
!	P2  = 100.D0/2.D0
!----------------------------------------------------------
	XK = 5.D0/6.D0							! Shear Factor	
	AM = E*Width*Depth*Depth*Depth/12.D0	! EI
	BM = E*Width*Depth						! EA 
	CM = XK*BM/(2.D0*(1.D0+PR))				! kGA
!	//////////////////////
	nStart = 0
	if(Nel == 1) Then
		FeM = 0.0D0
		FeS = 0.0D0
		FeA = 0.0D0
	elseif(Nel == 2) Then
		nStart = nStart + nPts - 1
	endif		 
!	//////////////////////--------------------------------- Computed
	delri = 1.D0/(nPts-1)
!
	do 40 i = 1,nPts
	ri = delri*(i-1)
!------------------------------------- Dtrain-Disp
	Call QQ_StrainDispMat(Qc,nQc,ri,Radius,Br,nQd,Det,
     &							Nel,NelType,Iout)
!-------------------------------------	
	sum = 0.D0
	do 10 j= 1,nQd
   10 sum = sum + Br(1,j)*Qd(j) 
	FeM(i+nStart) = AM*sum*P2			!Bending Moment
	sum = 0.D0
	do 20 j= 1,nQd
   20 sum = sum + Br(2,j)*Qd(j) 
	FeA(i+nStart) = BM*sum*P2			!Axial Force
	sum = 0.D0
	do 30 j= 1,nQd
   30 sum = sum + Br(3,j)*Qd(j) 
	FeS(i+nStart) = CM*sum*P2			!Shear Force
   40 continue
!
	return
	end   		