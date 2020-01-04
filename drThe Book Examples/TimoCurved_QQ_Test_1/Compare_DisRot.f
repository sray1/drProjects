	Subroutine Compare_DisRot_1ELModel(nQc,Qd,nQd,P2,
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
	FeW = 0.0D0
	FeU = 0.0D0
	FeR = 0.0D0
!	//////////////////////--------------------------------- Computed
	delri = 1.D0/(nPts-1)
!
	do 40 i = 1,nPts
	ri = delri*(nPts-i)
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
!	--------------------------------------- Print
	write(iOut,1000)
	write(iOut,1010) nPts,Nel,(FeW(i),i = 1,nPts)
	write(iOut,1020) nPts,Nel,(FeU(i),i = 1,nPts)
	write(iOut,1030) nPts,Nel,(FeR(i),i = 1,nPts)
!
	return
!
 1000 Format(/2x,"Just before Leaving: Compare_DisRot_1ELModel"/)
 1010 Format(/2x,"Computed Radial Disp.: 1x",I3," for Element #",I2/
     &										(6(1x,F12.7)) )
 1020 Format(/2x,"Computed Axial Disp.: 1x",I3," for Element #",I2/
     &										(6(1x,F12.7)) )
 1030 Format(/2x,"Computed Rotation: 1x",I3," for Element #",I2/
     &										(6(1x,F12.7)) )
!
	return
	end   		