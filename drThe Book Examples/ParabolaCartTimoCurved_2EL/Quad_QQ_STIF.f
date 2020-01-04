	Subroutine Quad_QQ_STIF(Qc,nQc,Nel,NelType,Nint,E,PR,
     &				Depth,Width,Radius,Stif,nStif,Iout,Trace)
!
!	Coerced Isoparametric Quadrilateral_Cubic_Cubic Element
!
!	Notes:	Nint should be atleast 2
!			nStif MUST be 32
!
!	Inputs
!		Qc(1,16)	= Bezier X-Coordinates
!					=	(qc00x qc10x...qc33x)
!		Qc(2,16)	= Bezier Y-Coordinates
!					=	(qc00y qc10y...qc33y)
!		Nel			= Element Number
!		NelType		= Element Type:
!						0 = Plane Stress
!						1 = Plane Strain
!						2 = Axi-symmtric	(NOT DONE YET)
!		Nint		= Number of Gauss Points
!		E			= Elasticity Modulus
!		PR			= Poisson's ratio
!		Thk			= Thickness
!		nStif		= Row or Col size of Stiffness matrix ( MUST BE 32)
!		Iout		= Error Output file#
!		 	
!	Outputs 
!		Stif(32,32)	= Desired Stiffness Matrix
!		Trace		= trace of the matrix
!
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays
!
	Real(kind=8)	Qc       ,E,PR,Thk,Radius,Depth,Width
	Dimension		Qc(2,nQc)
	integer			Nel,NelType,Iout,nStif
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	Stif			 ,Trace
	Dimension		Stif(nStif,nStif)
	Real(kind=8)	B         ,D     ,DB   ,Add    
	Dimension		B(3,nStif),D(3,3),DB(3),Add(32)
	Real(kind=8) AM,BM,CM,TH,Ri,Si,Wt,sum
!----------------------------------------------------------
	XK = 5.D0/6.D0							! Shear Factor	
	AM = E*Width*Depth*Depth*Depth/12.D0	! EI
	BM = E*Width*Depth						! EA 
	CM = XK*BM/(2.D0*(1.D0+PR))				! kGA
!
	D	   = 0.D0 !ALL
	D(1,1) = AM
	D(2,2) = BM
	D(3,3) = CM
!
!	Stiffness Matrix Calculation
!
	do 5 i = 1,nStif
	do 5 j = 1,nStif
    5	Stif(i,j) = 0.D0	! all elements = 0.
!
	write(Iout,1000) Nel,(i,(Qc(i,j),j=1,nQc),i=1,2)
!	Loop over Gauss Locations
	do 60 lr = 1,Nint
		Ri = GaussPtVal(lr,Nint,1) 
!
!	Get Strain Displacement Matrix: B(3,32)
!
	Call QQ_StrainDispMat(Qc,nQc,Ri,Radius,B,nStif,Det,
     &									Nel,NelType,Iout)
!
!	Add to stiffness matrix
!
	Wt = GaussPtVal(lr,Nint,2)*Det*Width
!
	do 50 j = 1,nStif
	do 20 k = 1,3		! 3 will be 4 if axisymmtric included
	DB(k) = 0.0
	do 20 l = 1,3		! 3 will be 4 if axisymmtric included
	DB(k) = DB(k) + D(k,l)*B(l,j)
   20 continue
	do 40 i = j,nStif
	sum = 0.0
	do 30 l = 1,3		! 3 will be 4 if axisymmtric included
	sum = sum + B(l,i)*DB(l)
   30	continue
	Stif(i,j) = Stif(i,j) + sum*Wt
   40	continue
   50 continue
   60 continue
!
!	symmetry: Upper Triangle 
!
	do 70 j = 1,nStif
	do 70 i = j,nStif
  	Stif(j,i) = Stif(i,j)
   70 continue
!
!	Get Trace
!
	Trace = 0.D0
	do 80 i = 1,nStif
	Trace = Trace + Stif(i,i)
   80 continue			
!
!	Check each col. vector for Null
!
	Add = 0.D0
	do 100 j = 1,nStif
	sum = 0.0 
	do 90 i = 1,nStif	
	sum = sum + Stif(i,j)
   90 continue
	Add(j) = sum
  100 continue			
!
!	done
!
	write(Iout,1010) nStif,nStif
	do 110 i = 1,nStif
!	write(Iout,1020) i,(Stif(i,j),j = 1,nStif)
!	Pause
  110	continue
	return
!
 1000 format("QC(2,5): Elem# =",I4/
     &        2(I5,5X,5(f10.6,1X)/) )
 1010 format("Full Stiffness Matrix:Stif(",I2,",",I2,")"/)
 1020 format(I5/(3(5(f16.6,1X)/)/))
	return
	end   		
	   		