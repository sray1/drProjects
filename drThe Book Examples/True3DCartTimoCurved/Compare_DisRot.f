	Subroutine Compare_DisRot_2ELModel(Qc,nQc,Qd,nQd,PP,
     &			FeU,FeV,FeW,Fe1,Fe2,Fe3,FeDis,
     &			nDim,nPts,nDim1,Nel,iOut)
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
	Real(kind=8)	FeDis   
	Dimension		FeDis(6,nDim)
	Real(kind=8)	Qc       
	Dimension		Qc(2,nQc)                          
	Real(kind=8)	rh,si,delsi,AM,ri,delri,P2
	Real(kind=8)	Qd     ,FeU       ,FeV       ,FeW			! Displacements 
	Dimension		Qd(nQd),FeU(nDim),FeV(nDim),FeW(nDim)
	Real(kind=8)	        Fe1       ,Fe2       ,Fe3			! Rotations
	Dimension		        Fe1(nDim),Fe2(nDim),Fe3(nDim)
	Real(kind=8)	Br  
	Dimension		Br(nQc)
!	//////////////////////
	P2 = dabs(PP)
!	-------------
	nStart = 0
	if(Nel == 1) Then
		FeU = 0.0D0
		FeV = 0.0D0
		FeW = 0.0D0
		Fe1 = 0.0D0
		Fe2 = 0.0D0
		Fe3 = 0.0D0
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
	sumU = 0.D0
	sumV = 0.D0
	sumW = 0.D0
	sum1 = 0.D0
	sum2 = 0.D0
	sum3 = 0.D0
	do 10 j= 1,nQc
      sumU = sumU + Br(j)*Qd(j) 
      sumV = sumV + Br(j)*Qd(j+nQc) 
      sumW = sumW + Br(j)*Qd(j+2*nQc) 
      sum1 = sum1 + Br(j)*Qd(j+3*nQc) 
      sum2 = sum2 + Br(j)*Qd(j+4*nQc) 
      sum3 = sum3 + Br(j)*Qd(j+5*nQc) 
   10 continue
	FeU(i+nStart) = sumU*P2 
	FeV(i+nStart) = sumV*P2 
	FeW(i+nStart) = sumW*P2 
	Fe1(i+nStart) = sum1*P2 
	Fe2(i+nStart) = sum2*P2 
	Fe3(i+nStart) = sum3*P2 
!
 	FeDis(1,i+nStart) = FeU(i+nStart)			 
 	FeDis(2,i+nStart) = FeV(i+nStart)			 
 	FeDis(3,i+nStart) = FeW(i+nStart)
 	FeDis(4,i+nStart) = Fe1(i+nStart)			 
 	FeDis(5,i+nStart) = Fe2(i+nStart)			 
 	FeDis(6,i+nStart) = Fe3(i+nStart)
   40 continue
!
!	--------------------------------------- Print: Cartesian
	write(iOut,1000)
	write(iOut,1010) nPts,Nel,(FeDis(1,i),i = nStart+1,nStart+nPts)
	write(iOut,1020) nPts,Nel,(FeDis(2,i),i = nStart+1,nStart+nPts)
	write(iOut,1030) nPts,Nel,(FeDis(3,i),i = nStart+1,nStart+nPts)
	write(iOut,1040) nPts,Nel,(FeDis(4,i),i = nStart+1,nStart+nPts)
	write(iOut,1050) nPts,Nel,(FeDis(5,i),i = nStart+1,nStart+nPts)
	write(iOut,1060) nPts,Nel,(FeDis(6,i),i = nStart+1,nStart+nPts)
!	--------------------------------------------------------------- For Paper 2
	return
!
 1000 Format(/2x,"Just before Leaving: Compare_DisRot_2ELModel"/)
 1010 Format(/2x,"Computed Dis_U: 1x",I3," for Element #",I2/
     &										(6(2x,F10.4)) )
 1020 Format(/2x,"Computed Dis_V: 1x",I3," for Element #",I2/
     &										(6(2x,F10.4)) )
 1030 Format(/2x,"Computed Dis_W: 1x",I3," for Element #",I2/
     &										(6(2x,F10.4)) )
 1040 Format(/2x,"Computed Rot_X: 1x",I3," for Element #",I2/
     &										(6(2x,F10.4)) )
 1050 Format(/2x,"Computed Rot_Y: 1x",I3," for Element #",I2/
     &										(6(2x,F10.4)) )
 1060 Format(/2x,"Computed Rot_Z: 1x",I3," for Element #",I2/
     &										(6(2x,F10.4)) )
	end   		