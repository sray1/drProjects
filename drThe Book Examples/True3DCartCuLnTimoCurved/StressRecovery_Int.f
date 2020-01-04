	Subroutine StressRecovery_2ELModel_Int(Qc,nQc,Stif,nStif,
     &			E,PR,Radius,Depth,Width,P,Qd,nQd,
     &			FeF1,FeF2,FeF3,FeM1,FeM2,FeM3,FeStr,
     &			nDim,nPts,nDim1,Nel,iOut)
!	Qd is Expanded Full after support Condition enforced
!	Exact Solution By Castigliano:
!------------------------------------------------------
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays
!
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	rh,si,delsi,AM,ri,delri,dxbardr
	Real(kind=8)	Qc       ,E,R,Depth,Width,P2
	Dimension		Stif(nStif,nStif)                          
	Real(kind=8)	Stif  
	Dimension		Qc(2,nQc)                          
	Real(kind=8)	Qd     ,Q4    ,Q3    ,Q2    ,Q1    ,B  
	Dimension		Qd(nQd),Q4(10),Q3(10),Q2(10),Q1(10),B(6,nStif)
	Real(kind=8)	Qfx    ,Qfy    ,Qfz    
	Dimension		Qfx(10),Qfy(10),Qfz(10)
	Real(kind=8)	Qmx    ,Qmy    ,Qmz    
	Dimension		Qmx(10),Qmy(10),Qmz(10)
	Real(kind=8)	ExMom      ,FeStr   
	Dimension		ExMom(nDim),FeStr(6,nDim1)
	Real(kind=8)	FeF1	    ,FeF2        ,FeF3        
	Dimension		FeF1(2,nDim1),FeF2(2,nDim1),FeF3(2,nDim1)
	Real(kind=8)	FeM1	    ,FeM2        ,FeM3        
	Dimension		FeM1(2,nDim1),FeM2(2,nDim1),FeM3(2,nDim1)
	Real(kind=8)	B1    ,B2    ,B3                
	Dimension		B1(10),B2(10),B3(10)
	Real(kind=8)	H1D     ,Reac   ,Axes      	 
	Dimension		H1D(nQc),Reac(6),Axes(3,3)
	Real(kind=8)	delCx,delCy
	Real(kind=8)	Det,AJI,sum,sumi,sumj,Fac  
!	//////////////////////
	iCalc = 1
!---------------	
	pi = DATAN(1.D0)*4.0D0
!	//////////////////////--------------------------------- Computed
	XK = 5.D0/6.D0							! Shear Factor	
	AI = E*Width*Depth*Depth*Depth/12.D0	! EII
	AO = E*Depth*Width*Width*Width/12.D0	! EIO
	GJ = (AI+AO)/(2.D0*(1.D0+PR))			! GJ 
	BM = E*Width*Depth						! EA 
	CM = XK*BM/(2.D0*(1.D0+PR))				! kGA
!	//////////////////////
	nStart = 0
	if(Nel == 1) Then
		FeStr= 0.0D0
		FeF1 = 0.0D0
		FeF2 = 0.0D0
		FeF3 = 0.0D0
		FeM1 = 0.0D0
		FeM2 = 0.0D0
		FeM3 = 0.0D0
	elseif(Nel == 2) Then
		nStart = nStart + nPts
	endif		 
!	//////////////////////--------------------------------- Computed
!	find Feaxi at s = 0	
	if(Nel == 1) Then
		call Compute_ElementReactions_1(Stif,Qd,nStif,Reac,6,Qc,nQc,P,
     &										Radius,Nel,iOut)
	elseif (Nel == 2) Then 
		call Compute_ElementReactions_2(Stif,Qd,nStif,Reac,6,Qc,nQc,P,
     &										Radius,Nel,iOut)
	endif 
!	-----------------------------
	delri = 1.D0/(nPts-1)
!	-------------------------------------------------- Loop
	do 50 i = 1,nPts
!	ri = delri*(nPts-i)
	ri = delri*(i-1)
!-----------------------------------------------------------
	Call QQ_StrainDispMat(Qc,nQc,ri,Radius,B,nStif,Det,Axes,
     &					Curvature,Torsion,Nel,NelType,Iout)
!	----------------------	
	sum4 = 0.D0
	sum5 = 0.D0
	sum6 = 0.D0
!	---------------------------------------------------------------- Moments First
	do 40 ix = 1,nQd
	sum4 = sum4 + GJ*B(4,ix)*Qd(ix)*P
	sum5 = sum5 + AI*B(5,ix)*Qd(ix)*P	
	sum6 = sum6 + AO*B(6,ix)*Qd(ix)*P	
   40	continue
!
!	--------------------------------------------------- Curv --> Cart
!	---------------------------
	sumx = Axes(1,1)*sum4+Axes(2,1)*sum5+Axes(3,1)*sum6
	sumy = Axes(1,2)*sum4+Axes(2,2)*sum5+Axes(3,2)*sum6
	sumz = Axes(1,3)*sum4+Axes(2,3)*sum5+Axes(3,3)*sum6
!	--------------------------- Carte
 	FeStr(4,i+nStart) = sumx			 
 	FeStr(5,i+nStart) = sumy			 
 	FeStr(6,i+nStart) = sumz
!	--------------------------- Curvi
	FeM1(1,i+nStart) = sum4
	FeM2(1,i+nStart) = sum5
	FeM3(1,i+nStart) = sum6
!	---------------------------------------------------------------- Forces by Integration
	sum1 = 0.D0
	sum2 = 0.D0
	sum3 = 0.D0
!	-----------
		
!	--------------------------- Curvi
	FeF1(1,i+nStart) = sum1
	FeF2(1,i+nStart) = sum2
	FeF3(1,i+nStart) = sum3
!---------------------------------------------------------------- Loop
   50 continue
!	--------------------------------------- Print
	write(iOut,1000)
	write(iOut,1010) nPts,Nel,(FeStr(4,i),i = nStart+1,nStart+nPts)
	write(iOut,1020) nPts,Nel,(FeStr(5,i),i = nStart+1,nStart+nPts)
	write(iOut,1030) nPts,Nel,(FeStr(6,i),i = nStart+1,nStart+nPts)
!	--------------------------------------------------------------- For Paper 2
!	//////////////////////--------------------------------- Exact
	delsi = pi/2.D0/(nDim-1)
	if(Nel == 2) Then
		delsi = pi/2/(nDim-1)
		do 100 i = 1,nDim
		si = delsi*(i-1)
		FeM1(2,i) = P*Radius*(2.D0/pi - DCOS(si))	! P is already -P/2
  100     continue 
	endif		 

!
	return
!
 1000 Format(/2x,"Just before Leaving: Stress Recovery"/)
 1010 Format(/2x,"Computed Moment_X: 1x",I3," for Element #",I2/
     &										(6(2x,F10.4)) )
 1020 Format(/2x,"Computed Moment_Y: 1x",I3," for Element #",I2/
     &										(6(2x,F10.4)) )
 1030 Format(/2x,"Computed Moment_Z: 1x",I3," for Element #",I2/
     &										(6(2x,F10.4)) )
 1040 Format(/2x,"Computed Shear Force: 1x",I3," for Element #",I2/
     &										(6(2x,F10.4)) )
 1050 Format(/2x,"Computed Shear Force: 1x",I3," for Element #",I2/
     &										(6(2x,F10.4)) )
 1060 Format(/2x,"Computed Axial Force: 1x",I3," for Element #",I2/
     &										(6(2x,F10.4)) )
	end 
!
