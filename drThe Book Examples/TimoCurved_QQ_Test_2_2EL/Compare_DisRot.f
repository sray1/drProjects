	Subroutine Compare_DisRot_2ELModel(nQc,Qd,nQd,P2,
     &					FeW,FeU,FeR,nDim,nPts,Nel,iOut)
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
	Real(kind=8)	rh,si,delsi,AM,ri,delri,P2
	Real(kind=8)	Qd     ,FeW      ,FeU      ,FeR    
	Dimension		Qd(nQd),FeW(nDim),FeU(nDim),FeR(nDim)
	Real(kind=8)	Br  
	Dimension		Br(nQc)
!	//////////////////////
	nStart = 0
	if(Nel == 1) Then
		FeW = 0.0D0
		FeU = 0.0D0
		FeR = 0.0D0
	elseif(Nel == 2) Then
		nStart = nStart + nPts - 1
	endif		 
!	//////////////////////--------------------------------- Computed
	delri = 1.D0/(nPts-1)
!
	do 40 i = 1,nPts
	ri = delri*(i-1)
!------------------------------------- Displacement/Bernstein
	call Bernstein(Br,nQc,ri,iOut)
!-------------------------------------	
	sum = 0.D0
	do 10 j= 1,nQc
   10 sum = sum + Br(j)*Qd(j) 
	FeW(i+nStart) = sum*P2 
	sum = 0.D0
	do 20 j= 1,nQc
   20 sum = sum + Br(j)*Qd(j+nQc) 
	FeU(i+nStart) = sum*P2 
	sum = 0.D0
	do 30 j= 1,nQc
   30 sum = sum + Br(j)*Qd(j+2*nQc) 
	FeR(i+nStart) = sum*P2 
   40 continue
!
	return
	end   		