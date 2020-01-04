	Subroutine Compute_DisRot_2ELModel(Qc,nQc,Qd,nQd,PP,
     &			FeU,FeV,FeW,Fe1,Fe2,Fe3,FeDis,
     &			nDim,nPts,nDim1,Nel,iOut)
!	Qd is Expanded Full after support Condition enforced
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
	Dimension		FeDis(6,nDim1)
	Real(kind=8)	Qc       
	Dimension		Qc(2,nQc)                          
	Real(kind=8)	H1D     ,Reac   ,Axes      	 
	Dimension		H1D(nQc),Reac(6),Axes(3,3)
	Real(kind=8)	rh,si,delsi,AM,ri,delri,P2
	Real(kind=8)	Qd     ,FeU      ,FeV      ,FeW			! Displacements 
	Dimension		Qd(nQd),FeU(nDim),FeV(nDim),FeW(nDim)
	Real(kind=8)	        Fe1      ,Fe2      ,Fe3			! Rotations
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
      sumV = sumV + Br(j)*Qd(j+  nQc) 
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
!--------------------------------------------------- Curvilinear-->Cartesian
	call QQ_TMB_CuLn(Qc,nQc,nQc,ri,Det,Curvature,Torsion,Axes,
     &							dxbardr,Nel,Iout,0)
!
	sumTX = Axes(1,1)*sumU+Axes(2,1)*sumV+Axes(3,1)*sumW
	sumTY = Axes(1,2)*sumU+Axes(2,2)*sumV+Axes(3,2)*sumW
	sumTZ = Axes(1,3)*sumU+Axes(2,3)*sumV+Axes(3,3)*sumW
!
	sumRX = Axes(1,1)*sum1+Axes(2,1)*sum2+Axes(3,1)*sum3
	sumRY = Axes(1,2)*sum1+Axes(2,2)*sum2+Axes(3,2)*sum3
	sumRZ = Axes(1,3)*sum1+Axes(2,3)*sum2+Axes(3,3)*sum3
!
	FeU(i+nStart) = sumTX*P2 
	FeV(i+nStart) = sumTY*P2 
	FeW(i+nStart) = sumTZ*P2 
	Fe1(i+nStart) = sumRX*P2 
	Fe2(i+nStart) = sumRY*P2 
	Fe3(i+nStart) = sumRZ*P2
!
 	FeDis(1,i+nStart) = sumTX*P2			 
 	FeDis(2,i+nStart) = sumTY*P2			 
 	FeDis(3,i+nStart) = sumTZ*P2
 	FeDis(4,i+nStart) = sumRX*P2			 
 	FeDis(5,i+nStart) = sumRY*P2			 
 	FeDis(6,i+nStart) = sumRZ*P2
   40 continue
	return
	end   		