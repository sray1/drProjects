	Subroutine StressRecovery_2ELModel(XP,Qc,nQc,Stif,nStif,
     &			E,PR,Radius,Depth,Width,P,Qd,nQd,
     &			FeF1,FeF2,FeF3,FeM1,FeM2,FeM3,FeStr,
     &			nDim,nPts,nDim1,Nel,iOut,
     &			CurTor)
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
	Real(kind=8)	XP	 ,Qc       ,E,R,Depth,Width,P2
	Dimension		XP(4),Qc(2,nQc)                          
	Dimension		Stif(nStif,nStif)                          
	Real(kind=8)	Stif  
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
	Real(kind=8)	CurTor        
	Dimension		CurTor(2,nDim1)
	Real(kind=8)	B1    ,B2    ,B3                
	Dimension		B1(10),B2(10),B3(10)
	Real(kind=8)	H1D     ,ReI   ,ReJ   ,Axes      	 
	Dimension		H1D(nQc),ReI(6),ReJ(6),Axes(3,3)
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
		call Compute_ElementReactions_1(Stif,Qd,nStif,ReI,ReJ,6,Qc,nQc,P,
     &										Radius,Nel,iOut)
	elseif (Nel == 2) Then 
		call Compute_ElementReactions_2(Stif,Qd,nStif,ReI,ReJ,6,Qc,nQc,P,
     &										Radius,Nel,iOut)
	endif 
!	------------------------------------------------------- prep. for deriv
	do 20 ii = 1,nQc
!     	Qmx(ii) = Qd(3*nQc+ii)		! theta_t		
     	Qmy(ii) = Qd(4*nQc+ii)		! theta_b		
     	Qmz(ii) = Qd(5*nQc+ii)		! theta_m
   20 continue
!	------------------------------------------ prep. 2nd deriv.theta_b:    		
	nQcm2 = nQc - 2
	xn = Factorial(nQc-1)/Factorial(nQc-3)
	do 25 ii = 1,nQcm2
     	Q2(ii) = xn*(Qmy(ii+2) - 2.D0*Qmy(ii+1) + Qmy(ii))	! theta_b
   25 continue
!	------------------------------------------ prep. ist deriv.theta_m:    		
	nQcm1 = nQc - 1
	xn = Factorial(nQc-1)/Factorial(nQc-2)
	do 26 ii = 1,nQcm1
    	Q3(ii) = nQcm1*(Qmz(ii+1) - Qmz(ii))	! theta_m
   26 continue
!	-----------------------------
	delri = 1.D0/(nPts-1)
!	-------------------------------------------------- Loop
	do 50 i = 1,nPts
!	ri = delri*(nPts-i)
	ri = delri*(i-1)
!-----------------------------------------------------------
	Call QQ_StrainDispMat(Qc,nQc,ri,Radius,B,nStif,Det,Axes,
     &					Curvature,Torsion,Nel,NelType,Iout)
!
	CurTor(1,i+nStart) = Curvature 
	CurTor(2,i+nStart) = Torsion 
!	--------------------------------------------------------------------------------- Moments	
	sum1 = 0.D0
	sum2 = 0.D0
	sum3 = 0.D0
	sum4 = 0.D0
	sum5 = 0.D0
	sum6 = 0.D0
	do 40 ix = 1,nQd
	sum4 = sum4 + GJ*B(4,ix)*Qd(ix)*P
	sum5 = sum5 + AI*B(5,ix)*Qd(ix)*P	
	sum6 = sum6 + AO*B(6,ix)*Qd(ix)*P	
   40	continue
!	--------------------------------------------------- Curv-->Cart
	sumx = Axes(1,1)*sum4+Axes(2,1)*sum5+Axes(3,1)*sum6
	sumy = Axes(1,2)*sum4+Axes(2,2)*sum5+Axes(3,2)*sum6
	sumz = Axes(1,3)*sum4+Axes(2,3)*sum5+Axes(3,3)*sum6
!	---------------------------
 	FeStr(4,i+nStart) = sumx			 
 	FeStr(5,i+nStart) = sumy			 
 	FeStr(6,i+nStart) = sumz
!	--------------------------- Curvi
	FeM1(1,i+nStart) = sum4
	FeM2(1,i+nStart) = sum5
	FeM3(1,i+nStart) = sum6
!	--------------------------------------------------------------------------------- Forces	
	CurTor(1,i+nStart) = Curvature 
	CurTor(2,i+nStart) = Torsion 
!	------------------------------ 
	if(i.GE.2) Then
!----------------------------------------------------------------------------------- Nt 
!		---------------------------------------------- dMb/dzi and Mm
		sumM2 = (FeM2(1,i+nStart) - FeM2(1,i+nStart-1))
		sumM3 = FeM3(1,i+nStart)
!		------------------------------ Curvature*dMb/dzi2 
		sumBT = sumM2*Curvature/delri
!		------------------------------ Curvature*torsion*Mm*Det 
		sumMT = sumM3*Curvature*Torsion*Det
!		------------------------------------------ (Integration by sum)
		sumBMT = (sumBT + sumMT)*delri		! Incremental
		sumBMT = sumBMT + FeF1(1,i+nStart-1)! Total
!
		FeF1(1,i+nStart) = sumBMT
		FeF1(2,i+nStart) = -ReI(1) - sumBMT 
!----------------------------------------------------------------------------------- Vb 
!		------------------------------ Torsion*dMb/dzi2 
		sumBB = sumM2*Torsion/delri
!		------------------------------ Torsion*torsion*Mm 
		sumMB = sumM3*Torsion*Torsion*Det
!		------------------------------------------ (Integration by sum)
		sumBMB = (sumBB + sumMB)*delri		!Incremental
		sumBMB = sumBMB + FeF2(1,i+nStart-1)!Total
!
		FeF2(1,i+nStart) = sumBMB
		FeF2(2,i+nStart) = -ReI(2) + sumBMB 
!----------------------------------------------------------------------------------- Vm 
!		------------------------------ Torsion*Vb 
		sumBB = FeF2(2,i+nStart)*Torsion
!		------------------------------ Curvature*Nt 
		sumBT = FeF1(2,i+nStart)*Curvature
!		------------------------------------------ (Integration by sum)
		sumBBT = (sumBB - sumBT)*delri*Det	!Incremental
		sumBBT = sumBBT + FeF3(1,i+nStart-1)!Total
!
		FeF3(1,i+nStart) = sumBBT
		FeF3(2,i+nStart) = -ReI(3) + sumBBT
!		---------------------------------- Reactions		 
	else
		FeF1(1,i+nStart) = 0.D0  
		FeF1(2,i+nStart) = -ReI(1) 
		FeF2(1,i+nStart) = 0.D0  
		FeF2(2,i+nStart) = -ReI(2) 
		FeF3(1,i+nStart) = 0.D0  
		FeF3(2,i+nStart) = -ReI(3) 
	endif
!	----------------------------- Curvi
	sum1 = FeF1(2,i+nStart) 
	sum2 = FeF2(2,i+nStart) 
	sum3 = FeF3(2,i+nStart) 
!	--------------------------------------------------- Curv --> Cart
	sumx = Axes(1,1)*sum1+Axes(2,1)*sum2+Axes(3,1)*sum3
	sumy = Axes(1,2)*sum1+Axes(2,2)*sum2+Axes(3,2)*sum3
	sumz = Axes(1,3)*sum1+Axes(2,3)*sum2+Axes(3,3)*sum3
!	---------------------------
 	FeStr(1,i+nStart) = sumx			 
 	FeStr(2,i+nStart) = sumy			 
 	FeStr(3,i+nStart) = sumz
!---------------------------------------------------------------- Loop
   50 continue
!	--------------------------------------- Print: Cartesian
	write(iOut,1000)
	write(iOut,1040) nPts,Nel,(FeStr(1,i),i = nStart+1,nStart+nPts)
	write(iOut,1050) nPts,Nel,(FeStr(2,i),i = nStart+1,nStart+nPts)
	write(iOut,1060) nPts,Nel,(FeStr(3,i),i = nStart+1,nStart+nPts)
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
 1040 Format(/2x,"Computed Force_X: 1x",I3," for Element #",I2/
     &										(6(2x,F10.4)) )
 1050 Format(/2x,"Computed Force_Y: 1x",I3," for Element #",I2/
     &										(6(2x,F10.4)) )
 1060 Format(/2x,"Computed Force_Z: 1x",I3," for Element #",I2/
     &										(6(2x,F10.4)) )
	end 
!
!		------------------------------------------ d2Theta_b/dzi2 
!		call Bernstein(B3,nQc-2,ri,iOut)
!		--------------
!		sumB = 0.D0
!		do 15 jj= 1,nQc-2
!		sumB = sumB + Curvature*B3(jj)*Q2(jj)		
!   15		continue
!		sumB = AI*sumB*delri*P
!------------------------------------------ torsion*dTheta_m/dzi 
!		call Bernstein(B3,nQc-1,ri,iOut)
!	--------------
!		sumM = 0.D0
!		do 16 jj= 1,nQc-1
!		sumM = sumM + Curvature*Torsion*B3(jj)*Q3(jj)		
!   16		continue
!		sumM = AO*sumM*delri*P
!	--------------------------------------------------- Axial Force (Integration by sum)
!		sumBM = sumB + sumM
!		do 17 kk = 1,i
!		sumBM = sumBM + FeF1(1,kk)
!   17		continue
!		FeF1(1,i+nStart) = sumBM
!		FeF2(1,i+nStart) = ReI(1) - sumBM 
!	else
!		FeF1(1,i+nStart) = 0.D0  
!		FeF2(1,i+nStart) = ReI(1) 
!	endif
