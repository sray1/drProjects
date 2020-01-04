	Subroutine StressRecovery_2ELModel(Qc,nQc,Stif,nStif,
     &			E,PR,Radius,Depth,Width,P,Qd,nQd,
     &			FeMom,FeShe,FeAxi,FeStr,nDim,nPts,nDim1,Nel,iOut)
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
	Real(kind=8)	rh,si,delsi,AM,ri,delri
	Real(kind=8)	Qc       ,E,R,Depth,Width,P2
	Dimension		Qc(2,nQc)
	Real(kind=8)	Qd     ,Q4    ,Q3    ,Q2    ,Q1
	Dimension		Qd(nQd),Q4(10),Q3(10),Q2(10),Q1(10)
	Real(kind=8)	ExMom      ,FeStr   
	Dimension		ExMom(nDim),FeStr(3,nDim1)
	Real(kind=8)	FeMom	     ,FeAxi        ,FeShe        
	Dimension		FeMom(2,nDim),FeAxi(2,nDim),FeShe(2,nDim)
	Real(kind=8)	B1    ,B2    ,B3                
	Dimension		B1(10),B2(10),B3(10)
	Real(kind=8)	H1D     ,Reac      	 
	Dimension		H1D(nQc),Reac(6)
	Real(kind=8)	Det,AJI,sum,sumi,sumj  
!	//////////////////////
	pi = DATAN(1.D0)*4.0D0
!	//////////////////////--------------------------------- Computed
	AM = E*Width*Depth*Depth*Depth/12.D0	! EI
!-------------------------------------------------- Q4 for theta
	nQcm1 = nQc
	do 5 i = 1,nQcm1
    5	Q4(i) = Qd(2*nQc+i)			
	nQcm1 = nQcm1 -1
	do 6 ii = 1,nQcm1
    6	Q3(ii) = nQcm1*(Q4(ii+1) - Q4(ii))	!Moment
	nQcm1 = nQcm1 -1
	do 7 ii = 1,nQcm1
    7	Q2(ii) = nQcm1*(Q3(ii+1) - Q3(ii))	!Shear
	nQcm1 = nQcm1 -1
	do 8 ii = 1,nQcm1
    8	Q1(ii) = nQcm1*(Q2(ii+1) - Q2(ii))	!Axial
!	//////////////////////
	nStart = 0
	if(Nel == 1) Then
		FeMom = 0.0D0
		FeShe = 0.0D0
		FeAxi = 0.0D0
	elseif(Nel == 2) Then
		nStart = nStart + nPts
	endif		 
!	//////////////////////--------------------------------- Computed
!	find Feaxi at s = 0	
	call Compute_ElementReactions(Stif,Qd,nStif,Reac,6,nQc,P,
     &												Nel,iOut)
!	-----------------------------
	delri = 1.D0/(nPts-1)
!	-------------------------------------------------- Loop
	do 50 i = 1,nPts
!	ri = delri*(nPts-i)
	ri = delri*(i-1)
!	--------------------------------------------- Jacobian
!	Inverse & determinant of Jacobian
!
	call QQ_Jacobian(Qc,nQc,nQc,ri,H1D,AJI,Det,Radius,Nel,Iout,0)
!	AJI = 4.D0/pi/Radius	!Exact		
!------------------------------------------ FeMom
	call Bernstein(B3,nQc-1,ri,iOut)
!	--------------
	XMult = AM*AJI*P		
	sum = 0.D0
	do 15 jj= 1,nQc-1
   15 sum = sum + B3(jj)*Q3(jj)
	FeStr(1,i+nStart) = sum*XMult			 
	if(Nel == 1) Then
		FeMom(1,i+nStart)   = FeStr(1,i+nStart)			 
	elseif(Nel == 2) Then
		FeMom(1,i+nStart-1)   = FeStr(1,i+nStart)
	endif					 
!------------------------------------------ FeShe: Derivative of Moment
	if ( 1 == 2) Then	
		call Bernstein(B2,nQc-2,ri,iOut)
!		--------------
		XMult = XMult*AJI		! 
		sum = 0.D0
		do 16 jj= 1,nQc-2
   16		sum = sum + B2(jj)*Q2(jj)
		FeStr(2,i+nStart) = sum*XMult			 
		FeStr(2,i+nStart) = -FeStr(2,i+nStart)
		if(Nel == 1) Then
			FeShe(1,i+nStart)   = FeStr(2,i+nStart)			 
		elseif(Nel == 2) Then
			FeShe(1,i+nStart-1)   = FeStr(2,i+nStart)
		endif					 
!------------------------------------------------	FeShe:Alternate: Integrated Axial"Better"
	else if( 1 == 1) Then	
		call Bernstein(B1,nQc,ri,iOut)
!		--------------
		nn  = nQc-1
		n1  = nn + 1
		sumi = 0.D0
!		XMult = XMult*pi/4.D0/Radius		! 
		XMult = XMult/AJI/Radius/Radius		! 
		do 20 ii= 1,nn

		sumj = 0.D0
		do 19 jj= ii+1,n1
   19		sumj = sumj + B1(jj)

   20		sumi = sumi + sumj*Q3(ii)/nn

		FeStr(2,i+nStart)
     &			=	-sumi*XMult 
!     &			- Reac(1) - (Reac(2)+ Reac(3)/Radius)*ri*pi/4.D0		 
     &			- Reac(1) - (Reac(2)+ Reac(3)/Radius)*ri/AJI/Radius		 
		FeStr(2,i+nStart) = -FeStr(2,i+nStart)
		if(Nel == 1) Then
			FeShe(1,i+nStart)   = FeStr(2,i+nStart)			 
		elseif(Nel == 2) Then
			FeShe(1,i+nStart-1)   = FeStr(2,i+nStart)
		endif
	endif
!------------------------------------------------- FeAxi
!	call Bernstein(B1,nQc-3,ri,iOut)
!	--------------
!	XMult = XMult*AJI		! 
!	sum = 0.D0
!	do 17 jj= 1,nQc-3
!   17 sum = sum + B1(jj)*Q1(jj)
!	FeStr(3,i+nStart) = sum*XMult*Radius			 
!	if(Nel == 1) Then
!		FeAxi(i+nStart)   = FeStr(3,i+nStart)			 
!	elseif(Nel == 2) Then
!		FeAxi(i+nStart-1)   = FeStr(3,i+nStart)
!	endif
!------------------------------------------------	FeAxi:Alternate: Integrated Moment	
	nn  = nQc - 2
	n1  = nn + 1
!
	if(Nel == 1) Then
		FeStr(3,i+nStart)
     &		= -FeStr(1,i+nStart)/Radius - (Reac(2)+ Reac(3)/Radius)		 
		FeAxi(1,i+nStart)   = FeStr(3,i+nStart)			 
	elseif(Nel == 2) Then
		FeStr(3,i+nStart)
     &		= -FeStr(1,i+nStart)/Radius - (Reac(2)+ Reac(3)/Radius)		 
		FeAxi(1,i+nStart-1)   = FeStr(3,i+nStart)
	endif
!---------------------------------------------------------------- Loop
   50 continue
!	--------------------------------------- Print
	write(iOut,1000)
	write(iOut,1010) nPts,Nel,(FeStr(1,i),i = nStart+1,nStart+nPts)
	write(iOut,1020) nPts,Nel,(FeStr(2,i),i = nStart+1,nStart+nPts)
	write(iOut,1030) nPts,Nel,(FeStr(3,i),i = nStart+1,nStart+nPts)
!	--------------------------------------------------------------- For Paper 2
!	//////////////////////--------------------------------- Exact
	delsi = pi/2.D0/(nDim-1)
	if(Nel == 2) Then
		delsi = pi/2/(nDim-1)
		do 100 i = 1,nDim
		si = delsi*(i-1)
		FeMom(2,i) = P*Radius*(2.D0/pi - DCOS(si))	! P is already -P/2
		FeAxi(2,i) = P*DCOS(si)
		FeShe(2,i) = -P*DSIN(si)
  100     continue 
	endif		 

!
	return
!
 1000 Format(/2x,"Just before Leaving: Stress Recovery"/)
 1010 Format(/2x,"Computed Moment: 1x",I3," for Element #",I2/
     &										(6(2x,F10.4)) )
 1020 Format(/2x,"Computed Shear Force: 1x",I3," for Element #",I2/
     &										(6(2x,F10.4)) )
 1030 Format(/2x,"Computed Axial Force: 1x",I3," for Element #",I2/
     &										(6(2x,F10.4)) )
	end 
!
