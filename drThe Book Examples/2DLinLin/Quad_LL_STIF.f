	Subroutine Quad_LL_STIF(Qc,Nel,NelTyp,Nint,E,PR,Thk,Stif,nStif,
     &						nOrder,nSize,Iout,Trace)
!
!	Coerced Isoparametric Quadrilateral_Cubic_Cubic Element
!
!	Notes:	Nint should be atleast 2
!			nStif MUST be 32
!
!	Inputs
!		nOrder				= nDegree+1 of Element: 
!								2 for Linear
!								3 for Quadratic
!								4 for Cubic
!		nStif				= Stiffness size nStifxnStif 
!		nSize				= nStif/2
!		Qc(1,nSize)			= Bezier X-Coordinates
!							=	(qc00x qc10x...qc11x)
!		Qc(2,nSize)			= Bezier Y-Coordinates
!							=	(qc00y qc10y...qc11y)
!		Nel					= Element Number
!		NelType				= Element Type:
!								0 = Plane Stress
!								1 = Plane Strain
!								2 = Axi-symmtric	(NOT DONE YET)
!		Nint				= Number of Gauss Points
!		E					= Elasticity Modulus
!		PR					= Poisson's ratio
!		Thk					= Thickness
!		nStif				= Row or Col size of Stiffness matrix ( MUST BE 32)
!		Iout				= Error Output file#
!		 	
!	Outputs 
!		Stif(nStif,nStif)	= Desired Stiffness Matrix
!		Trace				= trace of the matrix
!
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays
!
	Real(kind=8)	Qc     ,E,PR,Thk
	Dimension		Qc(2,*)
	integer			Nel,NelType,Iout,nStif,nOrder,nSize
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	Stif			 ,Trace
	Dimension		Stif(nStif,nStif)
	
!--------------------------------------------------
!	Rk(3,3)		= Gauss-Legendre Nodes		Upto 3 Points
!	Ak(3,3)		= Gauss-Legendre Weights	Upto 3 Points
!	
!	Recall: 
!		Our integration,r=[0,1]
!		Conventional	x=[-1,1]
!		ie., x = (2r-1)
!	So, following values modified as:
!		Rk	= (1/2)(xk+1)
!		Ak	= (1/2)Axk
!
!	Rk:
!	0.0                     ->0.5
!	0.57735026918962576451  ->0.788675134594813
!	-.57735026918962576451  ->0.211324865405187
!	0.77459666924148337704  ->0.887298334620742
!	-.77459666924148337704  ->0.112701665379258
!
!	Ak:
!     2.0						->1.0
!     1.0						->0.5 
!     5/9						->0.277777777777777 
!     8/9						->0.444444444444444
!-------------------------------------------------- 
	Real(kind=8) AM,BM,CM,TH,Ri,Si,Wt,sum
	Real(kind=8) Rk     ,Ak     ,D     ,B      ,Add    ,DB    
	Dimension    Rk(3,3),Ak(3,3),D(3,3),B(3,nStif),Add(nStif),DB(4)
	DATA Rk/	0.5D0,				 0.0D0,						! 1-point		
     &            0.0D0,		
     &			0.211324865405187D0, 0.788675134594813D0,		! 2-point
     &			0.0D0,
     &			0.112701665379258D0, 0.5D0,						! 3-point
     &			0.887298334620742D0
     &       /
!     		 
	DATA Ak/	2.0D0,				 0.0D0,						! 1-point		
     &            0.0D0,		
     &			0.5D0,               0.5D0,						! 2-point
     &			0.0D0,
     &			0.277777777777778D0, 0.444444444444444D0,		! 3-point
     &			0.277777777777778D0
     &       /
!	//////////////////////
!
!	Stress-Strain Law
!
	if(NelTyp == 0)	Then					! Plain Stress
		AM = E
		BM = PR
		CM = AM/(1-BM*BM)
		TH = Thk			! thickness
	else if(NelTyp == 1) Then				! Plain Strain
		AM = E/(1-PR*PR)
		BM = PR/(1-PR)
		CM = AM/(1.-BM*BM)
		TH = 1				! thickness
	else
		Stop 'ElType Wrong'
	end if
!
	D(1,1) = CM
	D(1,2) = CM*BM
	D(1,3) = 0.
	D(2,1) = D(1,2)
	D(2,2) = CM
	D(2,3) = 0.
	D(3,1) = 0.
	D(3,2) = 0.
	D(3,3) = CM*(1.-BM)/2.
!
!	Stiffness Matrix Calculation
!
	do 5 i = 1,nStif
	do 5 j = 1,nStif
    5	Stif(i,j) = 0.D0	! all elements = 0.
!
!	Loop over Gauss Locations
	do 60 lr = 1,Nint
	Ri = Rk(lr,Nint) 
	do 60 ls = 1,Nint
	Si = Rk(ls,Nint) 
!
!	Get Strain Displacement Matrix: B(3,nStif)
!
	Call LL_StrainDispMat(Qc,Ri,Si,B,Det,Nel,NelType,Iout,nOrder,
     &							nSize,nStif)
!
!	Add to stiffness matrix
!
	Wt = Ak(lr,Nint)*Ak(ls,Nint)*Det*TH
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
	write(*,1000) nStif,nStif
	do 110 i = 1,nStif
	write(*,1010) (Stif(i,j),j = 1,nStif)
  110	continue
	Pause
	return
!
 1000 format("Full Stiffness Matrix:Stif(",I5,",",I5,")")
 1010 format(((8f10.6,1X))/)
	return
	end   		