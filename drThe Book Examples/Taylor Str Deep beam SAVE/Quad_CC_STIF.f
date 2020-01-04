	Subroutine Quad_CC_STIF(Qc,Nel,NelType,Nint,E,PR,Thk,Stif,nStif,
     &	Iout,Trace)
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
	Real(kind=8)	Qc     ,E,PR,Thk
	Dimension		Qc(2,*)
	integer			Nel,NelType,Iout,nStif
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	Stif			 ,Trace
	Dimension		Stif(nStif,nStif)
	
!--------------------------------------------------
!	Rk(6,6)		= Gauss-Legendre Nodes		Upto 6 Points
!	Ak(6,6)		= Gauss-Legendre Weights	Upto 6 Points
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
!	0.00000000000000000000  ->0.500000000000000  	n=1
!	0.57735026918962576451  ->0.788675134594813		n=2
!    -.57735026918962576451  ->0.211324865405187
!	0.77459666924148337704  ->0.887298334620742		n=3
!    -.77459666924148337704  ->0.112701665379258
!    -.33998104358485626480  ->0.330009478207572		n=4
!	0.33998104358485626480  ->0.669990521792428		
!    -.86113631159405257523  ->0.069431844202974
!	0.86113631159405257523  ->0.930568155797026
!    0.00000000000000000000  ->0.500000000000000		n=5	
!    -.53846931010568309104  ->0.230765344947158			
!    0.53846931010568309104  ->0.769234655052841			
!    -.90617984593866399280  ->0.046910077030668			
!    0.90617984593866399280  ->0.953089922969332			
!    0.93246951420315202781  ->0.966234757101576 		n=6	
!    -.93246951420315202781  ->0.033765242898424               			
!    0.66120938646626451366  ->0.830604693233132               			
!    -.66120938646626451366  ->0.169395306766868               			
!    0.23861918608319690863  ->0.619309593041598               			
!    -.23861918608319690863  ->0.380690406958402               			
! 



   
!	Ak:
!     2.0					   ->1.0					n=1
!     1.0					   ->0.5					n=2
!     5/9					   ->0.277777777777777		n=3
!     8/9					   ->0.444444444444444
!	0.65214515486254614263  ->0.326072577431273		n=4
!	0.34785484513745385737  ->0.173927422568727
!	0.56888888888888888889  ->0.284444444444444 		n=5
!	0.47862867049936646804  ->0.239314335249683		 
!	0.23692688505618908751  ->0.118463442528095 
!	0.17132449237917034504  ->0.085662246189585		n=6
!	0.36076157304813860757  ->0.180380786524069	 
!	0.46791393457269104739  ->0.233956967286346		 
!-------------------------------------------------- 
	Real(kind=8) AM,BM,CM,TH,Ri,Si,Wt,sum
	Real(kind=8) Rk     ,Ak     ,D     ,B      ,Add    ,DB    
	Dimension    Rk(6,6),Ak(6,6),D(3,3),B(3,32),Add(32),DB(4)
	DATA Rk/	0.5D0,				 0.0D0,						! 1-point		
     &            0.0D0,				 0.0D0,	
     &            0.0D0,				 0.0D0,	
     &			0.211324865405187D0, 0.788675134594813D0,		! 2-point
     &			0.0D0,				 0.0D0,
     &			0.0D0,				 0.0D0,
     &			0.112701665379258D0, 0.5D0,						! 3-point
     &			0.887298334620742D0, 0.0D0,
     &			0.0D0,				 0.0D0,
     &			0.069431844202974D0, 0.330009478207572D0,		! 4-point
     &			0.669990521792428D0, 0.930568155797026D0,	
     &			0.D0,				 0.0D0,
     &			0.0D0,               0.230765344947158D0,		! 5-point
     &			0.769234655052841D0, 0.046910077030668D0,	
     &			0.953089922969332D0, 0.0D0,
     &			0.966234757101576D0, 0.033765242898424D0,		! 6-point
     &			0.830604693233132D0, 0.169395306766868D0,	
     &			0.619309593041598D0, 0.380690406958402D0
     &       /
!     		 
	DATA Ak/	2.0D0,				 0.0D0,						! 1-point		
     &            0.0D0,				 0.0D0,	
     &            0.0D0,				 0.0D0,	
     &			0.5D0,               0.5D0,						! 2-point
     &			0.0D0,				 0.0D0,
     &            0.0D0,				 0.0D0,	
     &			0.277777777777778D0, 0.444444444444444D0,		! 3-point
     &			0.277777777777778D0, 0.0D0,
     &            0.0D0,				 0.0D0,	
     &			0.173927422568727D0, 0.326072577431273D0,		! 4-point
     &			0.326072577431273D0, 0.173927422568727D0,
     &			0.0D0,				 0.0D0,
     &            0.284444444444444D0, 0.239314335249683D0,		! 5-point	
     &			0.239314335249683D0, 0.118463442528095D0,		
     &            0.118463442528095D0, 0.0D0,	
     &			0.085662246189585D0, 0.085662246189585D0,		! 6-point
     &			0.180380786524069D0, 0.180380786524069D0,
     &            0.233956967286346D0, 0.233956967286346D0	
     &       /
!	//////////////////////
	if(nStif.NE.32) Then
		stop 'nStif !=32'
	end if
!	//////////////////////
!
!	Stress-Strain Law
!
	if(NelType == 0)	Then					! Plain Stress
		AM = E
		BM = PR
		CM = AM/(1-BM*BM)
		TH = Thk			! thickness
	else if(NelType == 1) Then				! Plain Strain
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
!	Get Strain Displacement Matrix: B(3,32)
!
	Call CC_StrainDispMat(Qc,Ri,Si,B,Det,Nel,NelType,Iout)
!
!	Add to stiffness matrix
!
	Wt = Ak(lr,Nint)*Ak(ls,Nint)*Det*TH
	do 50 j = 1,32
	do 20 k = 1,3		! 3 will be 4 if axisymmtric included
	DB(k) = 0.0
	do 20 l = 1,3		! 3 will be 4 if axisymmtric included
	DB(k) = DB(k) + D(k,l)*B(l,j)
   20 continue
	do 40 i = j,32
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
	do 70 j = 1,32
	do 70 i = j,32
  	Stif(j,i) = Stif(i,j)
   70 continue
!
!	Get Trace
!
	Trace = 0.D0
	do 80 i = 1,32
	Trace = Trace + Stif(i,i)
   80 continue			
!
!	Check each col. vector for Null
!
	Add = 0.D0
	do 100 j = 1,nStif
	sum = 0.0 
	do  90 i = 1,nStif	
	sum = sum + Stif(i,j)
   90 continue
	Add(j) = sum
  100 continue			
!
!	done
!
	iPrt = 1
	if(iPrt == 1) then
		write(iOut,1010) (j,Add(j),j = 1,nStif)
	endif
!
	return
!
 1010 format("Column Sums of Full Stiffness Matrix"/
     &         4(I5,2x,F15.10,5x) )
	return
	end   		
			