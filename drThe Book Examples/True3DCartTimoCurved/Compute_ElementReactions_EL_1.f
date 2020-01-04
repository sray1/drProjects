	Subroutine Compute_ElementReactions_1(Stif,D,nStif,FI,FJ,nF,
     &									Qc,nQc,P,Radius,Nel,iOut)
!
!	Coerced Isoparametric Quadrilateral_Cubic_Cubic Element
!
!
!	Inputs
!		nStif					= Row or Col size of Stiffness Control matrix 
!		Stif(nStif,nStif)		= Non-Singular Element Stiffness Matrix
!		D(nStif)				= Element Displacement Control Vector
!		 	
!	Outputs 
!		F						= Element Nodal Reactions at r = 0 & r = 1
!
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays
!
	Real(kind=8)	Stif		     ,D       ,P        
	Dimension		Stif(nStif,nStif),D(nStif)
	Real(kind=8)	Qc       
	Dimension		Qc(3,nQc)
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	H1D     ,Axes     ,dxbardr,Curvature,Torsion     	 
	Dimension		H1D(nQc),Axes(3,3)
	Real(kind=8)	FI    ,FJ    ,Fc   
	Dimension		FI(nF),FJ(nF),Fc(nF)
	Integer			IndxI5(6),IndxJ5(6)	! for Quartic: nQc = 5
	Integer			IndxI6(6),IndxJ6(6)	! for Quintic: nQc = 6
	Data IndxI5/ 1, 6,11,16,21,26/		!! Row Indices: for r = 0 
	Data Indxj5/ 5,10,15,20,25,30/		!! Row Indices: for r = 1
	Data IndxI6/ 1, 7,13,19,25,31/		!! Row Indices: for r = 0 
	Data Indxj6/ 6,12,18,24,30,36/		!! Row Indices: for r = 1
!	//////////////////////
	if(nF.NE.6) Then
		stop 'nF.NE.6'
	endif
!	////////////////////// Reactions: StifN*DN
	FI = 0.0D0
	FJ = 0.0D0
!--------------------------------------------------------- Cartesian: I-End
	do 50 i = 1,nF
	if(nQc == 5) Then			!Quartic
		irow = IndxI5(i)
	else if(nQc == 6) Then		!Quintic
		irow = IndxI6(i)
	endif
!
	sum = 0.0D0
	do 20 j = 1,nStif
	sum = sum + Stif(irow,j)*D(j)
   20	continue
	Fc(i) = sum*P
   50 continue	
!	///////////////////////////////////////////////////
	write(iOut,1000)
	write(iOut,1001) Nel,'I' 
	write(iOut,1010) (Fc(i),i = 1,nF) 
!   		 
!	////////////////////// i-End
	ri = 0.0D0	! iEnd
	call QQ_TMB_Cart(Qc,nQc,nQc,ri,H1D,Det,Radius,Axes,
     &								dxbardr,Nel,Iout,0)
!--------------------------------------------------------- Cart-->Curv
	do 70 i = 1,3	
	sumF	= 0.D0
	sumM	= 0.D0
	do 60 j = 1,3
   	sumF	= sumF + Axes(i,j)*Fc(j)
   60	sumM	= sumM + Axes(i,j)*Fc(j+3)
	FI(i)	= sumF
	FI(i+3)	= sumM
   70 continue		
!	/////////////////////////////////////////////////// 
	write(iOut,1020) (FI(i),i = 1,nF) 
!   		 
!--------------------------------------------------------- Cartesian: J-End
	do 51 i = 1,nF
	if(nQc == 5) Then			!Quartic
		irow = IndxJ5(i)
	else if(nQc == 6) Then		!Quintic
		irow = IndxJ6(i)
	endif
!
	sum = 0.0D0
	do 21 j = 1,nStif
	sum = sum + Stif(irow,j)*D(j)
   21	continue
	Fc(i) = sum*P
   51 continue	
!	///////////////////////////////////////////////////
	write(iOut,1001) Nel,'J' 
	write(iOut,1010) (Fc(i),i = 1,nF) 
!   		 
!	////////////////////// j-End
	ri = 1.0D0	! jEnd
	call QQ_TMB_Cart(Qc,nQc,nQc,ri,H1D,Det,Radius,Axes,
     &								dxbardr,Nel,Iout,0)
!--------------------------------------------------------- Cart-->Curv
	do 71 i = 1,3	
	sumF	= 0.D0
	sumM	= 0.D0
	do 61 j = 1,3
   	sumF	= sumF + Axes(i,j)*Fc(j)
   61	sumM	= sumM + Axes(i,j)*Fc(j+3)
	FJ(i)	= sumF
	FJ(i+3)	= sumM
   71 continue		
!	/////////////////////////////////////////////////// 
	write(iOut,1020) (FJ(i),i = 1,nF) 
!   		 
	return
!	/////////////////////////////////////////////////// format s
 1000 Format(/2x,"Just before Leaving: Compute_ElementReactions")
 1001 Format(//2x,25X,"Element #",i2, 5X," End ",A2)
 1010	Format(/2x," Nodal Actions: CARTESIAN Components"//
     &        2x,"       Fx(1)		= ",F16.7/
     &        2x,"       Fy(2)		= ",F16.7/
     &        2x,"       Fz(3)		= ",F16.7/
     &        2x,"       Mx(4)		= ",F16.7/
     &        2x,"       My(5)		= ",F16.7/
     &        2x,"       Mz(6)		= ",F16.7)
 1020	Format(/2x," Nodal Actions: CURVILINEAR Components"//
     &        2x,"       Axial_t      = ",F16.7/
     &        2x,"       Shear_b      = ",F16.7/
     &        2x,"       Shear_m      = ",F16.7/
     &        2x,"       Torsion_t    = ",F16.7/
     &        2x,"       Moment_b     = ",F16.7/
     &        2x,"       Moment_m     = ",F16.7)
	end   		