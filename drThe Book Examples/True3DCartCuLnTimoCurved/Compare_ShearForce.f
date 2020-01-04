	Subroutine CompareShearForce_2ELModel(Qc,nQc,
     &			E,PR,Radius,Depth,Width,P,Qd,nQd,
     &			FeShe,nDim,nPts,Nel,iOut)
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
	Real(kind=8)	Qc       ,Br     ,E,R,Depth,Width,P2
	Dimension		Qc(2,nQc),Br(nQc)
	Real(kind=8)	Qd           
	Dimension		Qd(nQd)
	Real(kind=8)	ExShe    
	Dimension		ExShe(nDim)
	Real(kind=8)	FeShe      
	Dimension		FeShe(nDim)
	Real(kind=8)	H1D      	 
	Dimension		H1D(nQc)
	Real(kind=8)	Det,AJI   
!	//////////////////////
	pi = DATAN(1.D0)*4.0D0
!	//////////////////////--------------------------------- Exact
	delsi = pi/2.D0/(nDim-1)
	do 10 i = 1,nDim
	si = delsi*(i-1)
!	ExMom(i) = -P*DSIN(si)
   10 continue
!	//////////////////////--------------------------------- Computed
	XK = 5.D0/6.D0							! Shear Factor	
	BM = E*Width*Depth						! EA 
	CM = XK*BM/(2.D0*(1.D0+PR))				! kGA
!	//////////////////////
	nStart = 0
	if(Nel == 1) Then
		FeShe = 0.0D0
	elseif(Nel == 2) Then
		nStart = nStart + nPts - 1
	endif		 
!	//////////////////////--------------------------------- Computed
	delri = 1.D0/(nPts-1)
!	-------------------------------------------------- Loop
	do 30 i = 1,nPts
!	ri = delri*(nPts-i)
	ri = delri*(i-1)
!	--------------------------------------------- Jacobian
!	Inverse & determinant of Jacobian
!
	call QQ_Jacobian(Qc,nQc,nQc,ri,H1D,AJI,Det,Radius,Nel,Iout,0)
!	AJI = 4.D0/pi/Radius	!Exact		
!------------------------------------------ FeShe
	nQ2	= nQc*2
	B	= 0.0D0	!ALL
!
	call Bernstein(Br,nQc,ri,iOut)
!
	sumS = 0.D0	
	do 20 j = 1,nQc	! For 1D Curve Beam with axial & shear strains 
	sumS = sumS + (AJI*H1D(j))*Qd(j)		!Shear Strain: dw/ds	
	sumS = sumS + (-Br(j)/Radius)*Qd(j+nQc)	!Shear Strain: -u/R
	sumS = sumS + Br(j)*Qd(j+nQ2)			!Shear Strain: theta
   20	continue
!	--------------
	FeShe(i+nStart)   = CM*sumS			 
!---------------------------------------------------------------- Loop
   30 continue
!	------
	return
	end   		
