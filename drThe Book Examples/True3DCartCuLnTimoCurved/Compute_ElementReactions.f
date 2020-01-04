	Subroutine Compute_ElementReactions(Stif,D,nStif,F,nF,Qc,nQc,P,
     &									Radius,Indx,iEnd,Nel,iOut)
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
	Real(kind=8)	F    ,Fc   
	Dimension		F(nF),Fc(nF)
	Integer			Indx(nF)
!	//////////////////////
	if(nF.NE.6) Then
		stop 'nF.NE.6'
	endif
!	////////////////////// 
!
!	Row Indices: for r = 0 
!
	if (Nel == 1) Then
		Indx(1)	= 1	
		Indx(2)	= 6	
		Indx(3)	= 11	
		Indx(4)	= 16	
		Indx(5)	= 21	
		Indx(6)	= 26
	elseif (Nel == 2) Then
		Indx(1)	= 34	
		Indx(2)	= 38	
		Indx(3)	= 42	
		Indx(4)	= 46	
		Indx(5)	= 50	
		Indx(6)	= 54
	endif 
!	//////////////////////
!
!	Reactions: StifN*DN
!
	F = 0.0D0
!--------------------------------------------------------- Curvilinear
	do 50 i = 1,nF
	irow = Indx(i)
	sum = 0.0D0
	do 20 j = 1,nStif
	sum = sum + Stif(irow,j)*D(j)
   20	continue
	Fc(i) = sum*P
   50 continue	
!	///////////////////////////////////////////////////
	write(iOut,1000) Nel
	write(iOut,1020) (Fc(i),i = 1,nF) 
!   		 
!	////////////////////// i-End
	ri = 0.0D0	! iEnd
	call QQ_TMB_CuLn(Qc,nQc,nQc,ri,H1D,Det,Curvature,Torsion,Axes,
     &							Nel,Iout,0)
	Radius = 1.D0/Curvature	
!--------------------------------------------------------- Cartesian
	do 70 i = 1,3	
	sumF	= 0.D0
	sumM	= 0.D0
	do 60 j = 1,3
   	sumF	= sumF + Axes(j,i)*Fc(j)
   60	sumM	= sumM + Axes(j,i)*Fc(j+3)
	F(i)	= sumF
	F(i+3)	= sumM
   70 continue		
!	///////////////////////////////////////////////////
	write(iOut,1010) (F(i),i = 1,nF) 
!   		 
	return
 1000 Format(/2x,"Just before Leaving: Compute_ElementReactions",
     &			5X,"Element #",i2/)
 1010	Format(/2x," Nodal Reactions: CARTESIAN Components"//
     &        2x,"End I: Fx(1)		= ",F16.7/
     &        2x,"       Fy(2)		= ",F16.7/
     &        2x,"       Fz(3)		= ",F16.7/
     &        2x,"       Mx(4)		= ",F16.7/
     &        2x,"       My(5)		= ",F16.7/
     &        2x,"       Mz(6)		= ",F16.7)
 1020	Format(/2x," Nodal Reactions: CURVILINEAR Components"//
     &        2x,"End I: Axial_t      = ",F16.7/
     &        2x,"       Shear_m      = ",F16.7/
     &        2x,"       Shear_b      = ",F16.7/
     &        2x,"       Torsion_t    = ",F16.7/
     &        2x,"       Moment_m     = ",F16.7/
     &        2x,"       Moment_b     = ",F16.7)
	end   		